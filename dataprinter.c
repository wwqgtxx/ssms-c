/*
 **Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */
#include <stdio.h>
#include <conio.h>
#include "console.h"
#include "dataprinter.h"
#include "dataoperator.h"


int ssms_dataprinter_printStudent(SSMS_STUDENT_PTR student) {
    char *sex;
    switch (student->sex) {
        case MALE:
            sex = "男";
            break;
        case FEMALE:
            sex = "女";
            break;
        default:
            sex = "未知";
            break;
    }
    printf(" -------------------------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n", "id", "姓名", "性别", "年龄", "专业/学院");
    printf(" -------------------------------------------------------------------------------\n");
    printf("|%-15lld|%-15s|%-15s|%-15d|%-15s|\n", student->id, student->name, sex, student->age, student->major);
    printf(" -------------------------------------------------------------------------------\n");
    return 0;
}

int ssms_dataprinter_printStudentPtrVecWithSelectCallback(SSMS_STUDENT_PTR_VEC students,
                                                          SSMS_DATAPRINTER_PRINT_STUDENT_PRT_VEC_CALLBACK callback) {
    SSMS_STUDENT_PTR student;
    int num = 0;
    int select_id = 0;
    int i;
    char *sex;
    printf(" -------------------------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n", "id", "姓名", "性别", "年龄", "专业/学院");
    printf(" -------------------------------------------------------------------------------\n");
    if (students.length > 0) {
        vec_foreach(&students, student, i) {
                switch (student->sex) {
                    case MALE:
                        sex = "男";
                        break;
                    case FEMALE:
                        sex = "女";
                        break;
                    default:
                        sex = "未知";
                        break;
                }
                if (i == select_id) {
                    ssms_console_setDifferentColor();
                }
                printf("|%-15lld|%-15s|%-15s|%-15d|%-15s|", student->id, student->name, sex, student->age,
                       student->major);
                if (i == select_id) {
                    ssms_console_setNormalColor();
                }
                printf("\n");
                num++;
                if (num % 19 == 0 || i == students.length - 1) {
                    printf(" -------------------------------------------------------------------------------\n");
                    printf("提示：按方向键可上下翻页，按ESC键可退出显示。\n");
                    if (num < 19) {
                        for (int tmp = num; tmp < 19; tmp++) printf("\n");
                    }
                    while (1) {
                        switch (getch()) {
                            case 0xe0:
                                switch (getch()) {
                                    case 72://up
                                        if (select_id > 0) {
                                            select_id--;
                                            if (num % 19 == 0 && i >= 19) {
                                                i--;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 80://down
                                        if (select_id < students.length - 1) {
                                            select_id++;
                                            if (num % 19 == 0 && i < students.length - 1) {
                                                i++;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 75: //left
                                        break;
                                    case 77://down
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0x0d://enter:
                                if (callback) {
                                    if(callback(students.data[select_id])){ return 0;}
                                    goto p1;
                                }
                                break;
                            case 0x1b://esc
                                ssms_console_clean();
                                return 0;
                            default:
                                break;
                        }

                    }
                    p1:
                    i -= num;
                    num = 0;
                    printf(" -------------------------------------------------------------------------------\n");
                    printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n", "id", "姓名", "性别", "年龄",
                           "专业/学院");
                    printf(" -------------------------------------------------------------------------------\n");
                }
            }
    } else {
        printf("                        ");
        printf("数据库中没有任何数据，请添加数据");
        for (i = 0; i < 20; i++) printf("\n");
        printf("                               ");
        ssms_console_setDifferentColor();
        printf("按任意键返回");
        ssms_console_setNormalColor();
        printf("\n");
        getch();
    }
    return 0;
}

int ssms_dataprinter_printStudentPtrVec(SSMS_STUDENT_PTR_VEC students) {
    return ssms_dataprinter_printStudentPtrVecWithSelectCallback(students, NULL);
}

int ssms_dataprinter_printScore(SSMS_SCORE_PTR score) {
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|\n", "id", "学生id", "分数", "学年");
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15lld|%-15lld|%-15lf|%-15d|\n", score->id, score->student_id, score->score, score->year);
    printf(" ---------------------------------------------------------------\n");
    return 0;
}

int ssms_dataprinter_printScorePtrVecWithSelectCallback(SSMS_SCORE_PTR_VEC scores,
                                                        SSMS_DATAPRINTER_PRINT_SCORE_PRT_VEC_CALLBACK callback) {
    SSMS_SCORE_PTR score;
    int num = 0;
    int select_id = 0;
    int i;
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|\n", "id", "学生名称", "分数", "学年");
    printf(" ---------------------------------------------------------------\n");
    if (scores.length > 0) {
        vec_foreach(&scores, score, i) {

                if (i == select_id) {
                    ssms_console_setDifferentColor();
                }
                printf("|%-15lld|%-15s|%-15lf|%-15d|", score->id, score->student_name, score->score, score->year);
                if (i == select_id) {
                    ssms_console_setNormalColor();
                }
                printf("\n");
                num++;
                if (num % 19 == 0 || i == scores.length - 1) {
                    printf(" -------------------------------------------------------------------------------\n");
                    printf("提示：按方向键可上下翻页，按ESC键可退出显示。\n");
                    if (num < 19) {
                        for (int tmp = num; tmp < 19; tmp++) printf("\n");
                    }
                    while (1) {
                        switch (getch()) {
                            case 0xe0:
                                switch (getch()) {
                                    case 72://up
                                        if (select_id > 0) {
                                            select_id--;
                                            if (num % 19 == 0 && i >= 19) {
                                                i--;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 80://down
                                        if (select_id < scores.length - 1) {
                                            select_id++;
                                            if (num % 19 == 0 && i < scores.length - 1) {
                                                i++;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 75: //left
                                        break;
                                    case 77://down
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0x0d://enter:
                                if (callback) {
                                    if(callback(scores.data[select_id])){ return 0;}
                                    goto p1;
                                }
                                break;
                            case 0x1b://esc
                                ssms_console_clean();
                                return 0;
                            default:
                                break;
                        }

                    }
                    p1:
                    i -= num;
                    num = 0;
                    printf(" ---------------------------------------------------------------\n");
                    printf("|%-15s|%-15s|%-15s|%-15s|\n", "id", "学生名称", "分数", "学年");
                    printf(" ---------------------------------------------------------------\n");

                }
            }
    } else {
        printf("                        ");
        printf("数据库中没有任何数据，请添加数据");
        for (i = 0; i < 20; i++) printf("\n");
        printf("                               ");
        ssms_console_setDifferentColor();
        printf("按任意键返回");
        ssms_console_setNormalColor();
        printf("\n");
        getch();
    }
    return 0;
}

int ssms_dataprinter_printScorePtrVec(SSMS_SCORE_PTR_VEC scores) {
    return ssms_dataprinter_printScorePtrVecWithSelectCallback(scores, NULL);
}

int ssms_dataprinter_printScoreNotPassNamesWithSelectCallback(SSMS_NAMES_VEC names,
                                                              SSMS_DATAPRINTER_PRINT_NAMES_VEC_CALLBACK callback) {
    char *name;
    int num = 0;
    int select_id = 0;
    int i;
    printf(" ---------------\n");
    printf("|%-15s|\n", "学生名称");
    printf(" ---------------\n");
    if (names.length > 0) {
        vec_foreach(&names, name, i) {

                if (i == select_id) {
                    ssms_console_setDifferentColor();
                }
                printf("|%-15s|", name);
                if (i == select_id) {
                    ssms_console_setNormalColor();
                }
                printf("\n");
                num++;
                if (num % 19 == 0 || i == names.length - 1) {
                    printf(" ---------------\n");
                    printf("提示：按方向键可上下翻页，按ESC键可退出显示。\n");
                    if (num < 19) {
                        for (int tmp = num; tmp < 19; tmp++) printf("\n");
                    }
                    while (1) {
                        switch (getch()) {
                            case 0xe0:
                                switch (getch()) {
                                    case 72://up
                                        if (select_id > 0) {
                                            select_id--;
                                            if (num % 19 == 0 && i >= 19) {
                                                i--;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 80://down
                                        if (select_id < names.length - 1) {
                                            select_id++;
                                            if (num % 19 == 0 && i < names.length - 1) {
                                                i++;
                                            }
                                            goto p1;
                                        }
                                        break;
                                    case 75: //left
                                        break;
                                    case 77://down
                                        break;
                                    default:
                                        break;
                                }
                                break;
                            case 0x0d://enter:
                                if (callback) {
                                    if(callback(names.data[select_id])){ return 0;}
                                    goto p1;
                                }
                                break;
                            case 0x1b://esc
                                ssms_console_clean();
                                return 0;
                            default:
                                break;
                        }

                    }
                    p1:
                    i -= num;
                    num = 0;
                    printf(" ---------------\n");
                    printf("|%-15s|\n", "学生名称");
                    printf(" ---------------\n");

                }
            }
    } else {
        printf("                        ");
        printf("名单为空");
        for (i = 0; i < 20; i++) printf("\n");
        printf("                               ");
        ssms_console_setDifferentColor();
        printf("按任意键返回");
        ssms_console_setNormalColor();
        printf("\n");
        getch();
    }
    return 0;
}

int ssms_dataprinter_printScoreNotPassNames(SSMS_NAMES_VEC names) {
    return ssms_dataprinter_printScoreNotPassNamesWithSelectCallback(names, NULL);
}


int ssms_dataprinter_printScorePassSubsectionTable(int *subsection) {
    int i = 0;
    printf("登记考生人数： %d\n", subsection[12]);
    printf(" -----------------------------------------------------------------------------------\n");
    printf("考生成绩分布表：\n");
    printf("             -----------------------------------------------------\n");
    printf("            |%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n", "0分", "1-9分", "10-19分", "20-29分", "30-39分", "40-49分");
    printf("             -----------------------------------------------------\n");
    printf("            ");
    for (; i < 6; i++) {
        printf("|%-8d", subsection[i]);
    }
    printf("|\n");
    printf("             -----------------------------------------------------\n");
    printf("\n");
    printf("             -----------------------------------------------------\n");
    printf("            |%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n", "50-59分", "60-69分", "71-79分", "80-89分", "90-99分", "100分");
    printf("             -----------------------------------------------------\n");
    printf("            ");
    for (; i < 12; i++) {
        printf("|%-8d", subsection[i]);
    }
    printf("|\n");
    printf("             -----------------------------------------------------\n");
    printf(" -----------------------------------------------------------------------------------\n");
    return 0;
}


int ssms_dataprinter_printScorePassSubsectionGraph(int *subsection) {
    int tmp_arr[10];
    int max = subsection[0];
    for (int i = 1; i < 12; i++) {
        if (subsection[i] > max) {
            max = subsection[i];
        }
    }
    tmp_arr[0] = (int) (((double) (subsection[0] + subsection[1])) / max * 19);
    tmp_arr[1] = (int) (((double) subsection[2]) / max * 19);
    tmp_arr[2] = (int) (((double) subsection[3]) / max * 19);
    tmp_arr[3] = (int) (((double) subsection[4]) / max * 19);
    tmp_arr[4] = (int) (((double) subsection[5]) / max * 19);
    tmp_arr[5] = (int) (((double) subsection[6]) / max * 19);
    tmp_arr[6] = (int) (((double) subsection[7]) / max * 19);
    tmp_arr[7] = (int) (((double) subsection[8]) / max * 19);
    tmp_arr[8] = (int) (((double) subsection[9]) / max * 19);
    tmp_arr[9] = (int) (((double) (subsection[10] + subsection[11])) / max * 19);


    printf("       -------------------------------------------------------------------\n");
    for (int i = 19; i > 0; i--) {
        printf("%6d|    ", (int) ((double) max / 19 * i));
        for (int j = 0; j < 10; j++) {
            if ((tmp_arr[j] - i) >= 0) {
                printf("■■■");
            } else {
                printf("　　　");
            }
        }
        printf("   |\n");
    }
//    printf("      |    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■   |\n");
    printf("      | --+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-- |\n");
    printf("      |  %-6s%-6s%-6s%-6s%-6s%-6s%-6s%-6s%-6s%-6s%-5s|\n", "0分", "10分", "20分", "30分", "40分", "50分", "60分",
           "70分", "80分", "90分", "100分");
    printf("      ---------------------------------------------------------------------\n");
    return 0;
}
