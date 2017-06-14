/**
 * Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "common.h"
#include "dataoperator.h"
#include "console.h"

const char *sql_create_student_table = "CREATE TABLE IF NOT EXISTS STUDENT("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "NAME TEXT UNIQUE,"
        "SEX INTEGER,"
        "AGE INTEGER,"
        "MAJOR TEXT"
        ")";
const char *sql_insert_student_data = "INSERT INTO STUDENT(NAME,SEX,AGE,MAJOR) VALUES(?,?,?,?)";
const char *sql_select_student_data_by_name = "SELECT ID,NAME,SEX,AGE,MAJOR FROM STUDENT WHERE NAME=?";
const char *sql_select_student_data_by_id = "SELECT ID,NAME,SEX,AGE,MAJOR FROM STUDENT WHERE ID=?";
const char *sql_update_student_data = "UPDATE STUDENT SET NAME=?,SEX=?,AGE=?,MAJOR=? WHERE ID=?";
const char *sql_delete_student_data_by_name = "DELETE FROM STUDENT WHERE NAME=?";
const char *sql_delete_student_data_by_id = "DELETE FROM STUDENT WHERE ID=?";
const char *sql_select_all_student_data = "SELECT ID,NAME,SEX,AGE,MAJOR FROM STUDENT";
const char *sql_delete_all_student_data = "DELETE FROM STUDENT";

const char *sql_create_score_table = "CREATE TABLE IF NOT EXISTS SCORE("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "STUDENT_ID INTEGER,"
        "SCORE REAL,"
        "YEAR INTEGER"
        ")";
const char *sql_insert_score_data = "INSERT INTO SCORE(STUDENT_ID,SCORE,YEAR) VALUES(?,?,?)";
const char *sql_select_score_data = "SELECT A.ID,A.STUDENT_ID,A.SCORE,A.YEAR,B.NAME FROM SCORE AS A,STUDENT AS B WHERE A.STUDENT_ID=? AND A.YEAR=? AND B.ID=A.STUDENT_ID";
const char *sql_update_score_data = "UPDATE SCORE SET SCORE=?,YEAR=? WHERE ID=?";
const char *sql_delete_score_data = "DELETE FROM SCORE WHERE ID=?";
const char *sql_select_all_score_data = "SELECT A.ID,A.STUDENT_ID,A.SCORE,A.YEAR,B.NAME FROM SCORE AS A,STUDENT AS B WHERE B.ID=A.STUDENT_ID";
const char *sql_select_all_score_data_order_by_score = "SELECT A.ID,A.STUDENT_ID,A.SCORE,A.YEAR,B.NAME FROM SCORE AS A,STUDENT AS B WHERE B.ID=A.STUDENT_ID ORDER BY A.SCORE";
const char *sql_delete_all_score_data = "DELETE FROM SCORE";
const char *sql_select_score_avg_data = "SELECT AVG(SCORE) FROM SCORE";
const char *sql_select_score_pass_data = "SELECT SUM(CASE WHEN SCORE>=60 THEN 1.0 ELSE 0.0 END)/COUNT(*) FROM SCORE";
const char *sql_select_score_not_pass_name_data = "SELECT DISTINCT B.NAME FROM SCORE AS A,STUDENT AS B WHERE SCORE<60 AND B.ID=A.STUDENT_ID";
const char *sql_select_score_subsection_data = "select count(*),\n"
        "count(case SCORE when 100 then 1 end),\n"
        "count(case when SCORE between 90 and 99 then 1 end),\n"
        "count(case when SCORE between 80 and 89 then 1 end),\n"
        "count(case when SCORE between 70 and 79 then 1 end),\n"
        "count(case when SCORE between 60 and 69 then 1 end),\n"
        "count(case when SCORE between 50 and 59 then 1 end),\n"
        "count(case when SCORE between 40 and 49 then 1 end),\n"
        "count(case when SCORE between 30 and 39 then 1 end),\n"
        "count(case when SCORE between 20 and 29 then 1 end),\n"
        "count(case when SCORE between 10 and 19 then 1 end),\n"
        "count(case when SCORE between 1 and 9 then 1 end),\n"
        "count(case SCORE when 0 then 1 end) FROM SCORE";


sqlite3_stmt *insert_student_data_stmt;
sqlite3_stmt *select_student_data_by_name_stmt;
sqlite3_stmt *select_student_data_by_id_stmt;
sqlite3_stmt *update_student_data_stmt;
sqlite3_stmt *delete_student_data_by_name_stmt;
sqlite3_stmt *delete_student_data_by_id_stmt;
sqlite3_stmt *select_all_student_data_stmt;

sqlite3_stmt *insert_score_data_stmt;
sqlite3_stmt *select_score_data_stmt;
sqlite3_stmt *update_score_data_stmt;
sqlite3_stmt *delete_score_data_stmt;
sqlite3_stmt *select_all_score_data_order_by_score_stmt;
sqlite3_stmt *select_all_score_data_stmt;

sqlite3 *db = 0;
int ret = 0;
char *errmsg = 0;

int ssms_initDatabase() {
    ret = sqlite3_open("./sqlite3.db", &db);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "Cannot open db: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("Open database\n");
    return 0;
}

int ssms_closeDatabase() {
    sqlite3_finalize(insert_student_data_stmt);
    sqlite3_finalize(select_student_data_by_name_stmt);
    sqlite3_finalize(select_student_data_by_id_stmt);
    sqlite3_finalize(update_student_data_stmt);
    sqlite3_finalize(delete_student_data_by_name_stmt);
    sqlite3_finalize(delete_student_data_by_id_stmt);
    sqlite3_finalize(select_all_student_data_stmt);
    sqlite3_finalize(insert_score_data_stmt);
    sqlite3_finalize(select_score_data_stmt);
    sqlite3_finalize(update_score_data_stmt);
    sqlite3_finalize(delete_score_data_stmt);
    sqlite3_finalize(select_all_score_data_order_by_score_stmt);
    sqlite3_finalize(select_all_score_data_stmt);
    sqlite3_close(db);

    printf("Close database\n");
    return 0;
}

int ssms_initTable() {
    ret = sqlite3_exec(db, sql_create_student_table, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "create table fail: %s\n", errmsg);
        return 1;
    }
    sqlite3_free(errmsg);
    ret = sqlite3_exec(db, sql_create_score_table, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "create table fail: %s\n", errmsg);
        return 1;
    }
    sqlite3_free(errmsg);
    return 0;
}

int ssms_initStmt() {
    sqlite3_prepare_v2(db, sql_insert_student_data, -1, &insert_student_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_student_data_by_name, -1, &select_student_data_by_name_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_student_data_by_id, -1, &select_student_data_by_id_stmt, 0);
    sqlite3_prepare_v2(db, sql_update_student_data, -1, &update_student_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_delete_student_data_by_name, -1, &delete_student_data_by_name_stmt, 0);
    sqlite3_prepare_v2(db, sql_delete_student_data_by_id, -1, &delete_student_data_by_id_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_all_student_data, -1, &select_all_student_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_insert_score_data, -1, &insert_score_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_score_data, -1, &select_score_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_update_score_data, -1, &update_score_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_delete_score_data, -1, &delete_score_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_all_score_data, -1, &select_all_score_data_stmt, 0);
    sqlite3_prepare_v2(db, sql_select_all_score_data_order_by_score, -1, &select_all_score_data_order_by_score_stmt, 0);
    return 0;
}

SSMS_STUDENT_PTR ssms_newStudent() {
    return (SSMS_STUDENT *) malloc(sizeof(SSMS_STUDENT));
}

int ssms_freeStudentPtr(SSMS_STUDENT_PTR student) {
    if (student->need_free) {
        if (student->name != NULL) free(student->name);
        if (student->major != NULL) free(student->major);
    }
    free(student);
    return 0;
}

int ssms_freeStudentPtrVec(SSMS_STUDENT_PTR_VEC *students) {
    SSMS_STUDENT_PTR student;
    int i;
    vec_foreach(students, student, i) {
            ssms_freeStudentPtr(student);
        }
    vec_deinit(students);
    return 0;
}

int ssms_insertStudent(SSMS_STUDENT_PTR student) {
    sqlite3_reset(insert_student_data_stmt);

    sqlite3_bind_text(insert_student_data_stmt, 1, student->name, (int) strlen(student->name), NULL);
    sqlite3_bind_int(insert_student_data_stmt, 2, student->sex);
    sqlite3_bind_int(insert_student_data_stmt, 3, student->age);
    sqlite3_bind_text(insert_student_data_stmt, 4, student->major, (int) strlen(student->major), NULL);

    ret = sqlite3_step(insert_student_data_stmt);
    if (ret != SQLITE_DONE) {
        if (ret == SQLITE_CONSTRAINT) {
            fprintf(stderr, "Insert constraint check failed : %s \n", sqlite3_errmsg(db));
        } else {
            fprintf(stderr, "Insert failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        }

        return 1;
    }
    student->id = sqlite3_last_insert_rowid(db);
    return 0;
}

SSMS_STUDENT_PTR ssms_getStudentFromPreparedStmt(sqlite3_stmt *stmt) {
    if (ret == SQLITE_ROW) {
        SSMS_STUDENT *student = ssms_newStudent();
        student->id = sqlite3_column_int64(stmt, 0);
        student->name = ssms_common_strcpy((char *) sqlite3_column_text(stmt, 1));
        student->sex = (SSMS_SEX) sqlite3_column_int(stmt, 2);
        student->age = sqlite3_column_int(stmt, 3);
        student->major = ssms_common_strcpy((char *) sqlite3_column_text(stmt, 4));
        student->need_free = 1;
        return student;
    }
    return NULL;
}

SSMS_STUDENT_PTR ssms_getStudentByName(char *name) {
    sqlite3_reset(select_student_data_by_name_stmt);
    sqlite3_bind_text(select_student_data_by_name_stmt, 1, name, (int) strlen(name), NULL);
    ret = sqlite3_step(select_student_data_by_name_stmt);
    return ssms_getStudentFromPreparedStmt(select_student_data_by_name_stmt);
}

int ssms_checkStudentByName(char *name) {
    sqlite3_reset(select_student_data_by_name_stmt);
    sqlite3_bind_text(select_student_data_by_name_stmt, 1, name, (int) strlen(name), NULL);
    ret = sqlite3_step(select_student_data_by_name_stmt);
    return ret == SQLITE_ROW;
}

SSMS_STUDENT_PTR ssms_getStudentById(sqlite_int64 id) {
    sqlite3_reset(select_student_data_by_id_stmt);
    sqlite3_bind_int64(select_student_data_by_id_stmt, 1, id);
    ret = sqlite3_step(select_student_data_by_id_stmt);
    return ssms_getStudentFromPreparedStmt(select_student_data_by_id_stmt);
}

SSMS_STUDENT_PTR_VEC ssms_getStudentsPrtVecByStmt(sqlite3_stmt *stmt) {
    ret = sqlite3_step(stmt);
    SSMS_STUDENT_PTR_VEC students;
    SSMS_STUDENT_PTR student;
    vec_init(&students);
    while (ret == SQLITE_ROW) {
        student = ssms_getStudentFromPreparedStmt(stmt);
        vec_push(&students, student);
        ret = sqlite3_step(stmt);
    }
    return students;
}

SSMS_STUDENT_PTR_VEC ssms_getAllStudents() {
    sqlite3_reset(select_all_student_data_stmt);
    return ssms_getStudentsPrtVecByStmt(select_all_student_data_stmt);
}

int ssms_updateStudent(SSMS_STUDENT_PTR student) {
    sqlite3_reset(update_student_data_stmt);

    sqlite3_bind_text(update_student_data_stmt, 1, student->name, (int) strlen(student->name), NULL);
    sqlite3_bind_int(update_student_data_stmt, 2, student->sex);
    sqlite3_bind_int(update_student_data_stmt, 3, student->age);
    sqlite3_bind_text(update_student_data_stmt, 4, student->major, (int) strlen(student->major), NULL);
    sqlite3_bind_int64(update_student_data_stmt, 5, student->id);

    ret = sqlite3_step(update_student_data_stmt);
    if (ret != SQLITE_DONE) {
        fprintf(stderr, "Update failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        return 1;
    }
    printf("Update records num: %i\n", sqlite3_changes(db));
    return 0;
}

int ssms_deleteStudentByName(char *name) {
    sqlite3_reset(delete_student_data_by_name_stmt);

    sqlite3_bind_text(delete_student_data_by_name_stmt, 1, name, (int) strlen(name), NULL);

    ret = sqlite3_step(delete_student_data_by_name_stmt);
    if (ret != SQLITE_DONE) {
        fprintf(stderr, "Delete failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        return 1;
    }
    printf("Deleted records num: %i\n", sqlite3_changes(db));
    return 0;
}

int ssms_deleteStudentById(sqlite_int64 id) {
    sqlite3_reset(delete_student_data_by_id_stmt);

    sqlite3_bind_int64(delete_student_data_by_id_stmt, 1, id);

    ret = sqlite3_step(delete_student_data_by_id_stmt);
    if (ret != SQLITE_DONE) {
        fprintf(stderr, "Delete failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        return 1;
    }
    printf("Deleted records num: %i\n", sqlite3_changes(db));
    return 0;
}

int ssms_deleteStudent(SSMS_STUDENT_PTR student) {
    return ssms_deleteStudentById(student->id);
}

int ssms_deleteStudents() {
    ret = sqlite3_exec(db, sql_delete_all_student_data, NULL, NULL, &errmsg);
    printf("Delete records: %s\n", ret == SQLITE_OK ? "OK" : "FAIL");
    if (ret == SQLITE_OK) {
        printf("Deleted records num: %i\n", sqlite3_changes(db));
    }
    return 0;
}

int ssms_printStudentsFromDb() {
    char **db_result;
    int j, n_row, n_column, index;
    ret = sqlite3_get_table(db, sql_select_all_student_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        printf("query %i records.\n", n_row);
        index = n_column;
        for (int i = 0; i < n_row; i++) {
            printf("[%2i]", i);
            for (j = 0; j < n_column; j++) {
                printf(" %s", db_result[index]);
                index++;
            }
            printf("\n");
        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return 0;
}

int ssms_freeNamesVec(SSMS_NAMES_VEC *names) {
    char* name;
    int i;
    vec_foreach(names, name, i) {
            free(name);
        }
    vec_deinit(names);
    return 0;
}

SSMS_SCORE_PTR ssms_newScore() {
    return (SSMS_SCORE *) malloc(sizeof(SSMS_SCORE));
}

int ssms_freeScorePtr(SSMS_SCORE_PTR score) {
    if (score->need_free) {
        free(score->student_name);
    }
    free(score);
    return 0;
}

int ssms_freeScorePtrVec(SSMS_SCORE_PTR_VEC *scores) {
    SSMS_SCORE_PTR score;
    int i;
    vec_foreach(scores, score, i) {
            ssms_freeScorePtr(score);
        }
    vec_deinit(scores);
    return 0;
}

int ssms_insertScore(SSMS_SCORE_PTR score) {
    sqlite3_reset(insert_score_data_stmt);

    sqlite3_bind_int64(insert_score_data_stmt, 1, score->student_id);
    sqlite3_bind_double(insert_score_data_stmt, 2, score->score);
    sqlite3_bind_int(insert_score_data_stmt, 3, score->year);

    ret = sqlite3_step(insert_score_data_stmt);
    if (ret != SQLITE_DONE) {
        if (ret == SQLITE_CONSTRAINT) {
            fprintf(stderr, "Insert constraint check failed : %s \n", sqlite3_errmsg(db));
        } else {
            fprintf(stderr, "Insert failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        }

        return 1;
    }
    score->id = sqlite3_last_insert_rowid(db);
    return 0;
}

SSMS_SCORE_PTR ssms_getScoreFromPreparedStmt(sqlite3_stmt *stmt) {
    if (ret == SQLITE_ROW) {
        SSMS_SCORE_PTR score = ssms_newScore();
        score->id = sqlite3_column_int64(stmt, 0);
        score->student_id = sqlite3_column_int64(stmt, 1);
        score->score = sqlite3_column_double(stmt, 2);
        score->year = sqlite3_column_int(stmt, 3);
        score->student_name = ssms_common_strcpy((char *) sqlite3_column_text(stmt, 4));
        score->need_free = score->student_name != NULL;
        return score;
    }
    return NULL;
}

SSMS_SCORE_PTR ssms_getScore(sqlite_int64 student_id, int year) {
    sqlite3_reset(select_score_data_stmt);
    sqlite3_bind_int64(select_score_data_stmt, 1, student_id);
    sqlite3_bind_int(select_score_data_stmt, 2, year);
    ret = sqlite3_step(select_score_data_stmt);

    return ssms_getScoreFromPreparedStmt(select_score_data_stmt);
}

SSMS_SCORE_PTR_VEC ssms_getScorePrtVecByStmt(sqlite3_stmt *stmt) {
    ret = sqlite3_step(stmt);
    SSMS_SCORE_PTR_VEC scores;
    SSMS_SCORE_PTR score;
    vec_init(&scores);
    while (ret == SQLITE_ROW) {
        score = ssms_getScoreFromPreparedStmt(stmt);
        vec_push(&scores, score);
        ret = sqlite3_step(stmt);
    }
    return scores;
}

SSMS_SCORE_PTR_VEC ssms_getAllScores() {
    sqlite3_reset(select_all_score_data_stmt);
    return ssms_getScorePrtVecByStmt(select_all_score_data_stmt);
}

SSMS_SCORE_PTR_VEC ssms_getAllScoresOrderByScore() {
    sqlite3_reset(select_all_score_data_order_by_score_stmt);
    return ssms_getScorePrtVecByStmt(select_all_score_data_order_by_score_stmt);
}

int ssms_updateScore(SSMS_SCORE_PTR score) {
    sqlite3_reset(update_score_data_stmt);

    sqlite3_bind_double(update_score_data_stmt, 1, score->score);
    sqlite3_bind_int(update_score_data_stmt, 2, score->year);

    ret = sqlite3_step(update_score_data_stmt);
    if (ret != SQLITE_DONE) {
        fprintf(stderr, "Update failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        return 1;
    }
    printf("Update records num: %i\n", sqlite3_changes(db));
    return 0;
}

int ssms_deleteScoreById(sqlite_int64 id) {
    sqlite3_reset(delete_score_data_stmt);

    sqlite3_bind_int64(delete_score_data_stmt, 1, id);

    ret = sqlite3_step(delete_score_data_stmt);
    if (ret != SQLITE_DONE) {
        fprintf(stderr, "Delete failed : <%s> %s \n", sqlite3_errstr(ret), sqlite3_errmsg(db));
        return 1;
    }
    printf("Deleted records num: %i\n", sqlite3_changes(db));
    return 0;
}

int ssms_deleteScore(SSMS_SCORE_PTR score) {
    return ssms_deleteScoreById(score->student_id);
}


int ssms_deleteScores() {
    ret = sqlite3_exec(db, sql_delete_all_score_data, NULL, NULL, &errmsg);
    printf("Delete records: %s\n", ret == SQLITE_OK ? "OK" : "FAIL");
    if (ret == SQLITE_OK) {
        printf("Deleted records num: %i\n", sqlite3_changes(db));
    }
    return 0;
}

int ssms_printScoreFromDb() {
    char **db_result;
    int j, n_row, n_column, index;
    ret = sqlite3_get_table(db, sql_select_all_score_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        printf("query %i records.\n", n_row);
        index = n_column;
        for (int i = 0; i < n_row; i++) {
            printf("[%2i]", i);
            for (j = 0; j < n_column; j++) {
                printf(" %s", db_result[index]);
                index++;
            }
            printf("\n");
        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return 0;
}

double ssms_getScoreAvg() {
    char **db_result;
    int n_row, n_column, index;
    double result = 0;
    ret = sqlite3_get_table(db, sql_select_score_avg_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        if (n_column == 1 && n_row == 1) {
            index = n_column;
            result = atof(db_result[index]);
        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return result;
}

double ssms_getScorePassPercent() {
    char **db_result;
    int n_row, n_column, index;
    double result = 0;
    ret = sqlite3_get_table(db, sql_select_score_pass_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        if (n_column == 1 && n_row == 1) {
            index = n_column;
            result = atof(db_result[index]);
        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return result;
}

SSMS_NAMES_VEC ssms_getScoreNotPassNames() {
    SSMS_NAMES_VEC result;
    vec_init(&result);
    char **db_result;
    int n_row, n_column, index;
    ret = sqlite3_get_table(db, sql_select_score_not_pass_name_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        if (n_column == 1){
            index = n_column;
            for(int i=0;i<n_row;i++){
                vec_push(&result,ssms_common_strcpy(db_result[index]));
                index++;
            }
        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return result;
}

int ssms_getScorePassSubsection(int *subsection) {
    char **db_result;
    int n_row, n_column, index;
    ret = sqlite3_get_table(db, sql_select_score_subsection_data, &db_result, &n_row, &n_column, &errmsg);
    if (ret == SQLITE_OK) {
        if (n_column == 13 && n_row == 1) {
            index = n_column;
            for (int i = 12; i >= 0; i--) {
                subsection[i] = atoi(db_result[index]);
                index++;
            }

        }
    }
    sqlite3_free_table(db_result);
    sqlite3_free(errmsg);
    return 0;
}