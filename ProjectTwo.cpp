/*
**Author:			Tammy Hartline
* Date/Version:		04/14/2023
* Course:			CS-300 SNHU GC
* Description:		Week 7 Final Project (Project 2)
* Instructor:		m.susalla@snhu.edu
*/


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;
using std::cout;
using std::cin;
//Create menu to display on screen with selection choices
void menuDisplay() {

	cout << "*************************" << endl;
	cout << "1. Load course file data" << endl;
	cout << "2. Print all courses" << endl;
	cout << "3. Course search" << endl;
	cout << "9. Exit program" << endl;
	cout << "*************************" << endl;

}

//Create stucture to hold and call for course info.
struct Course {

	string courseNum;
	string courseName;
	vector<string> coursePrereq;

};

//Create structure for tree nodes
struct Node {

	Course course;
	Node* right;
	Node* left;

	//Create default constructor
	Node() {
		
		right = nullptr;
		left = nullptr;
	}

	//Initialize Node with Course
	Node(Course aCourse) : 
		
		Node() {

		this->course = aCourse;

	}

};

//Create class to contain data members and methods to initialize bst
class BST {

private:

	//Create destructor
	void Destructor(Node* node);

public:

	Node* root;
	BST();
	virtual ~BST();
	void Insertion(BST* tree, Node* node);
	void Search(string courseNum);
	void PrintAll(Node* node);

};

//Create default constructor
BST::BST() {

	root = nullptr;

};

//Create destructor
BST::~BST() {

	Destructor(root);

};

//Create destructor to delete right and left pointer nodes
void BST::Destructor(Node* node) {

	if (node != nullptr) {

		Destructor(node->right);
		node->right = nullptr;

		Destructor(node->left);
		node->left = nullptr;
		delete node;

	}
};

//create for search
void BST::Search(string courseNum) {

	Node* currentNode = root;

	//while current node is not equal to null pointer
	while (currentNode != nullptr) {

		//if current nodes course number is equal to course number
		if (currentNode->course.courseNum == courseNum) {

			//Output courseNum, courseName, and coursePrereqs if they exist
			cout << currentNode->course.courseNum << " | "
				<< currentNode->course.courseName << " | "
				<< endl << "Prerequisites: "
				<< endl;

			//print prereqs if they exist below the lines above
			for (string coursePrereq : currentNode->course.coursePrereq) {

				//check how many prereqs exist
				if (coursePrereq == currentNode->course.coursePrereq.back()) {

					cout << coursePrereq << endl;

				}

				else {

					cout << coursePrereq << endl;

				}

			}

		
			return;

		}
		
		//if left pointer is not found
		else if (courseNum < currentNode->course.courseNum) {

			if (currentNode->left != nullptr) {

				currentNode = currentNode->left;

			}
		}

		//next if right pointer is not found
		else {

			currentNode = currentNode->right;

		}
	}

	//When pointers are not found
	Destructor(currentNode);
	cout << "You entered " << courseNum << ". Sorry, that course is currently unavailable as it is not in the course list." << endl;
	return;

}

//finish insert to insert leaf into root
void BST::Insertion(BST* tree, Node* node) {

	//if tree root points to null
	if (tree->root == nullptr) {

		tree->root = node;

	}

	//else set new node to tree root
	else {

		Node* current = tree->root;

		//while current is not equal to nullptr
		while (current != nullptr) {

			if (node->course.courseNum < current->course.courseNum) {

				if (current->left == nullptr) {

					current->left = node;
					current = nullptr;

				}

				else {

					current = current->left;

				}

			}

			else {

				if (current->right == nullptr) {

					current->right = node;
					current = nullptr;

				}

				else {

					current = current->right;

				}
			}
		}
	}
}

//finish print all
void BST::PrintAll(Node* node) {

	//traverse and print all courses in tree
	if (node == nullptr) {

		return;

	}

	//check nodes one at a time, iterating through file, to print courseNum and Name
	PrintAll(node->left);

	cout << node->course.courseNum << " | "
		<< node->course.courseName << endl;

	PrintAll(node->right);
};

//Use fstream to load and process file content
void loadFile(string fileName, BST* bst) {

	cout << "Please enter file name: " << endl;
	cin >> fileName;

	ifstream file(fileName);
	if (file.is_open()) {

		cout << "Your file loaded successfully." << endl;

		int numb;
		string readLine;
		string getWord;

		while (getline(file, readLine)) {

			numb = 0;
			Node* node = new Node();
			stringstream str(readLine);

		//check for at least 2 objects
		while (numb < 2) {

			getline(str, getWord, ',');

			if (numb == 0) {

				node->course.courseNum = getWord;

			}

			else {

				node->course.courseName = getWord;

			}

			numb++;

		}

		while (getline(str, getWord, ',')) {

			node->course.coursePrereq.push_back(getWord);

		}

		//Insert into search tree
		bst->Insertion(bst, node);

		}
	}

	//output error
	else {

		cout << "Sorry, an error occured because the file was not found." << endl;
		return;

	}

}

//Main

void main() {

	BST* bst = new BST();

	string chooseFile;
	string chooseCourse;
	int userIn = 0;

	while (userIn != 9) {

		//output message to user
		cout << "Welcome to Tammy Hartline's Course Planner!" << endl;

		//call menu
		menuDisplay();

		cout << "Enter your menu selection: " << endl;

		cin >> userIn;

			//create switch to handle program based on user entry
			switch (userIn) {

				//case 1 is load file
			case 1:

				cout << "You selected load file." << endl
					<< "The default file name is ABCU_Advising_Program_Input.csv"
					<< endl;

				//call file loading function
				loadFile(chooseFile, bst);
				cout << endl << endl;
				break;

				//case 2 is print all course information
			case 2:

				cout << endl;
				cout << "*********************************************" << endl;
				cout << "**   Course Number  ******   Course Name   **" << endl;
				cout << "*********************************************" << endl;
				cout << "=============================================" << endl;

				//call print all function and set to start at root to print in alphanumeric order
				bst->PrintAll(bst->root);
				cout << "=============================================" << endl;

				break;

				//case 3 output course if it matches user input for search
			case 3:

				cout << endl;
				cout << "Enter the course name you would like to search for: " << endl;
				
				cin >> chooseCourse;
				cout << endl << endl;
				bst->Search(chooseCourse);
				cout << endl << endl;
				

				//iterate search through file to check if course exists in file
				std::transform(chooseCourse.begin(), chooseCourse.end(), chooseCourse.begin(), ::toupper);
				cout << endl << endl;
				break;

				//case 9, user selects 9, then exit program
			case 9:

				cout << "You have selected Exit Program."
					<< endl << "Thank you for using Tammy Hartline's Course Planner!"
					<< "Good-bye" << endl;

				return;

			//set default
			default:
			
				//handle incorrect menu input
				cout << "Only numeric input of 1, 2, 3, or 9 is allowed."
				<< endl << "Please enter a valid menu option: " << endl;
				break;

			}
		}
	}
