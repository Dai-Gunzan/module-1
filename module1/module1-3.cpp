#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (argc < 2) {
        printf("Usage: %s <program_to_run>\n", argv[0]);
        return 1;
    }

    // สร้าง buffer สำหรับ command line
    char commandLine[256];
    snprintf(commandLine, sizeof(commandLine), "%s", argv[1]);

    printf("Parent PID: %lu\n", GetCurrentProcessId());

    BOOL ok = CreateProcessA(
        NULL,
        commandLine,
        NULL, NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si, &pi
    );

    if (!ok) {
        DWORD e = GetLastError();
        printf("CreateProcess failed (error %lu)\n", e);
        return 1;
    }

    printf("Child PID: %lu\n", pi.dwProcessId);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
