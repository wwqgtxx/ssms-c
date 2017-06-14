/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdlib.h>
#include <string.h>
#include "common.h"

char* ssms_strcpy(char* old_str){
    char* new_str = (char *) malloc(sizeof(char)*strlen(old_str)+1);
    strcpy(new_str,old_str);
    return new_str;
}

int* ssms_mallocIntArray(int length){
    return (int *)malloc(sizeof(int)*length);
}

