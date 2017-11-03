#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <stdexcept>
//#include <stddef.h>
#include "eightPuzzle.h"

using namespace std;

// constructor
puzzle::puzzle()
{
	rootNode = NULL;
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
		vector<char> row1, row2, row3;
		row1.push_back('1');
		row1.push_back('2');
		row1.push_back('3');

		row2.push_back('4');
		row2.push_back('8');
		row2.push_back('0');

		row3.push_back('7');
		row3.push_back('6');
		row3.push_back('8');

		p->puzzle.push_back(row1);
		p->puzzle.push_back(row2);
		p->puzzle.push_back(row3);

		rootNode = p;
		prevStates.push_back(rootNode->puzzle);
		if(!isValid(rootNode)){
			 throw std::invalid_argument( "Invalid Puzzle" );
		}
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

		p->puzzle.push_back(row1);
		p->puzzle.push_back(row2);
		p->puzzle.push_back(row3);

		rootNode = p;
		if(!isValid(rootNode)){
			 throw std::invalid_argument( "Invalid Puzzle" );
		}
		prevStates.push_back(rootNode->puzzle);

	}
	else{
		 throw std::invalid_argument( "received invalid value" );
	}

}

int puzzle::charToInt(char c){
	int i = c - '0';
	return i;
}
bool puzzle::isValid(path* x){
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) <= 8 && charToInt(x->puzzle.at(i).at(j)) >= 0){}
			else{return false;}
		}
	}
	return true;
}
// makes sure the user inputs 1, 2, or 3 to select algorithm
// also returns if root is NULL or the user input puzzle is not valid
void puzzle::algorithmSelector(int x){
	if(rootNode == NULL)
		 throw std::invalid_argument( "Failed to initalize puzzle" );
	cout << "Expanding state" << endl;
	if(x == 1){
		uniformCostSearch(rootNode);
	}
	else if(x == 2){
		misplacedTileSearch(rootNode);
	}
	else if(x == 3){
		manhattanDistanceSearch(rootNode);
	}
	else{
		 throw std::invalid_argument( "Invalid Response" );
	}

}

bool puzzle::isGoalState(vector< vector<char> > puzzle){
	vector< vector<char> > solvedPuzzle;
	vector<char> row1, row2, row3;
	row1.push_back('1');
	row1.push_back('2');
	row1.push_back('3');

	row2.push_back('4');
	row2.push_back('5');
	row2.push_back('6');

	row3.push_back('7');
	row3.push_back('8');
	row3.push_back('0');
	solvedPuzzle.push_back(row1);
	solvedPuzzle.push_back(row2);
	solvedPuzzle.push_back(row3);
	// tempPuzzle filled with complete 2D vector

	if(puzzle == solvedPuzzle)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int puzzle::childrenCalculator(path *x){
	int nOfChildren = 4;
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) == 0){
				if(i == 0){
					nOfChildren--;
					moves.push_back("Left");
					moves.push_back("Right");
					moves.push_back("Down");
				}
				else if(i == 2){
					nOfChildren--;
					moves.push_back("Left");
					moves.push_back("Right");
					moves.push_back("Up");
				}
				else if(j == 0){
					nOfChildren--;
					moves.push_back("Right");
					moves.push_back("Up");
					moves.push_back("Down");
				}
				else if(j == 2){
					nOfChildren--;
					moves.push_back("Left");
					moves.push_back("Up");
					moves.push_back("Down");
				}
			}
		}
	}
	return nOfChildren;
}

void puzzle::uniformCostSearch(path* x){
	if(isGoalState(x->puzzle)){
		cout << "LITTY BOIZ" << endl;
	}
	else{
		cout << "Fuck" << endl;
	}
}
void puzzle::misplacedTileSearch(path* x){}
void puzzle::manhattanDistanceSearch(path* x){}

void puzzle::moveLeft(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i).at(j-1));

}
void puzzle::moveRight(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i).at(j+1));
}
void puzzle::moveUp(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i-1).at(j));

}
void puzzle::moveDown(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i+1).at(j));

}
