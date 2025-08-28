#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // เตรียมโครงสร้างข้อมูลให้เป็น 0
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // เปลี่ยนจาก notepad เป็น calc
    char commandLine[] = "calc.exe";

    // แสดง PID ของโปรเซสหลัก (parent)
    printf("Parent PID: %lu\n", GetCurrentProcessId());

    // สร้าง child process เพื่อเปิด calculator
    BOOL ok = CreateProcessA(
        NULL,        // ไม่ระบุชื่อแอปแยก ใช้ commandLine แทน
        commandLine, // คำสั่งที่ใช้รัน (แก้ไขได้)
        NULL, NULL,  // ไม่มี security attributes
        FALSE,       // ไม่สืบทอด handle
        0,           // ไม่มี creation flags
        NULL,        // ใช้ environment เดิม
        NULL,        // ใช้ current directory เดิม
        &si, &pi     // ส่งโครงสร้างข้อมูลไปให้ระบบเติม
    );

    // ตรวจสอบว่า process ถูกสร้างสำเร็จไหม
    if (!ok)
    {
        DWORD e = GetLastError();
        printf("CreateProcess failed (error %lu)\n", e);
        return 1;
    }

    // แสดง PID ของโปรเซสลูก (child)
    printf("Child PID (calc.exe): %lu\n", pi.dwProcessId);

    // รอจนกว่าผู้ใช้จะปิด calc.exe
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ปิด handle ที่ไม่จำเป็น
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
