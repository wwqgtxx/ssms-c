/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include "common.h"

char *ssms_common_newstr(int length){
    if (length == 0){
        length = 1;
    }
    return (char *) malloc(sizeof(char) *length);
}

char *ssms_common_strcpy(char *old_str) {
    if (old_str == NULL) {
        return NULL;
    }
    char *new_str = ssms_common_newstr(strlen(old_str) + 1);
    strcpy(new_str, old_str);
    return new_str;
}

int *ssms_common_newIntArray(int length) {
    return (int *) malloc(sizeof(int) * length);
}

