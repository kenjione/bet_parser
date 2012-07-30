#ifndef WINDOW_H
#define WINDOW_H

#include <QUrl>
#include <QWidget>
//! [Window class definition]
#include "ui_window.h"

#include <QNetworkAccessManager>
#include <QNetworkCookieJar>


class Window : public QWidget, private Ui::Window
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    void setUrl(const QUrl &url);

private:
    void parsePage(QWebView *webview);
    void showBetInfo();

    void printTicket();
public slots:
    void on_elementLineEdit_returnPressed();
    void on_highlightButton_clicked();
    void finishLoading(bool);

private slots:
    void on_pushButton_clicked();
};
//! [Window class definition]

#endif
