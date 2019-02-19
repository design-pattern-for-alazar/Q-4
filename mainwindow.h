#include <QMainWindow>

#include "webview.h"

#include "document.h"
#include "documentfactory.h"
#include "filewatcher.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();
  ~MainWindow();

 private:
  void openDocument(QString filepath);
 private slots:
  void open();
  void about();
  void update();

 private:
  WebView* viewer;
  QMenu* fileMenu;
  QMenu* helpMenu;
  QAction* openAct;
  QAction* exitAct;
  QAction* aboutAct;
  QAction* aboutQtAct;

  Document* document;
  DocumentFactory* factory;
  FileWatcher* watcher;

  bool documentLoaded;

  void createActions();
  void createMenus();
};
