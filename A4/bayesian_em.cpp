#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <unordered_map>
#include <memory>
#include <chrono>
// #define chrono::
#define GET_DURATION(x) chrono::duration_cast<chrono::duration<double>>(x)
#define TIME chrono::high_resolution_clock::time_point
#define GET_TIME chrono::high_resolution_clock::now()
#define DURATION chrono::duration<double> 
#define DEBUG(x)  std::cout<<x<<endl
// #define DEB
// #define DEBUG1
#include <algorithm>
using namespace std;

template<typename T>
void print_vec(vector<T>& vt){
    for(int i=0;i<vt.size();i++){
        cout<<vt[i]<<" ";
    }
    cout<<endl;
}
int get_dim_for_index(vector<int>& dimens, int index){
    int dim_prod = 1;
    for(int i=index+1;i<dimens.size();i++){
        dim_prod *= dimens[i];
    }
    return dim_prod;
}
void get_dim_multiplied(vector<int>& dimens, vector<int>& dimens_m){
    dimens_m.resize(dimens.size());
    dimens_m[dimens.size()-1] = 1;
    for(int i=dimens_m.size()-2;i>=0;i--){
        dimens_m[i] = dimens[i+1]*dimens_m[i+1];
    }

}
class NetworkNode{
    public:

    string Node_Name;
    vector<int> children;
    vector<int> parents;
    // vector<string> Parents;
    // int nvalues;
    int domain_size;
    vector<string> values;
    vector<float> CPT;
    unordered_map<string,int> value_mapped;

    //NetworkNode(string name, vector<NetworkNode*> Child_Nodes,vector<NetworkNode*> Parent_Nodes,int n, vector<string> vals,vector<float> curr_CPT)
    
    NetworkNode(string name,vector<string> vals)
    {
        Node_Name=name;
        domain_size = vals.size();
        values=vals;
        int i=0;
        for(string val: vals){
            value_mapped[val] = i++;
        }
    }
    string get_name()
    {
        return Node_Name;
    }

};



class network{
public:
    vector<NetworkNode*> Pres_Graph;
    unordered_map<string,int> variable_mapping;
    vector<string> variables;

    void addNode(NetworkNode* node)
    {
        Pres_Graph.push_back(node);
    }

    NetworkNode* getNode(int i){
        return Pres_Graph[i];
    }
    int netSize()
    {
        return Pres_Graph.size();
    }

};

network read_network(char* filename)
{
    network Alarm;
    string line;
    int find=0;
    ifstream myfile(filename);
    string temp;
    string name;
    vector<string> values;
    
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            stringstream ss;
            getline (myfile,line);
            
            
            ss.str(line);
            ss>>temp;
            
            
            if(temp.compare("variable")==0)
            {
                
                ss>>name;
                getline (myfile,line);
                
                stringstream ss2;
                ss2.str(line);
                for(int i=0;i<4;i++)
                {
                    
                    ss2>>temp;
                    
                    
                }
                values.clear();
                while(temp.compare("};")!=0)
                {
                    values.push_back(temp);
                    
                    ss2>>temp;
                }
                Alarm.variable_mapping[name] = Alarm.variables.size();
                Alarm.variables.push_back(name);
                NetworkNode* new_node = new NetworkNode(name,values);
                // int pos=
                Alarm.addNode(new_node);
                
                
            }
            else if(temp.compare("probability")==0)
            {
                
                ss>>temp;
                
                ss>>temp;
                // std::cout<<temp<<endl;
                int index = Alarm.variable_mapping[temp];
                ss>>temp;
                values.clear();
                
                while(temp.compare(")")!=0)
                {
                    int pindex = Alarm.variable_mapping[temp];
                    Alarm.Pres_Graph[pindex]->children.push_back(index);
                    Alarm.Pres_Graph[index]->parents.push_back(pindex);
                    ss>>temp;

                }
                getline (myfile,line);
                stringstream ss2;   
                ss2.str(line);
                ss2>> temp;
                
                ss2>> temp;
                
                vector<float>& curr_CPT = Alarm.Pres_Graph[index]->CPT;
                while(temp.compare(";")!=0)
                {        
                    curr_CPT.push_back(atof(temp.c_str()));   
                    ss2>>temp;
                }
            }
            else
            {
                
            }
        }
        
        if(find==1)
        myfile.close();
    }
    
    return Alarm;
}
void print_alarm(network& net, char* filename, char* outfile)
{
    network Alarm;
    string line,testline;
    int find=0;
    ifstream myfile(filename);
    ofstream testfile(outfile);
    string temp;
    string name;
    vector<string> values;
    int line_count=1;
    int i=0;
    if (myfile.is_open())
    {
        
        while (! myfile.eof() )
        {
            
            getline (myfile,line);
            testfile << line;
            if (myfile.peek()!=-1 || line.length()==0){
                testfile<<endl;
            }
            line_count++;
            stringstream ss;
            ss.str(line);
            ss>>temp;
    
            if(temp.compare("probability")==0)
            {
                string test_temp;
                
                getline (myfile,line);
                testfile << "table ";
                NetworkNode* listIt1=net.Pres_Graph[i++];
        
                vector<float>& cpt1=listIt1->CPT;

                for(int j=0;j<cpt1.size();j++){
                    float tmp_prob = cpt1[j];

                    if (tmp_prob>0.99){
                        tmp_prob = 0.99;
                    }
                    else if(tmp_prob<0.01){
                        tmp_prob = 0.01;
                    }
                    char tmp[100];
                    int n = snprintf(tmp,100,"%0.4f ",tmp_prob);
                    
                    // testfile << std::fixed << std::setprecision(2) << var1 << " var2: " << var2;
                    // fprintf((FILE*)testfile,"%0.4f ",cpt1[j]);
                    // testfile<<cpt1[j]<<" ";
                    testfile << tmp;
                }
                testfile<<";"<<endl;
               
                line_count++;
                
            }

        }
        
        myfile.close();
        testfile.close();
    }
    
}

class Record{
    public:
        vector<int> data;  //if -1 then needs to get data distribution from missing_prob
        int missing_var;
        vector<float>* missing_prob; //access the question marked prob distribution
        int missing_value;
        //update this 

};

// void update_cpt(vector<Record*>& rc, vector<NetworkNode*>& nt){
//     int nvars = nt.size();
//     for(int i=0;i<nvars;i++){
//         vector<float>& old_vals = nt[i]->CPT;
//         vector<float> new_vals(old_vals.size(),0); 
//         //iterate through all records, and update new_vals


int get_offset(vector<int>& vals, vector<int>& domains){
    int offset = vals[0];
    for(int i=1;i<vals.size();i++){
        offset = offset*domains[i] + vals[i];
    }
    return offset;
}
int get_partial_offset(vector<int>& vals, vector<int>& domains, int qindex){
    int offset = vals[0];
    if (offset==-1){
        offset =0;
    }
    if (qindex==0){
        offset = 0;
    }
    for(int i=1;i<vals.size();i++){
        if (vals[i]==-1){
            offset = offset*domains[i];
        }
        else{
            offset = offset*domains[i]  + vals[i];
        }
    }
    // for(int i=1;i<qindex;i++){
    //     offset = offset*domains[i] + vals[i];
    // }
    // for(int i= qindex+1;i<vals.size();i++){
    //     offset = offset*domains[i] + vals[i];
    // }
    return offset;
}
void update_dimension(vector<int>& dimen, NetworkNode& nt, vector<NetworkNode*> vnt){
    dimen.resize(1+nt.parents.size());
    dimen[0] = nt.domain_size;
    for(int i=1;i<dimen.size();i++){
        dimen[i] = vnt[nt.parents[i-1]]->domain_size;
    }
}
void fill_records(vector<Record*>& rc, vector<NetworkNode*>& nt, vector<vector<float>*>& miss_probs_vector, vector<vector<vector<int> > >& blanket){
    vector<unordered_map<string,vector<int> > > qrs(nt.size());
// DEBUG("paernts done");
// DEBUG(rc.size());
// cout<<"sdds"<<endl;
    for (int i=0;i<rc.size();i++){
        Record* r = rc[i];
        int var = r->missing_var;
        if (var==-1){
            continue;
        }
        // cout<<var<<endl;
        string temp;
        //its parents
        for(int p: nt[var]->parents){
            temp.append(to_string(r->data[p]));
            temp.push_back(',');
        }

// DEBUG("paernts done");
// std::cout<<"parents_done"<<endl;
        // its children
        for(int c: nt[var]->children){
            temp.append(to_string(r->data[c]));
            temp.push_back(',');
            // parents of children
            for(int cp: nt[c]->parents){
                temp.append(to_string(r->data[cp]));
                temp.push_back(',');
            }
        }
        qrs[var][temp].push_back(i);
// DEBUG("children done");
    }
    //updating record pointer of missing prob
    for(int i=0;i<nt.size();i++){
        NetworkNode& varnode = *nt[i];
        for(auto it = qrs[i].begin(); it != qrs[i].end();it++){
            vector<float>* missing_prob = new vector<float>(varnode.domain_size,-1); 

            Record& one_record = *rc[it->second[0]];

            for(int index: it->second){
                rc[index]->missing_prob = missing_prob;
            }
            miss_probs_vector.push_back(missing_prob);
// DEBUG(to_string(i) + "making missing_prob");
            // blanket update
            vector<vector<int> > blanket_0(varnode.domain_size+1);
            for(int j=0;j<blanket_0.size();j++){
                blanket_0[j].resize(1+(varnode.children.size()));
            }
            blanket_0[0][0] = i;
            for(int j=1;j<blanket_0[0].size();j++){
                blanket_0[0][j] = varnode.children[j-1];
            }
            //
// DEBUG("BLANKETU"+to_string(1));
            vector<vector<int> > domain_size(varnode.children.size()+1);
            
            for(int j=0;j<domain_size.size();j++){
                update_dimension(domain_size[j],*nt[blanket_0[0][j]],nt);
                // domain_size[j].resize(nt[blanket_0[0][j]]->parents.size()+1);
                // domain_size[j][0] = varnode.domain_size;
                // for (int k=1;k<domain_size[j].size();k++){
                //     domain_size[j][k] = nt[varnode.parents[k-1]]->domain_size;
                // }
            }
// DEBUG("BLANKETU"+to_string(2));

            // j-1 are values possible of varnode
            for(int j=1;j<blanket_0.size();j++){
                
                for(int k=0;k<blanket_0[j].size();k++){
                    vector<int> vals(1);
                    
                    // vals[0] = k;
                    int ch = 0;
                    if (k==0){
                        vals[0] = j-1;
                        ch = i;
                    }
                    else{
                        ch = varnode.children[k-1];
                        vals[0] = one_record.data[ch];
                    }
                    for(int l=0;l<nt[ch]->parents.size();l++){
                        int chp = nt[ch]->parents[l];
                        if (chp==i){
                            vals.push_back(j-1);
                        }
                        else{
                            vals.push_back(one_record.data[chp]);
                        }
                    }
                    blanket_0[j][k] = get_offset(vals,domain_size[k]);
                    
                }
// DEBUG("BLANKETU"+to_string(3));

               
            }

            blanket.push_back(blanket_0);
            //
        }
    }
  
 
}
int get_vals(Record& rc, vector<NetworkNode*>& netw, int node_index, vector<int>& vals){
    int pos = vals.size();
    vector<int>& parents = netw[node_index]->parents;
    vals.resize(1+parents.size());
    vals[0] = rc.data[node_index];
    if (vals[0]==-1){
        pos = 0;
        vals[0] = 0;
    }
    int tmp;
    for(int i=1;i<vals.size();i++){
        tmp = rc.data[parents[i-1]];
        if (tmp==-1){
            pos = i;
            tmp = 0;
        }
        vals[i] = tmp;
    }
    return pos;
}
int get_vals2(Record& rc, vector<NetworkNode*>& netw, int node_index, vector<int>& vals){
    int pos = vals.size();
    vector<int>& parents = netw[node_index]->parents;
    vals.resize(1+parents.size());
    vals[0] = rc.data[node_index];
    // int miss_elem = *max_element(rc.missing_prob->begin(), rc.missing_prob->end());
    int max_elem =rc.missing_prob->at(0);

    int max_index = 0;
    vector<float>& miss_prob = *rc.missing_prob;

    for(auto it=1;it<miss_prob.size();it++){
        if (miss_prob[it]>max_elem){
            max_elem = miss_prob[it];
            max_index = it;
        }
    }
    if (vals[0]==-1){
        vals[0] = max_index;
    }
    int tmp;
    for(int i=1;i<vals.size();i++){
        tmp = rc.data[parents[i-1]];
        if (tmp==-1){
            tmp = max_index;
            pos = i;
        }
        vals[i] = tmp;
    }
    return pos;
}
void get_file_in_a_vector(string file_path, vector<NetworkNode*>& nt, vector<Record*>& rc )
{
    //takes in a dat file path and initializations of networks and records. Fills in the data values of records
    string s1;
	ifstream file;
	file.open(file_path);
	if(file.is_open())
	{
        int line=0;
		while(getline(file,s1))
		{
            //cout<<s1<<endl;
			int length_line = s1.size();
			int ques_pos=0;
            int var_label=0;
            int start=0;
            Record* temp_rec = new Record();
            rc.push_back(temp_rec);
			for(int i=0;i<length_line;i++)
			{
                string var_value="";
                // temp_rec->missing_var = -1;
                if(s1.at(i)==' ' || i==(length_line-1))
                {
                    if(i==length_line-1)
                        var_value = s1.substr(start,i+1-start);
                    else
                        var_value = s1.substr(start,i-start);
                    
                    //cout<<var_value<<endl;
                    start = i+1;
                    if(var_value.compare("\"?\"")==0)
                    {
                        if(i==length_line-1)
                            ques_pos = i;
                        else
                            ques_pos=i-1;
                        temp_rec->data.push_back(-1);
                        // DEBUG(var_label);
                        temp_rec->missing_var = var_label;
                        var_label++;
                    }
                    else
                    {
                       
                        temp_rec->data.push_back( nt.at(var_label)->value_mapped[var_value] );
                        var_label++;
                    }
                }
					
			}

            line++;
		
        }
	}
}

void infer(vector<vector<vector<int> > >&blanket, vector<NetworkNode*> nt, vector<vector<float>*>& miss_probs_vector)
{
	/*
	blanket  -  first vector corresponds to the number of variables
				second vector corresponds to the number of unique blanket values in the data file
				first element of pair corresponds to the matrix of node offsets in CPT, where the first dimension is equal to domain size of variable and the other two are offset values
				second element of pair corresponds to the index of vector in which to place the infered probs
	out_place - the vector to store the prob values
	*/

	for(int i=0;i<blanket.size();i++)
	{
        vector<float>& miss_probs = *miss_probs_vector[i];
        vector<int>& var_pos = blanket[i][0];
        float denom = 0;
        for(int j=0;j<blanket[i].size()-1;j++){
            float temp = 1;
            for(int k=0;k<blanket[i][j+1].size();k++){
                temp *= nt[var_pos[k]]->CPT[blanket[i][j+1][k]];
            }
            // cout<<temp<<endl;
            miss_probs_vector[i]->at(j) = temp;
            denom += temp;
        }
        //  max_element(miss_probs.begin(),miss_probs.end())
        for(int j=0;j<blanket[i].size()-1;j++){
            miss_probs_vector[i]->at(j) /= denom;
        }
	}
}



void initialize_CPT(vector<Record*>& rc, vector<NetworkNode*>& nt, float smooth){
    // for all variables
    for(int i=0;i<nt.size();i++){
        vector<float>& old_vals = nt[i]->CPT;
        for(int j=0;j<old_vals.size();j++){
            old_vals[j] = smooth;
        }
   
        vector<int> dimensions;
        update_dimension(dimensions, *nt[i], nt);
// #ifdef DEB
//     // if (dimensions.size()!=*nt[i].parents.size())
// #endif
        vector<int>& parents = nt[i]->parents;
        for(Record* r: rc){
            vector<int> vals(1+parents.size());
            vector<int>& data = r->data;
// print_vec<float>(*r->missing_prob);
            if (data[i]==-1){
                continue;
            }
            else{
                bool to_quit = false;


                vals[0] = data[i];
                for(int j=1;j<vals.size();j++){
                    if (data[parents[j-1]]==-1){
                        to_quit=true;
                        break;
                    }
                    vals[j] = data[parents[j-1]];
                }

                if (to_quit){
                    continue;
                }
                int index = get_offset(vals,dimensions);

                old_vals[index] +=1;

            }
// DEBUG(r); 
        }
// DEBUG(i); 
        int dm = nt[i]->domain_size;
     
        int seg = old_vals.size()/dm;
// print_vec<float>(old_vals);
// DEBUG(dm);
// DEBUG(seg);
        //normalization
        for(int j =0;j<seg;j++){
            float denom = 0;

            for(int k=0;k<dm;k++){
                denom += old_vals[(seg*k+j)];

            }
            // if (denom<=0){
            //     DEBUG(denom);
            //     print_vec<float>(old_vals);
            // }
            // int denom = old_vals[j] + old_vals[half+j];
            for(int k=0;k<dm;k++){
                old_vals[seg*k+ j] /= denom;
            }

        }
#ifdef DEB
// print_vec<float>(old_vals);
#endif
    }
}


void update_CPT(vector<Record*>& rc, vector<NetworkNode*>& nt, float smooth){
    // for all variables
#ifdef DEB
    // int i=0;
    // for(Record* r: rc){
    //     // cout << r->missing_var;
    //     print_vec<int>(r->data);
    //     print_vec<float>(*r->missing_prob);
    // }
#endif
    for(int i=0;i<nt.size();i++){
        vector<float>& old_vals = nt[i]->CPT;
        for(int j=0;j<old_vals.size();j++){
            old_vals[j] = smooth;
        }
        // vector<float> new_vals(old_vals.size(),0); 
       
        vector<int> dimensions;
        update_dimension(dimensions, *nt[i], nt);
        vector<int>& parents = nt[i]->parents;
        vector<int> dim_multiplied;
        get_dim_multiplied(dimensions, dim_multiplied);
        // vector<float>& cpt = nt[i]->CPT;

        // int domain_size = nt[i]->domain_size;
        int rec_count = 0 ;
        for(Record* r: rc){
            vector<float>& missing_prob = *(r->missing_prob);
            int domain_size = missing_prob.size();
            vector<int> vals(1+parents.size());
            int qindex = get_vals(*r,nt,i,vals);
            // if (qindex!=r->missing_var){
            //     cout<<qindex<<endl;
            //     DEBUG(r->missing_var);
            //     DEBUG("error2");
            // }
            int offset = get_offset(vals, dimensions);
#ifdef DEB
            get_vals2(*r,nt,i,vals);
            offset = get_offset(vals,dimensions);
            old_vals[offset] +=1;
#else
#ifdef DEBUG1
    if (i==2){
        // if (rec_count==2){
            DEBUG("d");
            print_vec<int>(r->data);
            print_vec<int>(vals);
            print_vec<int>(dimensions);
            DEBUG(qindex);
            DEBUG(offset);
        // }
        // print_vec<float>(*r->missing_prob);
    }
#endif

            
// if (i==3)
// print_vec<float>(missing_prob);
            if (qindex==vals.size()){
                old_vals[offset] += 1;
                continue;
            }
            // DEBUG(qindex);
            // DEBUG(parents[qindex-1]);
  
            // int domain_size = nt[i]->domain_size;
            // if (qindex>0){
            //     // DEBUG(qindex);
            //     // DEBUG(parents[qindex-1]);
            //     if (domain_size!=nt[parents[qindex-1]]->domain_size){
            //         DEBUG("error");
            //     }
            // }
// print_vec<float>(missing_prob);
            int dim = dim_multiplied[qindex];
            for(int j=0;j<domain_size;j++){
                old_vals[offset] += missing_prob[j];
                offset += dim;
            }
#endif
#ifdef DEBUG1
    if (rec_count==4){
        cout<<"here"<<endl;
        cout<<offset<<endl;
        print_vec<float>(missing_prob);
        cout<<dim<<endl;
        cout<<"here exit"<<endl;
    }
#endif
// if (i==3)
// print_vec<float>(missing_prob);
            rec_count +=1;
        }
#ifdef DEBUG1
    if (i==2){
        print_vec<float>(old_vals);
    }
#endif
        // DEBUG(i);
        int dm = nt[i]->domain_size;
        int seg = old_vals.size()/dm;
        
        for(int j =0;j<seg;j++){
            float denom = 0;
            for(int k=0;k<dm;k++){
                denom += old_vals[seg*k+j];
            }
            // int denom = old_vals[j] + old_vals[half+j];
            for(int k=0;k<dm;k++){
                old_vals[seg*k+ j] /= denom;
            }
        }
#ifdef DEBUG1
    if (i==3){
        print_vec<float>(old_vals);
    }
#endif
// #ifdef DEBUG1
//     print_vec<float>(old_vals);
// #endif
        // DEBUG('a');
        // DEBUG(i);
// print_vec<float>(old_vals);
    }
}

int main(int argc,char *argv[]){
    int net_time = 90;
    //read the network
    network init_network = read_network(argv[1]);
    cout<<"init network done"<<endl;
    //instantiate records
    vector<Record*> rc;
    //fill records from the file
    get_file_in_a_vector(argv[2], init_network.Pres_Graph, rc);
    cout<<"Get file in a vector done"<<endl;
    //make the missing_prob_vector and markov blanket vector
    vector<vector<float> *> miss_probs_vector;
    vector<vector<vector<int>>> blanket;
    fill_records(rc, init_network.Pres_Graph, miss_probs_vector, blanket);
    cout<<"fill records done"<<endl;
    //initialize the CPTs
    double smooth = 0.001;
    initialize_CPT(rc, init_network.Pres_Graph, smooth);
    cout<<"initialize cpt done"<<endl;
    TIME t1 = GET_TIME;
    TIME t2 = GET_TIME;
    // DURATION dur = GET_DURATION(t2-t1);
    while(true)
    {
        int dur = GET_DURATION(t2-t1).count();
        // cout <<dur<<endl;
        if (dur>net_time){
            break;
        }
        //inference step
        infer(blanket, init_network.Pres_Graph, miss_probs_vector);
        // cout<<to_string(i) + "inference done"<<endl;
        //updation step
        update_CPT(rc, init_network.Pres_Graph, smooth);
        // cout<<"Updation done"<<endl;
        t2 = GET_TIME;
    }

    //print the network
    print_alarm(init_network, argv[1],(char*)"solved_alarm.bif");
    cout<<"Printing done"<<endl;
    return 0;
}