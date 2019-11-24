#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include "heuristics.h"
#include "state.h"
#include "pruner.h"
using namespace std;

ofstream fout;
//double maxval(pair<vector<vector<int>>,double> &state_pair, double alpha, double beta, int k, vector<double> &weights, int who_am_i);
//double minval(pair<vector<vector<int>>,double> &state_pair, double alpha, double beta, int k, vector<double> &weights,int who_am_i);

// vector<pair<vector<vector<int> >,double> > myThinking;
int depth;
double minval(pair<vector<vector<int>>,double> &state_pair ,double alpha, double beta, int k, vector<double> &weights, int who_am_i);

int giveDepth(double time, int branchFactor)
{
	if(time<3 && time >1)
		return 4;
	else if(time < 1)
		return 3;

	if(branchFactor <= 20 && branchFactor >= 15)
	{
		if(time>33)
			return 6;
		else
			return 5;
	}
	else if(branchFactor < 15){
		if(time>25 && branchFactor<10)
			return 7;
		// else if(time > 20)
		// 	return 6;
		// else
		return 6;
	}
	return 5;


}

bool two_enemy_townhalls(vector<vector<int>> state, int who_am_i)
{
	int enemy_townhalls=0;
	if(who_am_i)
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[state.size()-1][i]==4)
				enemy_townhalls++;
		}
	}
	else
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[0][i]==4)
				enemy_townhalls++;
		}
	}
	if(enemy_townhalls==2)
		return true;
	return false;
}

bool two_townhalls(vector<vector<int>> state, int who_am_i)
{
	int my_townhalls;
	if(who_am_i)
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[0][i]==2)
				my_townhalls++;
		}
	}
	else
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[state.size()-1][i]==2)
				my_townhalls++;
		}
	}
	if(my_townhalls==2)
		return true;
	return false;
}

bool lesser_townhalls(vector<vector<int>> state, int who_am_i)
{
	int my_townhalls=0;
	int enemy_townhalls=0;
	if(who_am_i)
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[0][i]==2)
				my_townhalls++;
			if(state[state.size()-1][i]==4)
				enemy_townhalls++;
		}
	}
	else
	{
		for(int i=0;i<state[0].size();i++)
		{
			if(state[0][i]==4)
				enemy_townhalls++;
			if(state[state.size()-1][i]==2)
				my_townhalls++;
		}
	}
	if(my_townhalls<enemy_townhalls)
		return true;
	return false;
}


bool am_I_killable(vector<vector<int>> curr_state,vector<vector<int>> next_state,int who_am_i)
{
	/*
	returns true if the move involves losing a tower 
	*/
	int current_townhalls=0;
	int next_townhalls=0;
	int rows = curr_state.size();
	int cols = curr_state.at(0).size();
	if(who_am_i==1)
	{
		for(int j=0;j<cols;j++)
		{
			if(curr_state.at(0).at(j)==2)
			{
				current_townhalls++;
			}
			if(next_state.at(0).at(j)==2)
			{
				next_townhalls++;
			}
		}
	}
	else
	{
		for(int j=0;j<cols;j++)
		{
			if(curr_state.at(rows-1).at(j)==2)
			{
				current_townhalls++;
			}
			if(next_state.at(rows-1).at(j)==2)
			{
				next_townhalls++;
			}
		}
	}
	if(next_townhalls<current_townhalls)
	{
		return true;
	}
	return false;
}

bool killable(vector<vector<int>> curr_state,vector<vector<int>> next_state,int who_am_i)
{
	/*
	returns true if the move involves killing a tower 
	*/
	int current_enemy_townhalls=0;
	int next_enemy_townhalls=0;
	int rows = curr_state.size();
	int cols = curr_state.at(0).size();
	if(who_am_i==0)
	{
		for(int j=0;j<cols;j++)
		{
			if(curr_state.at(0).at(j)==4)
			{
				current_enemy_townhalls++;
			}
			if(next_state.at(0).at(j)==4)
			{
				next_enemy_townhalls++;
			}
		}
	}
	else
	{
		for(int j=0;j<cols;j++)
		{
			if(curr_state.at(rows-1).at(j)==4)
			{
				current_enemy_townhalls++;
			}
			if(next_state.at(rows-1).at(j)==4)
			{
				next_enemy_townhalls++;
			}
		}
	}
	if(next_enemy_townhalls<current_enemy_townhalls)
	{
		return true;
	}
	return false;
}



double maxval(pair<vector<vector<int>>,double> &state_pair , double alpha, double beta, int k, vector<double> &weights,int who_am_i)
{
	/*
	returns the maximum value attained on going down this state
	Inputs: state_pair - a pair of the 2d array of state and its heuristic
			alpha - the lower bound
			beta - the upper bound
			k - the actal depth. It is already doubled from the calling function
			weights - required for calculating the heuristic
			who_am_i - 0 if black, 1 if white
	Outputs: the maximum value attained 
	*/
	int m = state_pair.first.size();
	int n = state_pair.first[0].size();
	double best_child = -1*INFINITY;
	if(k==0)  //leaf nodes
	{
		//cout<<"Reached here"<<endl;
		if(state_pair.second == -1*INFINITY)
			state_pair.second = heuristic(state_pair.first,weights,who_am_i);
			//cout<<"reached here"<<endl;
		
		return state_pair.second;
	}
	else  //recursively go deeper
	{
		vector<pair<vector<vector<int> >,double> > all_children = giveNeighbourStates(state_pair.first,m,n,who_am_i,false);
		// random_shuffle(all_children.begin(), all_children.end());

		// myThinking[depth-k] = all_children[0];
		if(all_children.size()==0)
		{
			if(lesser_townhalls(state_pair.first, who_am_i))
				return -1*INFINITY;
			else
				return 50;
		}

		for(int i=0;i<all_children.size();i++)
		{
			if(two_townhalls(all_children[i].first, who_am_i)){
				return -1*INFINITY;
			}
			if(two_enemy_townhalls(all_children[i].first, who_am_i)){
				return INFINITY;
			}

			double childval = minval(all_children[i],alpha,beta,k-1,weights,who_am_i);
			if(childval>best_child){
				// myThinking[depth-k] = all_children[i];
				best_child = childval;
			}
			if(childval>alpha)
				alpha = childval;
			if(alpha > beta)
				return childval;
		}
	}
	return best_child;
}

double minval(pair<vector<vector<int>>,double> &state_pair ,double alpha, double beta, int k, vector<double> &weights, int who_am_i)
{
	/*
	returns the maximum value attained on going down this state
	Inputs: state_pair - a pair of the 2d array of state and its heuristic
			alpha - the lower bound
			beta - the upper bound
			k - the actal depth. It is already doubled from the calling function
			weights - required for calculating the heuristic
			who_am_i - 0 if black, 1 if white
	Outputs: the maximum value attained 
	*/
	int m = state_pair.first.size();
	int n = state_pair.first[0].size();
	double best_child=INFINITY;
	if(k==0)  //leaf nodes
	{
		//cout<<"Reached here"<<endl;
		if(state_pair.second == -1*INFINITY)
			state_pair.second = heuristic(state_pair.first,weights,who_am_i);
		//cout<<"Heuristic: "<<state_pair.second<<endl;
		return state_pair.second;
	}
	else  //recursively go deeper
	{
		vector<pair<vector<vector<int> >,double> > all_children = giveNeighbourStates(state_pair.first,m,n,who_am_i,true);
		// random_shuffle(all_children.begin(), all_children.end());

		// cout<<"Reached Here"<<endl;
		// myThinking[depth-k] = all_children[0];
		int bestK = 0;

		if(all_children.size()==0)
		{
			if(lesser_townhalls(state_pair.first, who_am_i))
				return -1*INFINITY;
			else
				return 50;
		}
		for(int i=0;i<all_children.size();i++)
		{
			if(am_I_killable(state_pair.first, all_children[i].first, who_am_i))
			{
				return -1*INFINITY;
			}		

			if(two_townhalls(all_children[i].first, who_am_i)){
				return -1*INFINITY;
			}
			if(two_enemy_townhalls(all_children[i].first, who_am_i)){
				return INFINITY;
			}

			double childval = maxval(all_children[i],alpha,beta,k-1,weights,who_am_i);
			//cout<<"Reached here"<<childval<<endl;
			//cout<<"Childval "<<i<<": "<<childval<<endl;
			if(childval<best_child){
				// myThinking[depth-k] = all_children[i];
				bestK = i;
				best_child = childval;
			}
			if(childval<beta)
				beta = childval;
			if(alpha>beta){
				// cout<<"InMaxVal: "<<endl;
				// for(int i=0;i<8;i++){
				// 	for(int j=0;j<8;j++){
				// 		cout<<all_children[bestK].first[i][j]<<" ";
				// 	}
				// 	cout<<endl;
				// }

				return childval;
			}
		}
	
	// cout<<"InMaxVal: "<<endl;
	// for(int i=0;i<8;i++){
	// 	for(int j=0;j<8;j++){
	// 		cout<<all_children[bestK].first[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	return best_child;	}
}


vector<vector<int>> generate_next_state(pair<vector<vector<int>>,double> &curr_state_pair, int who_am_i, double time, vector<double> &weights, bool samuel)
{
	/*
	Returns the next best move of the computer after k levels of search
	Inputs: curr_state_pair - the current state of the board
			who_am_i - 0 if black, 1 if white
			k - levels of search
	*/
	int k=0;
	vector<vector<int>> curr_state = curr_state_pair.first;
	int m = curr_state.size();
	int n = curr_state[0].size();
	//vector<double> weights{4,-4,2,-2,3,-3,4,-4,9,-9};
	double alpha = -1*INFINITY;
	double beta = INFINITY;
	int which_move = 0;
	

	vector<pair<vector<vector<int>>,double>> all_children = giveNeighbourStates(curr_state,m,n,who_am_i,false); //get all the possible next moves
	k = giveDepth(time,all_children.size());
	// k = 8;
	// depth = k;
	// k=3;
	// myThinking.resize(k);

	// random_shuffle(all_children.begin(), all_children.end());

	for(int i=0;i<all_children.size();i++)
	{
		//cout<<k<<endl;
		// if(killable(curr_state, all_children.at(i).first, who_am_i))
		// {
		// 	return all_children[i].first;
		// }
		// cout<<"I: "<<i<<endl;
		if(heuristic(all_children[i].first, weights, who_am_i)>=INFINITY)
			return  all_children[i].first;

		double best_value_below = minval(all_children[i],alpha,beta,k-1,weights,who_am_i);
		//cout<<"up"<<all_children[i].second<<" ";
		// cout<<"Reached Here"<<endl;
		if(best_value_below>alpha)  // if a better state is obtained, make it the next candidate
		{
			alpha = best_value_below;
			which_move = i;
		}
	}
	//cout<<"Reached Here"<<endl;
	// myThinking[0]=all_children[which_move];
	// cout<<"thing that matters\n\n\n\n";
	// double timePass = minval(all_children[which_move],alpha,beta,k-1,weights,who_am_i);
	if(curr_state_pair.second==-1*INFINITY)
		curr_state_pair.second = heuristic(curr_state_pair.first, weights, who_am_i);

	if(samuel)
	{
		//cout<<"ALPHA: "<<alpha<<", CURR: "<<curr_state_pair.second<<endl;
		if(alpha>curr_state_pair.second)
		{
			for(int w=0; w< weights.size();w++)
			{
				if(weights[w]>0)
					weights[w] = 0.001 + (weights[w]);
				else
					weights[w] = (weights[w]) + 0.001;
			}
		}
		else if(alpha<curr_state_pair.second)
		{
			for(int w=0; w< weights.size();w++)
			{
				if(weights[w]<0)
					weights[w] = (weights[w]) - 0.001;
				else
					weights[w] = (weights[w]) - 0.001;
			}
		}


		fout.open("master_weights.txt",std::ios_base::trunc);
		for(int wt=0;wt<weights.size();wt++)
		{
			fout<<(weights[wt])<<endl;
		}
		fout.close();

	}



	// fout.open("myThinking.txt",std::ios_base::trunc);
	// // cout<<"myThinking: "<<myThinking.size();
	// for(int i=0;i<myThinking.size();i++){
	// 	fout<<"Eval: "<<heuristic(myThinking[i].first,weights,who_am_i)<<endl;
	// 	for(int j=0;j<8;j++){
	// 		for(int k=0;k<8;k++)
	// 			fout<<myThinking[i].first[j][k]<<" ";
	// 		fout<<endl;
	// 	}
	// }
	// fout.close();



	
	return all_children[which_move].first;
}
