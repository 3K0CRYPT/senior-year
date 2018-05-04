
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Student.h"

using namespace std;

/* A GradeBook stores all the students, and provides loading/searching/reporting on them */
class GradeBook {
private:
    const static int NUM_STUDENTS = 10;  // number of lines in your data file
	Student students[NUM_STUDENTS];
	
public:
	bool LoadGrades(string fileName);
    int SearchId(int studentId);
    void PrintGradeReport(int studentId);
};
