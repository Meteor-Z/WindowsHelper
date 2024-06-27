#include "MessageWindow.h"

MessageWindow::MessageWindow(QWidget *parent, HWND hwnd)
	: QWidget(parent), m_CurrentWindowHandler(hwnd) {
	ui.setupUi(this);
}

MessageWindow::~MessageWindow() {
}
