/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include "window.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QtSql>

#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

using namespace std;

class PersistentCookieJar : public QNetworkCookieJar {
public:
    PersistentCookieJar(QObject *parent) : QNetworkCookieJar(parent) { load(); }
    ~PersistentCookieJar() { save(); }

public:
    void save()
    {
        QList<QNetworkCookie> list = allCookies();
        QByteArray data;
        foreach (QNetworkCookie cookie, list) {
            if (!cookie.isSessionCookie()) {
                data.append(cookie.toRawForm());
                data.append("\n");
            }
        }
        QSettings settings;
        settings.setValue("Cookies",data);
    }

    void load()
    {
        QSettings settings;
        QByteArray data = settings.value("Cookies").toByteArray();
        setAllCookies(QNetworkCookie::parseCookies(data));
    }
};



Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
}

void Window::on_elementLineEdit_returnPressed()
{
    parsePage(webView);
}

void Window::on_highlightButton_clicked()
{
    on_elementLineEdit_returnPressed();
}

void Window::setUrl(const QUrl &url)
{
    webView->setUrl(url);
}

void Window::parsePage(QWebView *webview)
{
    QFile file("../output.html");

//    foreach (QWebElement element, elements) {
//        element.setAttribute("style", "background-color: #f0f090");
//    }

    if (file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        QWebFrame *frame = webview->page()->mainFrame();
        QWebElement document = frame->documentElement();
        QWebElementCollection elements = document.findAll(elementLineEdit->text());

        foreach (QWebElement element, elements) {
            element.setAttribute("style", "background-color: #ffffff");
        }

        frame = webview->page()->mainFrame();
        QString html = frame->toHtml();
        QTextStream out(&file);
        out << html;

        /* парсинг изнутри

        QWebElementCollection frames = webView->page()->mainFrame()->findAllElements("div.BetMoreWindow");
        foreach (QWebElement paraElement, frames) {
            qDebug() << paraElement.toOuterXml() << "\n ---- \n";
        }

        */


    } file.close();

    qDebug() << system("cd .. && ruby main_local.rb");
}



void Window::on_pushButton_clicked()
{
    // проверка

    webView_2->page()->setNetworkAccessManager(webView->page()->networkAccessManager());
    webView_2->setUrl(QUrl("http://www.forexsport.ru/mybets"));

    sleep(2); // TODO: ожидание дозагрузки страницы

    parsePage(webView_2);

    sleep(2); // TODO: ожидание парсинга страницы

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../test.db");

    if (!sdb.open()) {
          qDebug() << sdb.lastError().text();
    }
    QString id = lineEdit->text();

    QSqlQuery bet("SELECT * FROM bets WHERE id = " + id + ";");
    while (bet.next()) {
        for (int i = 0; i < 7; i++) tableWidget->setItem(i,0,new QTableWidgetItem(bet.value(i).toString()));
    }

    //tableWidget
}
