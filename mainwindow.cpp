#include <QDir>
#include <QFileInfo>
#include <QtWebKitWidgets>
#include <QtWidgets>

#include "documentfactory.h"
#include "mainwindow.h"

MainWindow::MainWindow() {
  createActions();
  createMenus();

  viewer = new WebView(this);
  this->showMaximized();
  documentLoaded = false;
  setCentralWidget(viewer);
}

MainWindow::~MainWindow() {
  delete viewer;
  delete openAct;
  delete exitAct;
  delete aboutAct;
  delete aboutQtAct;
  if (documentLoaded) {
    delete document;
    delete factory;
    watcher->exit();
    delete watcher;
  }
}

void MainWindow::openDocument(QString fileName) {
  if (!fileName.isEmpty()) {
    factory = DocumentFactory::instance(
        QFileInfo(fileName).fileName().toUtf8().constData());

    try {
      document = factory->createDocument(fileName.toUtf8().constData());
      watcher = factory->createFileWatcher(fileName.toUtf8().constData());
      watcher->add(document);
      watcher->start();
      document->read();
      viewer->setUrl(document->convertToHTML());
      documentLoaded = true;
      openAct->setDisabled(true);

      connect(document->getStab(), SIGNAL(updateHTML()), this, SLOT(update()));

    } catch (fs::filesystem_error e) {
      QMessageBox::critical(this, "Can't Open File", e.what());
    }
  }
}

void MainWindow::createActions() {
  openAct = new QAction("&Open...", this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip("Open an existing HTML file");
  connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

  exitAct = new QAction("E&xit", this);
  exitAct->setStatusTip("Exit the application");
  exitAct->setShortcuts(QKeySequence::Quit);
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  aboutAct = new QAction("&About", this);
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAct = new QAction("About &Qt", this);
  connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}

void MainWindow::open() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(),
      "Text (*.txt *.c *.cpp *.h *.hpp *.py *.java);;"
      "MarkDown (*.md *.MD readme README Readme);;"
      "HTML (*.html *.xml *.json *.htm)"
#ifdef HAS_PDF2HTML
      ";;Pdf (*.pdf)"
#endif
#ifdef HAS_GROFF
      ";;Manpage (*.1 *.2 *.3 *.4 *.5 *.6 *.7 *.8)"
#endif
  );
  openDocument(fileName);
}

void MainWindow::about() {
  QMessageBox::about(
      this, "About mdview",
      "This application views different file formats.Including markdown.");
}

void MainWindow::update() {
  if (documentLoaded) { viewer->setUrl(document->convertToHTML()); }
}
