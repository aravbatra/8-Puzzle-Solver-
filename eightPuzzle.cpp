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
	p->head = NULL;
	p->heuristic = 0;
	p->branchCost = 0;

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
		row3.push_back('5');

		p->puzzle.push_back(row1);
		p->puzzle.push_back(row2);
		p->puzzle.push_back(row3);

		rootNode = p;
		if(!isValid(rootNode)){
			 throw std::invalid_argument( "Invalid Puzzle" );
		}
		prevStates.push_back(rootNode->puzzle);
		q.push(rootNode);
		//TODO: add displayPuzzle
		displayPuzzle(rootNode);


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
		displayPuzzle(rootNode);

		p->puzzle.push_back(row1);
		p->puzzle.push_back(row2);
		p->puzzle.push_back(row3);

		rootNode = p;
		if(!isValid(rootNode)){
			 throw std::invalid_argument( "Invalid Puzzle" );
		}
		prevStates.push_back(rootNode->puzzle);
		q.push(rootNode);

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
		//Left = 1
		//Right = 2
		//Up = 3
		//Down = 4
	int nOfChildren = 4;
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) == 0){
				if(i == 0){
					nOfChildren--;
					// moves.push_back("Left");
					// moves.push_back("Right");
					// moves.push_back("Down");
					x->illegalMoves.push_back(3); // UP
				}
				else if(i == 2){
					nOfChildren--;
					// moves.push_back("Left");
					// moves.push_back("Right");
					// moves.push_back("Up");
					x->illegalMoves.push_back(4); // Down
				}

				if(j == 0){
					nOfChildren--;
					// moves.push_back("Right");
					// moves.push_back("Up");
					// moves.push_back("Down");
					x->illegalMoves.push_back(1); //LEFT
				}
				else if(j == 2){
					nOfChildren--;
					// moves.push_back("Left");
					// moves.push_back("Up");
					// moves.push_back("Down");
					x->illegalMoves.push_back(2); //Right
				}
			}
		}
	}
	return nOfChildren;
}

void puzzle::uniformCostSearch(path* x){
	int horizontalIndex = 0;
	int verticalIndex = 0;

	vector< vector<char> > leftShift;
	vector< vector<char> > rightShift;
	vector< vector<char> > downShift;
	vector< vector<char> > upShift;

	if(isGoalState(x->puzzle)){
		goalState = true;
		goalNode = x;
	}
	else{
		q.pop();
	}
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) == 0){
				horizontalIndex = i;
				verticalIndex = j;
				break;
			}
		}
	}
	int nOfChildren = childrenCalculator(x);
	bool left = true;
 	bool right = true;
	bool up = true;
	bool down = true;
	for(int i = 0; i < x->illegalMoves.size(); i++){
		if(x->illegalMoves.at(i) == 1){
			left = false;
		}
		else if(x->illegalMoves.at(i) == 2){
			right = false;
		}
		if(x->illegalMoves.at(i) == 3){
			up = false;
		}
		else if(x->illegalMoves.at(i) == 4){
			down = false;
		}
	}

	if(left){
		leftShift = moveLeft(x,horizontalIndex,verticalIndex);
		assignChild(x, leftShift, x->child1);
	}
	if(right){
		rightShift = moveRight(x,horizontalIndex,verticalIndex);
		assignChild(x, rightShift, x->child2);
	}
	if(up){
		upShift = moveUp(x,horizontalIndex,verticalIndex);
		assignChild(x, upShift, x->child3);
	}
	if(down){
		downShift = moveDown(x,horizontalIndex,verticalIndex);
		assignChild(x, downShift, x->child4);
	}

	if(goalState){
		while(q.top() != goalNode)
		{
			q.pop();
		}
		displayPuzzle(q.top());
		cout << "Goal!" << endl;

		cout << "To solve this problem the search algorithm expanded a total of ";
		cout << totalNodes << " nodes." << endl;

		cout << "The maximum nodes in the queue at any one time was ";
		cout << nodesInQueue << "." << endl;

		cout << "The depth of the goal node was ";
		cout << q.top()->branchCost << "." << endl;

		return;
	}

	//Left = 1
	//Right = 2
	//Up = 3
	//Down = 4

	uniformCostSearch(q.top());

}
void puzzle::misplacedTileSearch(path* x){
	int heuristicMisplaced = 0;
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

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(x->puzzle.at(i).at(j) != solvedPuzzle.at(i).at(j))
			{
				heuristicMisplaced++;
			}
		}
	}
	x->heuristic = heuristicMisplaced;
	int horizontalIndex = 0;
	int verticalIndex = 0;

	vector< vector<char> > leftShift;
	vector< vector<char> > rightShift;
	vector< vector<char> > downShift;
	vector< vector<char> > upShift;

	if(isGoalState(x->puzzle)){
		goalState = true;
		goalNode = x;
	}
	else{
		q.pop();
	}
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) == 0){
				horizontalIndex = i;
				verticalIndex = j;
				break;
			}
		}
	}
	int nOfChildren = childrenCalculator(x);
	bool left = true;
	bool right = true;
	bool up = true;
	bool down = true;
	for(int i = 0; i < x->illegalMoves.size(); i++){
		if(x->illegalMoves.at(i) == 1){
			left = false;
		}
		else if(x->illegalMoves.at(i) == 2){
			right = false;
		}
		if(x->illegalMoves.at(i) == 3){
			up = false;
		}
		else if(x->illegalMoves.at(i) == 4){
			down = false;
		}
	}

	if(left){
		leftShift = moveLeft(x,horizontalIndex,verticalIndex);
		assignChild(x, leftShift, x->child1);
	}
	if(right){
		rightShift = moveRight(x,horizontalIndex,verticalIndex);
		assignChild(x, rightShift, x->child2);
	}
	if(up){
		upShift = moveUp(x,horizontalIndex,verticalIndex);
		assignChild(x, upShift, x->child3);
	}
	if(down){
		downShift = moveDown(x,horizontalIndex,verticalIndex);
		assignChild(x, downShift, x->child4);
	}

	if(goalState){
		while(q.top() != goalNode)
		{
			q.pop();
		}
		displayPuzzle(q.top());
		cout << "Goal!" << endl;

		cout << "To solve this problem the search algorithm expanded a total of ";
		cout << totalNodes << " nodes." << endl;

		cout << "The maximum nodes in the queue at any one time was ";
		cout << nodesInQueue << "." << endl;

		cout << "The depth of the goal node was ";
		cout << q.top()->branchCost << "." << endl;

		return;
	}

	//Left = 1
	//Right = 2
	//Up = 3
	//Down = 4

	misplacedTileSearch(q.top());
}
void puzzle::manhattanDistanceSearch(path* x){
	int heuristicDistance = 0;
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

	vector<int> one;
	one.push_back(0);
	one.push_back(0);
	vector<int> two;
	two.push_back(0);
	two.push_back(1);
	vector<int> three;
	three.push_back(0);
	three.push_back(2);
	vector<int> four;
	four.push_back(1);
	four.push_back(0);
	vector<int> five;
	five.push_back(1);
	five.push_back(1);
	vector<int> six;
	six.push_back(1);
	six.push_back(2);
	vector<int> seven;
	seven.push_back(2);
	seven.push_back(0);
	vector<int> eight;
	eight.push_back(2);
	eight.push_back(1);
	vector<int> zero;
	zero.push_back(2);
	zero.push_back(2);

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(x->puzzle.at(i).at(j) != solvedPuzzle.at(i).at(j))
			{
				int misplacedValue = charToInt(x->puzzle.at(i).at(j));
				switch (misplacedValue) {
					case 0:{
						heuristicDistance += abs(zero.at(0) - i);
						heuristicDistance += abs(zero.at(1) - j);
						break;
					}
					case 1:{
						heuristicDistance += abs(one.at(0) - i);
						heuristicDistance += abs(one.at(1) - j);
						break;
					}
					case 2:{
						heuristicDistance += abs(two.at(0) - i);
						heuristicDistance += abs(two.at(1) - j);
						break;
					}
					case 3:{
						heuristicDistance += abs(three.at(0) - i);
						heuristicDistance += abs(three.at(1) - j);
						break;
					}
					case 4:{
						heuristicDistance += abs(four.at(0) - i);
						heuristicDistance += abs(four.at(1) - j);
						break;
					}
					case 5:{
						heuristicDistance += abs(five.at(0) - i);
						heuristicDistance += abs(five.at(1) - j);
						break;
					}
					case 6:{
						heuristicDistance += abs(six.at(0) - i);
						heuristicDistance += abs(six.at(1) - j);
						break;
					}
					case 7:{
						heuristicDistance += abs(seven.at(0) - i);
						heuristicDistance += abs(seven.at(1) - j);
						break;
					}
					case 8:{
						heuristicDistance += abs(eight.at(0) - i);
						heuristicDistance += abs(eight.at(1) - j);
						break;
					}

				}

			}
		}
	}
	x->heuristic = heuristicDistance;
	int horizontalIndex = 0;
	int verticalIndex = 0;

	vector< vector<char> > leftShift;
	vector< vector<char> > rightShift;
	vector< vector<char> > downShift;
	vector< vector<char> > upShift;

	if(isGoalState(x->puzzle)){
		goalState = true;
		goalNode = x;
	}
	else{
		q.pop();
	}
	for(int i =0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(charToInt(x->puzzle.at(i).at(j)) == 0){
				horizontalIndex = i;
				verticalIndex = j;
				break;
			}
		}
	}
	int nOfChildren = childrenCalculator(x);
	bool left = true;
	bool right = true;
	bool up = true;
	bool down = true;
	for(int i = 0; i < x->illegalMoves.size(); i++){
		if(x->illegalMoves.at(i) == 1){
			left = false;
		}
		else if(x->illegalMoves.at(i) == 2){
			right = false;
		}
		if(x->illegalMoves.at(i) == 3){
			up = false;
		}
		else if(x->illegalMoves.at(i) == 4){
			down = false;
		}
	}

	if(left){
		leftShift = moveLeft(x,horizontalIndex,verticalIndex);
		assignChild(x, leftShift, x->child1);
	}
	if(right){
		rightShift = moveRight(x,horizontalIndex,verticalIndex);
		assignChild(x, rightShift, x->child2);
	}
	if(up){
		upShift = moveUp(x,horizontalIndex,verticalIndex);
		assignChild(x, upShift, x->child3);
	}
	if(down){
		downShift = moveDown(x,horizontalIndex,verticalIndex);
		assignChild(x, downShift, x->child4);
	}

	if(goalState){
		while(q.top() != goalNode)
		{
			q.pop();
		}
		displayPuzzle(q.top());
		cout << "Goal!" << endl;

		cout << "To solve this problem the search algorithm expanded a total of ";
		cout << totalNodes << " nodes." << endl;

		cout << "The maximum nodes in the queue at any one time was ";
		cout << nodesInQueue << "." << endl;

		cout << "The depth of the goal node was ";
		cout << q.top()->branchCost << "." << endl;

		return;
	}

	//Left = 1
	//Right = 2
	//Up = 3
	//Down = 4

	manhattanDistanceSearch(q.top());
}

vector< vector<char> > puzzle::moveLeft(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i).at(j-1));

	//displayPuzzle(x);
	return tempPuzzle;
}
vector< vector<char> > puzzle::moveRight(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i).at(j+1));
	//displayPuzzle(x);
	return tempPuzzle;
}
vector< vector<char> > puzzle::moveUp(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i-1).at(j));
	//displayPuzzle(x);
	return tempPuzzle;
}
vector< vector<char> > puzzle::moveDown(path* x,int i,int j){
	vector< vector<char> > tempPuzzle = x->puzzle;
	swap(tempPuzzle.at(i).at(j), tempPuzzle.at(i+1).at(j));
	//displayPuzzle(x);
	return tempPuzzle;
}

void puzzle::assignChild(path* x, vector< vector<char> > puzzle, path* child){
	path* temp = childCreator(x, puzzle);

	if(goalState){
		return;
	}
	if(isGoalState(puzzle)){
		goalState = true;
		prevStates.push_back(puzzle);

		child = temp;
		child->head = x;
		q.push(child);
		totalNodes++;
		nodesInQueue++;

		goalNode = child;

		return;
	}

	if(isUnique(temp->puzzle)){
		prevStates.push_back(temp->puzzle);
		cout << "ENTERED assign" << endl;
		child = temp;
		child->head = x;
		q.push(child);

		totalNodes++;
		nodesInQueue++;

		displayPuzzle(temp);
	}
}
//Only if brand new state
path* puzzle::childCreator(path* x, vector< vector<char> > puzzle){
	path* temp = new path;

	temp->heuristic = x->heuristic;
	temp->branchCost = x->branchCost + 1;
	temp->puzzle = puzzle;


	return temp;
}

bool puzzle::isUnique(vector< vector<char> > puzzle){
	for(int i = 0; i < prevStates.size(); i++){
		if(puzzle == prevStates.at(i)){
			return false;
		}
	}
	return true;
}

// void puzzle::displaySolution(path* x){
// 	if(x == root){
// 		solutionPath.push_front(x)
// 		for (int i = 0; i < solutionPath.size(); i++) {
// 			cou
// 		}
// 	}
// 	else{
// 		solutionPath.push_front(x)
// 		displaySolution(x->head);
// 	}
//
// }



void puzzle::displayPuzzle(path* x){
	if(x != rootNode)
		{
			cout << "The best state to expand with a g(n) = ";
			cout << x->branchCost;
			cout << " and h(n) = ";
			cout << x->heuristic;
			cout << " is..." << endl;
		}

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << x->puzzle.at(i).at(j) << " ";
		}
		cout << endl;

	}
	cout << endl;
}
