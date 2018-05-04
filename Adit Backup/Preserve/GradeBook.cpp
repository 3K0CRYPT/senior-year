#include "GradeBook.h"

/* Load student information from a file into our Student objects */
bool GradeBook::LoadGrades(string fileName) {
    ifstream dataFile(fileName);
    if(!dataFile)
        return false;

    string line;
    for(int i = 0; i < NUM_STUDENTS && !dataFile.eof(); i++) {
        getline(dataFile, line);
        students[i].InitFromLine(line);
    }
    dataFile.close();
    return true;
}

int GradeBook::SearchId(int studentId){
	for (int i = 0; i < NUM_STUDENTS; i++)	{
		if (studentId == students[i].getID()){ return i; }
	}
	return -1;
}

void GradeBook::PrintGradeReport(int studentId){
	students[studentId].PrintGrades();
}
