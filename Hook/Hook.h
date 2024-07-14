#pragma once

#ifndef HOOK_H
#define HOOK_H



#include "pch.h"
#include <Windows.h>

#define DLL_EXPORT __declspec(dllexport)

// 这个 #pragma好像是一个数据段，在这里面的东西可以进行共享
#pragma data_seg("Shared")
extern HWND g_hNotifyWnd; // 将消息传递给哪一个窗口
extern HWND g_hCaptureWnd; // 要捕获消息的窗口

extern HHOOK g_hCBTHook; // CBT的钩子句柄, 以下同理
extern HHOOK g_hCallWndProcHook;
extern HHOOK g_hCallWndProcRetHook;
extern HHOOK g_hGetMessageHook;

extern HINSTANCE g_hInstance;

#pragma data_seg()
// Initialised data End of data share
#pragma comment(linker,"/section:Shared,RWS")

// What ?
enum NotifyMsg {
    WM_NotifyActivate = WM_APP + 1,
    WM_NotifyFocus,
    WM_NotifyCallWndProc,
    WM_NotifyCallWndProcRet,
    WM_NotifyGetMessage,
};
// 转换函数，注意，这里应该返回POD类型，因为跨DLL了
extern "C" DLL_EXPORT const char* EnumToChar(UINT msg);
extern "C" DLL_EXPORT bool InstallCBTHook(HWND hwnd);
extern "C" DLL_EXPORT bool UninstallMessageHook();

extern "C" DLL_EXPORT bool InstallCallWndProcHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallCallWndProcHook();

extern "C" DLL_EXPORT bool InstallCallWndProcRetHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallCallWndProcRetHook();

extern "C" DLL_EXPORT bool InstallGetMessageHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallGetMessageHook();

extern "C" DLL_EXPORT const WCHAR* GetMsgStringW(UINT uMsg);

#endif
