/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */
#include "console.h"
#include <stdlib.h>
#include <windows.h>

int ssms_console_init() {
//    system("chcp 65001");
    system("chcp 936");
    return system("mode con cols=85 lines=25");
}

int ssms_console_clean() {
    ssms_console_setNormalColor();
    return system("cls");
}

int ssms_console_setNormalColor() {
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                   BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
                                   FOREGROUND_INTENSITY);
}

int ssms_sonsole_setDifferentColor() {
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                   BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE |
                                   FOREGROUND_INTENSITY);
}
