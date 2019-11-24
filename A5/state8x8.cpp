#include<bits/stdc++.h>
#include "state.h"
using namespace std;
// ofstream ft;

vector<pair<vector<vector<int> >,double> > giveNeighbourStates(vector<vector<int> > v,int n,int m,int id,bool swap);
string actionToString(vector<vector<int> > v1, vector<vector<int> > v2,int n,int m);
/*	
int main(){

	int n,m,id;
	cin>>id>>n>>m;

	vector<vector<int> > v;

	for(int i=0;i<n;i++){
		vector<int> temp;
		v.push_back(temp);
		for(int j=0;j<m;j++){
			int x;
			cin>>x;
			v[i].push_back(x);
		}
	}

	vector<pair<vector<vector<int> >,double> > ans = giveNeighbourStates(v,n,m,id,false);
	int temp =0;
	
	for(int l=0;l<ans.size();l++){
		temp++;
		cout<<"New State: "<<temp<<endl;
		cout<<actionToString(v,(ans[l].first),8,8)<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cout<<(ans[l].first)[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}




	return 0;
}*/

vector<pair<vector<vector<int> >,double> > giveNeighbourStates(vector<vector<int> > v,int n, int m, int id, bool swap){

	vector<pair<vector<vector<int> >,double> >  ans;
	// ft.open("output1.txt",std::ios_base::app);

	int k=-1;
	bool flag = false;

	//id = 0 black
	//id =1 white
	if(!swap){
		if(id==0){ 
			//soldiers movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==1){
						//look for F movement
						if(i-1>=0 && v[i-1][j]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j] = 0;
							(ans[k].first)[i-1][j] = 1;
						}
						//look for FL movement
						if(i-1>=0 && j+1<m && v[i-1][j+1]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i-1][j+1]=1;
						}
						//loook for FR movement
						if(i-1>=0 && j-1>=0 && v[i-1][j-1]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i-1][j-1]=1;
						}

						//if there is a soldier in front of other
						bool b = (i-1>=0 && v[i-1][j]==3) || (i-1>=0 && j-1>=0 && v[i-1][j-1]==3) || (i-1>=0 && j+1<m && v[i-1][j+1]==3) || (j-1>=0 && v[i][j-1]==3) || (j+1<m && v[i][j+1]==3);
						// ft<<"ij"<<i<<j<<" "<<b<<endl;
						if(b){
							//5 extra movements will be added
							//look for L
							if(j-1>=0 && (v[i][j-1]==3 || v[i][j-1]==4)){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j-1]=1;
							}
							//look for  R
							if(j+1<m && (v[i][j+1]==3 || v[i][j-1]==4)){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j+1]=1;
							}
							//look for BB
							if(i+2<n && v[i+2][j]!=1 && v[i+2][j]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j]=1;
							}
							//look for BR
							if(i+2<n && j-2>=0 && v[i+2][j-2]!=1 && v[i+2][j-2]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j-2]=1;
							}
							//look for BL
							if(i+2<n && j+2<m && v[i+2][j+2]!=1 && v[i+2][j+2]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j+2]=1;
							}

						}
						//only L movement
						if(j-1>=0 && v[i][j-1]==4){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j-1]=1;
						}

						//only for R movement
						if(j+1<m && v[i][j+1]==4){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j+1]=1;
						}
					}


				}
			}


			//cannon shot and movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==1){
						//looking for horizontal cannon
						//x,y will be the tail of cannon
						//i,j will be the head of cannon
						int x = j;
						int y=0; 	//will be used later
						while(x+1<m && v[i][x+1]==1 && x-j<2)
							x++;

						//size of cannon = x-j+1

						//if cannon is detected
						if(x-j>=2){
							//cannon already detected
							// bool temp = false;
							// if(j-1>=0 && v[i][j-1]==1)
							// 	temp = true;

							//forward shot and movement (<----)
							if(j-1>=0&&v[i][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][x]=0;
								(ans[k].first)[i][j-1]=1;

								//shot at 2 pos away
								if(j-2>=0 && (v[i][j-2]==3 || v[i][j-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-2]=0;
								}

								//shot at 2 pos away --empty
								if(!flag && j-2>=0 && v[i][j-2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(j-3>=0 && (v[i][j-3]==3 || v[i][j-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-3]=0;
								}

								//shot at 3 pos away --empty
								if(!flag && j-3>=0 && v[i][j-3]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//backward shot and movement (----->)
							if(x+1<m && v[i][x+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][x+1]=1;

								//shot at 2 pos away
								if(x+2<m && (v[i][x+2]==3 || v[i][x+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+2]=0;
								}

								//shot at 2 pos away --empty
								if(!flag && x+2<m && v[i][x+2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(x+3<m && (v[i][x+3]==3 || v[i][x+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+3]=0;
								}

								//shot at 3 pos away --empty
								if(!flag && x+3<m && v[i][x+3]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}


						//looking for vertical cannon
						x = i;
						while(x+1<n && v[x+1][j]==1 && x-i<2)
							x++;

						//we found cannon vertically
						if(x-i>=2){	
							//cannon already detected
							bool temp = false;
							// if(i-1>=0 && v[i-1][j]==1)
							// 	temp = true;

							//for upward shot and movemet
							if(i-1>=0 && v[i-1][j]==0 && !temp){
								//movement
								// cout<<"yo"<<endl;
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][j]=0;
								(ans[k].first)[i-1][j]=1;

								//forward shot at 2 pos away
								if(i-2>=0 && (v[i-2][j]==3 || v[i-2][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j]=0;
								}

								//forward shot at 2 pos away --empty
								if(!flag && i-2>=0 && v[i-2][j]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(i-3>=0 && (v[i-3][j]==3 || v[i-3][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j]=0;
								}

								//forward shot at 3 pos away --empty
								if(!flag && i-3>=0 && v[i-3][j]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for downward shot and movement
							if(x+1<n && v[x+1][j]==0 && !temp){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][j]=1;

								//forward shot at 2 pos away
								if(x+2<n && (v[x+2][j]!=1 && v[x+2][j]!=2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][j]=0;
								}

								//forward shot at 2 pos away
								if(x+2<n && (v[x+2][j]==3 || v[x+2][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][j]=0;
								}

								//forward shot at 3 pos away
								if(x+3<n && (v[x+3][j]==3 || v[x+3][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && x+2<n && v[x+2][j]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && x+3<n && v[x+3][j]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}


						}

						//if cannon found diagonally dd1
						x=i;
						y=j;

						while(x+1<n && y+1<m && v[x+1][y+1]==1 && x-i<2 && y-i<2){
							x++;
							y++;
						}

						//size of cannon will be min(x-i+1,y-j+1)
						int size = min(x-i,y-j);
						if(size>=2){
							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j-1>=0 && v[i-1][j-1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j-1>=0 && v[i-1][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j-1]=1;

								//shot at 2 pos away
								if(i-2>=0 && j-2>=0 && (v[i-2][j-2]==3 || v[i-2][j-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j-2]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j-2>=0 && v[i-2][j-2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(i-3>=0 && j-3>=0 && (v[i-3][j-3]==3 || v[i-3][j-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j-3]=0;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j-3>=0 && v[i-3][j-3]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y+1<m && v[x+1][y+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y+1]=1;

								//shot at 2 pos away
								if(x+2<n && y+2<m && (v[x+2][y+2]==3 || v[x+2][y+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y+2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y+3<m && (v[x+3][y+3]==3 || v[x+3][y+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y+2<m && v[x+2][y+2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y+3<m && v[x+3][y+3]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}

						//if cannon found diagonally dd2
						x=i;
						y=j;

						while(x+1<n && y-1>=0 && v[x+1][y-1]==1 && x-i<2 && j-y<2){
							x++;
							y--;
						}

						//size of cannon will be min(x-i+1,j-y+1)
						size = min(x-i,j-y);
						if(size>=2){
							//if this cannon is already found
							// cout<<"dd2i,x,j,y:"<<i<<" "<<x<<" "<<j<<" "<<y;
							// bool temp = false;
							// if(i-1>=0 && j+1<m && v[i-1][j+1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j+1<m && v[i-1][j+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j+1]=1;

								//shot at 2 pos away
								if(i-2>=0 && j+2<m && (v[i-2][j+2]==3 || v[i-2][j+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j+2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j+3<m && (v[i-3][j+3]==3 || v[i-3][j+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j+3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j+2<m && v[i-2][j+2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j+3<m && (v[i-3][j+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y-1>=0 && v[x+1][y-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y-1]=1;

								//shot at 2 pos away
								if(x+2<n && y-2>=0 && (v[x+2][y-2]==3 || v[x+2][y-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y-2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y-3>=0 && (v[x+3][y-3]==3 || v[x+3][y-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y-3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y-2>=0 && v[x+2][y-2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y-3>=0 && (v[x+3][y-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag=true;
								}

							}

						}



					}
				}
			}
		}


		//for white
		else{
			//soldiers movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==1){
						//look for F movement
						if(i+1<n && v[i+1][j]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j] = 0;
							(ans[k].first)[i+1][j] = 1;
						}
						//look for FL movement
						if(i+1<n && j+1<m && v[i+1][j+1]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i+1][j+1]=1;
						}
						//loook for FR movement
						if(i+1<n && j-1>=0 && v[i+1][j-1]!=1){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i+1][j-1]=1;
						}

						//if there is a soldier in front of other
						bool b = (i+1<n && v[i+1][j]==3) || (i+1<n && j-1>=0 && v[i+1][j-1]==3) || (i+1<n && j+1<m && v[i+1][j+1]==3) || (j-1>=0 && v[i][j-1]==3) || (j+1<m && v[i][j+1]==3);
						if(b){
							//5 extra movements will be added
							//look for R
							if(j-1>=0 && (v[i][j-1]==3 || v[i][j-1]==4)){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j-1]=1;
							}
							//look for  L
							if(j+1<m && (v[i][j+1]==3 || v[i][j-1]==4)){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j+1]=1;
							}
							//look for BB
							if(i-2>=0 && v[i-2][j]!=1 && v[i-2][j]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j]=1;
							}
							//look for BR
							if(i-2>=0 && j-2>=0 && v[i-2][j-2]!=1 && v[i-2][j-2]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j-2]=1;
							}
							//look for BL
							if(i-2>=0 && j+2<m && v[i-2][j+2]!=1 && v[i-2][j+2]!=2){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j+2]=1;
							}

						}

						//only L movement
						if(j-1>=0 && v[i][j-1]==4){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j-1]=1;
						}

						//only for R movement
						if(j+1<m && v[i][j+1]==4){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j+1]=1;
						}
					}


				}
			}

			//cannon shot and movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==1){


						//looking for horizontal cannon
						//x will be the tail of cannon
						//j will be the head of cannon
						int x = j;
						int y=0; 	//will be used later
						while(x+1<m && v[i][x+1]==1 && x-j<2)
							x++;

						//size of cannon = x-j+1

						//if cannon is detected
						if(x-j>=2){

							//cannon already detected
							// bool temp = false;
							// if(j-1>=0 && v[i][j-1]==1)
							// 	temp = true;

							//forward shot and movement (<----)
							if(j-1>=0&&v[i][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][x]=0;
								(ans[k].first)[i][j-1]=1;

								//shot at 2 pos away
								if(j-2>=0 && (v[i][j-2]==3 || v[i][j-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-2]=0;
								}

								//shot at 3 pos away
								if(j-3>=0 && (v[i][j-3]==3 || v[i][j-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-3]=0;
								}

								//shot at 2 pos away
								if(!flag && j-2>=0 && v[i][j-2]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && j-3>=0 && v[i][j-3]==0){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//backward shot and movement (----->)
							if(x+1<m && v[i][x+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][x+1]=1;

								//shot at 2 pos away
								if(x+2<m && (v[i][x+2]==3 || v[i][x+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+2]=0;
								}

								//shot at 3 pos away
								if(x+3<m && (v[i][x+3]==3 || v[i][x+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<m && (v[i][x+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<m && (v[i][x+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}


						//looking for vertical cannon
						x = i;
						while(x+1<n && v[x+1][j]==1 && x-i<2)
							x++;

						//we found cannon vertically
						if(x-i>=2){

							//cannon already detected
							// bool temp = false;
							// if(i-1>=0 && v[i-1][j]==1)
							// 	temp = true;

							//for upward shot and movemet
							if(i-1>=0 && v[i-1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][j]=0;
								(ans[k].first)[i-1][j]=1;

								//forward shot at 2 pos away
								if(i-2>=0 && (v[i-2][j]==3 || v[i-2][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j]=0;
								}

								//forward shot at 3 pos away
								if(i-3>=0 && (v[i-3][j]==3 || v[i-3][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && i-2>=0 && (v[i-2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && i-3>=0 && (v[i-3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for downward shot and movement
							if(x+1<n && v[x+1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][j]=1;

								//forward shot at 2 pos away
								if(x+2<n && (v[x+2][j]==3 || v[x+2][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][j]=0;
								}

								//forward shot at 3 pos away
								if(x+3<n && (v[x+3][j]==3 || v[x+3][j]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && x+2<n && (v[x+2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && x+3<n && (v[x+3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}


						}

						//if cannon found diagonally dd1
						x=i;
						y=j;

						while(x+1<n && y+1<m && v[x+1][y+1]==1 && x-i<2 && y-j<2){
							x++;
							y++;
						}

						//size of cannon will be min(x-i+1,y-j+1)
						int size = min(x-i,y-j);
						if(size>=2){

							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j-1>=0 && v[i-1][j-1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j-1>=0 && v[i-1][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j-1]=1;

								//shot at 2 pos away
								if(i-2>=0 && j-2>=0 && (v[i-2][j-2]==3 || v[i-2][j-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j-2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j-3>=0 && (v[i-3][j-3]==3 || v[i-3][j-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j-3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j-2>=0 && (v[i-2][j-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j-3>=0 && (v[i-3][j-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y+1<m && v[x+1][y+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y+1]=1;

								//shot at 2 pos away
								if(x+2<n && y+2<m && (v[x+2][y+2]==3 || v[x+2][y+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y+2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y+3<m && (v[x+3][y+3]==3 || v[x+3][y+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y+2<m && (v[x+2][y+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y+3<m && (v[x+3][y+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}

						//if cannon found diagonally dd2
						x=i;
						y=j;

						while(x+1<n && y-1>=0 && v[x+1][y-1]==1 && x-i<2 && j-y<2){
							x++;
							y--;
						}

						//size of cannon will be min(x-i+1,j-y+1)
						size = min(x-i,j-y);
						if(size>=2){

							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j+1<m && v[i-1][j+1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j+1<m && v[i-1][j+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j+1]=1;

								//shot at 2 pos away
								if(i-2>=0 && j+2<m && (v[i-2][j+2]==3 || v[i-2][j+2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j+2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j+3<m && (v[i-3][j+3]==3 || v[i-3][j+3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j+3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j+2<m && (v[i-2][j+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j+2]=0;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j+3<m && (v[i-3][j+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y-1>=0 && v[x+1][y-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y-1]=1;

								//shot at 2 pos away
								if(x+2<n && y-2>=0 && (v[x+2][y-2]==3 || v[x+2][y-2]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y-2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y-3>=0 && (v[x+3][y-3]==3 || v[x+3][y-3]==4)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y-3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y-2>=0 && (v[x+2][y-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y-3>=0 && (v[x+3][y-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}



					}
				}
			}

		}
	}
	else{
		if(id==0)
			id=1;
		else
			id=0;

		if(id==0){ 

			//soldiers movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==3){
						//look for F movement
						if(i-1>=0 && v[i-1][j]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j] = 0;
							(ans[k].first)[i-1][j] = 3;
						}
						//look for FL movement
						if(i-1>=0 && j+1<m && v[i-1][j+1]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i-1][j+1]=3;
						}
						//loook for FR movement
						if(i-1>=0 && j-1>=0 && v[i-1][j-1]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i-1][j-1]=3;
						}


						//if there is a soldier in front of other
						bool b = (i-1>=0 && v[i-1][j]==1) || (i-1>=0 && j-1>=0 && v[i-1][j-1]==1) || (i-1>=0 && j+1<m && v[i-1][j+1]==1) || (j-1>=0 && v[i][j-1]==1) || (j+1<m && v[i][j+1]==1);
						if(b){
							//5 extra movements will be added
							//look for L
							if(j-1>=0 && v[i][j-1]==1){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j-1]=3;
							}
							//look for  R
							if(j+1<m && v[i][j+1]==1){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j+1]=3;
							}
							//look for BB
							if(i+2<n && v[i+2][j]!=3 && v[i+2][j]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j]=3;
							}
							//look for BR
							if(i+2<n && j-2>=0 && v[i+2][j-2]!=3 && v[i+2][j-2]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j-2]=3;
							}
							//look for BL
							if(i+2<n && j+2<m && v[i+2][j+2]!=3 && v[i+2][j+2]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i+2][j+2]=3;
							}

						}

						//only L movement
						if(j-1>=0 && v[i][j-1]==2){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j-1]=3;
						}

						//only for R movement
						if(j+1<m && v[i][j+1]==2){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j+1]=3;
						}


					}


				}
			}

			//cannon shot and movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==3){
						//looking for horizontal cannon
						//x,y will be the tail of cannon
						//i,j will be the head of cannon
						int x = j;
						int y=0; 	//will be used later
						while(x+1<m && v[i][x+1]==3 && x-j<2)
							x++;

						//size of cannon = x-j+1

						//if cannon is detected
						if(x-j>=2){
							//cannon already detected
							// bool temp = false;
							// if(j-1>=0 && v[i][j-1]==3)
							// 	temp = true;

							//forward shot and movement (<----)
							if(j-1>=0&&v[i][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][x]=0;
								(ans[k].first)[i][j-1]=3;

								//shot at 2 pos away
								if(j-2>=0 && (v[i][j-2]==1 || v[i][j-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-2]=0;
								}

								//shot at 3 pos away
								if(j-3>=0 && (v[i][j-3]==1 || v[i][j-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-3]=0;
								}

								//shot at 2 pos away
								if(!flag && j-2>=0 && (v[i][j-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && j-3>=0 && (v[i][j-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//backward shot and movement (----->)
							if(x+1<m && v[i][x+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][x+1]=3;

								//shot at 2 pos away
								if(x+2<m && (v[i][x+2]==1 || v[i][x+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+2]=0;
								}

								//shot at 3 pos away
								if(x+3<m && (v[i][x+3]==1 || v[i][x+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<m && (v[i][x+2]==1 || v[i][x+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<m && (v[i][x+3]==1 || v[i][x+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}


						//looking for vertical cannon
						x = i;
						while(x+1<n && v[x+1][j]==3 && x-i<2)
							x++;

						//we found cannon vertically
						if(x-i>=2){	
							//cannon already detected
							// bool temp = false;
							// if(i-1>=0 && v[i-1][j]==3)
							// 	temp = true;

							//for upward shot and movemet
							if(i-1>=0 && v[i-1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][j]=0;
								(ans[k].first)[i-1][j]=3;

								//forward shot at 2 pos away
								if(i-2>=0 && (v[i-2][j]==1 || v[i-2][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j]=0;
								}

								//forward shot at 3 pos away
								if(i-3>=0 && (v[i-3][j]==1 || v[i-3][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && i-2>=0 && (v[i-2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && i-3>=0 && (v[i-3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for downward shot and movement
							if(x+1<n && v[x+1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][j]=3;

								//forward shot at 2 pos away
								if(x+2<n && (v[x+2][j]==1 || v[x+2][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][j]=0;
								}

								//forward shot at 3 pos away
								if(x+3<n && (v[x+3][j]==1 || v[x+3][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && x+2<n && (v[x+2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && x+3<n && (v[x+3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}


						}

						//if cannon found diagonally dd1
						x=i;
						y=j;

						while(x+1<n && y+1<m && v[x+1][y+1]==3 && x-i<2 && y-j<2){
							x++;
							y++;
						}

						//size of cannon will be min(x-i+1,y-j+1)
						int size = min(x-i,y-j);
						if(size>=2){
							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j-1>=0 && v[i-1][j-1]==3)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j-1>=0 && v[i-1][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j-1]=3;

								//shot at 2 pos away
								if(i-2>=0 && j-2>=0 && (v[i-2][j-2]==1 || v[i-2][j-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j-2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j-3>=0 && (v[i-3][j-3]==1 || v[i-3][j-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j-3]=0;
								}
								//shot at 2 pos away
								if(!flag && i-2>=0 && j-2>=0 && (v[i-2][j-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j-3>=0 && (v[i-3][j-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}


							}

							//for shot and movement at tail
							if(x+1<n && y+1<m && v[x+1][y+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y+1]=3;

								//shot at 2 pos away
								if(x+2<n && y+2<m && (v[x+2][y+2]==1 || v[x+2][y+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y+2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y+3<m && (v[x+3][y+3]==1 || v[x+3][y+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y+3]=0;
								}
								//shot at 2 pos away
								if(!flag && x+2<n && y+2<m && (v[x+2][y+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y+3<m && (v[x+3][y+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}

						//if cannon found diagonally dd2
						x=i;
						y=j;

						while(x+1<n && y-1>=0 && v[x+1][y-1]==3 && x-i<2 && j-y<2){
							x++;
							y--;
						}

						//size of cannon will be min(x-i+1,j-y+1)
						size = min(x-i,j-y);
						if(size>=2){
							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j+1<m && v[i-1][j+1]==3)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j+1<m && v[i-1][j+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j+1]=3;

								//shot at 2 pos away
								if(i-2>=0 && j+2<m && (v[i-2][j+2]==1 || v[i-2][j+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j+2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j+3<m && (v[i-3][j+3]==1 || v[i-3][j+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j+3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j+2<m && (v[i-2][j+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j+3<m && (v[i-3][j+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y-1>=0 && v[x+1][y-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y-1]=3;

								//shot at 2 pos away
								if(x+2<n && y-2>=0 && (v[x+2][y-2]==1 || v[x+2][y-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y-2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y-3>=0 && (v[x+3][y-3]==1 || v[x+3][y-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y-3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y-2>=0 && (v[x+2][y-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y-3>=0 && (v[x+3][y-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}



					}
				}
			}
		}


		//for white
		else{
			//soldiers movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==3){
						//look for F movements
						if(i+1<n && v[i+1][j]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j] = 0;
							(ans[k].first)[i+1][j] = 3;
						}
						//look for FL movement
						if(i+1<n && j+1<m && v[i+1][j+1]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i+1][j+1]=3;
						}
						//loook for FR movement
						if(i+1<n && j-1>=0 && v[i+1][j-1]!=3){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i+1][j-1]=3;
						}

						//if there is a soldier in front of other
						bool b = (i+1<n && v[i+1][j]==1) || (i+1<n && j-1>=0 && v[i+1][j-1]==1) || (i+1<n && j+1<m && v[i+1][j+1]==1) || (j-1>=0 && v[i][j-1]==1) || (j+1<m && v[i][j+1]==1);
						if(b){
							//5 extra movements will be added
							//look for R
							if(j-1>=0 && v[i][j-1]==1){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j-1]=3;
							}
							//look for  L
							if(j+1<m && v[i][j+1]==1){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][j+1]=3;
							}
							//look for BB
							if(i-2>=0 && v[i-2][j]!=3 && v[i-2][j]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j]=3;
							}
							//look for BR
							if(i-2>=0 && j-2>=0 && v[i-2][j-2]!=3 && v[i-2][j-2]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j-2]=3;
							}
							//look for BL
							if(i-2>=0 && j+2<m && v[i-2][j+2]!=3 && v[i-2][j+2]!=4){
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i-2][j+2]=3;
							}

						}
						//only L movement
						if(j-1>=0 && v[i][j-1]==2){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j-1]=3;
						}

						//only for R movement
						if(j+1<m && v[i][j+1]==2){
							ans.push_back(make_pair(v,-1*INFINITY));
							k++;
							(ans[k].first)[i][j]=0;
							(ans[k].first)[i][j+1]=3;
						}
					}


				}
			}

			//cannon shot and movement
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){

					if(v[i][j]==3){


						//looking for horizontal cannon
						//x will be the tail of cannon
						//j will be the head of cannon
						int x = j;
						int y=0; 	//will be used later
						while(x+1<m && v[i][x+1]==3 && x-j<2)
							x++;

						//size of cannon = x-j+1

						//if cannon is detected
						if(x-j>=2){

							//cannon already detected
							// bool temp = false;
							// if(j-1>=0 && v[i][j-1]==3)
							// 	temp = true;

							//forward shot and movement (<----)
							if(j-1>=0&&v[i][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][x]=0;
								(ans[k].first)[i][j-1]=3;

								//shot at 2 pos away
								if(j-2>=0 && (v[i][j-2]==1 || v[i][j-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-2]=0;
								}

								//shot at 3 pos away
								if(j-3>=0 && (v[i][j-3]==1 || v[i][j-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][j-3]=0;
								}

								//shot at 2 pos away
								if(!flag && j-2>=0 && (v[i][j-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && j-3>=0 && (v[i][j-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag  =true;
								}

							}

							//backward shot and movement (----->)
							if(x+1<m && v[i][x+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[i][x+1]=3;

								//shot at 2 pos away
								if(x+2<m && (v[i][x+2]==1 || v[i][x+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+2]=0;
								}

								//shot at 3 pos away
								if(x+3<m && (v[i][x+3]==1 || v[i][x+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i][x+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<m && (v[i][x+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag=true;
								}

								//shot at 3 pos away
								if(!flag && x+3<m && (v[i][x+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag=true;
								}

							}

						}


						//looking for vertical cannon
						x = i;
						while(x+1<n && v[x+1][j]==3 && x-i<2)
							x++;

						//we found cannon vertically
						if(x-i>=2){

							//cannon already detected
							// bool temp = false;
							// if(i-1>=0 && v[i-1][j]==3)
							// 	temp = true;

							//for upward shot and movemet
							if(i-1>=0 && v[i-1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][j]=0;
								(ans[k].first)[i-1][j]=3;

								//forward shot at 2 pos away
								if(i-2>=0 && (v[i-2][j]==1 || v[i-2][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j]=0;
								}

								//forward shot at 3 pos away
								if(i-3>=0 && (v[i-3][j]==1 || v[i-3][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && i-2>=0 && (v[i-2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && i-3>=0 && (v[i-3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for downward shot and movement
							if(x+1<n && v[x+1][j]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][j]=3;

								//forward shot at 2 pos away
								if(x+2<n && (v[x+2][j]==1 || v[x+2][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][j]=0;
								}

								//forward shot at 3 pos away
								if(x+3<n && (v[x+3][j]==1 || v[x+3][j]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][j]=0;
								}

								//forward shot at 2 pos away
								if(!flag && x+2<n && (v[x+2][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//forward shot at 3 pos away
								if(!flag && x+3<n && (v[x+3][j]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}


						}

						//if cannon found diagonally dd1
						x=i;
						y=j;

						while(x+1<n && y+1<m && v[x+1][y+1]==3 && x-i<2 && y-j<2){
							x++;
							y++;
						}

						//size of cannon will be min(x-i+1,y-j+1)
						int size = min(x-i,y-j);
						if(size>=2){

							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j-1>=0 && v[i-1][j-1]==3)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j-1>=0 && v[i-1][j-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j-1]=3;

								//shot at 2 pos away
								if(i-2>=0 && j-2>=0 && (v[i-2][j-2]==1 || v[i-2][j-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j-2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j-3>=0 && (v[i-3][j-3]==1 || v[i-3][j-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j-3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j-2>=0 && (v[i-2][j-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j-3>=0 && (v[i-3][j-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y+1<m && v[x+1][y+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y+1]=3;

								//shot at 2 pos away
								if(x+2<n && y+2<m && (v[x+2][y+2]==1 || v[x+2][y+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y+2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y+3<m && (v[x+3][y+3]==1 || v[x+3][y+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y+3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y+2<m && (v[x+2][y+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y+3<m && (v[x+3][y+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag  =true;
								}

							}

						}

						//if cannon found diagonally dd2
						x=i;
						y=j;

						while(x+1<n && y-1>=0 && v[x+1][y-1]==3 && x-i<2 && j-y<2){
							x++;
							y--;
						}

						//size of cannon will be min(x-i+1,j-y+1)
						size = min(x-i,j-y);
						if(size>=2){

							//if this cannon is already found
							// bool temp = false;
							// if(i-1>=0 && j+1<m && v[i-1][j+1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j+1<m && v[i-1][j+1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[x][y]=0;
								(ans[k].first)[i-1][j+1]=3;

								//shot at 2 pos away
								if(i-2>=0 && j+2<m && (v[i-2][j+2]==1 || v[i-2][j+2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-2][j+2]=0;
								}

								//shot at 3 pos away
								if(i-3>=0 && j+3<m && (v[i-3][j+3]==1 || v[i-3][j+3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[i-3][j+3]=0;
								}

								//shot at 2 pos away
								if(!flag && i-2>=0 && j+2<m && (v[i-2][j+2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && i-3>=0 && j+3<m && (v[i-3][j+3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y-1>=0 && v[x+1][y-1]==0){
								//movement
								ans.push_back(make_pair(v,-1*INFINITY));
								k++;
								(ans[k].first)[i][j]=0;
								(ans[k].first)[x+1][y-1]=3;

								//shot at 2 pos away
								if(x+2<n && y-2>=0 && (v[x+2][y-2]==1 || v[x+2][y-2]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+2][y-2]=0;
								}

								//shot at 3 pos away
								if(x+3<n && y-3>=0 && (v[x+3][y-3]==1 || v[x+3][y-3]==2)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									(ans[k].first)[x+3][y-3]=0;
								}

								//shot at 2 pos away
								if(!flag && x+2<n && y-2>=0 && (v[x+2][y-2]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

								//shot at 3 pos away
								if(!flag && x+3<n && y-3>=0 && (v[x+3][y-3]==0)){
									ans.push_back(make_pair(v,-1*INFINITY));
									k++;
									flag = true;
								}

							}

						}



					}
				}
			}

		}

	}

	// ft.close();
	return ans;


}


string actionToString(vector<vector<int> > v1, vector<vector<int> > v2,int n,int m){
	//initial state is v1
	//final state is v2
	//n -> no_of_rows
	//m -> no_of_columns

	int x1=-1,y1=-1,x2=-1,y2=-1;
	bool b = true;

	// cout<<"initial State:\n";
	// for(int i=0;i<n;i++){
	// 	for(int j=0;j<m;j++)
	// 		cout<<v1[i][j];
	// 	cout<<endl;
	// }
	// cout<<endl;

	// cout<<"final State:\n";
	// for(int i=0;i<n;i++){
	// 	for(int j=0;j<m;j++)
	// 		cout<<v2[i][j];
	// 	cout<<endl;
	// }
	// cout<<endl;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){

			if(v1[i][j]!=v2[i][j]){
				if(b){
					x1=i;
					y1=j;
					b=false;
				}
				else{
					x2=i;
					y2=j;
					break;
				}

			}

		}
	}

	// cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
	if(x2==-1 && x1==-1){

		int bx = -1,by=-1;
		int kx =-1, ky=-1;

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){

				if(v1[i][j]==1){

					//horizontal

					//looking for horizontal cannon
						//x will be the tail of cannon
						//j will be the head of cannon
						int x = j;
						int y=0; 	//will be used later
						while(x+1<m && v1[i][x+1]==1 && x-j<2)
							x++;

						//size of cannon = x-j+1

						//if cannon is detected
						if(x-j>=2){

							//cannon already detected
							bool temp = false;
							// if(j-1>=0 && v[i][j-1]==1)
							// 	temp = true;

							//forward shot and movement (<----)
							if(j-1>=0&&v1[i][j-1]==0 && !temp){

								//shot at 2 pos away
								if(j-2>=0 && v1[i][j-2]==0){
									bx=i;
									by=j-2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(j-3>=0 && v1[i][j-3]==0){
									bx=i;
									by=j-3;
									kx =i;
									ky=j;
									break;
								}

							}

							//backward shot and movement (----->)
							if(x+1<m && v1[i][x+1]==0 && !temp){
								//shot at 2 pos away
								if(x+2<m && v1[i][x+2]==0){
									bx=i;
									by=x+2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(x+3<m && v1[i][x+3]==0){
									bx=i;
									by=x+3;
									kx =i;
									ky=j;
									break;
								}

							}

						}


						//looking for vertical cannon
						x = i;
						while(x+1<n && v1[x+1][j]==1 && x-i<2)
							x++;

						//we found cannon vertically
						if(x-i>=2){

							//cannon already detected
							bool temp = false;
							// if(i-1>=0 && v[i-1][j]==1)
							// 	temp = true;

							//for upward shot and movemet
							if(i-1>=0 && v1[i-1][j]==0 && !temp){
								//forward shot at 2 pos away
								if(i-2>=0 && v1[i-2][j]==0){
									bx=i-2;
									by=j;
									kx =i;
									ky=j;
									break;
								}

								//forward shot at 3 pos away
								if(i-3>=0 && v1[i-3][j]==0){
									bx=i-3;
									by=j;
									kx =i;
									ky=j;
									break;
								}

							}

							//for downward shot and movement
							if(x+1<n && v1[x+1][j]==0 && !temp){
								//forward shot at 2 pos away
								if(x+2<n && v1[x+2][j]==0){
									bx=x+2;
									by=j;
									kx =i;
									ky=j;
									// cout<<"washere\n";
									break;
								}

								//forward shot at 3 pos away
								if(x+3<n && v1[x+3][j]==0){
									bx=x+3;
									by=j;
									kx =i;
									ky=j;
									break;
								}

							}


						}

						//if cannon found diagonally dd1
						x=i;
						y=j;

						while(x+1<n && y+1<m && v1[x+1][y+1]==1 && x-i<2 && y-j<2){
							x++;
							y++;
						}

						//size of cannon will be min(x-i+1,y-j+1)
						int size = min(x-i,y-j);
						if(size>=2){

							//if this cannon is already found
							bool temp = false;
							// if(i-1>=0 && j-1>=0 && v[i-1][j-1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j-1>=0 && v1[i-1][j-1]==0 && !temp){

								//shot at 2 pos away
								if(i-2>=0 && j-2>=0 && v1[i-2][j-2]==0 ){
									bx=i-2;
									by=j-2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(i-3>=0 && j-3>=0 && v1[i-3][j-3]==0){
									bx=i-3;
									by=j-2;
									kx =i;
									ky=j;
									break;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y+1<m && v1[x+1][y+1]==0 && !temp){

								//shot at 2 pos away
								if(x+2<n && y+2<m && v1[x+2][y+2]==0){
									bx=x+2;
									by=y+2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(x+3<n && y+3<m && v1[x+3][y+3]==0){
									bx=x+3;
									by=y+3;
									kx =i;
									ky=j;
									break;
								}

							}

						}

						//if cannon found diagonally dd2
						x=i;
						y=j;

						while(x+1<n && y-1>=0 && v1[x+1][y-1]==1 && x-i<2 && j-y<2){
							x++;
							y--;
						}

						//size of cannon will be min(x-i+1,j-y+1)
						size = min(x-i,j-y);
						if(size>=2){

							//if this cannon is already found
							bool temp = false;
							// if(i-1>=0 && j+1<m && v[i-1][j+1]==1)
							// 	temp = true;

							//for shot and movement at head
							if(i-1>=0 && j+1<m && v1[i-1][j+1]==0 && !temp){
								//shot at 2 pos away
								if(i-2>=0 && j+2<m && v1[i-2][j+2]==0){
									bx=i-2;
									by=j+2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(i-3>=0 && j+3<m && v1[i-3][j+3]==0){
									bx=i-3;
									by=j+3;
									kx =i;
									ky=j;
									break;
								}

							}

							//for shot and movement at tail
							if(x+1<n && y-1>=0 && v1[x+1][y-1]==0 && !temp){

								//shot at 2 pos away
								if(x+2<n && y-2>=0 && v1[x+2][y-2]==0 ){
									bx=x+2;
									by=y-2;
									kx =i;
									ky=j;
									break;
								}

								//shot at 3 pos away
								if(x+3<n && y-3>=0 && v1[x+3][y-3]==0){
									bx=x+3;
									by=y-2;
									kx =i;
									ky=j;
									break;
								}

							}

						}

				}

				if(bx!=-1){
					return "S " + to_string(ky) + " " + to_string(kx) +" B " + to_string(by) + " " +to_string(bx);
				}

			}
		}

		return  "Invalidn";


	}


	//if soldier is moved
	if(x2!=-1 && v1[x1][y1]==1 && v2[x2][y2]==1 && v2[x1][y1]==0){
		//i.e. soldier is moved from x1,y1 to x2,y2 pos;
		return "S " + to_string(y1)+" "+to_string(x1) +" M "+ to_string(y2)+" "+to_string(x2);
	}
	if(x2!=-1 && v1[x2][y2]==1 && v2[x1][y1]==1 && v2[x2][y2]==0){
		//if soldier moved from x2,y2 to x1,y1
		return "S " + to_string(y2)+" "+to_string(x2) +" M "+ to_string(y1)+" "+to_string(x1);
	}

	//if cannon is shot
	if(x2==-1 && v2[x1][y1]==0 && (v1[x1][y1]==3 || v1[x1][y1]==4)){
		//if cannon is shot at x1,y1

		//looking for position from where it is shot

		//shot from below
		if(x1+4<n && v1[x1+2][y1]==1 && v1[x1+3][y1]==1 && v1[x1+4][y1]==1 && v1[x1+1][y1]==0)
			return "S " + to_string(y1)+" "+to_string(x1+2) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from right side
		if(y1+4<m && v1[x1][y1+2]==1 && v1[x1][y1+3]==1 && v1[x1][y1+4]==1 && v1[x1][y1+1]==0)
			return "S " + to_string(y1+2)+" "+to_string(x1) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from above
		if(x1-4>=0 && v1[x1-2][y1]==1 && v1[x1-3][y1]==1 && v1[x1-4][y1]==1 && v1[x1-1][y1]==0)
			return "S " + to_string(y1)+" "+to_string(x1-2) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from left side
		if(y1-4>=0 && v1[x1][y1-2]==1 && v1[x1][y1-3]==1 && v1[x1][y1-4]==1 && v1[x1][y1-1]==0)
			return "S " + to_string(y1-2)+" "+to_string(x1) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal below right
		if(x1+4<n && y1+4<m && v1[x1+2][y1+2]==1 && v1[x1+3][y1+3]==1 && v1[x1+4][y1+4]==1 && v1[x1+1][y1+1]==0)
			return "S " + to_string(y1+2)+" "+to_string(x1+2) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal below left
		if(x1+4<n && y1-4>=0 && v1[x1+2][y1-2]==1 && v1[x1+3][y1-3]==1 && v1[x1+4][y1-4]==1 && v1[x1+1][y1-1]==0)
			return "S " + to_string(y1-2)+" "+to_string(x1+2) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal above left
		if(x1-4>=0 && y1-4>=0 && v1[x1-2][y1-2]==1 && v1[x1-3][y1-3]==1 && v1[x1-4][y1-4]==1 && v1[x1-1][y1-1]==0)
			return "S " + to_string(y1-2)+" "+to_string(x1-2) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal above right
		if(x1-4>=0 && y1+4<m && v1[x1-2][y1+2]==1 && v1[x1-3][y1+3]==1 && v1[x1-4][y1+4]==1 && v1[x1-1][y1+1]==0)
			return "S " + to_string(y1+2)+" "+to_string(x1-2) +" B "+ to_string(y1)+" "+to_string(x1);



		//for 3
		//shot from below
		if(x1+5<n && v1[x1+3][y1]==1 && v1[x1+4][y1]==1 && v1[x1+5][y1]==1 && v1[x1+2][y1]==0)
			return "S " + to_string(y1)+" "+to_string(x1+3) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from right side
		if(y1+5<m && v1[x1][y1+3]==1 && v1[x1][y1+4]==1 && v1[x1][y1+5]==1 && v1[x1][y1+2]==0)
			return "S " + to_string(y1+3)+" "+to_string(x1) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from above
		if(x1-5>=0 && v1[x1-3][y1]==1 && v1[x1-4][y1]==1 && v1[x1-5][y1]==1 && v1[x1-2][y1]==0)
			return "S " + to_string(y1)+" "+to_string(x1-3) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from left side
		if(y1-5>=0 && v1[x1][y1-3]==1 && v1[x1][y1-4]==1 && v1[x1][y1-5]==1 && v1[x1][y1-2]==0)
			return "S " + to_string(y1-3)+" "+to_string(x1) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal below right
		if(x1+5<n && y1+5<m && v1[x1+3][y1+3]==1 && v1[x1+4][y1+4]==1 && v1[x1+5][y1+5]==1 && v1[x1+2][y1+2]==0)
			return "S " + to_string(y1+3)+" "+to_string(x1+3) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal below left
		if(x1+5<n && y1-5>=0 && v1[x1+3][y1-3]==1 && v1[x1+4][y1-4]==1 && v1[x1+5][y1-5]==1 && v1[x1+2][y1-2]==0)
			return "S " + to_string(y1-3)+" "+to_string(x1+3) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal above left
		if(x1-5>=0 && y1-5>=0 && v1[x1-3][y1-3]==1 && v1[x1-4][y1-4]==1 && v1[x1-5][y1-5]==1 && v1[x1-2][y1-2]==0)
			return "S " + to_string(y1-3)+" "+to_string(x1-3) +" B "+ to_string(y1)+" "+to_string(x1);

		//shot from diagonal above right
		if(x1-5>=0 && y1+5<m && v1[x1-3][y1+3]==1 && v1[x1-4][y1+4]==1 && v1[x1-5][y1+5]==1 && v1[x1-2][y1+2]==0)
			return "S " + to_string(y1+3)+" "+to_string(x1-3) +" B "+ to_string(y1)+" "+to_string(x1);


	}



	return "Invalid State";

}
