#include "SpyWindow.h"
#include <Windows.h>
#include <QStyleOption>
#include <QPainter>

SpyWindow::SpyWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setStyleSheet("background-color: blue;");
}

SpyWindow::~SpyWindow(){
}

void SpyWindow::paintEvent(QPaintEvent* e) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
