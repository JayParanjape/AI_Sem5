#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <random>

#include "loss.h"
#include "IO.h"
using namespace std;

int random_n(int n)
{

	//Returns a random number between 0 and n-1
	//srand (time(NULL));
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, (float)(n+1));
	
	return (int)(dist(mt)) - 1;
}


vector<string> best_neighbour(double CC, vector<string> &input_set, vector<vector<double>> &MC, vector<char> &vocab, float ttl){

	// cout<<input_set[0];
	float start_time = (float)clock()/CLOCKS_PER_SEC;
	int num_strings = input_set.size();
	int x = 1;
	x = x<<(num_strings);
	//x = x<<15;
	x -= 1;
	long long int cost = LONG_MAX;
	int best_num;

	for(int it=0; it<x; ++it){	//checking for all possible neighbours
		int i = random_n(x);
		if((((float)clock()/CLOCKS_PER_SEC)-start_time) > ttl)
		{
			//cout<<"Breaking i is "<<i<<endl; 
			break;
		}
		for(int j=0; j<num_strings; ++j){	//iterating through all strings

			if(((input_set[j].size()) != 0) && ((i>>j) % 2 != 0)){
				input_set[j].push_back('-');
			}

		}

		float s1 = (float)clock()/(CLOCKS_PER_SEC);
		double temp = total_cost(CC, input_set, MC, vocab);
		//cout<<"Bottleneck: "<<(float)clock()/(CLOCKS_PER_SEC) - s1<<endl;
		if(temp < cost){
			best_num = i;
			cost = temp;
		}

		for(int j=0; j<num_strings; ++j){

			if(((input_set[j].size()) != 0) && ((i>>j) % 2 != 0)){
				input_set[j].pop_back();
			}

		}

		//cout<<i<<endl;

	}


	for(int j=0; j<num_strings; ++j){

		if(((input_set[j].size()) != 0) && ((best_num>>j) % 2 != 0)){
			input_set[j].push_back('-');
		}

	}

	return input_set;
}

int num_empty_strings(vector<string> &input_set){
	int k = input_set.size();
	int num = 0;

	for(int i=0; i<k; ++i){

		if(input_set[i].size() == 0){
			++num;
		}

	}

	return num;
}

vector<string> answer(double CC, vector<string> &input_set,vector<vector<double>> &MC, vector<char> &vocab, float ttl)
{
	int k = input_set.size();
	vector<string> suffix(k);
	//vector<string> best_ans_yet(k);
	float start_time = (float)clock()/CLOCKS_PER_SEC;

	// while(true)
	// { //cout<<"hi";

		while(num_empty_strings(input_set) < k){
			// cout<<"start_time: "<<start_time<<endl;
			//cout<<ttl<<endl;
			//cout<<"Elapsed TIME: "<<(((float)clock()/CLOCKS_PER_SEC)-start_time)<<endl;
			if( (((float)clock()/CLOCKS_PER_SEC)-start_time) > (ttl) )
			{

			//	cout<<"Returning from A with start_time "<<start_time<<" and ttl "<<ttl<<endl;
				break;

			}

			if(num_empty_strings(input_set) == k-2){ //will do dp here
				vector<string> non_empty_strings;	//stores the 2 non empty strings
				int pos_1 = -1;
				int pos_2 = -1;
				for(int i=0; i<k; ++i){	//find the 2 non empty strings

					if(input_set[i].size() != 0){
						non_empty_strings.push_back(input_set[i]);
						input_set[i] = "";
						if(pos_1 == -1){
							pos_1 = i;
						}
						else{
							pos_2 = i;
						}
					}

				}

				input_set.pop_back();
				input_set.pop_back();	//decreasing size by 2, will add 2 modified eleemtns using dp

				reverse(non_empty_strings[0].begin(), non_empty_strings[0].end());	// since we have to reverse the suffix in the end
				reverse(non_empty_strings[1].begin(), non_empty_strings[1].end());

				// cout<<non_empty_strings[0]<<endl<<non_empty_strings[1]<<endl;
				// input_set[0] = non_empty_strings[0];
				// input_set[1] = non_empty_strings[1];

				int len_1 = non_empty_strings[0].size();
				int len_2 = non_empty_strings[1].size();
				int num_rows = non_empty_strings[0].size();
				int num_cols = non_empty_strings[1].size();


				double dp_arr[num_rows+1][num_cols+1];	//since there can be empty strings also
				int dp_arr_directions[num_rows+1][num_cols+1]; //0 for diagonal, 1 for down, 2 for right

				dp_arr[num_rows][num_cols] = 0;

				for(int i=num_rows-1; i>=0; --i){
					input_set.push_back("");
					input_set.push_back(non_empty_strings[0].substr(i));

					dp_arr[i][num_cols] = total_cost(CC, input_set, MC, vocab);
					dp_arr_directions[i][num_cols] = 1;

					input_set.pop_back();
					input_set.pop_back();

				}

				for(int i=num_cols-1; i>=0; --i){
					input_set.push_back("");
					input_set.push_back(non_empty_strings[1].substr(i));

					dp_arr[num_rows][i] = total_cost(CC, input_set, MC, vocab);
					dp_arr_directions[num_rows][i] = 2;

					input_set.pop_back();
					input_set.pop_back();

				}

				for(int i=num_rows-1; i>=0; --i){

					for(int j=num_cols-1; j>=0; --j){
						//for 00
						//cout<<"Elapsed time: "<<(time(NULL))<<endl;
						//cout<<"Elapsed TIME: "<<(((float)clock()/CLOCKS_PER_SEC)-start_time)<<endl;
						// if( (((float)clock()/CLOCKS_PER_SEC)-start_time) > (ttl) )
						// 	{return best_ans_yet;
						// 		cout<<"Returning from b"<<endl;}

						input_set.push_back(non_empty_strings[1].substr(j, 1));
						input_set.push_back(non_empty_strings[0].substr(i, 1));
						double val_0 = total_cost(CC, input_set, MC, vocab) + dp_arr[i+1][j+1];
						input_set.pop_back();
						input_set.pop_back();

						//for 01
						input_set.push_back("-");
						input_set.push_back(non_empty_strings[0].substr(i, 1));
						double val_1 = total_cost(CC, input_set, MC, vocab) + dp_arr[i+1][j];
						input_set.pop_back();
						input_set.pop_back();

						//for 10
						input_set.push_back(non_empty_strings[1].substr(j, 1));
						input_set.push_back("-");
						double val_2 = total_cost(CC, input_set, MC, vocab) + dp_arr[i][j+1];
						input_set.pop_back();
						input_set.pop_back();

						if(val_0 <= val_1 && val_0 <= val_2){
							dp_arr[i][j] = val_0;
							dp_arr_directions[i][j] = 0;
						}
						else{
							if(val_1 <= val_0 && val_1 <= val_2){
								dp_arr[i][j] = val_1;
								dp_arr_directions[i][j] = 1;
							}
							else{
								dp_arr[i][j] = val_2;
								dp_arr_directions[i][j] = 2;
							}
						}

					}

				}

				//constructing the answer string
				int x_traveller = 0;
				int y_traveller = 0;
				while(x_traveller != num_cols || y_traveller != num_rows){

					// if( (((float)clock()/CLOCKS_PER_SEC)-start_time) > (ttl) )
					// 		{return best_ans_yet;
					// 			cout<<"Returning from c"<<endl;}

					if(dp_arr_directions[y_traveller][x_traveller] == 0){
						suffix[pos_1].push_back(non_empty_strings[0][y_traveller]);
						suffix[pos_2].push_back(non_empty_strings[1][x_traveller]);
						++x_traveller;
						++y_traveller;
					}

					else{

						if(dp_arr_directions[y_traveller][x_traveller] == 1){
							suffix[pos_1].push_back(non_empty_strings[0][y_traveller]);
							suffix[pos_2].push_back('-');
							++y_traveller;
							++len_2;
						}
						else{
							suffix[pos_1].push_back('-');
							suffix[pos_2].push_back(non_empty_strings[1][x_traveller]);
							++x_traveller;
							++len_1;
						}

					}

				}

				int len = max(len_1, len_2);
				for(int i=0; i<k; ++i){	//making all strings of equal length
					if(i != pos_1 && i != pos_2){
						for(int j=0; j<len; ++j){
							suffix[i].push_back('-');
						}
					}
				}

				//normalising the size of input set
				input_set.push_back("");
				input_set.push_back("");
				//best_ans_yet = suffix;
				break;
			}
			else{
				input_set = best_neighbour(CC, input_set, MC, vocab, ttl/3);

				for(int i=0; i<k; ++i){

					if((input_set[i] !=  "")){
						suffix[i].push_back(input_set[i].back());
						input_set[i].pop_back();
					}
					else{
						suffix[i].push_back('-');
					}

				}
				//best_ans_yet = suffix;
			}

		}

		int max_len = -1;
		for(int i=0; i<k; ++i){
			reverse(suffix[i].begin(), suffix[i].end());
			suffix[i] = input_set[i] + suffix[i];
			
			if((signed)suffix[i].size() > max_len){
				max_len = suffix[i].size();
			
			}

			// cout<<suffix[i].size()<<endl<<temp;
		}

		// cout<<max_len<<endl;
		for(int i=0; i<k; ++i){
			int size_diff = max_len - suffix[i].size();
			string temp = "";
			for(int j=0; j<size_diff; ++j){
				temp.push_back('-');
			}
			suffix[i] = temp + suffix[i];
			// reverse(suffix[i].begin(), suffix[i].end());
			// for(int j=0; j<size_diff; ++j){
			// 	suffix[i].push_back('-');
			// }
			// reverse(suffix[i].begin(), suffix[i].end());
		}
		//best_ans_yet = suffix;
	// }
	return suffix;
}

//Driver Code

int main(int argc, char *argv[]){

	
	time_t init_time = (float)clock()/CLOCKS_PER_SEC;
	
	string input_filename = argv[1];
	string output_filename = argv[2];

	Input* input = input_reader(input_filename);
	vector<string> input_strings_copy = input->input_strings;
	int num_inputs = input_strings_copy.size();
	input->vocabulary.push_back('-');//vocabulary also contains a hyphen

	float ttl_left = (input->time_to_solve)-((float)clock()/CLOCKS_PER_SEC-init_time);
	bool first_time_answer_1 = true;
	bool first_time_answer_2 = true; 
	vector<string> final_answer_2;
	vector<string> final_answer_1;
	while(ttl_left > 1.5){

		float time1 = (float)clock();

		if(first_time_answer_1){ //cout<<"1"<<endl;
			final_answer_1 = answer(input->conversion_cost, input->input_strings, input->matching_cost, input->vocabulary, (ttl_left-1.5)/2);
			first_time_answer_1 = false;
		}
		else{ //cout<<"2"<<endl;
			for(int i=0; i<num_inputs; ++i){
				reverse(final_answer_2[i].begin(), final_answer_2[i].end());
			}
		 	final_answer_1 = answer(input->conversion_cost, final_answer_2, input->matching_cost, input->vocabulary, (ttl_left-1.5)/2);	
		}
		//cout<<"1-3"<<endl;
		for(int i=0; i<num_inputs; ++i){
				reverse(final_answer_1[i].begin(), final_answer_1[i].end());
			}
		//cout<<"3"<<endl;
		final_answer_2 = answer(input->conversion_cost, final_answer_1, input->matching_cost, input->vocabulary, (ttl_left-1.5)/2);
			
		float time_ela = ((float)clock() - time1)/(CLOCKS_PER_SEC);

		ttl_left -= time_ela;
		// if(first_time_answer_2){
		// 	for(int i=0; i<num_inputs; ++i){
		// 		reverse(final_answer_1[i].begin(), final_answer_2[i].end());
		// 	}
		// 	final_answer_2 = answer(input->conversion_cost, final_answer_1, input->matching_cost, input->vocabulary, (ttl_left-1.5)/2);
		// 	first_time_answer_12= false;
		// }
		// else{
		// 	for(int i=0; i<num_inputs; ++i){
		// 		reverse(first_time_answer_2[i].begin(), first_time_answer_2[i].end());
		// 	}
		//  	final_answer_1 = answer(input->conversion_cost, final_answer_2, input->matching_cost, input->vocabulary, (ttl_left-1.5)/2);	
		// }		
	
	
	
		// final_answer_2 = answer(input->conversion_cost, input_strings_copy, input->matching_cost, input->vocabulary, (input->time_to_solve)-((float)clock()/CLOCKS_PER_SEC-init_time)-1 );
	}

	

	if(total_cost(input->conversion_cost, final_answer_1, input->matching_cost, input->vocabulary) < total_cost(input->conversion_cost, final_answer_2, input->matching_cost, input->vocabulary)){
		output_writer(output_filename, final_answer_1);
	}
	else{
		for(int i=0; i<num_inputs; ++i){
			reverse(final_answer_2[i].begin(), final_answer_2[i].end());
		}
		output_writer(output_filename, final_answer_2);
	}
	

	return 0;

}
