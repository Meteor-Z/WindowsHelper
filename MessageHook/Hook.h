#pragma once

#include "pch.h"
#include <Windows.h>

#define DLL_EXPORT __declspec(dllexport)


// What ?
enum NotifyMsg
{
    WM_NotifyActivate = WM_APP + 1,
    WM_NotifyFocus,
    WM_NotifyCallWndProc,
    WM_NotifyCallWndProcRet,
    WM_NotifyGetMessage,
};


extern "C" DLL_EXPORT bool InstallCBTHook(HWND hwnd);
extern "C" DLL_EXPORT bool UninstallMessageHook();

extern "C" DLL_EXPORT bool InstallCallWndProcHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallCallWndProcHook();

extern "C" DLL_EXPORT bool InstallCallWndProcRetHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallCallWndProcRetHook();

extern "C" DLL_EXPORT bool InstallGetMessageHook(HWND hNotifyWnd, HWND hCaptureWnd);
extern "C" DLL_EXPORT bool UninstallGetMessageHook();

extern "C" DLL_EXPORT const WCHAR* GetMsgStringW(UINT uMsg);
