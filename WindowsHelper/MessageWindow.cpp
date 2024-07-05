#include "MessageWindow.h"

MessageWindow::MessageWindow(QWidget *parent, HWND hwnd)
	: QWidget(parent), m_CurrentWindowHandler(hwnd) {
	ui.setupUi(this);
}

MessageWindow::~MessageWindow() {
}

bool MessageWindow::injectDLLByHwnd(HWND hwnd, const QString& dllPath) {
    DWORD dwProcessId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcessId);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId);
    const char* path = dllPath.toStdString().c_str();
    LPVOID pRemoteMemory = VirtualAllocEx(hProcess, nullptr, strlen(path) + 1, MEM_COMMIT, PAGE_READWRITE);

    if (!pRemoteMemory) {
        CloseHandle(hProcess);
        return false;
    }

    WriteProcessMemory(hProcess, pRemoteMemory, (LPVOID)path, strlen(path) + 1, NULL);

    // 创建一个虚拟线程？？干啥用的呢？
    HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pRemoteMemory, 0, nullptr);

    if (hThread == nullptr) {
        VirtualFreeEx(hProcess, pRemoteMemory, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
    return true;
}
