#ifndef AutoCopy_H
#define AutoCopy_H

#include <QtWidgets/QWidget>
#include "ui_AutoCopy.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

namespace Ui {
	class mQWidget;
}

class AutoCopy : public QWidget
{
	Q_OBJECT

public:

	explicit AutoCopy(QWidget *parent = Q_NULLPTR);
	~AutoCopy();

public:
	QSystemTrayIcon *mSysTrayIcon = 0;
	QMenu *mMenu = NULL;;
	QAction *mShowMainAction = NULL;;
	QAction *mExitAppAction = NULL;;

public:
	void createActions();
	void createMenu();


private slots :
	void on_pushButton_Minimize_clicked();
	void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void on_showMainAction();
	void on_exitAppAction();
	void on_pushButton_Start_clicked();
	void on_pushButton_Manual_clicked();
	void on_pushButton_Save_clicked();


private:
	Ui::mQWidget *ui;
};



#endif 