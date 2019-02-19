#ifndef WEBVIEW_H
#define WEBVIEW_H
#include <ui_webview.h>

#include <QUrl>

namespace Ui {
  class WebView;
}

class WebView : public QWidget, public Ui::Form {
  Q_OBJECT

 public:
  explicit WebView(QWidget* parent = nullptr);

  void setUrl(const QUrl& url);
};

#endif  // WEBVIEW_H
