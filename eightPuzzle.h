#ifndef _EIGHTPUZZLE_H_
#define _EIGHTPUZZLE_H_
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <list>
using namespace std;



struct path
{
	//4 Children for each direction the blank can move
	path* child1;
	path* child2;
	path* child3;
	path* child4;

  path* head;

  vector<int> illegalMoves;
	vector< vector<char> > puzzle; //store vector of puzzles here

  int heuristic;
	int branchCost;

};

class path_compare {
public:
    bool operator()(path* p1, path* p2)
    {
       if ((p1->branchCost + p1->heuristic) > (p2->branchCost + p2->heuristic)) return true;
       return false;
    }
};



class puzzle
{

private:

  //root node
  path* rootNode;

  //goalnode
  path* goalNode;

  bool goalState;

  //Keeps track of total nodes expanded
  int totalNodes;

  //Keeps track of total nodes expanded
  int nodesInQueue;

  //vector of puzzles to store states to check repeats
  vector< vector< vector<char> > >prevStates;

  priority_queue<path*, vector<path*>, path_compare > q;

  //stores path to goal state
  list<path*> solutionPath;

  int charToInt(char c);

  int childrenCalculator(path* x);

  path* childCreator(path* x, vector< vector<char> > puzzle);

  void assignChild(path* x, vector< vector<char> > puzzle, path* child);



public:
      puzzle();
      void generatePuzzle(int x);
      void algorithmSelector(int x);

      void displayPuzzle(path* x);
      void displaySolution(path* x);

      bool isValid(path* x);
      bool isGoalState(vector< vector<char> > puzzle);
      bool isUnique(vector< vector<char> > puzzle);

      void uniformCostSearch(path* x);
      void misplacedTileSearch(path* x);
      void manhattanDistanceSearch(path* x);

      vector< vector<char> > moveLeft(path* x,int i,int j);
      vector< vector<char> > moveRight(path* x,int i,int j);
      vector< vector<char> > moveUp(path* x,int i,int j);
      vector< vector<char> > moveDown(path* x,int i,int j);

      };
#endif
