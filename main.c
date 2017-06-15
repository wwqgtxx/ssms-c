/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdio.h>
#include "cli.h"
#include "console.h"
#include "common.h"
#include "dataoperator.h"
#include "dataprinter.h"

int main() {
    ssms_console_init();
    ssms_console_clean();

    if (ssms_initDatabase() != 0 || ssms_initTable() != 0 || ssms_initStmt() != 0) {
        return 1;
    }
    ssms_cli_main_loop();
    return 0;
}