/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#ifndef SSMS_CONSOLE_H
#define SSMS_CONSOLE_H

int ssms_console_init();
int ssms_console_clean();
int ssms_console_setNormalColor();
int ssms_console_setDifferentColor();
int ssms_console_flushStdIn();
int ssms_console_readLine(char * _Buf, int _MaxCount);


#endif //SSMS_CONSOLE_H
