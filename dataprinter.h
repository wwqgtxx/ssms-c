/*
 **Copyright (c) wwqgtxx <wwqgtxx@gmail.com>
 */

#ifndef SSMS_DATAPRINTER_H
#define SSMS_DATAPRINTER_H

#include "dataoperator.h"

int ssms_dataprinter_printStudent(SSMS_STUDENT_PTR student);
int ssms_dataprinter_printStudentPtrVec(SSMS_STUDENT_PTR_VEC students);
int ssms_dataprinter_printScore(SSMS_SCORE_PTR score);
int ssms_dataprinter_printScorePtrVec(SSMS_SCORE_PTR_VEC scores);

#endif //SSMS_DATAPRINTER_H
