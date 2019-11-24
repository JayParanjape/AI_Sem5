#ifndef PRUNER_INCLUDE
#define PRUNER_INCLUDE

#include <vector>
using namespace std;

extern vector<vector<int>> generate_next_state(pair<vector<vector<int>>,double> &, int , double , vector<double> & , bool );
extern int giveDepth(double , int );


#endif