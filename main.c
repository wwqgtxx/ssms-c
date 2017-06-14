/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include "cli.h"
#include "console.h"
#include "common.h"
#include "dataoperator.h"
#include "dataprinter.h"

int main() {
    ssms_console_init();
    ssms_console_clean();
    printf("开始!\n");

    if (ssms_initDatabase() != 0 || ssms_initTable() != 0 || ssms_initStmt() != 0) {
        return 1;
    }
    ssms_cli_main_loop();
    return 0;

    SSMS_STUDENT_PTR student = ssms_newStudent();
    student->name = "小张";
    student->sex = MALE;
    student->age = 18;
    student->major = "生科学院";
    student->need_free = 0;
    ssms_insertStudent(student);
    student->name = "小明";
    student->sex = FEMALE;
    student->age = 16;
    student->major = "信息学院";
    ssms_insertStudent(student);
    student->major = "物电学院";
    ssms_updateStudent(student);
    student->name = "小1";
    ssms_insertStudent(student);
    student->name = "小2";
    ssms_insertStudent(student);
    student->name = "小3";
    ssms_insertStudent(student);
    student->name = "小4";
    ssms_insertStudent(student);
    student->name = "小5";
    ssms_insertStudent(student);
    student->name = "小6";
    ssms_insertStudent(student);
    student->name = "小7";
    ssms_insertStudent(student);
    student->name = "小8";
    ssms_insertStudent(student);
    student->name = "小9";
    ssms_insertStudent(student);
    student->name = "小10";
    ssms_insertStudent(student);
    student->name = "小11";
    ssms_insertStudent(student);
    student->name = "小12";
    ssms_insertStudent(student);
    student->name = "小13";
    ssms_insertStudent(student);
    student->name = "小14";
    ssms_insertStudent(student);
    student->name = "小15";
    ssms_insertStudent(student);
    student->name = "小16";
    ssms_insertStudent(student);
    student->name = "小17";
    ssms_insertStudent(student);
    student->name = "小18";
    ssms_insertStudent(student);
    student->name = "小19";
    ssms_insertStudent(student);
    student->name = "小20";
    ssms_insertStudent(student);
    student->name = "小21";
    ssms_insertStudent(student);
    student->name = "小22";
    ssms_insertStudent(student);
    student->name = "小23";
    ssms_insertStudent(student);
    student->name = "小24";
    ssms_insertStudent(student);
    student->name = "小25";
    ssms_insertStudent(student);
    ssms_freeStudentPtr(student);
    ssms_printStudentsFromDb();
    SSMS_STUDENT_PTR_VEC students = ssms_getAllStudents();
    ssms_dataprinter_printStudentPtrVec(students);
    ssms_freeStudentPtrVec(&students);
    ssms_deleteStudentByName("小张");
    ssms_printStudentsFromDb();
    student = ssms_getStudentByName("小明");
    ssms_dataprinter_printStudent(student);

    SSMS_SCORE_PTR score = ssms_newScore();
    score->student_id = student->id;
    score->score = 40.5;
    score->year = 2017;
    ssms_insertScore(score);
    SSMS_SCORE_PTR_VEC scores = ssms_getAllScoresOrderByScore();
    ssms_dataprinter_printScorePtrVec(scores);

    printf("平均成绩： %lf\n", ssms_getScoreAvg());
    printf("及格率： %lf%%\n",ssms_getScorePassPercent()*1e2);
    ssms_freeScorePtrVec(&scores);

    int *subsection = ssms_common_newIntArray(13);
    ssms_getScorePassSubsection(subsection);
    ssms_dataprinter_printScorePassSubsectionTable(subsection);
    free(subsection);

    ssms_freeStudentPtr(student);
    ssms_deleteStudents();
    ssms_closeDatabase();


    system("pause");
    return 0;
}