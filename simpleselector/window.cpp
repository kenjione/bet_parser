#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include "window.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QtSql>
#include <QNetworkAccessManager>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QNetworkCookieJar>
#include <QPrintPreviewDialog>

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

void Window::on_elementLineEdit_returnPressed() // парсинг, баркод, хтмл, печать
{
    parsePage(webView);
    qDebug() << system("cd .. && ruby main_local.rb barcode");
    // хтмл
    // печать
}

void Window::on_highlightButton_clicked()
{
    printTicket();
    //on_elementLineEdit_returnPressed();
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

        /* РїР°СЂСЃРёРЅРі РёР·РЅСѓС‚СЂРё

        QWebElementCollection frames = webView->page()->mainFrame()->findAllElements("div.BetMoreWindow");
        foreach (QWebElement paraElement, frames) {
            qDebug() << paraElement.toOuterXml() << "\n ---- \n";
        }

        */


    } file.close();
}

void Window::showBetInfo()
{
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

}

void Window::printTicket() {
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    QPrintPreviewDialog *prevDig = new QPrintPreviewDialog(&printer);

    connect(prevDig, SIGNAL(paintRequested(QPrinter*)), webView, SLOT(print(QPrinter*)));

    prevDig->exec();

//    if (printDialog.exec())
//    {
//        QTextDocument textDoc;
//        textDoc.setHtml("../ticket.html");
//    }
}

void Window::finishLoading(bool){
    parsePage(webView_2);
    qDebug() << system("cd .. && ruby main_local.rb");
    showBetInfo();
}


void Window::on_pushButton_clicked() // парсинг, бд, удаление из бд
{
    // РїСЂРѕРІРµСЂРєР°

    webView_2->page()->setNetworkAccessManager(webView->page()->networkAccessManager());
    webView_2->setUrl(QUrl("http://www.forexsport.ru/mybets"));

    connect(webView_2, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
    // удаление из бд
}
