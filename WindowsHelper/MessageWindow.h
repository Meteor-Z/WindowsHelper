#pragma once

#include <Windows.h>
#include <QWidget>
#include "ui_MessageWindow.h"

// 这个是Spxx的相关信息，然后弹出对应的信息框
class MessageWindow : public QWidget {
	Q_OBJECT

public:
	MessageWindow(QWidget *parent = nullptr, HWND hwnd);
	~MessageWindow();

private:
	Ui::MessageWindowClass ui;
    HWND m_CurrentWindowHandler{}; // 当前句柄的 HWND
};
