#ifndef __IO_H_INCLUDED__
#define __IO_H_INCLUDED__

#include <bits/stdc++.h>
using namespace std;

struct Input{
	float time_to_solve;
	double conversion_cost;
	vector<char> vocabulary;
	vector<string> input_strings;
	vector<vector<double>> matching_cost;
};

extern Input* input_reader(string);
extern void output_writer(string, vector<string> &);

#endif //IO.h
