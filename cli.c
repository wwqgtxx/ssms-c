/*
 **Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdio.h>
#include <conio.h>
#include "cli.h"
#include "common.h"
#include "console.h"
#include "dataoperator.h"
#include "dataprinter.h"

#pragma warning( disable : 4996)

int ssms_cli_main_menu(int select_id) {
    int need_print = 1;
    ssms_console_clean();
    while (1) {
        if (need_print) {
            ssms_console_clean();
            printf_s("\n");
            printf_s("      ----------------------------------------------------------------------\n");
            printf_s("     |                           学生成绩管理系统                           |\n");
            printf_s("      ----------------------------------------------------------------------\n");
            printf_s(" 功能选择：\n");
            printf_s("     ");
            if (select_id == 1) {
                ssms_console_setDifferentColor();
            }
            printf_s("1.学生基本信息录入");
            if (select_id == 1) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 2) {
                ssms_console_setDifferentColor();
            }
            printf_s("2.学生基本信息删除");
            if (select_id == 2) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 3) {
                ssms_console_setDifferentColor();
            }
            printf_s("3.学生基本信息修改");
            if (select_id == 3) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 4) {
                ssms_console_setDifferentColor();
            }
            printf_s("4.学生基本信息查看");
            if (select_id == 4) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 5) {
                ssms_console_setDifferentColor();
            }
            printf_s("5.学生成绩录入");
            if (select_id == 5) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 6) {
                ssms_console_setDifferentColor();
            }
            printf_s("6.学生成绩删除");
            if (select_id == 6) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 7) {
                ssms_console_setDifferentColor();
            }
            printf_s("7.学生成绩修改");
            if (select_id == 7) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 8) {
                ssms_console_setDifferentColor();
            }
            printf_s("8.学生成绩查看");
            if (select_id == 8) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 9) {
                ssms_console_setDifferentColor();
            }
            printf_s("9.查看学生成绩统计信息");
            if (select_id == 9) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 10) {
                ssms_console_setDifferentColor();
            }
            printf_s("10.查看学生成绩排名");
            if (select_id == 10) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 11) {
                ssms_console_setDifferentColor();
            }
            printf_s("11.生成补考名单");
            if (select_id == 11) {
                ssms_console_setNormalColor();
            }
            printf_s("\n");
            printf_s("     ");
            if (select_id == 12) {
                ssms_console_setDifferentColor();
            }
            printf_s("12.查看成绩分布图");
            if (select_id == 12) {
                ssms_console_setNormalColor();
            }
            for (int i = 0; i < 7; i++) printf_s("\n");
            printf_s("提示：按方向键可上下选择，按回车键进入所选项，按ESC键可退出系统。\n");
            need_print = 0;
        }
        switch (_getch()) {
            case 0xe0:
                switch (_getch()) {
                    case 72://up
                        if (select_id > 1) {
                            select_id--;
                        } else {
                            select_id = 12;
                        }
                        need_print = 1;
                        break;
                    case 80://down
                        if (select_id < 12) {
                            select_id++;
                        } else {
                            select_id = 1;
                        }
                        need_print = 1;
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
                ssms_console_clean();
                return select_id;
            case 0x1b://esc
                ssms_console_clean();
                return 0;
            default:
                break;
        }

    }

    return 0;
}

int ssms_cli_addNewStudent() {
    int tmp_int;
    SSMS_STUDENT_PTR student = ssms_newStudent();
    student->id = 0;
    student->name = ssms_common_newstr(50);
    student->major = ssms_common_newstr(50);
    student->need_free = 1;
    input_name:
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("     |                          |学生成绩管理系统|                          |\n");
    printf_s("     |                           ----------------                           |\n");
    printf_s("     |                                                                      |\n");
    printf_s("     |                           学生基本信息录入                           |\n");
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("请输入姓名：\n");
    ssms_console_flushStdIn();
    if (ssms_console_readLine(student->name, 50) == 0) {
        printf_s("------------------------------------------\n");
        printf_s("警告：姓名不可为空，请使用别的姓名重新输入！\n");
        printf_s("------------------------------------------\n");
        printf_s("是否要重新输入？ 0:重新输入 1:放弃并返回主菜单\n");
        ssms_console_flushStdIn();
        scanf("%d", &tmp_int);
        if (tmp_int) {
            return 0;
        }
        ssms_console_clean();
        goto input_name;
    }
    if (ssms_checkStudentByName(student->name)) {
        printf_s("------------------------------------------\n");
        printf_s("警告：姓名不可重复，请使用别的姓名重新输入！\n");
        printf_s("------------------------------------------\n");
        printf_s("是否要重新输入？ 0:重新输入 1:放弃并返回主菜单\n");
        ssms_console_flushStdIn();
        scanf("%d", &tmp_int);
        if (tmp_int) {
            return 0;
        }
        ssms_console_clean();
        goto input_name;
    }
    printf_s("请输入性别： 0：男 1：女\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    student->sex = tmp_int ? FEMALE : MALE;
    printf_s("请输入年龄：（整数）\n");
    ssms_console_flushStdIn();
    scanf("%d", &student->age);
    printf_s("请输入专业/学院:\n");
    ssms_console_flushStdIn();
    ssms_console_readLine(student->major, 50);
    printf_s("您录入的信息为：\n");
    ssms_dataprinter_printStudent(student);
    printf_s("是否确定保存？ 0:确定 1:放弃并返回主菜单\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    if (tmp_int) {
        ssms_freeStudentPtr(student);
        return 0;
    }

    if (ssms_insertStudent(student) != 1) {
        printf_s("信息录入成功！\n");
        printf_s("您录入的学生ID为：%lld", student->id);
    }
    ssms_freeStudentPtr(student);

    printf_s("        ");
    ssms_console_setDifferentColor();
    printf_s("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf_s("\n");
    _getch();

    return 0;
}

int ssms_cli_deleteStudent_callback(SSMS_STUDENT_PTR student) {
    int tmp_int;
    ssms_console_clean();
    printf_s("您选择的记录是:\n");
    ssms_dataprinter_printStudent(student);
    printf_s("是否确定删除该记录（***此操作不可逆***）？ 0:确定 1:放弃并返回\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    if (tmp_int) {
        return 0;
    }
    if (ssms_deleteStudent(student) == 0) {
        return 1;
    }

    return 0;
}

int ssms_cli_deleteStudent() {
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVecWithSelectCallback(students, ssms_cli_deleteStudent_callback);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_alertStudent_callback(SSMS_STUDENT_PTR student) {
    SSMS_STUDENT_PTR tmp_student = ssms_newStudent();
    int select, tmp_int;
    p1:
    tmp_student->id = student->id;
    tmp_student->name = student->name;
    tmp_student->sex = student->sex;
    tmp_student->age = student->age;
    tmp_student->major = student->major;
    tmp_student->need_free = 0;
    ssms_console_clean();
    printf_s("您选择的记录是:\n");
    ssms_dataprinter_printStudent(student);
    printf_s("请输入您要修改的具体属性\n");
    printf_s("1:姓名\n");
    printf_s("2:性别\n");
    printf_s("3:年龄\n");
    printf_s("4:专业\n");
    printf_s("0:放弃修改\n");
    p0:
    ssms_console_flushStdIn();
    scanf("%d", &select);
    switch (select) {
        case 0:
            return 0;
        case 1:
            tmp_student->name = ssms_common_newstr(50);
        input_name:
            printf_s("请输入姓名：\n");
            ssms_console_flushStdIn();
            if (ssms_console_readLine(tmp_student->name, 50) == 0) {
                printf_s("------------------------------------------\n");
                printf_s("警告：姓名不可为空，请使用别的姓名重新输入！\n");
                printf_s("------------------------------------------\n");
                printf_s("是否要重新输入？ 0:重新输入 1:放弃修改\n");
                ssms_console_flushStdIn();
                scanf("%d", &tmp_int);
                if (tmp_int) {
                    free(tmp_student->name);
                    ssms_freeStudentPtr(tmp_student);
                    return 0;
                }
                goto input_name;
            }
            if (ssms_checkStudentByName(tmp_student->name)) {
                printf_s("------------------------------------------\n");
                printf_s("警告：姓名不可重复，请使用别的姓名重新输入！\n");
                printf_s("------------------------------------------\n");
                printf_s("是否要重新输入？ 0:重新输入 1:放弃修改\n");
                ssms_console_flushStdIn();
                scanf("%d", &tmp_int);
                if (tmp_int) {
                    free(tmp_student->name);
                    ssms_freeStudentPtr(tmp_student);
                    return 0;
                }
                goto input_name;
            }
            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printStudent(tmp_student);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                free(tmp_student->name);
                ssms_freeStudentPtr(tmp_student);
                return 0;
            }
            if (ssms_updateStudent(tmp_student) != 1) {
                printf_s("信息录入成功！\n");
                free(student->name);
                student->name = tmp_student->name;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        case 2:
            printf_s("请输入性别： 0：男 1：女\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            tmp_student->sex = tmp_int ? FEMALE : MALE;
            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printStudent(tmp_student);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                ssms_freeStudentPtr(tmp_student);
                return 0;
            }
            if (ssms_updateStudent(tmp_student) != 1) {
                printf_s("信息录入成功！\n");
                student->sex = tmp_student->sex;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        case 3:
            printf_s("请输入年龄：（整数）\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_student->age);
            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printStudent(tmp_student);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                ssms_freeStudentPtr(tmp_student);
                return 0;
            }
            if (ssms_updateStudent(tmp_student) != 1) {
                printf_s("信息录入成功！\n");
                student->age = tmp_student->age;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        case 4:
            tmp_student->major = ssms_common_newstr(50);
            printf_s("请输入专业/学院:\n");
            ssms_console_flushStdIn();
            ssms_console_readLine(tmp_student->major, 50);

            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printStudent(tmp_student);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                free(tmp_student->major);
                ssms_freeStudentPtr(tmp_student);
                return 0;
            }
            if (ssms_updateStudent(tmp_student) != 1) {
                printf_s("信息录入成功！\n");
                free(student->major);
                student->major = tmp_student->major;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        default:
            goto p0;
    }
    return 0;
}

int ssms_cli_alertStudent() {
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVecWithSelectCallback(students, ssms_cli_alertStudent_callback);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_showStudentInfo() {
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVec(students);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_addNewScore_callback(SSMS_STUDENT_PTR student) {
    int tmp_int;
    ssms_console_clean();
    printf_s("您选择的学生是:\n");
    ssms_dataprinter_printStudent(student);
    printf_s("是否要登记该学生的成绩？ 0:继续输入 1:放弃并返回主菜单\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    if (tmp_int) {
        return 1;
    }
    SSMS_SCORE_PTR score = ssms_newScore();
    score->id = 0;
    score->student_id = student->id;
    score->student_name = student->name;
    score->need_free = 0;
    printf_s("请输入成绩：\n");
    ssms_console_flushStdIn();
    scanf("%lf", &score->score);
    printf_s("请输入学年：\n");
    ssms_console_flushStdIn();
    scanf("%d", &score->year);

    printf_s("您录入的信息为：\n");
    ssms_dataprinter_printScore(score);
    printf_s("是否确定保存？ 0:确定 1:放弃并返回主菜单\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    if (tmp_int) {
        ssms_freeScorePtr(score);
        return 0;
    }

    if (ssms_insertScore(score) != 1) {
        printf_s("信息录入成功！\n");
        printf_s("您录入的成绩ID为：%lld", score->id);
    }
    ssms_freeScorePtr(score);


    printf_s("        ");
    ssms_console_setDifferentColor();
    printf_s("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf_s("\n");
    _getch();

    return 1;
}

int ssms_cli_addNewScore() {
    int tmp_int;
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("     |                          |学生成绩管理系统|                          |\n");
    printf_s("     |                           ----------------                           |\n");
    printf_s("     |                                                                      |\n");
    printf_s("     |                           学生成绩信息录入                           |\n");
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("按任意键进入学生选择菜单，ESC键退出编辑");
    tmp_int = _getch();
    if (tmp_int == 0x1b) {//esc
        return 0;
    }
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVecWithSelectCallback(students, ssms_cli_addNewScore_callback);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_deleteScore_callback(SSMS_SCORE_PTR score) {
    int tmp_int;
    ssms_console_clean();
    printf_s("您选择的记录是:\n");
    ssms_dataprinter_printScore(score);
    printf_s("是否确定删除该记录（***此操作不可逆***）？ 0:确定 1:放弃并返回\n");
    ssms_console_flushStdIn();
    scanf("%d", &tmp_int);
    if (tmp_int) {
        return 1;
    }
    if (ssms_deleteScore(score) == 0) {
        return 1;
    }

    return 1;
}

int ssms_cli_deleteScore() {
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScores();
    ssms_dataprinter_printScorePtrVecWithSelectCallback(scores, ssms_cli_deleteScore_callback);
    ssms_freeScorePtrVec(&scores);
    return 0;
}

int ssms_cli_alertScore_callback(SSMS_SCORE_PTR score) {
    SSMS_SCORE_PTR tmp_score = ssms_newScore();
    int select, tmp_int;
    p1:
    tmp_score->id = score->id;
    tmp_score->student_id = score->student_id;
    tmp_score->score = score->score;
    tmp_score->year = score->year;
    tmp_score->student_name = score->student_name;
    tmp_score->need_free = score->need_free;
    ssms_console_clean();
    printf_s("您选择的记录是:\n");
    ssms_dataprinter_printScore(score);
    printf_s("请输入您要修改的具体属性\n");
    printf_s("1:分数\n");
    printf_s("2:学年\n");
    printf_s("0:放弃修改\n");
    p0:
    ssms_console_flushStdIn();
    scanf("%d", &select);
    switch (select) {
        case 0:
            return 1;
        case 1:
            printf_s("请输入成绩：\n");
            ssms_console_flushStdIn();
            scanf("%lf", &tmp_score->score);
            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printScore(tmp_score);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                ssms_freeScorePtr(tmp_score);
                return 1;
            }
            if (ssms_updateScore(tmp_score) != 1) {
                printf_s("信息录入成功！\n");
                score->score = tmp_score->score;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        case 2:
            printf_s("请输入学年：\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_score->year);
            printf_s("您录入的信息为：\n");
            ssms_dataprinter_printScore(tmp_score);
            printf_s("是否确定保存？ 0:确定 1:放弃并返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                ssms_freeScorePtr(tmp_score);
                return 1;
            }
            if (ssms_updateScore(tmp_score) != 1) {
                printf_s("信息录入成功！\n");
                score->year = tmp_score->year;
            }
            printf_s("是否确定修改其他项？ 0:确定 1:返回\n");
            ssms_console_flushStdIn();
            scanf("%d", &tmp_int);
            if (tmp_int) {
                break;
            }
            goto p1;
        default:
            goto p0;
    }
    return 1;
}

int ssms_cli_alertScore() {
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScores();
    ssms_dataprinter_printScorePtrVecWithSelectCallback(scores, ssms_cli_alertScore_callback);
    ssms_freeScorePtrVec(&scores);
    return 0;
}

int ssms_cli_showGradeInfo() {
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScores();
    ssms_dataprinter_printScorePtrVec(scores);
    ssms_freeScorePtrVec(&scores);
    return 0;
}

int ssms_cli_showGradeStat() {
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("     |                          |学生成绩管理系统|                          |\n");
    printf_s("     |                           ----------------                           |\n");
    printf_s("     |                                                                      |\n");
    printf_s("     |                           学生成绩统计信息                           |\n");
    printf_s("      ----------------------------------------------------------------------\n");
    printf_s("平均成绩： %lf\n", ssms_getScoreAvg());
    printf_s("及格率： %lf%%\n", ssms_getScorePassPercent() * 1e2);
    int *subsection = ssms_common_newIntArray(13);
    ssms_getScorePassSubsection(subsection);
    ssms_dataprinter_printScorePassSubsectionTable(subsection);
    free(subsection);
    printf_s("                               ");
    ssms_console_setDifferentColor();
    printf_s("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf_s("\n");
    _getch();
    return 0;
}

int ssms_cli_showScoreRanking() {
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScoresOrderByScore();
    ssms_dataprinter_printScorePtrVec(scores);
    ssms_freeScorePtrVec(&scores);
    return 0;
}

int ssms_cli_showNoPassNames() {
    SSMS_NAMES_VEC names = ssms_getScoreNotPassNames();
    ssms_dataprinter_printScoreNotPassNames(names);
    ssms_freeNamesVec(&names);
    return 0;
}

int ssms_cli_showGradeStatGraph() {
    int *subsection = ssms_common_newIntArray(13);
    ssms_getScorePassSubsection(subsection);
    ssms_dataprinter_printScorePassSubsectionGraph(subsection);
    free(subsection);
    printf_s("                               ");
    ssms_console_setDifferentColor();
    printf_s("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf_s("\n");
    _getch();
    return 0;
}


int ssms_cli_main_loop() {
    int select_id = 1;
    while ((select_id = ssms_cli_main_menu(select_id)) != 0) {
        switch (select_id) {
            case 1:
                ssms_cli_addNewStudent();
                break;
            case 2:
                ssms_cli_deleteStudent();
                break;
            case 3:
                ssms_cli_alertStudent();
                break;
            case 4:
                ssms_cli_showStudentInfo();
                break;
            case 5:
                ssms_cli_addNewScore();
                break;
            case 6:
                ssms_cli_deleteScore();
                break;
            case 7:
                ssms_cli_alertScore();
                break;
            case 8:
                ssms_cli_showGradeInfo();
                break;
            case 9:
                ssms_cli_showGradeStat();
                break;
            case 10:
                ssms_cli_showScoreRanking();
                break;
            case 11:
                ssms_cli_showNoPassNames();
                break;
            case 12:
                ssms_cli_showGradeStatGraph();
                break;
            default:
                break;
        }
    }
    return 0;
}