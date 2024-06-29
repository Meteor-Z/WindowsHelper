#pragma once

// 只要是支持UTF-8的指令
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

#include <Windows.h>
#include <QWidget>
#include <QString>
#include "ui_MessageWindow.h"

// 这个是Spxx的相关信息，然后弹出对应的信息框
class MessageWindow : public QWidget {
	Q_OBJECT

public:
	MessageWindow(QWidget *parent = nullptr, HWND hwnd = nullptr);
	~MessageWindow();

private:
    // 注入DLL然后获取消息
    bool injectDLLByHwnd(HWND hwnd, const QString& dllPath);
private:
	Ui::MessageWindowClass ui;
    HWND m_CurrentWindowHandler{}; // 当前句柄的 HWND
};
