#include "filewatcher/linuxfilewatcher.h"

#ifdef __linux__
#include <fcntl.h>
#include <sys/inotify.h>
#include <unistd.h>

const unsigned BUF_LEN = 10 * (sizeof(struct inotify_event) + NAME_MAX + 1);

LinuxFileWatcher::LinuxFileWatcher(const fs::path& p) : FileWatcher(p) {}

void LinuxFileWatcher::watch() {
  char buf[BUF_LEN];
  struct inotify_event* event;
  fd = inotify_init();

  if (fd < 0) { return; }

  wd = inotify_add_watch(fd, getPath().c_str(), IN_CLOSE_WRITE);

  if (wd < 0) { return; }
  while (true) {
    if (read(fd, buf, BUF_LEN) > 0) {
      event = (inotify_event*) buf;
      if (event->mask & IN_CLOSE_WRITE) notify();
    }
  }
}

#endif
