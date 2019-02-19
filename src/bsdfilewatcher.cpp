#include "filewatcher/bsdfilewatcher.h"

#if defined(__APPLE_CC__) || defined(BSD)

#include <fcntl.h>
#include <stdio.h>
#include <sys/event.h>
#include <sys/stat.h>
#include <unistd.h>

void BSDFileWatcher::watch() {
  int kq, f, nev;
  struct kevent change;
  struct kevent event;

  if ((kq = kqueue()) < 0) {
    fprintf(stderr, "Can't initalize kqueue\n");
    return;
  }

  if ((f = open(file_path.c_str(), O_RDONLY)) < 0) {
    fprint(stderr, "Can't open file\n");
    return;
  }
  EV_SET(
      &change, f, EVFILT_VNODE,  // use f as identifier to event watch
      EV_ADD | EV_ENABLE,        // add this event and enable notification
      NOTE_CLOSE_WRITE,  // notify when the file is opened for write and closed
      0, 0);
  while (true) {
    nev = kevent(kq, &change, 1, &event, 1, NULL);

    if (nev > 0) {
      if (event.fflags & NOTE_CLOSE_WRITE) { this->notify(); }
    }
  }
}

#endif
