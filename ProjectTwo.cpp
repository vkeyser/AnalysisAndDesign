//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Victoria Keyser
// Date        : February 21, 2024
// Description : Hash table in C++ for ABCU Advising Team
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// define a structure for the course
struct Course {
	string courseNumber;
	string courseTitle;
	// stores prerequisites for the course
	vector<string> prerequisites; 

	// constructors
	Course() {} 
	Course(string number, string title) : courseNumber(number), courseTitle(title) {}
}; // end Course

// define a class containing data members and methods to implement a hash table with chaining
class HashTable {
private:
	// hash table to store courses
	unordered_map<string, Course> courses; 

	// hash function
	size_t hash(string key) {
		// hash function based on length of key
		return key.length(); 
	}

public:
	// constructor
	HashTable() {}

	// insert a course into the hash table
	void Insert(Course course) {
		// insert course with its number as the key
		courses[course.courseNumber] = course; 
	} // end Insert

	// retrieve course information given its number
	Course CourseInformation(string courseNumber) {
		auto courseIterator = courses.find(courseNumber);
		if (courseIterator != courses.end()) {
			// return course information if found
			return courseIterator->second;
		} // end if
		else {
			// return empty course if not found
			return Course();
		} // end else
	} // end CourseInformation

	// function to print all courses in sorted order
	void PrintSampleSchedule() {
		cout << "Course List" << endl;
		vector < pair<string, string>> sortedCourses;
		for (const auto& pair : courses) {
			sortedCourses.push_back({ pair.second.courseNumber, pair.second.courseTitle });
		} // end for

		sort(sortedCourses.begin(), sortedCourses.end());

		for (const auto& course : sortedCourses) {
			cout << course.first << ": " << course.second << endl;
		} // end for
	} // end PrintSampleSchedule

	// functions to search and print course prerequisites
	void PrintCourseInformation(string courseNumber) {

		auto courseIterator = courses.find(courseNumber);
		if (courseIterator != courses.end()) {
			Course& course = courseIterator->second;
			cout << course.courseNumber << ": " << course.courseTitle << endl;


			int numPrereqs = course.prerequisites.size();
			if (numPrereqs > 0) {
				if (numPrereqs == 1) {
					cout << "Prerequisite: ";
				}
				else {
					cout << "Prerequisites: ";
				}
				for (size_t i = 0; i < numPrereqs; ++i) {
					cout << course.prerequisites[i];
					if (i < numPrereqs - 1) {
						cout << ", ";
					} // end if
					else {
						cout << endl;
					} // end else
				} // end for
			} // end if
			else {
				cout << "No prerequisites" << endl;
			} // end else
		} // end if
		else {
			cout << "Course not found" << endl;
		} // end else
	} // end PrintCourseInformation

	// function to count the number of prerequisite courses for a given course
	int NumPrerequisiteCourses(string courseNumber) {
		auto courseIterator = courses.find(courseNumber);
		if (courseIterator != courses.end()) {
			return courseIterator->second.prerequisites.size();
		} // end if
		else {
			return -1;
		} // end else
	} // end NumPrerequisiteCourses
}; // end HashTable

// function to read course data from a file and populate the hashtable
void readCourseDataFromFile(string filePath, HashTable& hashTable) {
	ifstream file(filePath);
	// if file does not open, print error message
	if (!file.is_open()) {
		cout << "Error opening file: " << filePath << endl;
		return;
	} // end if

	string line;
	// parse eachline into course number, title, and prerequisites, if any
	while (getline(file, line)) {
		stringstream ss(line);
		string courseNumber, courseTitle, prereq;
		getline(ss, courseNumber, ',');
		getline(ss, courseTitle, ',');
		Course course(courseNumber, courseTitle);
		while (getline(ss, prereq, ',')) {
			// add prerequisires to the course
			course.prerequisites.push_back(prereq);
		} // end while
		// insert the course into the hashtable
		hashTable.Insert(course);
	} // end while
	file.close();
} // end readCourseDataFromFile

int main() {
	HashTable hashTable;

	// file path given
	string filePath = "ABCU_Advising_Program_Input.txt";

	// user choice initalization
	int choice = 0;
	
	// initialize valid input from user
	bool validInput = false;

	// to search for course information
	string courseNumber;

	// main menu loop
	while (!validInput) {
		// cout << endl;
		cout << "Main Menu" << endl;
		cout << "1. Load Data Structure" << endl;
		cout << "2. Print Course List" << endl;
		cout << "3. Print Course" << endl;
		cout << "9: Exit" << endl;
		cout << endl;
		cout << "Enter menu option: ";
		cin >> choice;

		switch (choice) {
		case 1:
			// load data from file into hashtable
			readCourseDataFromFile(filePath, hashTable);
			cout << "Data loadded into Hashtable" << endl;
			cout << endl;
			break;
		case 2:
			cout << endl;
			// print all courses in sorted order
			hashTable.PrintSampleSchedule();
			cout << endl;
			break;
		case 3:
			cout << "Enter course number: ";
			cin >> courseNumber;
			cout << endl;
			// print course information including prerequisites
			hashTable.PrintCourseInformation(courseNumber);
			cout << endl;
			break;
		case 9:
			cout << "Goodbye" << endl;
			// exit the program
			return 0;
		default:
			// invalid choice, prompt user again
			validInput = true;
			cout << choice << " is not a valid choice. Please try again" << endl;
			cout << endl;
		} // end switch
	} // end while
	return 0;
} // end main