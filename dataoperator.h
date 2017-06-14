/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#ifndef SSMS_DATAOPERATOR_H
#define SSMS_DATAOPERATOR_H


#include "sqlite3.h"
#include "vec.h"
typedef enum {MALE,FEMALE} SSMS_SEX;

typedef struct {
    sqlite_int64 id;
    char* name;
    SSMS_SEX sex;
    int age;
    char* major;
    int need_free;
} SSMS_STUDENT;

typedef SSMS_STUDENT* SSMS_STUDENT_PTR;
typedef vec_t(SSMS_STUDENT_PTR) SSMS_STUDENT_PTR_VEC;

typedef struct {
    sqlite_int64 id;
    sqlite_int64 student_id;
    double score;
    int year;
    char* student_name;
    int need_free;
} SSMS_SCORE;

typedef SSMS_SCORE* SSMS_SCORE_PTR;
typedef vec_t(SSMS_SCORE_PTR) SSMS_SCORE_PTR_VEC;


int ssms_initDatabase();
int ssms_closeDatabase();
int ssms_initTable();
int ssms_initStmt();
SSMS_STUDENT_PTR ssms_newStudent();
int ssms_freeStudentPtr(SSMS_STUDENT* student);
int ssms_freeStudentPtrVec(SSMS_STUDENT_PTR_VEC *students);
int ssms_insertStudent(SSMS_STUDENT *student);
int ssms_deleteStudentByName(char *name);
int ssms_deleteStudentById(sqlite_int64 id);
int ssms_deleteStudent(SSMS_STUDENT_PTR student);
SSMS_STUDENT_PTR ssms_getStudentFromPreparedStmt(sqlite3_stmt *stmt);
SSMS_STUDENT_PTR ssms_getStudentByName(char *name);
int ssms_checkStudentByName(char *name);
SSMS_STUDENT_PTR ssms_getStudentById(sqlite_int64 id);
SSMS_STUDENT_PTR_VEC ssms_getStudentsPrtVecByStmt(sqlite3_stmt* stmt);
SSMS_STUDENT_PTR_VEC ssms_getAllStudents();
int ssms_updateStudent(SSMS_STUDENT *student);
int ssms_deleteStudents();
int ssms_printStudentsFromDb();

typedef vec_t(char*) SSMS_NAMES_VEC;
int ssms_freeNamesVec(SSMS_NAMES_VEC *names);

SSMS_SCORE_PTR ssms_newScore();
int ssms_freeScorePtr(SSMS_SCORE_PTR score);
int ssms_freeScorePtrVec(SSMS_SCORE_PTR_VEC *scores);
int ssms_insertScore(SSMS_SCORE_PTR score);
SSMS_SCORE_PTR ssms_getScoreFromPreparedStmt(sqlite3_stmt *stmt);
SSMS_SCORE_PTR ssms_getScore(sqlite_int64 student_id, int year);
SSMS_SCORE_PTR_VEC ssms_getScorePrtVecByStmt(sqlite3_stmt *stmt);
SSMS_SCORE_PTR_VEC ssms_getAllScoresOrderByScore();
SSMS_SCORE_PTR_VEC ssms_getAllScores();
int ssms_updateScore(SSMS_SCORE_PTR score);
int ssms_deleteScore(sqlite_int64 id);
int ssms_deleteScores();
int ssms_printScoreFromDb();
double ssms_getScoreAvg();
double ssms_getScorePassPercent();
SSMS_NAMES_VEC ssms_getScoreNotPassNames();
int ssms_getScorePassSubsection(int *subsection);


#endif //SSMS_DATAOPERATOR_H
