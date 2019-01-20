#include "AutoCopy.h"
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
bool manual = false;
int mode = 1;
int copy_hour = 0, copy_minute = 0;
string skip_Words[5] = { "" };
string src = "", dst = "", src2 = "", dst2 = "", src3 = "", dst3 = "";
string upper_src = "", upper_src2 = "", upper_src3 = "";
string setting = "", setting2 = "", setting3 = "";
LPCWSTR Lsetting = TEXT("");
HANDLE myHandle;


vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名
	_finddata_t file;
	long lf = 0;
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

void get_Setting(string s) {

	mode = GetPrivateProfileInt(_T("Copy_Setting"), TEXT("mode"), 0, CA2CT(s.c_str()));

	TCHAR lpTexts[13];
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_1"), TEXT(""), lpTexts, 12, CA2CT(s.c_str()));
	skip_Words[0] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_2"), TEXT(""), lpTexts, 12, CA2CT(s.c_str()));
	skip_Words[1] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_3"), TEXT(""), lpTexts, 12, CA2CT(s.c_str()));
	skip_Words[2] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_4"), TEXT(""), lpTexts, 12, CA2CT(s.c_str()));
	skip_Words[3] = CT2A(lpTexts);
	GetPrivateProfileString(TEXT("Copy_Setting"), TEXT("skip_filename_Words_5"), TEXT(""), lpTexts, 12, CA2CT(s.c_str()));
	skip_Words[4] = CT2A(lpTexts);

}

bool File_Name_Compare(string file) {

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


bool CopressFileCheck(string s) {

	if (s[s.size() - 1] == 'r' || s[s.size() - 1] == 'R')
		if (s[s.size() - 2] == 'a' || s[s.size() - 2] == 'A')
			if (s[s.size() - 3] == 'r' || s[s.size() - 3] == 'R')
				if (s[s.size() - 4] == '.')
					return true;

	if (s[s.size() - 1] == 'p' || s[s.size() - 1] == 'P')
		if (s[s.size() - 2] == 'i' || s[s.size() - 2] == 'I')
			if (s[s.size() - 3] == 'z' || s[s.size() - 3] == 'Z')
				if (s[s.size() - 4] == '.')
					return true;

	return false;

}


void upload() {

	string str = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString();

	get_Setting(setting);
	vector<string> files1 = getFiles(src + "*");
	vector<string> ::iterator iVector = files1.begin();

	if (mode > 0&& src.length() > 5) {
		while (iVector != files1.end())
		{
			string s = src + *iVector;
			string d = dst + *iVector;

			if ((mode & 2)>0 || !File_Name_Compare(*iVector))
				CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);

			++iVector;
		}

		WritePrivateProfileString(TEXT("Copy_Setting"), TEXT("Last_Copy_Date"), CA2CT(str.c_str()), CA2CT(setting.c_str()));

		if (upper_src.size() > 2 && (mode & 8) > 0) {
			vector<string> files11 = getFiles(upper_src + "*");
			iVector = files11.begin();
			while (iVector != files11.end())
			{
				string s = upper_src + *iVector;
				string d = dst + *iVector;

				if (CopressFileCheck(s))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);

				++iVector;
			}
		}
	}

	if (src2.length() > 5) {

		get_Setting(setting2);
		vector<string> files2 = getFiles(src2 + "*");
		iVector = files2.begin();

		if (mode > 0) {
			while (iVector != files2.end())
			{
				string s = src2 + *iVector;
				string d = dst2 + *iVector;

				if ((mode & 2)>0 || !File_Name_Compare(*iVector))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), true);

				++iVector;
			}
		}
		WritePrivateProfileString(TEXT("Copy_Setting"), TEXT("Last_Copy_Date"), CA2CT(str.c_str()), CA2CT(setting2.c_str()));
		
		if (upper_src3.size() > 2 && (mode & 8) > 0) {
			vector<string> files22 = getFiles(upper_src2 + "*");
			iVector = files22.begin();

			while (iVector != files22.end())
			{
				string s = upper_src2 + *iVector;
				string d = dst2 + *iVector;

				if (CopressFileCheck(s))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);

				++iVector;
			}
		}
	}

	if (src3.length() > 5) {

		get_Setting(setting3);
		vector<string> files3 = getFiles(src3 + "*");
		iVector = files3.begin();
		if (mode > 0) {
			while (iVector != files3.end())
			{
				string s = src3 + *iVector;
				string d = dst3 + *iVector;

				if ((mode & 2) > 0 || !File_Name_Compare(*iVector))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), true);

				++iVector;
			}
		}
		WritePrivateProfileString(TEXT("Copy_Setting"), TEXT("Last_Copy_Date"), CA2CT(str.c_str()), CA2CT(setting3.c_str()));

		if (upper_src3.size() > 2 && (mode & 8) > 0){
			vector<string> files33 = getFiles(upper_src3 + "*");
			iVector = files33.begin();

			while (iVector != files33.end())
			{
				string s = upper_src3 + *iVector;
				string d = dst3 + *iVector;

				if (CopressFileCheck(s))
					CopyFile(CA2CT(s.c_str()), CA2CT(d.c_str()), false);

				++iVector;
			}
		}
	}

}


DWORD WINAPI myThread(LPVOID argv) {

	char buff[10];
	ZeroMemory(buff, sizeof(buff));
	memcpy(buff, argv, 10);
	bool work = true;

	while (1) {
		if (start) {
			get_Setting(setting);
			QTime ct = QTime::currentTime();
			int hour_now = ct.hour();
			int minute_now = ct.minute();
			if (work && (hour_now == copy_hour && minute_now > copy_minute)) {
				upload();
				if (mode>0)
					work = false;
			}

			if ((mode & 4) > 0) {
				upload();
				WritePrivateProfileString(TEXT("Copy_Setting"), TEXT("mode"), TEXT("1"), CA2CT(setting.c_str()));
			}

			if (!work && hour_now >= copy_hour + 1) {
				work = true;
			}
		}

		Sleep(300000);
		if (mode == -1)
			start = false;
	}

	return NULL;
}

int getLastPath(string s) {

	int len = s.length()-1;
	while (len > 0 && s[len] != '\\'){
		len--;
	}
	return len+1;
}


AutoCopy::AutoCopy(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::mQWidget)
{
	int lastPath;
	ui->setupUi(this);

	TCHAR lpTexts[200];
	GetPrivateProfileString(TEXT("Path"), TEXT("from"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	src = CT2A(lpTexts);
	lastPath = getLastPath(src);
	upper_src = src.substr(0, lastPath);

	GetPrivateProfileString(TEXT("Path"), TEXT("to"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	dst = CT2A(lpTexts);

	GetPrivateProfileString(TEXT("Path"), TEXT("from2"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	src2 = CT2A(lpTexts);
	lastPath = getLastPath(src2);
	upper_src2 = src2.substr(0, lastPath);

	GetPrivateProfileString(TEXT("Path"), TEXT("to2"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	dst2 = CT2A(lpTexts);

	GetPrivateProfileString(TEXT("Path"), TEXT("from3"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	src3 = CT2A(lpTexts);
	lastPath = getLastPath(src3);
	upper_src3 = src3.substr(0, lastPath);

	GetPrivateProfileString(TEXT("Path"), TEXT("to3"), TEXT(""), lpTexts, 200, TEXT(".\\Setting\\Setting.ini"));
	dst3 = CT2A(lpTexts);


	copy_hour = GetPrivateProfileInt(_T("Time"), TEXT("hour"), 0, TEXT(".\\Setting\\Setting.ini"));
	copy_minute = GetPrivateProfileInt(_T("Time"), TEXT("minute"), 0, TEXT(".\\Setting\\Setting.ini"));

	ui->from->setText(src.c_str());
	ui->to->setText(dst.c_str());
	ui->from_2->setText(src2.c_str());
	ui->to_2->setText(dst2.c_str());
	ui->from_3->setText(src3.c_str());
	ui->to_3->setText(dst3.c_str());

	ui->hour->setText(QString::number(copy_hour, 10));
	ui->minute->setText(QString::number(copy_minute, 10));

	src += "\\";
//	upper_src += "\\";
	dst += "\\";
	src2 += "\\";
//	upper_src2 += "\\";
	dst2 += "\\";
	src3 += "\\";
//	upper_src3 += "\\";
	dst3 += "\\";


	setting = dst + "copy_set.ini";
	setting2 = dst2 + "copy_set.ini";
	setting3 = dst3 + "copy_set.ini";

	on_pushButton_Minimize_clicked();
	string s = "1";
	myHandle = CreateThread(NULL, 0, myThread, (LPVOID)s.c_str(), 0, NULL);

}


AutoCopy:: ~AutoCopy()
{
	TerminateProcess(myHandle, 4);
	delete ui;
}


void AutoCopy::on_pushButton_Start_clicked() {

	if (start) {
		start = false;
		ui->pushButton_Start->setText("Start");
	}
	else {
		start = true;
		ui->pushButton_Start->setText("Stop");

	}
}


void AutoCopy::on_pushButton_Manual_clicked() {

	upload();

}


void AutoCopy::on_pushButton_Save_clicked() {

	src = ui->from->document()->toPlainText().toLocal8Bit().toStdString();
	dst = ui->to->document()->toPlainText().toLocal8Bit().toStdString();

	string str_hour = ui->hour->document()->toPlainText().toLocal8Bit().toStdString();
	string str_minute = ui->minute->document()->toPlainText().toLocal8Bit().toStdString();

	copy_hour = ui->hour->document()->toPlainText().toInt();
	copy_minute = ui->minute->document()->toPlainText().toInt();

	WritePrivateProfileString(TEXT("Path"), TEXT("from"), CA2CT(src.c_str()), TEXT(".\\Setting\\Setting.ini"));
	WritePrivateProfileString(TEXT("Path"), TEXT("to"), CA2CT(dst.c_str()), TEXT(".\\Setting\\Setting.ini"));

	WritePrivateProfileString(TEXT("Time"), TEXT("hour"), CA2CT(str_hour.c_str()), TEXT(".\\Setting\\Setting.ini"));
	WritePrivateProfileString(TEXT("Time"), TEXT("minute"), CA2CT(str_minute.c_str()), TEXT(".\\Setting\\Setting.ini"));

	src2 = ui->from_2->document()->toPlainText().toLocal8Bit().toStdString();
	dst2 = ui->to_2->document()->toPlainText().toLocal8Bit().toStdString();

	WritePrivateProfileString(TEXT("Path"), TEXT("from2"), CA2CT(src2.c_str()), TEXT(".\\Setting\\Setting.ini"));
	WritePrivateProfileString(TEXT("Path"), TEXT("to2"), CA2CT(dst2.c_str()), TEXT(".\\Setting\\Setting.ini"));

	src3 = ui->from_3->document()->toPlainText().toLocal8Bit().toStdString();
	dst3 = ui->to_3->document()->toPlainText().toLocal8Bit().toStdString();

	WritePrivateProfileString(TEXT("Path"), TEXT("from3"), CA2CT(src3.c_str()), TEXT(".\\Setting\\Setting.ini"));
	WritePrivateProfileString(TEXT("Path"), TEXT("to3"), CA2CT(dst3.c_str()), TEXT(".\\Setting\\Setting.ini"));


	src += "\\";
	dst += "\\";
	src2 += "\\";
	dst2 += "\\";
	src3 += "\\";
	dst3 += "\\";

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
	mSysTrayIcon->setToolTip(QObject::trUtf8("Sensor2005 Data AutoLoader"));

	//给QSystemTrayIcon添加槽函数
	connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

	//建立托盘操作的菜单
	createActions();
	createMenu();
	//在系统托盘显示此对象

	mSysTrayIcon->show();

}


void AutoCopy::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {

	case QSystemTrayIcon::Trigger:
		this->show();
		mSysTrayIcon->hide();
		break;

	case QSystemTrayIcon::DoubleClick:
		break;
	default:
		break;
	}
}

void AutoCopy::createActions()
{
	mShowMainAction = new QAction(QObject::trUtf8("Show Setting Window"), this);
	connect(mShowMainAction, SIGNAL(triggered()), this, SLOT(on_showMainAction()));

	mUploadAction = new QAction(QObject::trUtf8("Upload Data"), this);
	connect(mUploadAction, SIGNAL(triggered()), this, SLOT(on_pushButton_Manual_clicked()));

	mExitAppAction = new QAction(QObject::trUtf8("Exit"), this);
	connect(mExitAppAction, SIGNAL(triggered()), this, SLOT(on_exitAppAction()));
}

void AutoCopy::createMenu()
{
	mMenu = new QMenu(this);
	mMenu->addAction(mShowMainAction);
	mMenu->addAction(mUploadAction);
	mMenu->addSeparator();

	mMenu->addAction(mExitAppAction);

	mSysTrayIcon->setContextMenu(mMenu);
}

void AutoCopy::on_showMainAction()
{
	this->show();
	mSysTrayIcon->hide();
}

void AutoCopy::on_exitAppAction()
{
	TerminateProcess(myHandle, 4);
	exit(0);
}
//
//BOOL CopyDir(LPCTSTR lpszSrcDir, LPCTSTR lpszDstDir) 
//{
//	SHFILEOPSTRUCT sfo;
//	ZeroMemory(&sfo, sizeof(sfo));
//	sfo.wFunc = FO_COPY;
//	sfo.pFrom = lpszSrcDir;
//	sfo.pTo = lpszDstDir;
//	sfo.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;
//	int ret = SHFileOperation(&sfo);
//	if (ret == 0)
//		return TRUE;
//	else return FALSE;
//}
