#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutoCopy.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>


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
	void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void on_showMainAction();
	void on_exitAppAction();
	void on_pushButton_Start_clicked();
	void on_pushButton_Manual_clicked();
	void on_pushButton_Save_clicked();



private:
	Ui::AutoCopyClass *ui;

};
