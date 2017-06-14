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
                                                          SSMS_DATAPRINTER_PRINTSTUDENTPRTVEC_CALLBACK callback) {
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
                                    callback(student);
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
                                                        SSMS_DATAPRINTER_PRINTSCOREPRTVEC_CALLBACK callback) {
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
                                    callback(score);
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


int ssms_datapainter_printScorePassSubsection(int *subsection) {
    int i = 1;
    printf("登记考生人数： %d\n", subsection[0]);
    printf(" -----------------------------------------------------------------------------------\n");
    printf("考生成绩分布表：\n");
    printf("             -----------------------------------------------------\n");
    printf("            |%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n", "0分", "1-9分", "10-19分", "20-29分", "30-39分", "40-49分");
    printf("             -----------------------------------------------------\n");
    printf("            ");
    for (; i < 7; i++) {
        printf("|%-8d", subsection[i]);
    }
    printf("|\n");
    printf("             -----------------------------------------------------\n");
    printf("\n");
    printf("             -----------------------------------------------------\n");
    printf("            |%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|\n", "50-59分", "60-69分", "71-79分", "80-89分", "90-99分", "100分");
    printf("             -----------------------------------------------------\n");
    printf("            ");
    for (; i < 13; i++) {
        printf("|%-8d", subsection[i]);
    }
    printf("|\n");
    printf("             -----------------------------------------------------\n");
    printf(" -----------------------------------------------------------------------------------\n");
    return 0;
}
