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

int ssms_cli_main_menu(int select_id) {
    int need_print = 1;
    ssms_console_clean();
    while (1) {
        if (need_print) {
            printf("\n");
            printf("      ----------------------------------------------------------------------\n");
            printf("     |                           学生成绩管理系统                           |\n");
            printf("      ----------------------------------------------------------------------\n");
            printf(" 功能选择：\n");
            printf("     ");
            if (select_id == 1) {
                ssms_console_setDifferentColor();
            }
            printf("1.学生基本信息录入");
            if (select_id == 1) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 2) {
                ssms_console_setDifferentColor();
            }
            printf("2.学生基本信息删除");
            if (select_id == 2) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 3) {
                ssms_console_setDifferentColor();
            }
            printf("3.学生基本信息修改");
            if (select_id == 3) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 4) {
                ssms_console_setDifferentColor();
            }
            printf("4.学生基本信息查看");
            if (select_id == 4) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 5) {
                ssms_console_setDifferentColor();
            }
            printf("5.学生成绩录入");
            if (select_id == 5) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 6) {
                ssms_console_setDifferentColor();
            }
            printf("6.学生成绩删除");
            if (select_id == 6) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 7) {
                ssms_console_setDifferentColor();
            }
            printf("7.学生成绩修改");
            if (select_id == 7) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 8) {
                ssms_console_setDifferentColor();
            }
            printf("8.学生成绩查看");
            if (select_id == 8) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 9) {
                ssms_console_setDifferentColor();
            }
            printf("9.查看学生成绩统计信息");
            if (select_id == 9) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 10) {
                ssms_console_setDifferentColor();
            }
            printf("10.查看学生成绩排名");
            if (select_id == 10) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 11) {
                ssms_console_setDifferentColor();
            }
            printf("11.生成补考名单");
            if (select_id == 11) {
                ssms_console_setNormalColor();
            }
            printf("\n");
            printf("     ");
            if (select_id == 12) {
                ssms_console_setDifferentColor();
            }
            printf("12.查看成绩分布图");
            if (select_id == 12) {
                ssms_console_setNormalColor();
            }
            for (int i = 0; i < 7; i++) printf("\n");
            printf("提示：按方向键可上下选择，按回车键进入所选项，按ESC键可退出系统。\n");
            need_print = 0;
        }
        switch (getch()) {
            case 0xe0:
                switch (getch()) {
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
    printf("      ----------------------------------------------------------------------\n");
    printf("     |                          |学生成绩管理系统|                          |\n");
    printf("     |                           ----------------                           |\n");
    printf("     |                                                                      |\n");
    printf("     |                           学生基本信息录入                           |\n");
    printf("      ----------------------------------------------------------------------\n");
    printf("请输入姓名：\n");
    fflush(stdin);
    gets(student->name);
    if (ssms_checkStudentByName(student->name)) {
        printf("------------------------------------------\n");
        printf("警告：姓名不可重复，请使用别的姓名重新输入！\n");
        printf("------------------------------------------\n");
        printf("是否要重新输入？ 0:重新输入 1:放弃并返回主菜单\n");
        scanf("%d",&tmp_int);
        if (tmp_int){
            return 0;
        }
        ssms_console_clean();
        goto input_name;
    }
    printf("请输入性别： 0：男 1：女\n");
    scanf("%d", &tmp_int);
    student->sex = tmp_int ? FEMALE : MALE;
    printf("请输入年龄：（整数）\n");
    scanf("%d", &student->age);
    printf("请输入专业/学院:\n");
    fflush(stdin);
    gets(student->major);
    printf("您录入的信息为：\n");
    ssms_dataprinter_printStudent(student);
    printf("是否确定保存？ 0:确定 1:放弃并返回主菜单\n");
    scanf("%d",&tmp_int);
    if (tmp_int){
        return 0;
    }

    if (ssms_insertStudent(student) != 1) {
        printf("信息录入成功！\n");
        printf("您录入的学生ID为：%lld",student->id);
    }
    ssms_freeStudentPtr(student);

    printf("        ");
    ssms_console_setDifferentColor();
    printf("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf("\n");
    getch();

    return 0;
}

int callback1(SSMS_STUDENT_PTR student){
    system("pause");
    return 0;
}

int ssms_cli_deleteStudent(){
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVecWithSelectCallback(students,callback1);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_alertStudent(){
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVecWithSelectCallback(students,callback1);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int ssms_cli_showStudentInfo() {
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVec(students);
    ssms_freeStudentPtrVec(&students);
    return 0;
}

int callback2(SSMS_SCORE_PTR score){
    system("pause");
    return 0;
}


int ssms_cli_deleteScore(){
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScores();
    ssms_dataprinter_printScorePtrVecWithSelectCallback(scores,callback2);
    ssms_freeScorePtrVec(&scores);
    return 0;
}

int ssms_cli_alertScore(){
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScores();
    ssms_dataprinter_printScorePtrVecWithSelectCallback(scores,callback2);
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
    printf("      ----------------------------------------------------------------------\n");
    printf("     |                          |学生成绩管理系统|                          |\n");
    printf("     |                           ----------------                           |\n");
    printf("     |                                                                      |\n");
    printf("     |                           学生成绩统计信息                           |\n");
    printf("      ----------------------------------------------------------------------\n");
    printf("平均成绩： %lf\n", ssms_getScoreAvg());
    printf("及格率： %lf%%\n", ssms_getScorePassPercent() * 1e2);
    int *subsection = ssms_common_newIntArray(13);
    ssms_getScorePassSubsection(subsection);
    ssms_dataprinter_printScorePassSubsectionTable(subsection);
    free(subsection);
    printf("                               ");
    ssms_console_setDifferentColor();
    printf("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf("\n");
    getch();
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
    printf("                               ");
    ssms_console_setDifferentColor();
    printf("按任意键返回主菜单");
    ssms_console_setNormalColor();
    printf("\n");
    getch();
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