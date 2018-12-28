#include "AutoCopy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoCopy w;
//	w.show();
	w.hide();
	return a.exec();
	
}
