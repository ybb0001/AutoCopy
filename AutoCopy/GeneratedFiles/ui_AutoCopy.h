/********************************************************************************
** Form generated from reading UI file 'AutoCopy.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOCOPY_H
#define UI_AUTOCOPY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoCopyClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Minimize;
    QTextEdit *from;
    QTextEdit *to;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Stop;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *AutoCopyClass)
    {
        if (AutoCopyClass->objectName().isEmpty())
            AutoCopyClass->setObjectName(QStringLiteral("AutoCopyClass"));
        AutoCopyClass->resize(600, 270);
        AutoCopyClass->setAnimated(true);
        centralWidget = new QWidget(AutoCopyClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Minimize = new QPushButton(centralWidget);
        pushButton_Minimize->setObjectName(QStringLiteral("pushButton_Minimize"));
        pushButton_Minimize->setGeometry(QRect(510, 20, 75, 41));
        from = new QTextEdit(centralWidget);
        from->setObjectName(QStringLiteral("from"));
        from->setGeometry(QRect(10, 20, 480, 80));
        to = new QTextEdit(centralWidget);
        to->setObjectName(QStringLiteral("to"));
        to->setGeometry(QRect(10, 130, 480, 80));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 110, 54, 12));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(510, 80, 75, 23));
        pushButton_Stop = new QPushButton(centralWidget);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setGeometry(QRect(510, 120, 75, 23));
        AutoCopyClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(AutoCopyClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AutoCopyClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AutoCopyClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AutoCopyClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(AutoCopyClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        AutoCopyClass->setMenuBar(menuBar);

        retranslateUi(AutoCopyClass);

        QMetaObject::connectSlotsByName(AutoCopyClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoCopyClass)
    {
        AutoCopyClass->setWindowTitle(QApplication::translate("AutoCopyClass", "AutoCopy", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_Minimize->setToolTip(QApplication::translate("AutoCopyClass", "<html><head/><body><p>MiniMize Window</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_Minimize->setText(QApplication::translate("AutoCopyClass", "Minimize\n"
"to Tray", Q_NULLPTR));
        from->setHtml(QApplication::translate("AutoCopyClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">G:\\\345\267\245\345\205\267\\SEMICO\\797_single_12M_05_PR_[FP]_0724\\Data</p></body></html>", Q_NULLPTR));
        to->setHtml(QApplication::translate("AutoCopyClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">C:\\data</p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("AutoCopyClass", "From:", Q_NULLPTR));
        label_2->setText(QApplication::translate("AutoCopyClass", "To:", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("AutoCopyClass", "PushButton", Q_NULLPTR));
        pushButton_Stop->setText(QApplication::translate("AutoCopyClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AutoCopyClass: public Ui_AutoCopyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOCOPY_H
