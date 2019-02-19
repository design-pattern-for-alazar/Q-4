#ifndef FILEOBSERVER_H_
#define FILEOBSERVER_H_

class FileObserver {
 public:
  virtual void update() = 0;
  virtual ~FileObserver(){};
};

#endif
