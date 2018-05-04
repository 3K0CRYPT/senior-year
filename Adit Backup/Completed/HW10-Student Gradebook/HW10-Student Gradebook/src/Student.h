
#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    const static int NUM_HOMEWORKS = 10;
    const static int NUM_QUIZZES = 5;
    const static int NUM_TESTS = 4;    // Final Proj + 2 Mid-terms + Final Exam
    const static int NUM_GRADES = NUM_HOMEWORKS + NUM_QUIZZES + NUM_TESTS;
	int id;
	string name;
	int grades[NUM_GRADES];
    
public:
	void PrintGrades();
    void InitFromLine(string line);
	int getID();
};
