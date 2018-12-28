#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_AutoCopy.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
//#include "mythread.h" 

class AutoCopy : public QMainWindow
{
	Q_OBJECT

public:
	explicit AutoCopy(QWidget *parent = Q_NULLPTR);
	~AutoCopy();


public:
	QSystemTrayIcon *mSysTrayIcon;
	QMenu *mMenu;
	QAction *mShowMainAction;
	QAction *mExitAppAction;

public:
	void createActions();
	void createMenu();
	

private slots:
	void on_pushButton_Minimize_clicked();
	void on_pushButton_Start_clicked();
	void on_pushButton_Stop_clicked();

	void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void on_showMainAction();
	void on_exitAppAction();


private:
	Ui::AutoCopyClass *ui;

};
