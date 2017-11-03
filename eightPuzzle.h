#ifndef _EIGHTPUZZLE_H_
#define _EIGHTPUZZLE_H_
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
using namespace std;



struct path
{
	//4 Children for each direction the blank can move
	path* child1;
	path* child2;
	path* child3;
	path* child4;

	vector< vector<char> > puzzle; //store vector of puzzles here

};


class puzzle
{

private:

  //root node
  path* rootNode;

  //goalnode
  path* goalNode;

  //Keeps track of total nodes expanded
  int totalNodes;

  //Keeps track of total nodes expanded
  int nodesInQueue;

  //Sets true if we get to solved state
  bool goalState;

  //vector of puzzles to store states to check repeats
  vector< vector< vector<char> > >prevStates;

  //stores path to goal state
  list<path*> solutionPath;
public:
      puzzle();
      void generatePuzzle(int x);
      void algorithmSelect(int x);
      void displayPuzzle();
      bool isValid(path* x);
      int charToInt(char c);

      void uniformCostSearch(path* x);
      void misplacedTileSearch(path* x);
      void manhattanDistanceSearch(path* x);

      };
#endif
