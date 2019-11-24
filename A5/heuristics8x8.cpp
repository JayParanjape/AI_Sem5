#include<iostream>
#include<bits/stdc++.h>
#include "heuristics.h"
using namespace std;


double heuristic(vector< vector<int> > &board , vector<double> &weights, int what_am_i);

vector<int> compute_all(vector< vector<int> > &board, int what_am_i)
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
	// else
	// {
	// 	for(int i=0;i<3;i++)
	// 	{
	// 		eucDis += distance_from_townhall_1[i] + distance_from_townhall_2[i] 
	// 				+ distance_from_townhall_3[i] + distance_from_townhall_4[i];
	// 	}
	// }

	all.push_back(m_s); 
	all.push_back(e_s);
	all.push_back(m_h_sum);
	all.push_back(e_h_sum); 
	all.push_back(m_v_sum); 
	all.push_back(e_v_sum);
	all.push_back(m_c_sum); 
	all.push_back(e_c_sum);
	all.push_back(m_townhall); 
	all.push_back(e_townhall);
	//all.push_back(m_c_kill_sum); all.push_back(o_c_kill_sum);
	//all.push_back(my_soldier_kill); all.push_back(opp_soldier_kill);
	all.push_back(my_blocked_h); all.push_back(my_blocked_v); all.push_back(my_blocked_c);
	all.push_back(opp_blocked_h); all.push_back(opp_blocked_v); all.push_back(opp_blocked_c);
	all.push_back(my_killable_cannons);
	all.push_back(left_attended); all.push_back(right_attended);
	all.push_back(close_opp_soldiers);
	all.push_back(killable_close_soldiers);
	all.push_back((-1/(eucDis1+0.00001)));
	all.push_back((-1/(eucDis2+0.00001)));
	all.push_back((-1/(eucDis3+0.00001)));
	all.push_back((-1/(eucDis4+0.00001)));


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


	// cout<<"MY SOLDIERS: "<<m_s<<endl;
	// cout<<"ENEMY SOLDIERS: "<<e_s<<endl;
	// cout<<"MY HORIZONTAL CANNONS: "<<m_h_sum<<endl;
	// cout<<"ENEMY HORIZONTAL CANNONS: "<<e_h_sum<<endl;
	// cout<<"MY VERTICAL CANNONS: "<<m_v_sum<<endl;
	// cout<<"ENEMY VERTICAL CANNONS: "<<e_v_sum<<endl;
	// cout<<"MY CROSS CANNONS: "<<m_c_sum<<endl;
	// cout<<"ENEMY CROSS CANNONS: "<<e_c_sum<<endl;
	// cout<<"MY TOWNHALLS: "<<m_townhall<<endl;
	// cout<<"ENEMY TOWNHALLS: "<<e_townhall<<endl;
	
	// cout<<"MY BLOCKED HORIZONTAL CANNONS: "<<my_blocked_h<<endl;
	// cout<<"MY BLOCKED VERTICAL CANNONS: "<<my_blocked_v<<endl;
	// cout<<"MY BLOCKED CROSS CANNONS: "<<my_blocked_c<<endl;
	// cout<<"ENEMY BLOCKED HORIZONTAL CANNONS: "<<opp_blocked_h<<endl;
	// cout<<"ENEMY BLOCKED VERTICAL CANNONS: "<<opp_blocked_v<<endl;
	// cout<<"ENEMY BLOCKED CROSS CANNONS: "<<opp_blocked_c<<endl;
	
	// cout<<"CLOSE SOLDIERS: "<<close_opp_soldiers<<endl;
	// cout<<"Killable Cannons: "<<my_killable_cannons<<endl;
	// cout<<"left attended: "<<left_attended;
	// cout<<"right attended: "<<right_attended;
	// cout<<"eucDis1: "<<eucDis1;
	// cout<<"eucDis2: "<<eucDis2;
	// cout<<"eucDis3: "<<eucDis3;
	// cout<<"eucDis4: "<<eucDis4;


	return all;
}

double heuristic(vector< vector<int> > &board , vector<double> &weights, int what_am_i)
{
	/*
	Computes the evaluation for the current function
	Inputs: board - the current state
	Outputs: heur - the evaluation of the current state

	in the array, 0 represents empty tile
					1 represents my soldiers
					2 represents my town halls
					3 represents enemy soldiers
					4 represents enemy townhalls

	*/
	double heur=0.0;

	// for(int i=0;i<8;i++)
	// {
	// 	for(int j=0;j<8; j++)
	// 		cout<<board[i][j]<<" ";
	// 	cout<<endl;
	// }

	vector<int> x = compute_all(board, what_am_i);
	// cout<<"yo"<<endl;
	// if(x[2]==2)
	// {
	// 	for(int i=0;i<x.size();i++)
	// 		if(i==2)
	// 			heur+=x[i]*(2);
	// 		else if(i==9)
	// 			heur += x[i]*-1000;
	// 		else
	// 			heur += weights[i]*x[i];	
	// }
	// else if(x[2]==1)
	// {
	// 	for(int i=0;i<x.size();i++)
	// 		if(i==2)
	// 			heur+=x[i]*200;
	// 		else if(i==9)
	// 			heur += x[i]*-1000;
	// 		else
	// 			heur += weights[i]*x[i];
	// }

	// else
	for(int i=0;i<x.size();i++)
		heur += weights[i]*x[i];

	//cout<<"Final heuristic: "<<heur<<endl;
	// heur = 1/(1+exp(-1*heur));

	if(x[8]<=2)
		return -1*INFINITY;
	else if(x[9]<=2)
		return INFINITY;

	return heur;
}


// int main()
// {
// 	int n,m;
// 	cin>>n>>m;
// 	vector<vector<int>> board{

// 		{4,0,4,0,4,0,4,0},
// 		{0,0,0,0,0,0,0,0},
// 		{0,0,0,0,0,0,0,0},
// 		{0,3,0,0,0,0,0,3},
// 		{0,0,0,0,0,1,0,0},
// 		{0,3,0,0,1,0,0,0},
// 		{0,0,0,1,1,0,0,0},
// 		{0,2,1,2,0,2,0,3}
// 	};

// 	// vector<vector<int> > board;

// 	// for(int i=0;i<n;i++){
// 	// 	vector<int> temp;
// 	// 	board.push_back(temp);
// 	// 	for(int j=0;j<m;j++){
// 	// 		int x;
// 	// 		cin>>x;
// 	// 		board[i].push_back(x);
// 	// 	}
// 	// }

// 	ifstream w_file;
// 	vector<double> weights;
// 	w_file.open("master_weights.txt");
// 	string line;
// 	int count=1;
// 	double weight;
// 	//cout<<"oy"<<endl;
// 	while(count<=25)
// 	{
// 		count++;
// 		w_file>>weight;
// 		weights.push_back(weight);
// 	}
// 	w_file.close();
// 	count=1;

// 	double score = heuristic(board,weights,0);
// 	cout<<"SCORE: "<<score<<endl;

// 	return 0;
// }