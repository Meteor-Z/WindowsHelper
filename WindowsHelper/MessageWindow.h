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
#include <QTableWidget>
#include <QListWidget>
#include "ui_MessageWindow.h"

// 这个是Spxx的相关信息，然后弹出对应的信息框
class MessageWindow : public QWidget {
	Q_OBJECT

public:
	MessageWindow(QWidget *parent = nullptr, HWND hCaptureWnd = nullptr);
	~MessageWindow();
protected:
    // 处理来气Windows程序发来的消息
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:
    // 设置基础样式
    void initStyle();
    // 设置TextEdit的相关配置
    void setTextEdit();
    // 注入DLL然后获取消息
    bool injectDLLByHwnd(HWND hwnd, const QString& dllPath);

private:
	Ui::MessageWindowClass ui;
    QListWidget* m_ListWidget{}; // 显示数据的

    HWND m_hCaptureHwnd{}; // 监视的窗口


    
};
