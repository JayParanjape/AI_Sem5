#include <iostream>
#include <vector>
#include <string.h>
#include <bits/stdc++.h>
#include "loss.h"
using namespace std;

int finder(vector<char> &vocab,char c)
{
	for(int i=0;i<vocab.size();i++)
	{
		if(vocab[i]==c)
			return i;
	}
	return -1;
}

// double conv_cost(double CC, vector<string> &words)
// {
// 	//return the total conversion cost for all strings in the words vector,
// 	//Inputs: CC - cost of adding a dash
// 	//		  words - a vector of strings

// 	int total=0;
// 	for(int i=0;i<words.size();i++)
// 	{
// 		string str = words[i];
// 		total += std::count(str.begin(),str.end(),'-');
// 	}
// 	return CC*total;
// }

// double matching_cost(vector<vector<double>> &MC, vector<string> &words, vector<char> &vocab)
// {
// 	//returns the pairwise matching cost for all strings according to MC
// 	//Inputs: MC - array describing the costs
// 	//		  words - vector of all strings, assuming same lengths
// 	//		  vocab - vector representing the vocabulary.

// 	double ans=0;
// 	int len = words.size(); int word_size = words[0].size();
// 	for(int i=0;i<len;i++)
// 	{
// 		for(int j=i+1;j<len;j++)
// 		{
// 			for(int k=0;k<word_size;k++)
// 			{
// 				char letter1 = words[i][k]; char letter2 = words[j][k];
// 				int l1_pos = finder(vocab,letter1);
// 				int l2_pos = finder(vocab,letter2);
// 				ans += MC[l1_pos][l2_pos];
// 			}
// 		}
// 	}
// 	return ans;
// }

int max_length(vector<string> &words)
{
	int ans=0;
	for(int i=0;i<words.size();i++)
	{
		if(words[i].size()>ans)
			ans = words[i].size();
	}
	return ans;
}

double total_cost(double CC, vector<string> &words,vector<vector<double>> &MC, vector<char> &vocab )
{
	// Compute the total cost of matching and conversion for given vector of strings
	//Inputs: CC - cost of adding a dash
 	//		  words - vector of all strings, assuming same lengths
	//		  MC - array describing the costs
 	//		  vocab - vector representing the vocabulary.

	double ans=0; int len=words.size(); int mc_size=MC.size();
	//Find out the maximum length of a string in the vector
	int max_len = max_length(words);
	int dashes=0;
	for(int i=0;i<len;i++)
	{
		string word = words[i];
		dashes += (count(word.begin(),word.end(),'-') + max_len - word.size() );
	}
	//cout<<"Dashes: "<<dashes<<endl;


	for(int i=0;i<len;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			//Loop through all combinations of 2 words
			string word1 = words[i]; string word2 = words[j];
			int size1 = word1.size(); int size2 = word2.size();
			//cout<<"Size1: "<<size1<<" Size2: "<<size2<<endl;
			//cout<<ans<<endl;
			for(int k=0;k<max_len;k++)
			{

				//Starting from the end, match chars of the string, if null then consider it as a dash
				int pos1 = size1-k-1; int pos2 = size2-k-1;

				if(pos1<0 && pos2<0)
				{
					//ans = ans + (CC*2);
					ans += MC[mc_size-1][mc_size-1];
				}
				else if(pos1>=0 && pos2<0)
				{
					int l1_pos = finder(vocab,word1[pos1]);

					ans = ans + MC[l1_pos][mc_size-1]; //+ CC;
					// if(word1[pos1]=='-')
					// 	ans+=CC;
				}
				else if(pos1<0 && pos2>=0)
				{
					int l2_pos = finder(vocab,word2[pos2]);
					ans = ans + MC[mc_size-1][l2_pos];// + CC;
					// if(word2[pos2]=='-')
					// 	ans+=CC;
				}
				else
				{
					//cout<<"letter1: "<<word1[pos1]<<" letter2: "<<word2[pos2]<<endl;
					int l1_pos = finder(vocab,word1[pos1]);
					int l2_pos = finder(vocab,word2[pos2]);
					// if(i==len-2)
					// {
					// 	cout<<l1_pos<<", "<<vocab[l1_pos]<<", "<<l2_pos<<", "<<vocab[l2_pos]<<endl;
					// 	cout<<MC[l1_pos][l2_pos]<<endl;
					// }
					ans = ans + MC[l1_pos][l2_pos];
					//cout<<ans<<endl;;
					// if(word1[pos1]=='-')
					// 	ans+=CC;
					// if(word2[pos2]=='-')
					// 	ans+=CC;
				}

			}
		}
	}
	//cout<<(dashes*CC)<<endl;
	ans += (dashes*CC);
	return ans;
}

// int main()
// {
// 	double CC=9.0;
// 	vector<string> words{"VQNQNHNQ","I----HI-","R---NHHK","Y----HV-"};
// 	vector<char> vocab{'K','V','I','Q','Y','R','N','H','-'};

// 	vector<vector<double>> MC{
// 		{0,19,14,19,0,18,19,11,12},
// 		{19,0,2,18,14,7,7,1,14},
// 		{14,2,0,1,7,12,1,19,16},
// 		{19,18,1,0,19,8,4,13,2},
// 		{0,14,7,19,0,12,15,0,14},
// 		{18,7,12,8,12,0,18,16,15},
// 		{19,7,1,4,15,18,0,17,12},
// 		{11,1,19,13,0,16,17,0,17},
// 		{12,14,16,2,14,15,12,17,0}
// 	};

// 	// vector<string> words{"-ACTGTGA","TACT--GC","-ACTG--A"};
// 	// vector<char> vocab{'A','C','T','G','-'};

// 	// vector<vector<double>> MC{
// 	// 	{0,2,2,2,1},
// 	// 	{2,0,2,2,1},
// 	// 	{2,2,0,2,1},
// 	// 	{2,2,2,0,1},
// 	// 	{1,1,1,1,0}
// 	// };

// 	// cout<< "The conv cost is "<<conv_cost(CC,words)<<endl;
// 	// cout<< "The matching cost is "<<matching_cost(MC,words,vocab)<<endl;
// 	cout<< "The total cost is "<<total_cost(CC,words,MC,vocab)<<endl;
// 	return 0;
// }
