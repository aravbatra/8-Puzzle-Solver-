#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include "eightPuzzle.h"

using namespace std;

int main()
{
	puzzle p;

	int puzzleChoice = 0;
    cout << "Welcome to Arav Batra's 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle" << endl;
    cin >> puzzleChoice;
	p.generatePuzzle(puzzleChoice);

	int algorithmChoice = 0;
	cout << "Enter your choice of algorithm" << endl;
	cout << "\t1) Uniform Cost Search" << endl;
	cout << "\t2) A* with Misplaced Tile Heuristic" << endl ;
	cout << "\t3) A* with Manhattan Distance Heuristic" << endl;
	cin >> algorithmChoice;
	p.algorithmSelect(algorithmChoice);

    return 0;
}
