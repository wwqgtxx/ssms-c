/*
 **Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#ifndef SSMS_DATAPRINTER_H
#define SSMS_DATAPRINTER_H

#include "dataoperator.h"

typedef int SSMS_DATAPRINTER_PRINTSTUDENTPRTVEC_CALLBACK(SSMS_STUDENT_PTR student);
typedef int SSMS_DATAPRINTER_PRINTSCOREPRTVEC_CALLBACK(SSMS_SCORE_PTR score);


int ssms_dataprinter_printStudent(SSMS_STUDENT_PTR student);
int ssms_dataprinter_printStudentPtrVecWithSelectCallback(SSMS_STUDENT_PTR_VEC students,SSMS_DATAPRINTER_PRINTSTUDENTPRTVEC_CALLBACK callback);
int ssms_dataprinter_printStudentPtrVec(SSMS_STUDENT_PTR_VEC students);
int ssms_dataprinter_printScore(SSMS_SCORE_PTR score);
int ssms_dataprinter_printScorePtrVecWithSelectCallback(SSMS_SCORE_PTR_VEC scores,SSMS_DATAPRINTER_PRINTSCOREPRTVEC_CALLBACK callback);
int ssms_dataprinter_printScorePtrVec(SSMS_SCORE_PTR_VEC scores);
int ssms_datapainter_printScorePassSubsectionTable(int *subsection);
int ssms_datapainter_printScorePassSubsectionGraph(int *subsection);

#endif //SSMS_DATAPRINTER_H
