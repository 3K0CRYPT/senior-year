
#include "Student.h"

// These constants are used only within this CPP, so we don't need to place them in the header
const int MAX_SCORES[6] = { 25, 10, 100, 200, 200, 200 };  // HW, Quiz, Final Proj, 2 Mid-terms, Final Exam
const double WEIGHTS[6] = { .3, .12, .1, .15, .15, .18};
const string GRADE_MAP[12] = { "F", "D-", "D", "D+", "C-", "C", "C+", "B-", "B", "B+", "A-", "A"};

/* Convert a grade percentage into the +/- grading scale */
string GradeLetter(double finalGrade) {
    if(finalGrade < 60)
        return GRADE_MAP[0];
    else
        return GRADE_MAP[(int)((finalGrade - 60) / 10. * 3) + 1];
}

/* Extract a single field from a delimeted format, and remove that field
 * from the input. This can be used to consume CSV fields from a line.
 * The field is erased so that the function can be re-called on the same
 * input variable.
 */
void Split(string& str, const string& delimiter, string& field) {
    short pos = str.find(delimiter);
    if(pos == string::npos) {
        field = str;
    } else {
        field = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
    }
}

// Given a line from the file, initialize this student
void Student::InitFromLine(string line) {
    // TODO: Started mocking up the use of the Split function, but didn't get to storing anything

    string field;
    // id
    Split(line, ",", field);    // get string ID in line (data until 1st comma)
    id = stoi(field);
	
    // name
    Split(line, ",", field);    // get name in line (data until next comma)
    name = field;

    // Extract the grades
    for (int j = 0; j < NUM_HOMEWORKS; ++j) {
        Split(line, ",", field);   // get next grade (data until next comma)
		grades[j] = stoi(field);
    }

    for (int j = 0; j < NUM_QUIZZES; ++j) {
        Split(line, ",", field);   // get next grade (data until next comma)
		grades[j+NUM_HOMEWORKS] = stoi(field);
    }

    for (int j = 0; j < NUM_TESTS; ++j) {
        Split(line, ",", field);   // get next grade (data until next comma)
		grades[j + NUM_HOMEWORKS + NUM_QUIZZES] = stoi(field);
    }

}

void Student::PrintGrades() {
    // TODO: This function was copied from the original solution, but it needs to be
    // adapted to our new solution
	cout << "Grade Report for " << id << " - " << name << endl;

    cout << "Homeworks = { ";
    int sumHwk = 0;
    for(int i = 0; i < NUM_HOMEWORKS; i++)
    {
        cout << grades[i] << " ";
        sumHwk += grades[i];
    }
    cout << "} = " << sumHwk << endl;

    cout << "Quiz = { ";
    int sumQuiz = 0;
    for(int i = NUM_HOMEWORKS; i < NUM_HOMEWORKS + NUM_QUIZZES; i++)
    {
        cout << grades[i] << " ";
        sumQuiz += grades[i];
    }
    cout << "} = " << sumQuiz << endl;

    cout << "Final project = { " << grades[15] << " }" <<endl;

    cout << "Midterms: { " << grades[16] << " " << grades[17] << " }" << endl;

    cout << "Final exam = { " << grades[18] << " }" << endl;

    cout << "Final grade = " << endl;
    cout << '\t' << (double)sumHwk << " / " << (NUM_HOMEWORKS *MAX_SCORES[0]) 
        << " * " << (WEIGHTS[0] * 100) << " + " << endl;
    cout << '\t' << (double)sumQuiz << " / " << (NUM_QUIZZES * MAX_SCORES[1]) 
        << " * " << (WEIGHTS[1] * 100) << " + " << endl;
	cout << '\t' << (double)grades[15] << " / " << MAX_SCORES[2] << " * "
		<< (WEIGHTS[2] * 100) << " + " << endl;
	cout << '\t' << (double)grades[16] << " / " << MAX_SCORES[3] << " * "
		<< (WEIGHTS[3] * 100) << " + " << endl;
	cout << '\t' << (double)grades[17] << " / " << MAX_SCORES[4] << " * "
		<< (WEIGHTS[4] * 100) << " + " << endl;
	cout << '\t' << (double)grades[18] << " / " << MAX_SCORES[5] << " * "
		<< (WEIGHTS[5] * 100) << " = ";
    double finalGrade = 
		(double)sumHwk / (NUM_HOMEWORKS * MAX_SCORES[0]) * WEIGHTS[0] * 100 +
		(double)sumQuiz / (NUM_QUIZZES * MAX_SCORES[1]) * WEIGHTS[1] * 100 +
		(double)grades[15] / MAX_SCORES[2] * WEIGHTS[2] * 100 +
		(double)grades[16] / MAX_SCORES[3] * WEIGHTS[3] * 100 +
		(double)grades[17] / MAX_SCORES[4] * WEIGHTS[4] * 100 +
		(double)grades[18] / MAX_SCORES[5] * WEIGHTS[5] * 100;
    cout << finalGrade << endl;
    cout << "Letter grade: " << GradeLetter(finalGrade) << endl << endl;
	}

int Student::getID() {
	return id;
}