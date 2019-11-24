#include<bits/stdc++.h>
using namespace std;
int main(){
	int id,n,m;
	cin>>id;
	cin>>n;
	cin>>m;

	double time;
	cin>>time;

	ofstream of;
	of.open("selector.txt",std::ios_base::trunc);
	of<<id<<endl;
	of<<n<<endl;
	of<<m<<endl;
	of<<time<<endl;

	if(n==8 && m==8)
		system("./master8x8");
	else
		system("./master_108");

	return 0;

}