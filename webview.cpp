#include <QtWidgets>

#include "webview.h"

WebView::WebView(QWidget* parent) : QWidget(parent) { setupUi(this); }
void WebView::setUrl(const QUrl& url) { this->webView->setUrl(url); }
