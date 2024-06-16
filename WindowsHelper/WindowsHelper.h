#pragma once

// VS������������Ľ��
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")// ��ָ���֧��VS����
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
    // ��ʼ�������Button��Ϣ��
    void setInitFrameButton();

    // ��ʼ�������Widget��
    void initMainWidget();
private:
private:
    Ui::WindowsHelperClass ui{};
    
    QWidget* m_CentralWidget{}; // ��Ҫ�Ĵ���

    QHBoxLayout* m_ButtonLayout{}; // ����һϵ��Button��Layout
    QVBoxLayout* m_MainLayout{}; // ���ϵ��µĲ���

    QStackedWidget* m_StackedWidget{}; // ������

    QPushButton* m_FrameSpyButton{}; // ����Spy Button
    QPushButton* m_FramProcessManagementButton{}; // ���̹����Button

    SpyWindow* m_SpyWindowWidget{}; // ����


    



};
