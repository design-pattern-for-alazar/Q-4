#ifndef DOCUMENTSTAB_H
#define DOCUMENTSTAB_H

#include <QObject>

class DocumentStab : public QObject {
  Q_OBJECT
 public:
  explicit DocumentStab(QObject* parent = nullptr);

 signals:
  void updateHTML();
 public slots:
  void update();
};

#endif  // DOCUMENTSTAB_H
