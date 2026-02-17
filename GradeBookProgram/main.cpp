#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int TESTCOUNT = 5;

void readGradeData(string, string[], int[][TESTCOUNT]);

void getAverageScores(const int[][TESTCOUNT], double[]);

void getLetterGrades(const double[], char[]);

void displayReport(const string[], const double[], const char[]);

int main()
{
    // Variables
    string studentNames[20];

    int testScores[20][TESTCOUNT];
    double averageScores[20];

    char letterGrades[20];

    // Main procedure
    readGradeData("StudentGrades.txt", studentNames, testScores); // student names and raw test scores extracted

    getAverageScores(testScores, averageScores); // test scores turned to averages for each student

    getLetterGrades(averageScores, letterGrades); // average scores turned into letter grades

    displayReport(studentNames, averageScores, letterGrades);

    return 0;
}

/*
    Summary: Opens a file of a specified name, moving string data into a 1-dimensional array and integer data into a 2-dimensional one. Processes grade data from the file.
    Parameters: fileName, a string which holds the name of the file holding data, names[], the array for student names, and grades[][], the integer array for test scores belonging to each student.
    Return: None.
    Preconditions: Libraries <fstream> and <sstream> are used. data file must be arranged properly, TESTCOUNT must be accurate, and both arrays should be large enough in size for data.
    Postconditions: The referenced arrays will be filled with data from the file being read, their contents changed in the calling function.
*/
void readGradeData(string fileName, string names[], int grades[][TESTCOUNT])
{
    string dataLine;

    ifstream gradeList(fileName);

    if (gradeList)
    {
        int i = 0;

        while(getline(gradeList, dataLine))
        {
            int j = 0;

            stringstream ss(dataLine);

            ss >> names[i]; // First extracts the name

            while (ss >> grades[i][j]) // Then extracts each grade, adapting to however many tests there are
            {
                j++;
            }

            i++;
        }
    }
    else
    {
        cout << "ERROR: File " << fileName << " does not exist.\n";
        exit(1);
    }

    gradeList.close();
}

/*
    Summary: Takes an average of all test scores, condensing a 2D array of raw scores into a single dimension of averages which run parallel.
    Parameters: A constant integer 2D array of scores, rawScores[][], then an integer array of average scores, averages[].
    Return: None.
    Preconditions: rawScores[][] must be already filled or partially filled with real, valid data.
    Postconditions: averages[] will be filled with data and updated in calling function, given that it functions as a reference.
*/
void getAverageScores(const int rawScores[][TESTCOUNT], double averages[])
{
    for (int i = 0; i < 20; i++) // 20 indices horizontally for all arrays in program
    {
        int scoreTotal = 0;

        for (int j = 0; j < TESTCOUNT; j++) // Goes through all test scores for a given student
        {
            scoreTotal += rawScores[i][j];
        }

        averages[i] = (float(scoreTotal) / float(TESTCOUNT)); // trying to prevent integer division
    }
}

/*
    Summary: Turns the average of test grades from one array into letter grades depending on what range they fall into.
    Parameters: constant int array grades[], holding the number average grades, and character array letters[], which holds the character of a given letter grade.
    Return: None.
    Preconditions: grades[] should contain valid data, letters[] should be empty.
    Postconditions: letters[] is updated with a character for each item in grades[]. However, any which are by default 0 will be assigned an 'F'.
*/
void getLetterGrades(const double grades[], char letters[])
{
    for (int i = 0; i < 20; i++) // For each of up to 20 students
    {
        if (grades[i] >= 90)
        {
            letters[i] = 'A';
        }
        else if (grades[i] >= 80)
        {
            letters[i] = 'B';
        }
        else if (grades[i] >= 70)
        {
            letters[i] = 'C';
        }
        else if (grades[i] >= 60)
        {
            letters[i] = 'D';
        }
        else
        {
            letters[i] = 'F';
        }
    }
}

/*
    Summary: Displays a report which makes a table showing the names of students, their average scores, and the resulting letter grade.
    Parameters: names[], which holds student names, scores[], which holds average scores for each student, and grades[], which holds letter grades for each student and score. All are constant.
    Return: None.
    Preconditions: All arrays passed in contain valid data, <iomanip> is used.
    Postconditions: cout is used to print a report to console.
*/
void displayReport(const string names[], const double scores[], const char grades[])
{
    for (int i = 0; i < 20; i++) // Goes through 20 indices for all parallel arrays
    {
        if (names[i] > "") // If an actual name exists for a given index
        {
            cout << left << setw(15) << names[i] << setw(10) << scores[i] << setw(5) << grades[i] << endl; // A row in the table is printed
        }
    }
}
