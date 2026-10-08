#include <stdio.h>
#include <uv.h>

static uv_fs_event_t watcher;
static uv_timer_t timer;
static const char* watched_path;
static int error_count;

static void on_event(uv_fs_event_t* handle, const char* filename, int events, int status) {
  if (status < 0) {
    printf("ERROR  %s: %s (%d) %s\n", watched_path, uv_err_name(status), status, uv_strerror(status));
    error_count++;
    return;
  }
  printf("EVENT  %s: %s events=%d\n", watched_path, filename ? filename : "(null)", events);
}

static void on_timeout(uv_timer_t* handle) {
  uv_fs_event_stop(&watcher);
  uv_close((uv_handle_t*) &watcher, NULL);
  uv_close((uv_handle_t*) handle, NULL);
}

int main(int argc, char** argv) {
  uv_loop_t* loop = uv_default_loop();
  int result;

  if (argc < 2) {
    fprintf(stderr, "usage: watch <directory>\n");
    return 2;
  }
  watched_path = argv[1];

  uv_fs_event_init(loop, &watcher);
  result = uv_fs_event_start(&watcher, on_event, watched_path, 0);
  if (result < 0) {
    printf("START FAILED  %s: %s (%d)\n", watched_path, uv_err_name(result), result);
    return 1;
  }

  uv_timer_init(loop, &timer);
  uv_timer_start(&timer, on_timeout, 2000, 0);
  uv_run(loop, UV_RUN_DEFAULT);

  if (error_count == 0)
    printf("OK     %s: no error after 2s\n", watched_path);
  return error_count ? 1 : 0;
}
