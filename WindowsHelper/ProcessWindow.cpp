#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <QtWinExtras/qtwinextrasversion.h>
#include <QImage>
#include <QPixmap>
#include "ProcessWindow.h"
#include <QtWin>
#include <QPushButton>

// enum到QString的转换
static QString EnumToQString(ExeInfo info) {
    switch (info) {
    case ExeInfo::FileDescription: return QString("FileDescription");
    case ExeInfo::CompanyName: return QString("CompanyName");
    default: return QString("");
    }
}

// 根据进程号获得完整的进程路径
static QString GetExeFullPath(DWORD dwProcessId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
    WCHAR filePath[MAX_PATH];
    DWORD ret = GetModuleFileNameEx(hProcess, NULL, filePath, MAX_PATH);
    if (ret) {
        return QString::fromWCharArray(filePath);
    } else {
        return QString("nullptr");
    }
}

ProcessWindow::ProcessWindow(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
    initAllLayout();
    initTableWidget();
    setButtomTableWidget();
    setAllSignal();

    setAllButton();
    
    
}

ProcessWindow::~ProcessWindow() {}

void ProcessWindow::initAllLayout() {
    m_VBoxLayout = new QVBoxLayout(this);
    m_HTopLayout = new QHBoxLayout(this);
    m_ProcessTableWidget = new QTableWidget(this);
    

    m_TabWidget = new QTabWidget(this);

    /*
    QWidget* processModulePage{}; // 进程模块
    QWidget* processWindowPage{}; // 进程窗口
    QWidget* processThreadPage{}; // 进程线程
    QWidget* processPermissionPage{}; // 进程权限
    */
    
    m_ProcessModulePage = new QWidget(this);
    m_ProcessModuleTableWidget = new QTableWidget(this);

    m_ProcessWindowPage = new QWidget(this);
    m_ProcessWindowTableWidget = new QTableWidget(this);

    m_ProcessThreadPage = new QWidget(this);
    m_ProcessThreadTableWidget = new QTableWidget(this);

    m_ProcessPermissionPage = new QWidget(this);
    m_ProcessPermissionTableWidget = new QTableWidget(this);

    // 可以为每个页面添加布局和控件
    QVBoxLayout* moduleLayout = new QVBoxLayout;
    moduleLayout->addWidget(m_ProcessModuleTableWidget);
    m_ProcessModulePage->setLayout(moduleLayout);
    

    QVBoxLayout* windowLayout = new QVBoxLayout;
    windowLayout->addWidget(m_ProcessWindowTableWidget);
    m_ProcessWindowPage->setLayout(windowLayout);
    

    QVBoxLayout* threadLayout = new QVBoxLayout;
    threadLayout->addWidget(m_ProcessThreadTableWidget);
    m_ProcessThreadPage->setLayout(threadLayout);

    QVBoxLayout* permissionLayout = new QVBoxLayout;
    permissionLayout->addWidget(m_ProcessPermissionTableWidget);
    m_ProcessPermissionPage->setLayout(permissionLayout);

    // 将页面添加到 QTabWidget
    m_TabWidget->addTab(m_ProcessModulePage, "进程模块");
    m_TabWidget->addTab(m_ProcessWindowPage, "进程窗口");
    m_TabWidget->addTab(m_ProcessThreadPage, "进程线程");
    m_TabWidget->addTab(m_ProcessPermissionPage, "进程权限");
    
    m_VBoxLayout->addLayout(m_HTopLayout);
    m_VBoxLayout->addWidget(m_ProcessTableWidget);
    m_VBoxLayout->addWidget(m_TabWidget);
    
}

void ProcessWindow::initTableWidget() {
    m_ProcessTableWidget->setWindowTitle("Process List");
    m_ProcessTableWidget->setColumnCount(4);
    QStringList headers{ tr("进程名"), tr("进程号"), tr("公司"), tr("描述")};
    m_ProcessTableWidget->setHorizontalHeaderLabels(headers);
    updateProcessInfo();

}

void ProcessWindow::setButtomTableWidget() {
    QStringList processModuleHeaders = { "模块名", "模块句柄", "模块路径", "描述", "公司", "版本" };
    m_ProcessModuleTableWidget->setColumnCount(processModuleHeaders.size());
    m_ProcessModuleTableWidget->setHorizontalHeaderLabels(processModuleHeaders);

    QStringList processWindowHeaders = { "进程句柄", "窗口标题", "窗口类名", "窗口可视", "窗口位置", "窗口位置", "线程句柄"};
    m_ProcessWindowTableWidget->setColumnCount(processWindowHeaders.size());
    m_ProcessWindowTableWidget->setHorizontalHeaderLabels(processWindowHeaders);

    QStringList processThreadHeaders = { "线程ID", "优先级", "切换数", "状态", "模块"};
    m_ProcessThreadTableWidget->setColumnCount(processThreadHeaders.size());
    m_ProcessThreadTableWidget->setHorizontalHeaderLabels(processThreadHeaders);

    QStringList processPermissionHeaders = { "权限", "状态", "说明", "ID" };
    m_ProcessPermissionTableWidget->setColumnCount(processPermissionHeaders.size());
    m_ProcessPermissionTableWidget->setHorizontalHeaderLabels(processPermissionHeaders);
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

    m_ProcessTableWidget->clearContents();
    m_ProcessTableWidget->setRowCount(0);
    int row{ 0 };
    do {
        
        m_ProcessTableWidget->insertRow(row);

        QString fileFullPath = GetExeFullPath(pe32.th32ProcessID);
        // 名称
        m_ProcessTableWidget->setItem(row, 0, getProcessName(pe32.szExeFile, pe32.th32ProcessID));
        // 进程号
        m_ProcessTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(pe32.th32ProcessID)));
        // 进程号
        m_ProcessTableWidget->setItem(row, 2, new QTableWidgetItem(getFileVersionInfo(GetExeFullPath(pe32.th32ProcessID), ExeInfo::CompanyName)));
        // 描述
        m_ProcessTableWidget->setItem(row, 3, new QTableWidgetItem(getFileVersionInfo(GetExeFullPath(pe32.th32ProcessID), ExeInfo::FileDescription)));

        row++;
    } while (Process32Next(hProcessSnap, &pe32));
}

void ProcessWindow::setAllSignal() {
    connect(m_ProcessTableWidget, &QTableWidget::cellClicked, this, &ProcessWindow::updateProcessModule);
    connect(m_ProcessTableWidget, &QTableWidget::cellClicked, this, &ProcessWindow::updateProcessWindow);
}

void ProcessWindow::setAllButton() {
    QPushButton* button = new QPushButton("刷新列表", this);
    m_HTopLayout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [this]() {
        updateProcessInfo();
        });
}

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


#pragma comment(lib, "version") // 链接使用的

QString ProcessWindow::getFileVersionInfo(const QString& filePath, ExeInfo key) {
    DWORD handle{ 0 };
    DWORD size = GetFileVersionInfoSize(filePath.toStdWString().c_str(), &handle);
    if (size == 0) {
        return QString("");
    }
    if (handle != 0) {
        return QString("");
    }

    std::vector<BYTE> buffer(size);
    if (!GetFileVersionInfo(filePath.toStdWString().c_str(), handle, size, buffer.data())) {
        return QString("");
    }

    LPVOID versionInfo = nullptr;
    UINT versionInfoLength = 0;
    std::wstring subBlock = QString(QString("\\StringFileInfo\\040904B0\\") + EnumToQString(key)).toStdWString();

    if (!VerQueryValue(buffer.data(), subBlock.c_str(), &versionInfo, &versionInfoLength)) {
        return QString("");
    }

    return QString::fromStdWString(std::wstring(static_cast<wchar_t*>(versionInfo)));

}
// 获取模块的版本信息
static QMap<QString, QString> GetModuleInfo(HMODULE hModule) {
    QMap<QString, QString> infoMap{};
    WCHAR szFilePath[MAX_PATH];
    if (GetModuleFileName(hModule, szFilePath, MAX_PATH) == 0) {
        return infoMap;
    }

    DWORD dwHandle;
    DWORD dwSize = GetFileVersionInfoSize(szFilePath, &dwHandle);
    if (dwSize == 0) {
        return infoMap;
    }

    // 分配内存来存储版本信息
    LPBYTE lpVersionData = new BYTE[dwSize];
    if (!GetFileVersionInfo(szFilePath, dwHandle, dwSize, lpVersionData)) {
        delete[] lpVersionData;
        return infoMap;
    }
    // 查询版本信息字段
    QStringList keys = { "CompanyName", "FileDescription", "FileVersion", "ProductName", "ProductVersion" };
    for (const QString& key : keys) {
        QString versionInfoKey = QStringLiteral("\\StringFileInfo\\040904b0\\") + key;
        LPVOID lpBuffer;
        UINT uLen;
        if (VerQueryValue(lpVersionData, versionInfoKey.toStdWString().c_str(), &lpBuffer, &uLen)) {
            infoMap[key] = QString::fromWCharArray(reinterpret_cast<LPCWSTR>(lpBuffer));
        } else {
            infoMap[key] = "No information found";
        }
    }

    // 清理内存
    return infoMap;
}
struct ProcessModuleInfo {
    QString moduleName{}; // 模块名称
    QString moduleHandle{}; // 模块句柄
    QString modulePath{}; // 模块地址
    QString description{}; // 描述
    QString company{}; // 公司
    QString version{}; // 版本
};
void ProcessWindow::updateProcessModule(int row, int column) {
    DWORD processId = m_ProcessTableWidget->item(row, 1)->text().toLong();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return;
    }
    QVector<ProcessModuleInfo> moduleVec{};
    MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
    if (Module32First(hSnapshot, &me32)) {
        do {
            //std::wcout << L"Module: " << me32.szModule << L", Path: " << me32.szExePath << std::endl;
            //QStringList keys = { "CompanyName", "FileDescription", "FileVersion", "ProductName", "ProductVersion" };
            ProcessModuleInfo info{};
            QMap<QString, QString> mapInfo = GetModuleInfo(me32.hModule);
            info.moduleName = QString::fromWCharArray(me32.szModule);
            info.modulePath = QString::fromWCharArray(me32.szExePath);
            info.description = mapInfo["FileDescription"];
            info.company = mapInfo["CompanyName"];
            info.moduleHandle = QString("0x%1").arg(reinterpret_cast<quintptr>(me32.hModule), QT_POINTER_SIZE * 2, 16, QLatin1Char('0')).toUpper();
            info.version = mapInfo["ProductVersion"];
            moduleVec.push_back(std::move(info));
        } while (Module32Next(hSnapshot, &me32));
    }

    CloseHandle(hSnapshot);

    // 更新数据
    m_ProcessModuleTableWidget->clearContents();
    m_ProcessModuleTableWidget->setRowCount(0);
    for (int i = 0; i < moduleVec.size(); i++) {
        m_ProcessModuleTableWidget->insertRow(i);
        m_ProcessModuleTableWidget->setItem(i, 0, new QTableWidgetItem(moduleVec[i].moduleName));
        m_ProcessModuleTableWidget->setItem(i, 1, new QTableWidgetItem(moduleVec[i].moduleHandle));
        m_ProcessModuleTableWidget->setItem(i, 2, new QTableWidgetItem(moduleVec[i].modulePath));
        m_ProcessModuleTableWidget->setItem(i, 3, new QTableWidgetItem(moduleVec[i].description));
        m_ProcessModuleTableWidget->setItem(i, 4, new QTableWidgetItem(moduleVec[i].company));

        m_ProcessModuleTableWidget->setItem(i, 5, new QTableWidgetItem(moduleVec[i].version));
    }
}

struct WindowInfo {
    HWND hwnd; // 窗口
    DWORD processId; // 进程号
    QString title{}; // 进程标题
    QString className{}; // 类名
    
};
static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    QVector<WindowInfo>& windows = *reinterpret_cast<QVector<WindowInfo>*>(lParam);
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    WindowInfo info{};
    info.hwnd = hwnd;
    info.processId = processId;
    windows.push_back(info);
    return TRUE; // 继续枚举窗口
}
void ProcessWindow::updateProcessWindow(int row, int column) {
    DWORD processId = m_ProcessTableWidget->item(row, 1)->text().toLong();
    QVector<WindowInfo> windows;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windows));

    QVector<WindowInfo> processWindows;
    for (const auto& window : windows) {
        if (window.processId == processId) {
            processWindows.push_back(window);
        }
    }

    m_ProcessWindowTableWidget->clearContents();
    m_ProcessWindowTableWidget->setRowCount(0);
    
    for (int i = 0; i < processWindows.size(); i++) {
        quintptr hwndValue = reinterpret_cast<quintptr>(processWindows[i].hwnd);
        QString hwndString = QString::number(hwndValue, 16).toUpper();
        m_ProcessWindowTableWidget->setItem(i, 0, new QTableWidgetItem(hwndString));
    }


}
