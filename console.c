/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */
#include "console.h"
#include <stdlib.h>

int ssms_setConsole() {
//    system("chcp 65001");
    system("color 1f");
    system("chcp 936");
    return system("mode con cols=85 lines=25");
}

int ssms_cleanConsole() {
    return system("cls");
}
