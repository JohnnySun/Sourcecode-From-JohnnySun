/********************************************************************************
** Form generated from reading UI file 'denmainwindow.ui'
**
** Created: Sun Aug 3 00:27:37 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DENMAINWINDOW_H
#define UI_DENMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DenMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *conn_button;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DenMainWindow)
    {
        if (DenMainWindow->objectName().isEmpty())
            DenMainWindow->setObjectName(QString::fromUtf8("DenMainWindow"));
        DenMainWindow->resize(400, 300);
        centralWidget = new QWidget(DenMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        conn_button = new QPushButton(centralWidget);
        conn_button->setObjectName(QString::fromUtf8("conn_button"));
        conn_button->setCheckable(true);
        conn_button->setChecked(false);

        gridLayout->addWidget(conn_button, 1, 0, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 2);

        DenMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DenMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 28));
        DenMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DenMainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DenMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DenMainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DenMainWindow->setStatusBar(statusBar);

        retranslateUi(DenMainWindow);

        QMetaObject::connectSlotsByName(DenMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DenMainWindow)
    {
        DenMainWindow->setWindowTitle(QApplication::translate("DenMainWindow", "DenMainWindow", 0, QApplication::UnicodeUTF8));
        conn_button->setText(QApplication::translate("DenMainWindow", "&Connect To Node(Debug)", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DenMainWindow", "&Readline", 0, QApplication::UnicodeUTF8));
        mainToolBar->setWindowTitle(QApplication::translate("DenMainWindow", "Den Project", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DenMainWindow: public Ui_DenMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DENMAINWINDOW_H
