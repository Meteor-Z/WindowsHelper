#pragma once

// VS窗口乱码问题的解决
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8") // 该指令仅支持VS环境
#endif

#include <Windows.h>
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include "ui_ProcessWindow.h"

// 根据传入的消息来进行选择
enum class ExeInfo {
    FileDescription,
    CompanyName,
};


class ProcessWindow : public QWidget
{
	Q_OBJECT

public:
	ProcessWindow(QWidget *parent = nullptr);
	~ProcessWindow();
    
private:
    void initAllLayout();
    // 设置所有的样式
    void initTableWidget();

    // 更新进程信息
    void updateProcessInfo();

    // 得到进程名,并且包含应用的图片,如果获取不到,就不显示出来了
    // szExeFile: 进程名称
    // dwProcesId: 进程号
    QTableWidgetItem* getProcessName(WCHAR szExeFile[MAX_PATH], DWORD dwProcessId);

    // 根据完整路径获取对应的图标
    QIcon getFileIcon(const QString& filePullPath);

    // 根据Key来获取到对应的消息
    QString getFileVersionInfo(const QString& filePath, ExeInfo info);

private:
	Ui::ProcessWindowClass ui;
    QVBoxLayout* m_VBoxLayout{}; // 总的竖直排布
    QTableWidget* m_ProcessTableWidget{}; // 进程
};
