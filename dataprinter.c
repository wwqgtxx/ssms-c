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

int ssms_dataprinter_printStudentPtrVec(SSMS_STUDENT_PTR_VEC students) {
    SSMS_STUDENT_PTR student;
    int num = 0;
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
            printf("|%-15lld|%-15s|%-15s|%-15d|%-15s|\n", student->id, student->name, sex, student->age,
                   student->major);
            num++;
            if (num % 19 == 0 || i == students.length - 1) {
                printf(" -------------------------------------------------------------------------------\n");
                printf("提示：按方向键可上下翻页，按ESC键可退出显示。\n");
                p2:
                while (1) {
                    switch (getch()) {
                        case 0xe0:
                            switch (getch()) {
                                case 72://up
                                    if (i >= 19) {
//                                            ssms_console_clean();
                                        num = 0;
                                        i -= 20;
                                        printf(" -------------------------------------------------------------------------------\n");
                                        printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n", "id", "姓名", "性别", "年龄",
                                               "专业/学院");
                                        printf(" -------------------------------------------------------------------------------\n");
                                        goto p1;
                                    }
                                    break;
                                case 80://down
//                                        ssms_console_clean();
                                    if (i < students.length - 1) {
                                        num = 0;
                                        i -= 18;
                                        printf(" -------------------------------------------------------------------------------\n");
                                        printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n", "id", "姓名", "性别", "年龄",
                                               "专业/学院");
                                        printf(" -------------------------------------------------------------------------------\n");
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
                        case 0x1b://esc
                            ssms_console_clean();
                            return 0;
                        default:
                            break;
                    }

                }
                p1:
                continue;
            }
        }
    } else {
        printf("                        ");
        printf("数据库中没有任何数据，请添加数据");
        for (i = 0; i < 20; i++) printf("\n");
        printf("                               ");
        ssms_sonsole_setDifferentColor();
        printf("按任意键返回");
        ssms_console_setNormalColor();
        printf("\n");
        getch();
    }
    return 0;
}

int ssms_dataprinter_printScore(SSMS_SCORE_PTR score) {
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|\n", "id", "学生id", "分数", "学年");
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15lld|%-15lld|%-15lf|%-15d|\n", score->id, score->student_id, score->score, score->year);
    printf(" ---------------------------------------------------------------\n");
    return 0;
}

int ssms_dataprinter_printScorePtrVec(SSMS_SCORE_PTR_VEC scores) {
    SSMS_SCORE_PTR score;
    int num = 0;
    int i;
    char *sex;
    printf(" ---------------------------------------------------------------\n");
    printf("|%-15s|%-15s|%-15s|%-15s|\n", "id", "学生名称", "分数", "学年");
    printf(" ---------------------------------------------------------------\n");
    if (scores.length > 0) {
        vec_foreach(&scores, score, i) {

                printf("|%-15lld|%-15s|%-15lf|%-15d|\n", score->id, score->student_name, score->score, score->year);
                num++;
                if (num % 19 == 0 || i == scores.length - 1) {
                    printf(" ---------------------------------------------------------------\n");
                    printf("提示：按方向键可上下翻页，按ESC键可退出显示。\n");
                    p2:
                    while (1) {
                        switch (getch()) {
                            case 0xe0:
                                switch (getch()) {
                                    case 72://up
                                        if (i >= 19) {
//                                            ssms_console_clean();
                                            num = 0;
                                            i -= 20;
                                            goto p1;
                                        }
                                        break;
                                    case 80://down
//                                        ssms_console_clean();
                                        if (i < scores.length - 1) {
                                            num = 0;
                                            i -= 18;
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
                            case 0x1b://esc
                                ssms_console_clean();
                                return 0;
                            default:
                                break;
                        }

                    }
                    p1:
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
        ssms_sonsole_setDifferentColor();
        printf("按任意键返回");
        ssms_console_setNormalColor();
        printf("\n");
        getch();
    }
    return 0;
}