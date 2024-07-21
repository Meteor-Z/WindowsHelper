#pragma once

/*
当打开监听消息的时候，就会出现这个窗口，主要是监控消息
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
#include <QMessageBox>

// 这个是Spxx的相关信息，然后弹出对应的信息框
class MessageWindow : public QWidget {
	Q_OBJECT

public:
	MessageWindow(QWidget *parent = nullptr, HWND hCaptureWnd = nullptr);
	~MessageWindow();
protected:
    // 处理来气Windows程序发来的消息
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
    void closeEvent(QCloseEvent* event) override;
private:
    // 设置基础样式
    void initStyle();

    // 设置TextEdit的相关配置
    void setTextEdit();

   

private:
	Ui::MessageWindowClass ui;
    QListWidget* m_ListWidget{}; // 显示数据的

    HWND m_hCaptureHwnd{}; // 监视的窗口


    
};
