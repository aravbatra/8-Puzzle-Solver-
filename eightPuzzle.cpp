#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <stdexcept>
#include "eightPuzzle.h"

using namespace std;

// constructor
puzzle::puzzle()
{
	//root = NULL;
}

// Uses default puzzle or takes user input
void puzzle::generatePuzzle(int x){
	path* p = new path;
	p->child1 = NULL;
	p->child2 = NULL;
	p->child3 = NULL;
	p->child4 = NULL;

	goalState = false;
	totalNodes = 0;
	nodesInQueue = 0;

	if(x == 1){
		// pre-set puzzle
		// 1 2 3
		// 4 8 0
		// 7 6 5
		cout << "Default puzzle is " << endl;
		vector<char> vec1;
		vec1.push_back('1');
		vec1.push_back('2');
		vec1.push_back('3');
		vector<char> vec2;
		vec2.push_back('4');
		vec2.push_back('8');
		vec2.push_back('0');
		vector<char> vec3;
		vec3.push_back('7');
		vec3.push_back('6');
		vec3.push_back('5');

		p->puzzle.push_back(vec1);
		p->puzzle.push_back(vec2);
		p->puzzle.push_back(vec3);

		rootNode = p;
		prevStates.push_back(rootNode->puzzle);
		//TODO: add displayPuzzle
		//displayPuzzle(rootNode);


	}
	else if(x == 2){
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		char val1, val2, val3;
		vector<char> row1, row2, row3;

		cout << "Enter the first row. Use space or tabs between numbers." << endl;
	  cin >> val1 >> val2 >> val3;
		row1.push_back(val1);
		row1.push_back(val2);
		row1.push_back(val3);

		cout << "Enter the second row. Use space or tabs between numbers." << endl;
	  cin >> val1 >> val2 >> val3;
		row2.push_back(val1);
		row2.push_back(val2);
		row2.push_back(val3);

		cout << "Enter the third row. Use space or tabs between numbers." << endl;
	  cin >> val1 >> val2 >> val3;
		row3.push_back(val1);
		row3.push_back(val2);
		row3.push_back(val3);

		cout << "Your puzzle is " << endl;
		//TODO: add displayPuzzle
		//displayPuzzle(rootNode);
		rootNode = p;
		prevStates.push_back(rootNode->puzzle);

	}
	else{
		 throw std::invalid_argument( "received invalid value" );
	}

}
// makes sure the user inputs 1, 2, or 3 to select algorithm
// also returns if root is NULL or the user input puzzle is not valid
void puzzle::algorithmSelect(int x)
{

}
