#include <iostream> 
#include <string> 
#include <stdio.h>
#include <limits>
#include <fstream>
#include<bits/stdc++.h>
#include <vector>
#include "pruner.h"
#include "state.h"
#include "heuristics.h"
using namespace std;

double INFINITE = std::numeric_limits<float>::infinity();
ofstream fut;


void compute_all_check(vector< vector<int> > &board, int what_am_i)
{
	/*
	Returns the various factors of the current state
	Inputs: board - the current state
			what_am_i - 0 if black, 1 if white
	Outputs: all - vector of the various factors of the state
	*/
	

	vector <int> all;

	int m = board.size();
	int n = board[0].size();
	
	int m_s = 0;      //my soldiers
	int e_s=0;        //enemy soldiers

	int m_h_sum = 0;  //my horizontal cannons
	int e_h_sum = 0;  //enemy horizontal cannons
	int m_v_sum = 0;  //my vertical cannons
	int e_v_sum = 0;  //enemy vertical cannons
	int m_c_sum = 0;  //my cross cannons
	int e_c_sum = 0;  //enemy cross cannons

	int m_townhall=0; //my townhalls
	int e_townhall=0;  //enemy townhalls

	int m_c_kill_sum = 0; //my possible cannon kills
	int o_c_kill_sum = 0; //opp possible cannon kills

	int my_cannon_townhall_kills=0;
	int opp_cannon_townhall_kills=0;

	int my_soldier_kill = 0; //my soldier kills
	int opp_soldier_kill= 0; //my opponent kills

	int my_soldier_townhall_kills = 0;
	int enemy_soldier_townhall_kills = 0;

	int my_blocked_h = 0; //my blocked horizontal cannons
	int my_blocked_v = 0; //my blocked vertical cannons
	int my_blocked_c = 0; //my blocked cross cannons
	int opp_blocked_h = 0; //opponent blocked horizontal cannons
	int opp_blocked_v = 0; // opponent blocked vertical cannons
	int opp_blocked_c = 0; // opponent blocked cross cannons

	int my_killable_cannons = 0;

	int left_attended = 0;
	int right_attended = 0;

	double eucDis1 = 0;
	double eucDis2 = 0;
	double eucDis3 = 0;
	double eucDis4 = 0;


	int close_opp_soldiers = 0;
	int killable_close_soldiers = 0;

	vector<int> distance_from_townhall_1;
	vector<int> distance_from_townhall_2;
	vector<int> distance_from_townhall_3;
	vector<int> distance_from_townhall_4;

	if(what_am_i==1)
	{
		for(int i=0;i<m;i++)
		{
			if(board[0][i]==2)
			{
				m_townhall++;
			}
			if(board[n-1][i]==4)
			{
				e_townhall++;
			}
		}
	}
	else
	{
		for(int i=0;i<m;i++)
		{
			if(board[0][i]==4)
			{
				e_townhall++;
			}
			if(board[n-1][i]==2)
			{
				m_townhall++;
			}
		}
	}
	

	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			//cout<<"IJ: "<<i<<" "<<j<<endl;
			//my soldiers
			if(board[i][j]==1)
			{
				m_s+=1;
				if(what_am_i)
				{
					if(i<3 && j<=3)
					{
						left_attended++;
					}
					if(i<3 and j>=4)
					{
						right_attended++;
					}
				}
				else
				{
					if(i>4 && j<=3)
					{
						left_attended++;
					}
					if(i>4 && j>=4)
					{
						right_attended++;
					}
				}
			}


			//enemy soldiers
			if(board[i][j]==3)
			{
				e_s+=1;
				if(what_am_i)
				{

					distance_from_townhall_1.push_back(max(i,j));
					distance_from_townhall_2.push_back(max(i,abs(j-2)));
					distance_from_townhall_3.push_back(max(i,abs(j-4)));
					distance_from_townhall_4.push_back(max(i,abs(j-6)));

					if(i>4 && j<=3)
					{
						left_attended--;
					}
					if(i>4 and j>=4)
					{
						right_attended--;
					}
				}
				else
				{
					distance_from_townhall_1.push_back(max(7-i,abs(j-1)));
					distance_from_townhall_2.push_back(max(7-i,abs(j-3)));
					distance_from_townhall_3.push_back(max(7-i,abs(j-5)));
					distance_from_townhall_4.push_back(max(7-i,abs(j-7)));

					if(i<3 && j<=3)
					{
						left_attended--;
					}
					if(i<3 && j>=4)
					{
						right_attended--;
					}
				}
				//if I am white, enemy's possible kills
				if(what_am_i)

					{
						if(i<=1)
						{
							close_opp_soldiers+=1;
							if(board[0][j]==1)
							{
								killable_close_soldiers+=1;
							}
							if(j==0)
							{
								if(board[0][j+1]==1)
								{
									killable_close_soldiers+=1;
								}
							}
							else if(j==m-1)
							{
								if(board[0][j-1]==1)
								{
									killable_close_soldiers+=1;
								}
							}
							else
							{
								if(board[0][j-1]==1 && board[0][j-1]==1)
								{
									killable_close_soldiers+=1;
								}
							}	
						}

					}

				else

					{
						if(i>=6)
						{
							close_opp_soldiers+=1;
							if(board[n-1][j]==1)
							{
								killable_close_soldiers+=1;
							}
							if(j==0)
							{
								if(board[n-1][j+1]==1)
								{
									killable_close_soldiers+=1;
								}
							}
							else if(j==m-1)
							{
								if(board[n-1][j-1]==1)
								{
									killable_close_soldiers+=1;
								}
							}
							else
							{
								if(board[n-1][j-1]==1 && board[n-1][j+1])
								{
									killable_close_soldiers+=1;
								}
							}
						}
					}

			}


			// enemy and my horizontal cannons
			if(j<n-2)
			{
				//my possible horizontal kills
				if((board[i][j] == 1)&&(board[i][j+1]==1)&&(board[i][j+2]==1))
				{
					m_h_sum+=1;
					

					//my horizontal blocks
					if(j+3<n)
					{
						if(board[i][j+3]==3)
							my_blocked_h += 1;
					}
					// else
					// 	my_blocked_h +=1;
					
					if(j-1>=0)
					{
						if(board[i][j-1]==3)
							my_blocked_h +=1;
					}
					// else
					// 	my_blocked_h +=1;

				}

				//opponent's horizontal cannon kills
				if((board[i][j] == 3)&&(board[i][j+1]==3)&&(board[i][j+2]==3))
				{
					e_h_sum+=1;
					
					//enemy horizontal blocks
					if(j+3<n)
					{
						if(board[i][j+3]==1)
							opp_blocked_h += 1;
					}
					// else
					// 	opp_blocked_h+=1;
					
					if(j-1>=0)
					{
						if(board[i][j-1]==1)
							opp_blocked_h +=1;
					}
					// else
					// 	opp_blocked_h+=1;
				}
			}

			if(i<m-2)
			{
				//my vertical cannon kills 
				if((board[i][j] == 1)&&(board[i+1][j]==1)&&(board[i+2][j]==1))
				{
					m_v_sum+=1;
					
					//my vertical blocks
					if(i+3<m)
					{
						if(board[i+3][j]==3)
							my_blocked_v += 1;
					}
					// else
					// 	my_blocked_v+=1;
					
					if(i-1>=0)
					{
						if(board[i-1][j]==3)
							my_blocked_v +=1;
					}
					// else
					// 	my_blocked_v+=1;
				}

				//enemy vertical cannon kills
				if((board[i][j] == 3)&&(board[i+1][j]==3)&&(board[i+2][j]==3))
				{
					e_v_sum+=1;
					

					//enemy vertical blocks
					if(i+3<m)
					{
						if(board[i+3][j]==1)
							opp_blocked_v += 1;
					}
					// else
					// 	opp_blocked_v+=1;
					
					if(i-1>=0)
					{
						if(board[i-1][j]==1)
							opp_blocked_v +=1;
					}
					// else
					// 	opp_blocked_v+=1;
				}

				
			}


			if(i<(m-2) && j<(n-2))
			{
				//my cross cannon kills
				if((board[i][j] == 1)&&(board[i+1][j+1]==1)&&(board[i+2][j+2]==1))
				{
					m_c_sum+=1;
					

					//my cross blocks
					if(j+3<n && i+3<m)
					{
						if(board[i+3][j+3]==3)
							my_blocked_c += 1;
					}
					// else
					// 	my_blocked_c +=1;
					
					if(j-1>=0 && i-1>=0)
					{
						if(board[i-1][j-1]==3)
							my_blocked_c +=1;
					}
					// else
					// 	my_blocked_c+=1;

				}
				if((board[i][j] == 3)&&(board[i+1][j+1]==3)&&(board[i+2][j+2]==3))
				{
					e_c_sum+=1;
					
					//enemy cross blocks
					if(j+3<n && i+3<m)
					{
						if(board[i+3][j+3]==1)
							opp_blocked_c += 1;
					}
					// else
					// 	opp_blocked_c+=1;

					
					if(j-1>=0 && i-1>=0)
					{
						if(board[i-1][j-1]==1)
							opp_blocked_c +=1;
					}
					// else
					// 	opp_blocked_c+=1;
				}
			}

			if(j>=2 && i<m-2)
			{
				//my cross cannon kills
				if((board[i][j] == 1)&&(board[i+1][j-1]==1)&&(board[i+2][j-2]==1))
				{
					m_c_sum+=1;
					
					//my cross blocks
					if(j-3>=0 && i+3<m)
					{
						if(board[i+3][j-3]==3)
							my_blocked_c += 1;
					}
					// else
					// 	my_blocked_c+=1;

					if(j+1>=0 && i-1>=0)
					{
						if(board[i-1][j+1]==3)
							my_blocked_c +=1;
					}
					// else
					// 	my_blocked_c+=1;

				}

				if((board[i][j] == 3)&&(board[i+1][j-1]==3)&&(board[i+2][j-2]==3))
				{
					e_c_sum+=1;
					
					//enemy cross blocks
					if(j-3>=0 && i+3<m)
					{
						if(board[i+3][j-3]==1)
							opp_blocked_c += 1;
					}
					// else
					// 	opp_blocked_c +=1;
					
					if(j+1>=0 && i-1>=0)
					{
						if(board[i-1][j+1]==1)
							opp_blocked_c +=1;
					}
					// else
					// 	opp_blocked_c +=1;
				}	

			}



		}
	}

	sort(distance_from_townhall_1.begin(),distance_from_townhall_1.end());
	sort(distance_from_townhall_2.begin(),distance_from_townhall_2.end());
	sort(distance_from_townhall_3.begin(),distance_from_townhall_3.end());
	sort(distance_from_townhall_4.begin(),distance_from_townhall_4.end());

	if(distance_from_townhall_1.size()==0)
	{
		eucDis1 += 100;
		eucDis2 += 100;
		eucDis3 += 100;
		eucDis4 += 100; 
	}
	else
	{
		eucDis1 += distance_from_townhall_1[0];
		eucDis2 += distance_from_townhall_2[0];
		eucDis3 += distance_from_townhall_3[0]; 
		eucDis4 += distance_from_townhall_4[0];
	}


	/*
int my_soldier_kill = 0; //my soldier kills
	int opp_soldier_kill= 0; //my opponent kills

	int my_blocked_h = 0; //my blocked horizontal cannons
	int my_blocked_v = 0; //my blocked vertical cannons
	int my_blocked_c = 0; //my blocked cross cannons
	int opp_blocked_h = 0; //opponent blocked horizontal cannons
	int opp_blocked_v = 0; // opponent blocked vertical cannons
	int opp_blocked_c = 0; // opponent blocked cross cannons

	int close_opp_soldiers = 0;
	*/
	// sort(distance_from_townhall_1.begin(),distance_from_townhall_1.end());
	// sort(distance_from_townhall_2.begin(),distance_from_townhall_2.end());
	// sort(distance_from_townhall_3.begin(),distance_from_townhall_3.end());
	// sort(distance_from_townhall_4.begin(),distance_from_townhall_4.end());
	cout<<"Debug: "<<distance_from_townhall_1[0]<<" "<<distance_from_townhall_1[1]<<endl;


	cout<<"MY SOLDIERS: "<<m_s<<endl;
	cout<<"ENEMY SOLDIERS: "<<e_s<<endl;
	cout<<"MY HORIZONTAL CANNONS: "<<m_h_sum<<endl;
	cout<<"ENEMY HORIZONTAL CANNONS: "<<e_h_sum<<endl;
	cout<<"MY VERTICAL CANNONS: "<<m_v_sum<<endl;
	cout<<"ENEMY VERTICAL CANNONS: "<<e_v_sum<<endl;
	cout<<"MY CROSS CANNONS: "<<m_c_sum<<endl;
	cout<<"ENEMY CROSS CANNONS: "<<e_c_sum<<endl;
	cout<<"MY TOWNHALLS: "<<m_townhall<<endl;
	cout<<"ENEMY TOWNHALLS: "<<e_townhall<<endl;
	
	cout<<"MY BLOCKED HORIZONTAL CANNONS: "<<my_blocked_h<<endl;
	cout<<"MY BLOCKED VERTICAL CANNONS: "<<my_blocked_v<<endl;
	cout<<"MY BLOCKED CROSS CANNONS: "<<my_blocked_c<<endl;
	cout<<"ENEMY BLOCKED HORIZONTAL CANNONS: "<<opp_blocked_h<<endl;
	cout<<"ENEMY BLOCKED VERTICAL CANNONS: "<<opp_blocked_v<<endl;
	cout<<"ENEMY BLOCKED CROSS CANNONS: "<<opp_blocked_c<<endl;
	
	cout<<"CLOSE SOLDIERS: "<<close_opp_soldiers<<endl;
	cout<<"Killable Cannons: "<<my_killable_cannons<<endl;
	cout<<"left attended: "<<left_attended;
	cout<<"right attended: "<<right_attended<<endl;
	cout<<"eucdistance1: "<<eucDis1<<endl;;
	cout<<"eucdistance2: "<<eucDis2<<endl;;
	cout<<"eucdistance3: "<<eucDis3<<endl;;
	cout<<"eucdistance4: "<<eucDis4<<endl;;


}

bool less_soldiers(vector<vector<int>> state)
{
	int my_soldiers=0;
	int enemy_soldiers=0;
	for(int i=0;i<state.size();i++)
	{
		for(int j=0;j<state[0].size();j++)
		{
			if(state[i][j]==1)
				my_soldiers++;
			else if(state[i][j]==3)
				enemy_soldiers++;
		}
	}
	if(my_soldiers<=7 || enemy_soldiers<=7)
		return true;
	return false;
}

int time_to_k(double my_time)
{
	// if (my_time<65 && my_time>20)
	// 	return 6;
	// else if(my_time<5)
	// 	return 3;
	// return 5;
	if(my_time>5)
		return 5;
	else if(my_time>2)
		return 4;
	return 3;

	// double l1, l2, l3;
	// double ans = (l1*(my_time-opp_time) + l2*opp_time + l3*opp_time)/((l1+l2+l3)*total_time);
	// return 5*(1/(1+exp(-1*ans)));
}

vector<vector<int>> string_to_state(string move, vector<vector<int>> &state_now, int mode=0)
{
	//assuming valid moves at all times
	// cerr<<"move: "<<endl;
	string arr[6];
	int i=0;int k=0;int j=0;

	for(;j<move.size();j++)
	{
		if(move[j]==' ' || move[j]=='\0')
		{
			arr[i] = move.substr(k,j-k);
			i++; k=j+1;
		}

	}
	arr[5] = move.substr(k,move.size()-k);

	// cerr<<"arr[0]: "<<arr[0]<<endl;
	// cerr<<"arr[1]: "<<arr[1]<<endl;
	// cerr<<"arr[2]: "<<arr[2]<<endl;
	// cerr<<"arr[3]: "<<arr[3]<<endl;
	// cerr<<"arr[4]: "<<arr[4]<<endl;
	// cerr<<"arr[5]: "<<arr[5]<<endl;

	int curr_row, curr_col, new_row, new_col;
	curr_row = stoi(arr[2]); curr_col = stoi(arr[1]);
	new_row =  stoi(arr[5]); new_col = stoi(arr[4]);
	//cout<<curr_row<<endl<<curr_col<<new_row<<endl<<new_col<<endl;
	if(move[6]=='M')
	{
		state_now[curr_row][curr_col] = 0;
		if(mode==0)
			state_now[new_row][new_col] = 3;
		else
			state_now[new_row][new_col] = 1;

	}
	else if(move[6]=='B')
		state_now[new_row][new_col] = 0;
	return state_now;
}

// int main(){
// 	int n,m,id;
// 	cin>>id>>n>>m;

// 	vector<vector<int> > v;
// 	vector<double> weights;

// 	vector<vector<int> > ans;

// 	for(int i=0;i<n;i++){
// 		vector<int> temp;
// 		v.push_back(temp);
// 		for(int j=0;j<m;j++){
// 			int x;
// 			cin>>x;
// 			v[i].push_back(x);
// 		}
// 	}
// 	ifstream w_file;
// 	double weight;
// 	w_file.open("master_weights.txt");
// 		weights.clear();
// 		// cout<<"Count: "<<count<<endl;
// 		int count=1;
// 		while(count<=25)
// 		{
// 			count++;
// 			w_file>>weight;
// 			// getline(w_file, line);
// 		//	cout<<count<<" 1: "<<line<<endl;
// 			weights.push_back(weight);
// 		}

// 		w_file.close();

// 		pair<vector<vector<int>>,double> tempP = make_pair(v,-1*INFINITE);
// 		cout<<"heuristic: "<<heuristic(v,weights,id)<<endl;
// 	ans = generate_next_state(tempP, id, 1000.0, weights, false);
// 	compute_all_check(v, id);
// 	cout<<endl;
// 	cout<<actionToString(v,ans,n,m)<<endl;
// 	cout<<heuristic(ans,weights,id)<<endl;
// 	for(int i=0;i<n;i++){
// 		for(int j=0;j<m;j++){
// 			cout<<ans[i][j]<<" ";
// 		}
// 		cout<<endl;
// 	}
// 	compute_all_check(ans, id);
// 	return 0;


// }



int main(){

	clock_t start,end;
	start = clock();
	ifstream ifs;
	int n,m,id;
	
	ifs.open("selector.txt");
	ifs>>id;
	ifs>>n;
	ifs>>m;
	id--;
	double time,finalTime;
	ifs>>time;
	finalTime = time;
	// m=n;
	vector<vector<int> > v{

	{4, 3, 4, 3, 4, 3, 4, 3},
	{0, 3, 0, 3, 0, 3, 0, 3},
	{0, 3, 0, 3, 0, 3, 0, 3},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 1, 0, 1, 0},
	{1, 0, 1, 0, 1, 0, 1, 0},
	{1, 2, 1, 2, 1, 2, 1, 2}

	};

	if(id==0){
		if(n==10 && m==10){
			v = {
				{4, 3, 4, 3, 4, 3, 4, 3,4,3},
				{0, 3, 0, 3, 0, 3, 0, 3,4,3},
				{0, 3, 0, 3, 0, 3, 0, 3,4,3},
				{0, 0, 0, 0, 0, 0, 0, 0,0,0},
				{0, 0, 0, 0, 0, 0, 0, 0,0,0},
				{0, 0, 0, 0, 0, 0, 0, 0,0,0},
				{0, 0, 0, 0, 0, 0, 0, 0,0,0},
				{1, 0, 1, 0, 1, 0, 1, 0,0,0},
				{1, 0, 1, 0, 1, 0, 1, 0,1,0},
				{1, 2, 1, 2, 1, 2, 1, 2,1,2}
			};
		}
		else if(n==10 && m==8){
			v = {
				{4, 3, 4, 3, 4, 3, 4, 3},
				{0, 3, 0, 3, 0, 3, 0, 3},
				{0, 3, 0, 3, 0, 3, 0, 3},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0},
				{1, 0, 1, 0, 1, 0, 1, 0},
				{1, 0, 1, 0, 1, 0, 1, 0},
				{1, 2, 1, 2, 1, 2, 1, 2}
			};		
		}
	}





	if(id==1)
	{
		if(n==8 && m==8){
			v = {
				{2,1,2,1,2,1,2,1},
				{0,1,0,1,0,1,0,1},
				{0,1,0,1,0,1,0,1},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,0,3,0,3,0,3,0},
				{3,0,3,0,3,0,3,0},
				{3,4,3,4,3,4,3,4}
			};
		}
		else if(n==10 && m==10){
			v = {
				{2,1,2,1,2,1,2,1,2,1},
				{0,1,0,1,0,1,0,1,0,1},
				{0,1,0,1,0,1,0,1,0,1},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0},
				{3,0,3,0,3,0,3,0,3,0},
				{3,0,3,0,3,0,3,0,3,0},
				{3,4,3,4,3,4,3,4,3,4}
			};
		}
		else{
			v = {
				{2,1,2,1,2,1,2,1},
				{0,1,0,1,0,1,0,1},
				{0,1,0,1,0,1,0,1},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0},
				{3,0,3,0,3,0,3,0},
				{3,0,3,0,3,0,3,0},
				{3,4,3,4,3,4,3,4}
			};
		}


	}
	vector<vector<int> > currState;
	vector<vector<int> > prevState;
	vector<vector<int> > myState;


	ifstream w_file;
	vector<double> weights;
	cerr<<"opening weight file"<<endl;
	w_file.open("master_weights.txt");
	string line;
	int count=1;
	double weight;
	//cout<<"oy"<<endl;
	while(count<=25)
	{
		count++;
		w_file>>weight;
		weights.push_back(weight);
	}
	w_file.close();

	double myTime,oppTime;

	currState = v;
	prevState = v;

	int ind = 0;
	//cout<<id<<endl;

	string action, temp;
	string st[6];
	if(id==1){
		// cin>>action;
		cin>>st[0];
		cin>>st[1];
		cin>>st[2];
		cin>>st[3];
		cin>>st[4];
		cin>>st[5];
		action = st[0] + " " +st[1] + " " + st[2] + " " + st[3] + " " + st[4] + " " + st[5];
		
		// cerr<<"*********************"<<endl;
		currState = string_to_state(action,currState);

	}

	fut.open("heur.txt",std::ios_base::app);
	vector<vector<int> > oppState;
	string sTemp = "";

	count = 1;
	while(time!=0){
		//cout<<"here"<<endl;
		if(less_soldiers(currState))
		{
			w_file.open("close_weights.txt");
		}
		else
		{
			w_file.open("master_weights.txt");
		}
		weights.clear();
		// cout<<"Count: "<<count<<endl;
		count=1;
		while(count<=25)
		{
			count++;
			w_file>>weight;
			// getline(w_file, line);
		//	cout<<count<<" 1: "<<line<<endl;
			weights.push_back(weight);
		}

		w_file.close();
		// cout<<"weights: "<<weights[0]<<endl;
		
		end = clock();
		time = finalTime - (double(end - start) / double(CLOCKS_PER_SEC));
		//cout<<"Time: "<<time; 
		// int k = time_to_k(time);
		// fut<<"Depth: "<<k<<" "<<time<<endl;

		prevState = currState;
		// cout<<"REACHED HERE"<<endl;
		pair<vector<vector<int>>,double> tempP = make_pair(currState,-1*INFINITE);
		cerr<<"generating next step"<<endl;
		currState = generate_next_state(tempP,id,time,weights,false);
		cerr<<"generated next state"<<endl;
		string myAct = actionToString(prevState,currState,n,m);
		cout<<myAct<<"\n";
		int branchFact = giveNeighbourStates(currState,m,n,id,false).size();
		fut<<"BranchingFactor :"<<branchFact<<endl;
		fut<<"Time :"<<time<<endl;
		fut<<"Depth: "<<giveDepth(time,branchFact);
		fut<<"My Action: "<<myAct<<"\n";
		fut<<"Heur:"<<heuristic(currState,weights,id)<<endl;
		// cerr<<"edited heur"<<endl;	
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				fut<<currState[i][j]<<" ";
			}
			fut<<endl;
		}
		// cout<<"Heur:"<<heuristic(currState,weights,id)<<endl;
		// cout<<"Your Best Move:\n";
		// cin>>sTemp;
		// cout<<"Hello"<<sTemp<<endl;
		// if(sTemp.compare("S")==0){
		// 	cin>>st[1];
		// 	cin>>st[2];
		// 	cin>>st[3];
		// 	cin>>st[4];
		// 	cin>>st[5];
		// 	cout<<"Reached here"<<endl;
		// 	string s_action = sTemp + " " +st[1] + " " + st[2] + " " + st[3] + " " + st[4] + " " + st[5];
		// 	myState = string_to_state(s_action,prevState,1);
		// 	// for(int i=0;i<8;i++){
		// 	// 	for(int j=0;j<8;j++){
		// 	// 		cout<<myState[i][j]<<" ";
		// 	// 		// if(myState[i][j]!=currState[i][j]){
		// 	// 		// 	cout<<"Shit!!"<<endl;
		// 	// 		// 	cout<<i<<" "<<j<<end;
		// 	// 		// }
		// 	// 	}
		// 	// 	cout<<endl;
		// 	// }
		// 	cout<<"My best(heur):"<<heuristic(myState,weights,id)<<endl;
		// 	compute_all_check(myState, id);
		// 	cout<<"Computer Move"<<endl;
		// 	compute_all_check(currState,id);
		// }

		cin>>st[0];
		cin>>st[1];
		cin>>st[2];
		cin>>st[3];
		cin>>st[4];
		cin>>st[5];
		action = st[0] + " " +st[1] + " " + st[2] + " " + st[3] + " " + st[4] + " " + st[5];
		fut<<"Oppn. Action: "<<action<<endl;

		currState = string_to_state(action, currState);
		cerr<<action<<"\n";
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				fut<<currState[i][j]<<" ";
			}
			fut<<endl;
		}
		action = "";
	}

	fut.close();



	return 0;
}