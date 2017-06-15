/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */
#include "console.h"
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

int ssms_console_init() {
    COORD size = {85, 25};
    SMALL_RECT rc = {0, 0, size.X - (short) 1, size.Y - (short) 1};
    SMALL_RECT minimal_window = {0, 0, 1, 1};
    SetConsoleOutputCP(936);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &minimal_window);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size); // 重新设置缓冲区大小
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rc);// 重置窗口位置和大小
    SetConsoleTitle("学生成绩管理系统");
    return 0;
    //    system("chcp 936");
    //    return system("mode con cols=85 lines=25");
}

int ssms_console_clean() {
    ssms_console_setNormalColor();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return 1;
    dwConSize = (DWORD) csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
                                    dwConSize, coordScreen, &cCharsWritten))
        return 1;

    // Get the current text attribute.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return 1;

    // Set the buffer's attributes accordingly.

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
                                    dwConSize, coordScreen, &cCharsWritten))
        return 1;

    // Put the cursor at its home coordinates.

    SetConsoleCursorPosition(hConsole, coordScreen);
    return 0;
//    return system("cls");
}

int ssms_console_setNormalColor() {
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                   BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
                                   FOREGROUND_INTENSITY);
}

int ssms_console_setDifferentColor() {
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                   BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE |
                                   FOREGROUND_INTENSITY);
}

int ssms_console_flushStdIn() {
    rewind(stdin);
    return 0;
}

int ssms_console_readLine(char * _Buf, int _MaxCount) {
    memset(_Buf, '\0', (size_t) _MaxCount);
    char *ok = fgets(_Buf, _MaxCount, stdin);
    if (ok != NULL) {
        if(_Buf[0] == '\n'){
            memset(_Buf, '\0', (size_t) _MaxCount);
            return 0;
        }
        int i = strlen(_Buf);
        i--;
        if (_Buf[i] == '\n') { //去除结尾的回车符
            _Buf[i] = '\0';
        }
        for (i--; i > 0; i++) {
            if (_Buf[i] == ' ') {//去除末尾的空格
                _Buf[i] = '\0';
            } else {
                break;
            }
        }
        return i;
    }
    return 0;
}