#pragma once

// VS窗口乱码问题的解决
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// 该指令仅支持VS环境
#endif

#include <QtWidgets/QMainWindow>
#include "ui_WindowsHelper.h"
#include "qpushbutton.h"
#include "qboxlayout.h"
#include "qstackedwidget.h"
#include <SpyWindow.h>

class WindowsHelper : public QMainWindow
{
    Q_OBJECT

public:
    WindowsHelper(QWidget *parent = nullptr);
    ~WindowsHelper();
private:
    // 初始化上面的Button信息的
    void setInitFrameButton();

    // 初始化下面的Widget的
    void initMainWidget();
private:
private:
    Ui::WindowsHelperClass ui{};
    
    QWidget* m_CentralWidget{}; // 主要的窗口

    QHBoxLayout* m_ButtonLayout{}; // 上面一系列Button的Layout
    QVBoxLayout* m_MainLayout{}; // 从上到下的布局

    QStackedWidget* m_StackedWidget{}; // 主界面

    QPushButton* m_FrameSpyButton{}; // 窗口Spy Button
    QPushButton* m_FramProcessManagementButton{}; // 进程管理的Button

    SpyWindow* m_SpyWindowWidget{}; // 窗口


    



};
