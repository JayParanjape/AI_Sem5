#include <iostream>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include "IO.h"
using namespace std;

// struct Input{
// 	float time_to_solve;
// 	double conversion_cost;
// 	vector<char> vocabulary;
// 	vector<string> input_strings;
// 	vector<vector<double>> matching_cost;
// };

Input* input_reader(string filename){
	int vocabulary_size;
	int num_strings;
	float time_to_solve;
	double conversion_cost;
	string vocabulary;
	Input* input_struct = new Input();

	ifstream file_reader;
	file_reader.open(filename);

	file_reader>>time_to_solve;
	input_struct->time_to_solve = time_to_solve*60;

	file_reader>>vocabulary_size;

	if(getline(file_reader, vocabulary)){
		getline(file_reader, vocabulary);
	}
	else{
		cout<<"Error"<<endl;
	}

	for(int i=0; i<vocabulary.size(); i+=3){
		(input_struct->vocabulary).push_back(vocabulary[i]);
	}


	file_reader>>num_strings;

	string temp;
	for(int i=0; i<num_strings; ++i){
		file_reader>>temp;
		input_struct->input_strings.push_back(temp);
		// cout<<temp<<endl;
	}

	file_reader>>conversion_cost;
	input_struct->conversion_cost = conversion_cost;

	for(int i=0; i<vocabulary_size+1; ++i){
		//vector<double> row;
		vector<double> temp_dbl;
		for(int j=0; j<vocabulary_size+1; ++j){
			double temp;
			file_reader>>temp;
			
			
			temp_dbl.push_back(temp);

			//(input_struct->matching_cost).push_back(row);
			// cout<<row[0]<<endl;
		}
		(input_struct->matching_cost).push_back(temp_dbl);
	}
	file_reader.close();
	return input_struct;
}


void output_writer(string output_filename, vector<string> &answer){
	ofstream file_writer;
	file_writer.open(output_filename);
	int num_rows = answer.size();

	for(int i=0; i<num_rows; ++i){
			file_writer<<answer[i]<<'\n';
	}

	file_writer.close();
}
