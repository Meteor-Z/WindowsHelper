#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <QtWinExtras/qtwinextrasversion.h>
#include <QImage>
#include <QPixmap>
#include "ProcessWindow.h"
#include <QtWin>

ProcessWindow::ProcessWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    initAllLayout();
    initTableWidget();
    
}

ProcessWindow::~ProcessWindow() {}

void ProcessWindow::initAllLayout() {
    m_VBoxLayout = new QVBoxLayout(this);
    m_ProcessTableWidget = new QTableWidget(this);
    m_VBoxLayout->addWidget(m_ProcessTableWidget);
    
    
}

void ProcessWindow::initTableWidget() {
    m_ProcessTableWidget->setWindowTitle("Process List");
    m_ProcessTableWidget->setColumnCount(4);
    QStringList headers{ tr("进程名"), tr("进程号"), tr("公司"), tr("描述")};
    m_ProcessTableWidget->setHorizontalHeaderLabels(headers);
    updateProcessInfo();

}

void ProcessWindow::updateProcessInfo() {
    // 获得当前的进程快照
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32{};

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return;
    }

    int row{ 0 };
    do {
        m_ProcessTableWidget->insertRow(row);

        // 名称
        m_ProcessTableWidget->setItem(row, 0, getProcessName(pe32.szExeFile, pe32.th32ProcessID));
        // 进程号
        m_ProcessTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(pe32.th32ProcessID)));

        /*QString description = getProcessDescription(pe32.th32ProcessID);
        table.setItem(row, 2, new QTableWidgetItem(description));

        QString companyName = getProcessCompanyName(description);
        table.setItem(row, 3, new QTableWidgetItem(companyName));*/
        row++;
    } while (Process32Next(hProcessSnap, &pe32));
}

#include <iostream>

QTableWidgetItem* ProcessWindow::getProcessName(WCHAR szExeFile[MAX_PATH], DWORD dwProcessId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);

    // 权限不是很够的应用
    if (hProcess == NULL) {
        DWORD errorCode = GetLastError();
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setIcon(QIcon());
        item->setText(QString::fromWCharArray(szExeFile));
    }

    WCHAR filePath[MAX_PATH];
    DWORD ret = GetModuleFileNameEx(hProcess, NULL, filePath, MAX_PATH);
    QString path = QString::fromWCharArray(filePath);
    QIcon icon = getFileIcon(path);
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setIcon(icon);
    item->setText(QString::fromWCharArray(szExeFile));
    return item;
}

QTableWidgetItem* ProcessWindow::getProcessDescription(DWORD dwProcessId) {
    return nullptr;
}

QIcon ProcessWindow::getFileIcon(const QString& filePullPath) {
    HICON windowsIcon{ nullptr };
    if (filePullPath.isEmpty()) {
        return QIcon();
    }

    const char* name = filePullPath.toLocal8Bit().data();
    SHFILEINFOA info{};

    if (SHGetFileInfoA(name,
        FILE_ATTRIBUTE_NORMAL,
        &info,
        sizeof(info),
        SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | SHGFI_LARGEICON)) {
        windowsIcon = info.hIcon;
    }

    QPixmap qtIcon = QtWin::fromHICON(windowsIcon);

    // 释放HIcon资源
     DestroyIcon(windowsIcon);
   

    return QIcon(qtIcon);
}
