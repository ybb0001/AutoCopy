#include "AutoCopy.h"
#include "ui_AutoCopy.h"
//#include <Windows.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <io.h>
#include <afx.h>
#include <QIcon>
#include <fstream>
#include <qdatetime.h>

using namespace std;

bool start = true;
int mode = 1;
string skip_Words[5];
string src, dst, setting;
LPCWSTR Lsetting;

AutoCopy::AutoCopy(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);

	on_pushButton_Minimize_clicked();

}

AutoCopy:: ~AutoCopy()
{
	delete ui;
}

vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名
	_finddata_t file;
	long lf;
	//输入文件夹路径
	if ((lf = _findfirst(cate_dir.c_str(), &file)) == -1) {
		cout << cate_dir << " not found!!!" << endl;
	}
	else {
		while (_findnext(lf, &file) == 0) {
			//输出文件名
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);

	//排序，按从小到大排序
	sort(files.begin(), files.end());
	return files;
}


void get_Setting() {

	int mode = GetPrivateProfileInt(_T("Copy_Setting"), TEXT("mode"), 0, CA2CT(setting.c_str()));

	TCHAR lpTexts[13];
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_1"), TEXT(""), lpTexts, 12, CA2CT(setting.c_str()));
	skip_Words[0] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_2"), TEXT(""), lpTexts, 12, CA2CT(setting.c_str()));
	skip_Words[1] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_3"), TEXT(""), lpTexts, 12, CA2CT(setting.c_str()));
	skip_Words[2] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_4"), TEXT(""), lpTexts, 12, CA2CT(setting.c_str()));
	skip_Words[3] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_5"), TEXT(""), lpTexts, 12, CA2CT(setting.c_str()));
	skip_Words[4] = CT2A(lpTexts);

}


bool File_Name_Compare( string file) {

	for (int k = 0; k < 5; k++) {

		if (skip_Words[k].length()>2) {

			for (int i = 0; i < file.length(); i++) {

				if (file[i] == skip_Words[k][0]) {

					int e = 0;
					while (e < skip_Words[k].length() && file[i + e] == skip_Words[k][e]) {
						e++;

					}
					if (e == skip_Words[k].length())
						return true;		

				}

			}

		}

	}
	return false;
}




DWORD WINAPI myThread(LPVOID argv) {

	char buff[10];
	ZeroMemory(buff, sizeof(buff));
	memcpy(buff, argv, 10);

	while (start) {

		QTime ct = QTime::currentTime();
		if (ct.hour > 7 && ct.hour > 8) {

			get_Setting();
			vector<string> files = getFiles(src + "*");

			vector<string> ::iterator iVector = files.begin();
			while (iVector != files.end())
			{
				string s = src + *iVector;
				string d = dst + *iVector;

				if (mode == 2 || !File_Name_Compare(*iVector))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), true);

				++iVector;
			}
		}

		Sleep(30000);
		if (mode == 9)
			start = false;
	}

	return NULL;
}


void AutoCopy::on_pushButton_Start_clicked() {

	start = true;
	string s = "1";
	HANDLE myHandle = CreateThread(NULL, 0, myThread, (LPVOID)s.c_str(), 0, NULL);

}


void AutoCopy::on_pushButton_Stop_clicked() {

	start = false;

}



void AutoCopy::on_pushButton_Minimize_clicked() {

	//隐藏程序主窗口
	this->hide();
	//新建QSystemTrayIcon对象
	mSysTrayIcon = new QSystemTrayIcon(this);
	//新建托盘要显示的icon
	QIcon icon = QIcon("icon.png");
	//将icon设到QSystemTrayIcon对象中
	mSysTrayIcon->setIcon(icon);
	//当鼠标移动到托盘上的图标时，会显示此处设置的内容
	mSysTrayIcon->setToolTip(QObject::trUtf8("Sensor2005 Data AutoUpdate"));

	//给QSystemTrayIcon添加槽函数
	connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

	//建立托盘操作的菜单
	createActions();
	createMenu();
	//在系统托盘显示此对象
	mSysTrayIcon->show();

	src = ui->from->document()->toPlainText().toLocal8Bit().toStdString();
	dst = ui->to->document()->toPlainText().toLocal8Bit().toStdString();
	src += "\\";
	dst += "\\";
	setting = dst + "copy_set.int";
//	Lsetting = CA2CT(setting.c_str());

	on_pushButton_Start_clicked();

	//while (start) {

	//	get_Setting();
	//	vector<string> files = getFiles(src+"*");

	//	vector<string> ::iterator iVector = files.begin();
	//	while (iVector != files.end())
	//	{
	//		string s = src + *iVector;
	//		string d = dst + *iVector;

	//		if(mode==2|| !File_Name_Compare(*iVector))
	//			CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()),true);
	//	
	//		++iVector;
	//	}


	//	Sleep(30000);
	//	if(mode==9)
	//		start = false;
	//}

}


void AutoCopy::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
	/*	mSysTrayIcon->showMessage(QObject::trUtf8("Message Title"),
			QObject::trUtf8("D0n't Close!!!"),
			QSystemTrayIcon::Information,1000);
		break;
	case QSystemTrayIcon::DoubleClick:*/
		this->show();
		mSysTrayIcon->hide();
		break;
	default:
		break;
	}
}

void AutoCopy::createActions()
{
	mShowMainAction = new QAction(QObject::trUtf8("显示主界面"), this);
	connect(mShowMainAction, SIGNAL(triggered()), this, SLOT(on_showMainAction()));

	mExitAppAction = new QAction(QObject::trUtf8("退出"), this);
	connect(mExitAppAction, SIGNAL(triggered()), this, SLOT(on_exitAppAction()));

}

void AutoCopy::createMenu()
{
	mMenu = new QMenu(this);
	mMenu->addAction(mShowMainAction);

	mMenu->addSeparator();

	mMenu->addAction(mExitAppAction);

	mSysTrayIcon->setContextMenu(mMenu);
}

void AutoCopy::on_showMainAction()
{
	this->show();
}

void AutoCopy::on_exitAppAction()
{
	exit(0);
}



