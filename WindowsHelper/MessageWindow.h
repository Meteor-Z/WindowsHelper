#pragma once

/*
消息窗口，相当于写了一个新的窗口了

*/

// 只要是支持UTF-8的指令
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

#include <Windows.h>
#include <QWidget>
#include <QString>
#include <QTextEdit>
#include <QMouseEvent>
#include "ui_MessageWindow.h"

// 这个是Spxx的相关信息，然后弹出对应的信息框
class MessageWindow : public QWidget {
	Q_OBJECT

public:
	MessageWindow(QWidget *parent = nullptr, HWND hwnd = nullptr);
	~MessageWindow();
protected:

private:
    // 设置TextEdit的相关配置
    void setTextEdit();
    // 注入DLL然后获取消息
    bool injectDLLByHwnd(HWND hwnd, const QString& dllPath);
private:
	Ui::MessageWindowClass ui;
    HWND m_CurrentWindowHandler{}; // 当前的监控句柄
    QTextEdit* m_textEdit{}; // 显示消息的窗口

    
};
