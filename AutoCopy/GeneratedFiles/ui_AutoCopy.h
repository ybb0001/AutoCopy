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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mQWidget
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Minimize;
    QTextEdit *from;
    QTextEdit *to;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Manual;
    QPushButton *pushButton_Save;
    QLabel *label_3;
    QTextEdit *hour;
    QTextEdit *minute;
    QLabel *label_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QWidget *mQWidget)
    {
        if (mQWidget->objectName().isEmpty())
            mQWidget->setObjectName(QStringLiteral("mQWidget"));
        mQWidget->resize(600, 200);
        mQWidget->setMinimumSize(QSize(600, 200));
        mQWidget->setMaximumSize(QSize(600, 200));
        mQWidget->setProperty("iconSize", QVariant(QSize(24, 24)));
        mQWidget->setProperty("animated", QVariant(true));
        centralWidget = new QWidget(mQWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 600, 200));
        centralWidget->setMinimumSize(QSize(600, 200));
        centralWidget->setMaximumSize(QSize(600, 200));
        pushButton_Minimize = new QPushButton(centralWidget);
        pushButton_Minimize->setObjectName(QStringLiteral("pushButton_Minimize"));
        pushButton_Minimize->setGeometry(QRect(510, 20, 75, 41));
        from = new QTextEdit(centralWidget);
        from->setObjectName(QStringLiteral("from"));
        from->setGeometry(QRect(10, 20, 480, 60));
        to = new QTextEdit(centralWidget);
        to->setObjectName(QStringLiteral("to"));
        to->setGeometry(QRect(10, 120, 480, 60));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 5, 71, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 61, 16));
        pushButton_Start = new QPushButton(centralWidget);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(510, 80, 75, 30));
        pushButton_Manual = new QPushButton(centralWidget);
        pushButton_Manual->setObjectName(QStringLiteral("pushButton_Manual"));
        pushButton_Manual->setGeometry(QRect(510, 130, 75, 40));
        pushButton_Save = new QPushButton(centralWidget);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));
        pushButton_Save->setGeometry(QRect(390, 90, 75, 25));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(137, 95, 121, 16));
        hour = new QTextEdit(centralWidget);
        hour->setObjectName(QStringLiteral("hour"));
        hour->setGeometry(QRect(247, 90, 31, 25));
        minute = new QTextEdit(centralWidget);
        minute->setObjectName(QStringLiteral("minute"));
        minute->setGeometry(QRect(287, 90, 31, 25));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(280, 95, 16, 16));
        mainToolBar = new QToolBar(mQWidget);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setGeometry(QRect(0, 0, 4, 12));
        statusBar = new QStatusBar(mQWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 0, 3, 18));

        retranslateUi(mQWidget);

        QMetaObject::connectSlotsByName(mQWidget);
    } // setupUi

    void retranslateUi(QWidget *mQWidget)
    {
        mQWidget->setWindowTitle(QApplication::translate("mQWidget", "AutoCopy_20180101", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_Minimize->setToolTip(QApplication::translate("mQWidget", "<html><head/><body><p>MiniMize Window</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_Minimize->setText(QApplication::translate("mQWidget", "Minimize\n"
"to Tray", Q_NULLPTR));
        from->setHtml(QApplication::translate("mQWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        to->setHtml(QApplication::translate("mQWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("mQWidget", "From Path:", Q_NULLPTR));
        label_2->setText(QApplication::translate("mQWidget", "To Path:", Q_NULLPTR));
        pushButton_Start->setText(QApplication::translate("mQWidget", "Stop", Q_NULLPTR));
        pushButton_Manual->setText(QApplication::translate("mQWidget", "Manual\n"
"Upload", Q_NULLPTR));
        pushButton_Save->setText(QApplication::translate("mQWidget", "Save", Q_NULLPTR));
        label_3->setText(QApplication::translate("mQWidget", "Auto Updata Time:", Q_NULLPTR));
        hour->setHtml(QApplication::translate("mQWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">7</p></body></html>", Q_NULLPTR));
        minute->setHtml(QApplication::translate("mQWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">30</p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("mQWidget", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">:</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mQWidget: public Ui_mQWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOCOPY_H
