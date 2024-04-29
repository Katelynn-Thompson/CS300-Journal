#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Define a Course struct
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Global variable to store course data
unordered_map<string, Course> courseData;

// Function prototypes
void displayMenu();
void loadDataStructure();
void printCourseList();
void printCourseInformation();
void exitProgram();
void printCourseInfo(const Course& course);
void sortAndPrintAlphanumeric();

int main() {
    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataStructure();
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            printCourseInformation();
            break;
        case 4:
            exitProgram();
            return 0;
        default:
            cout << "Error: Invalid choice. Please choose a valid option." << endl;
            break;
        }
    }
}

// Display the menu options
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "4. Exit" << endl;
}

// Load course data from the file into the hash table
void loadDataStructure() {
    ifstream file("text.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    courseData.clear(); // Clear existing data

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string courseNumber, courseTitle, prerequisite;
        iss >> courseNumber >> courseTitle;

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        // Read prerequisites
        while (iss >> prerequisite) {
            course.prerequisites.push_back(prerequisite);
        }

        // Add new course to the hash table
        courseData[courseNumber] = course;
    }

    cout << "Data loaded successfully." << endl;
}

// Prints list of courses in alphabetical order
void printCourseList() {
    if (courseData.empty()) {
        cout << "Error: Data structure not loaded. Please load data first." << endl;
        return;
    }

    sortAndPrintAlphanumeric();
}

// Course information printing
void printCourseInformation() {
    if (courseData.empty()) {
        cout << "Error: Data structure not loaded. Please load data first." << endl;
        return;
    }

    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    auto it = courseData.find(courseNumber);
    if (it == courseData.end()) {
        cout << "Error: Course not found." << endl;
    }
    else {
        printCourseInfo(it->second);
    }
}

// Exit the program
void exitProgram() {
    cout << "Closing course planner, thank you for using!" << endl;
}

// Prints info about a specific course
void printCourseInfo(const Course& course) {
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Title: " << course.courseTitle << endl;
    cout << "Prerequisites:" << endl;
    if (course.prerequisites.empty()) {
        cout << "No prerequisites" << endl;
    }
    else {
        for (const auto& prereq : course.prerequisites) {
            cout << "- " << prereq << endl;
        }
    }
}

// Sorts and prints the list of courses in alphanumeric order
void sortAndPrintAlphanumeric() {
    vector<Course> sortedCourses;
    for (const auto& pair : courseData) {
        sortedCourses.push_back(pair.second);
    }

    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber; // Sort by course number
        });

    cout << "Alphanumeric Course List:" << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << " - " << course.courseTitle << endl;
    }
}


