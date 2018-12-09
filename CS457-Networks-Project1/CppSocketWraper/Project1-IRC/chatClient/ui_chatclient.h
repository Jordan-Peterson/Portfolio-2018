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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
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
    QLineEdit *sendEdit;
    QPushButton *sendButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *chatText;
    QLabel *channelLabel;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QListWidget *channelList;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QPlainTextEdit *serverNoticeText;
    QLabel *userInformationLabel;
    QLabel *nicknameLabel;
    QLabel *fullnameLabel;
    QLabel *hostLabel;
    QLabel *serverNoticeLabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatClient)
    {
        if (ChatClient->objectName().isEmpty())
            ChatClient->setObjectName(QStringLiteral("ChatClient"));
        ChatClient->resize(845, 449);
        ChatClient->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(ChatClient);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendEdit = new QLineEdit(centralWidget);
        sendEdit->setObjectName(QStringLiteral("sendEdit"));
        sendEdit->setGeometry(QRect(430, 390, 311, 31));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(750, 390, 91, 31));
        sendButton->setAutoRepeat(false);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(430, 10, 411, 371));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 409, 369));
        chatText = new QPlainTextEdit(scrollAreaWidgetContents);
        chatText->setObjectName(QStringLiteral("chatText"));
        chatText->setGeometry(QRect(0, 0, 411, 371));
        chatText->setReadOnly(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        channelLabel = new QLabel(centralWidget);
        channelLabel->setObjectName(QStringLiteral("channelLabel"));
        channelLabel->setGeometry(QRect(220, 20, 151, 16));
        QFont font;
        font.setUnderline(true);
        channelLabel->setFont(font);
        channelLabel->setAutoFillBackground(true);
        channelLabel->setAlignment(Qt::AlignCenter);
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(180, 50, 241, 251));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 239, 249));
        channelList = new QListWidget(scrollAreaWidgetContents_2);
        channelList->setObjectName(QStringLiteral("channelList"));
        channelList->setGeometry(QRect(0, 0, 241, 251));
        channelList->setMouseTracking(true);
        channelList->setAutoFillBackground(false);
        channelList->setSortingEnabled(true);
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        scrollArea_3 = new QScrollArea(centralWidget);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(10, 310, 411, 111));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 409, 109));
        serverNoticeText = new QPlainTextEdit(scrollAreaWidgetContents_3);
        serverNoticeText->setObjectName(QStringLiteral("serverNoticeText"));
        serverNoticeText->setGeometry(QRect(0, 0, 411, 111));
        serverNoticeText->setAutoFillBackground(true);
        serverNoticeText->setUndoRedoEnabled(false);
        serverNoticeText->setTextInteractionFlags(Qt::NoTextInteraction);
        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        userInformationLabel = new QLabel(centralWidget);
        userInformationLabel->setObjectName(QStringLiteral("userInformationLabel"));
        userInformationLabel->setGeometry(QRect(20, 20, 121, 16));
        userInformationLabel->setFont(font);
        userInformationLabel->setAutoFillBackground(true);
        nicknameLabel = new QLabel(centralWidget);
        nicknameLabel->setObjectName(QStringLiteral("nicknameLabel"));
        nicknameLabel->setGeometry(QRect(10, 70, 131, 51));
        nicknameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        nicknameLabel->setWordWrap(true);
        fullnameLabel = new QLabel(centralWidget);
        fullnameLabel->setObjectName(QStringLiteral("fullnameLabel"));
        fullnameLabel->setGeometry(QRect(10, 130, 161, 41));
        fullnameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        fullnameLabel->setWordWrap(true);
        hostLabel = new QLabel(centralWidget);
        hostLabel->setObjectName(QStringLiteral("hostLabel"));
        hostLabel->setGeometry(QRect(10, 200, 161, 41));
        hostLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        hostLabel->setWordWrap(true);
        serverNoticeLabel = new QLabel(centralWidget);
        serverNoticeLabel->setObjectName(QStringLiteral("serverNoticeLabel"));
        serverNoticeLabel->setGeometry(QRect(20, 280, 121, 21));
        serverNoticeLabel->setFont(font);
        ChatClient->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChatClient);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChatClient->setStatusBar(statusBar);

        retranslateUi(ChatClient);

        QMetaObject::connectSlotsByName(ChatClient);
    } // setupUi

    void retranslateUi(QMainWindow *ChatClient)
    {
        ChatClient->setWindowTitle(QApplication::translate("ChatClient", "JP-IRC", 0));
        sendEdit->setText(QString());
        sendEdit->setPlaceholderText(QApplication::translate("ChatClient", "Type Messages and Commands here...", 0));
        sendButton->setText(QApplication::translate("ChatClient", "Send", 0));
        chatText->setPlaceholderText(QApplication::translate("ChatClient", "Waiting for messages...", 0));
        channelLabel->setText(QApplication::translate("ChatClient", "CHANNELS", 0));
        serverNoticeText->setPlaceholderText(QApplication::translate("ChatClient", "Waiting for server notices...", 0));
        userInformationLabel->setText(QApplication::translate("ChatClient", "USER INFORMATION", 0));
        nicknameLabel->setText(QApplication::translate("ChatClient", "NICKNAME:", 0));
        fullnameLabel->setText(QApplication::translate("ChatClient", "FULL NAME:", 0));
        hostLabel->setText(QApplication::translate("ChatClient", "HOST ADDRESS:", 0));
        serverNoticeLabel->setText(QApplication::translate("ChatClient", "SERVER NOTICES", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatClient: public Ui_ChatClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
