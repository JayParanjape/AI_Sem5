#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#include <vector>
#include <string>
using namespace std;
extern vector<pair<vector<vector<int> >,double> > giveNeighbourStates(vector<vector<int> > ,int ,int ,int, bool);
extern string actionToString(vector<vector<int> > , vector<vector<int> > ,int ,int );
#endif