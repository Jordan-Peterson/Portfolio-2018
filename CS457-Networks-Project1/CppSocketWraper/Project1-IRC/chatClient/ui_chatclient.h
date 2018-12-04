/********************************************************************************
** Form generated from reading UI file 'chatclient.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCLIENT_H
#define UI_CHATCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatClient
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatClient)
    {
        if (ChatClient->objectName().isEmpty())
            ChatClient->setObjectName(QStringLiteral("ChatClient"));
        ChatClient->resize(413, 327);
        centralWidget = new QWidget(ChatClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(0, 260, 331, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 260, 80, 22));
        pushButton->setAutoRepeat(false);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 411, 261));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 259));
        plainTextEdit = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 411, 261));
        plainTextEdit->setReadOnly(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        ChatClient->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ChatClient);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 413, 19));
        ChatClient->setMenuBar(menuBar);
        statusBar = new QStatusBar(ChatClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatClient->setStatusBar(statusBar);

        retranslateUi(ChatClient);

        QMetaObject::connectSlotsByName(ChatClient);
    } // setupUi

    void retranslateUi(QMainWindow *ChatClient)
    {
        ChatClient->setWindowTitle(QApplication::translate("ChatClient", "ChatClient", 0));
        lineEdit->setText(QString());
        pushButton->setText(QApplication::translate("ChatClient", "Send", 0));
        plainTextEdit->setPlaceholderText(QApplication::translate("ChatClient", "Waiting for Server Response...", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatClient: public Ui_ChatClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
