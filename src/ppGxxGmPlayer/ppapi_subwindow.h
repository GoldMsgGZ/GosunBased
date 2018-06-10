#ifndef _ppapi_subwindow_H_
#define _ppapi_subwindow_H_

#include <Windows.h>

#include "ppapi/cpp/rect.h"

void CreateChildWindow(struct PP_Rect *r)
{
	HWND hwnd = FindWindowEx(NULL, NULL, _T("CefBrowserWindow"), NULL);
    HWND hwndWeb = FindWindowEx(hwnd, NULL, _T("Chrome_WidgetWin_0"), NULL);;
    /*if (hwndWeb)
    {
        hwndWeb = FindWindowEx(hwndWeb, NULL, _T("Chrome_RenderWidgetHostHWND"), NULL); //web contents
    }*/
    if (hwndWeb != NULL)OutputDebugString(_T("Got Chrome_RenderWidgetHostHWND\r\n"));
    DWORD pluginPid = GetCurrentProcessId();
    DWORD browserPid = 0;
    GetWindowThreadProcessId(hwnd, &browserPid);
    TCHAR szLog[256] = { 0 };
    _stprintf_s(szLog, 256, _T("Browser pid - %d, plugin pid - %d, brower hwnd - 0x%08x, webpage hwnd - 0x%08x\r\n"), 
        browserPid, pluginPid, hwnd, hwndWeb);
    OutputDebugString(szLog);
    struct CreateChildWinParam *para = (struct PP_Rect *)malloc(sizeof(struct CreateChildWinParam));
    para->r = *r;
    para->hWndParent = hwndWeb;

    if (browserPid == pluginPid)
    {
        g_bInProcess = TRUE;
        g_core_interface->CallOnMainThread(0, PP_MakeCompletionCallback(CreateChildWindowOnMainThread, para), 0);
    }
    else
    {
        g_bInProcess = FALSE;
        g_hThread = CreateThread(NULL, 0, ThreadProc, para, 0, &g_dwThreadId);
        if (g_hThread != NULL)
        {
            OutputDebugString(_T("Launch child window thread.\r\n"));
        }
        else
        {
            OutputDebugString(_T("Launch child window thread FAILED!\r\n"));
        }
    }
}

#endif//_ppapi_subwindow_H_
