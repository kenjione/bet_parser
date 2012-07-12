/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QVBoxLayout *verticalLayout;
    QWebView *webView;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *elementLabel;
    QLineEdit *elementLineEdit;
    QPushButton *highlightButton;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(640, 480);
        verticalLayout = new QVBoxLayout(Window);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        webView = new QWebView(Window);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("http://www.webkit.org/")));

        verticalLayout->addWidget(webView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        elementLabel = new QLabel(Window);
        elementLabel->setObjectName(QString::fromUtf8("elementLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, elementLabel);

        elementLineEdit = new QLineEdit(Window);
        elementLineEdit->setObjectName(QString::fromUtf8("elementLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, elementLineEdit);


        horizontalLayout->addLayout(formLayout);

        highlightButton = new QPushButton(Window);
        highlightButton->setObjectName(QString::fromUtf8("highlightButton"));

        horizontalLayout->addWidget(highlightButton);


        verticalLayout->addLayout(horizontalLayout);

#ifndef QT_NO_SHORTCUT
        elementLabel->setBuddy(elementLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Window);

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "Web Element Selector", 0, QApplication::UnicodeUTF8));
        elementLabel->setText(QApplication::translate("Window", "&Element:", 0, QApplication::UnicodeUTF8));
        elementLineEdit->setText(QApplication::translate("Window", "div.BetMoreWindow", 0, QApplication::UnicodeUTF8));
        highlightButton->setText(QApplication::translate("Window", "&Highlight", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
