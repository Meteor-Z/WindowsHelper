#include "SpyWindow.h"
#include <Windows.h>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setStyleSheet("background-color: blue;");
}

SpyWindow::~SpyWindow(){
}
