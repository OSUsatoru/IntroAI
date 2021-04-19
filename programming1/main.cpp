//#include <bits/stdc++.h>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<queue>
#include<stack>

using namespace std;

typedef long long ll;
typedef pair<int,pair<int,string>> pipis;

const int M=2e5+5;
const int INF=2e9;
const int MOD=1e9+7;

struct myComp {
    constexpr bool operator()( pair<int,pair<int,string>> const& a, pair<int,pair<int,string>> const& b)
        const noexcept
    {
        return a.first > b.first;
    }
};

void solution_path(unordered_map<string,string> &mp, vector<string> &path, string goal_node)
{
    string current_node = goal_node;
    while(current_node != "0"){

        path.push_back(current_node);
        current_node = mp[current_node];
    }
}
void solution_path_iddfs_edit(unordered_map<string,pair<int,string>> &mp, vector<string> &path, string goal_node)
{
    string current_node = goal_node;
    while(current_node != "0"){
        path.push_back(current_node);
        current_node = mp[current_node].second;
    }
}
void read_file(string input, vector<int> &v)
{
    ifstream ifs(input);
    if(ifs.fail()){
        fprintf(stderr,"Invalid input file name\n");
        exit(2);
    }
    char c;
    for(int i = 0; i < 6; ++i){
        ifs >> v[i];
        if(i!=2){
            ifs >> c;
        }
    }
    ifs.close();
}

/*need to print out the number of search nodes expanded*/
void write_file(string output, int num_expanded, vector<string> path)
{
    ofstream ofs(output);

    if (!ofs) {
        fprintf(stderr, "invalid output file\n");
        exit(1);
    }

    int depth = path.size()-1;
    for(int i = depth; i >= 0; --i){
        ofs << "Node: " << path[i] << endl;
    }
    ofs << endl << "depth: " << depth << endl << "expanded node: " << num_expanded << endl;

    ofs.close();
}
void display_result(int num_expanded, vector<string> path)
{


    int depth = path.size()-1;
    for(int i = depth; i >= 0; --i){
        cout << "Node: " << path[i] << endl;
    }
    cout << endl << "depth: " << depth << endl << "expanded node: " << num_expanded << endl << endl;

}


void vector_to_string(vector<int> v, string &tmp)
{
    tmp = to_string(v[0])+' '+to_string(v[1])+' '+to_string(v[2])+' '+to_string(v[3])+' '+to_string(v[4])+' '+to_string(v[5]);
}

vector<int> string_to_vector(const string &str, char sep)
{
    vector<int> v;
    stringstream ss(str);
    string buffer;
    while(getline(ss, buffer, sep) ) {
        v.push_back(stoi(buffer));
    }
    return v;
}

/*
    if (c>=w) or c might be 0
    and c>=0 and w>=0

    auto itr = mp.find("new path");
    if( itr != mp.end() ) {
        cout << "there is" << endl;
    } else {
        cout << "there is not" << endl;
    }
*******************************************/
bool check_move(vector<int> &node)
{
    if(node[0]>=0 and node[1]>=0 and node[3]>=0 and node[4]>=0){
        if(node[0]>=node[1] and node[3]>=node[4]){
            return true;
        }else if(node[0]==0 or node[3]==0){
            return true;
        }
    }

    return false;
}
void expand_BFS(vector<int> &current_node, queue<string> &que, unordered_map<string, string> &mp)
{
    vector<int> next_node(6);
    string next_node_string, current_node_string;
    vector_to_string(current_node,current_node_string);

    int index1=0,index2=3;
    /* check the boat possition */
    /* boat is right side, we need to move index of 3,4*/
    if(current_node[2] == 0){
        index1=3;
        index2=0;
    }

    /*c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            que.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*c2*/
    next_node[index1]=current_node[index1]-2;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+2;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            que.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            que.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];
    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            que.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }
    /*w2*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-2;
    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+2;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            que.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

}
void expand_DFS(vector<int> &current_node, stack<string> &st, unordered_map<string, string> &mp)
{
    vector<int> next_node(6);
    string next_node_string,current_node_string;
    vector_to_string(current_node,current_node_string);

    int index1=0,index2=3;
    /* check the boat possition */
    /* boat is right side, we need to move index of 3,4*/
    if(current_node[2] == 0){
        index1=3;
        index2=0;
    }

    /*c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*c2*/
    next_node[index1]=current_node[index1]-2;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+2;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];
    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }
    /*w2*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-2;
    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+2;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(next_node_string);
            mp[next_node_string] = current_node_string;
        }
    }

}
void expand_IDDFS(vector<int> &current_node, stack<pair<int,string>> &st, int depth, unordered_map<string, string> &mp)
{
    vector<int> next_node(6);
    string next_node_string,current_node_string;
    vector_to_string(current_node,current_node_string);

    int index1=0,index2=3;
    /* check the boat possition */
    /* boat is right side, we need to move index of 3,4*/
    if(current_node[2] == 0){
        index1=3;
        index2=0;
    }

    /*c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }

    /*c2*/
    next_node[index1]=current_node[index1]-2;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+2;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];
    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }
    /*w2*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-2;
    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+2;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }

}
void expand_IDDFS_edited(vector<int> &current_node, stack<pair<int,string>> &st, int depth, unordered_map<string, pair<int,string>> &mp)
{
    vector<int> next_node(6);
    string next_node_string,current_node_string;
    vector_to_string(current_node,current_node_string);

    int index1=0,index2=3;
    /* check the boat possition */
    /* boat is right side, we need to move index of 3,4*/
    if(current_node[2] == 0){
        index1=3;
        index2=0;
    }

    /*c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = pair<int,string>(depth+1,current_node_string);
        }else{
            if(mp[next_node_string].first > depth+1){
                /*
                int tmp_d = mp[next_node_string].first;
                string tmp_s = mp[next_node_string].second;
                st.push(pair<int,string>(tmp_d,next_node_string));
                mp[next_node_string]=pair<int,string>(tmp_d,tmp_s);
                */
                st.push(pair<int,string>(depth+1,next_node_string));
                mp[next_node_string]=pair<int,string>(depth+1,current_node_string);
            }
        }
    }

    /*c2*/
    next_node[index1]=current_node[index1]-2;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+2;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = pair<int,string>(depth+1,current_node_string);
        }else{
            if(mp[next_node_string].first > depth+1){
                /*
                int tmp_d = mp[next_node_string].first;
                string tmp_s = mp[next_node_string].second;
                st.push(pair<int,string>(tmp_d,next_node_string));
                mp[next_node_string]=pair<int,string>(tmp_d,tmp_s);
                */
                st.push(pair<int,string>(depth+1,next_node_string));
                mp[next_node_string]=pair<int,string>(depth+1,current_node_string);
            }
        }
    }

    /*w1*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = pair<int,string>(depth+1,current_node_string);
        }else{
            if(mp[next_node_string].first > depth+1){
                /*
                int tmp_d = mp[next_node_string].first;
                string tmp_s = mp[next_node_string].second;
                st.push(pair<int,string>(tmp_d,next_node_string));
                mp[next_node_string]=pair<int,string>(tmp_d,tmp_s);
                */
                st.push(pair<int,string>(depth+1,next_node_string));
                mp[next_node_string]=pair<int,string>(depth+1,current_node_string);
            }
        }
    }

    /*w1c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];
    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = pair<int,string>(depth+1,current_node_string);
        }else{
            if(mp[next_node_string].first > depth+1){
                /*
                int tmp_d = mp[next_node_string].first;
                string tmp_s = mp[next_node_string].second;
                st.push(pair<int,string>(tmp_d,next_node_string));
                mp[next_node_string]=pair<int,string>(tmp_d,tmp_s);
                */
                st.push(pair<int,string>(depth+1,next_node_string));
                mp[next_node_string]=pair<int,string>(depth+1,current_node_string);
            }
        }
    }
    /*w2*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-2;
    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+2;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            st.push(pair<int,string>(depth+1,next_node_string));
            mp[next_node_string] = pair<int,string>(depth+1,current_node_string);
        }else{
            if(mp[next_node_string].first > depth+1){
                /*
                int tmp_d = mp[next_node_string].first;
                string tmp_s = mp[next_node_string].second;
                st.push(pair<int,string>(tmp_d,next_node_string));
                mp[next_node_string]=pair<int,string>(tmp_d,tmp_s);
                */
                st.push(pair<int,string>(depth+1,next_node_string));
                mp[next_node_string]=pair<int,string>(depth+1,current_node_string);
            }
        }
    }

}

/* n+1 + h(n) */
int evaluation_astar(vector<int> &current_node, vector<int> &goal_node, int depth)
{
    int h = abs(current_node[0]-goal_node[0]) + abs(current_node[1]-goal_node[1]);
    //cout << "h: "<< h <<endl;
    return h+depth+1;
}

void expand_astar(vector<int> &current_node, vector<int> &goal_node, priority_queue<pipis, vector<pipis>, myComp > &pq, int depth, unordered_map<string, string> &mp)
{
    vector<int> next_node(6);
    string next_node_string,current_node_string;
    vector_to_string(current_node,current_node_string);
    int cost;

    int index1=0,index2=3;
    /* check the boat possition */
    /* boat is right side, we need to move index of 3,4*/
    if(current_node[2] == 0){
        index1=3;
        index2=0;
    }

    /*c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            cost = evaluation_astar(next_node, goal_node, depth);
            pq.push(pipis(cost,pair<int,string>(depth+1, next_node_string)));
            mp[next_node_string] = current_node_string;
        }
    }

    /*c2*/
    next_node[index1]=current_node[index1]-2;
    next_node[index1+1]=current_node[index1+1];

    next_node[index2]=current_node[index2]+2;
    next_node[index2+1]=current_node[index2+1];

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            cost = evaluation_astar(next_node, goal_node, depth);
            pq.push(pipis(cost,pair<int,string>(depth+1, next_node_string)));
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            cost = evaluation_astar(next_node, goal_node, depth);
            pq.push(pipis(cost,pair<int,string>(depth+1, next_node_string)));
            mp[next_node_string] = current_node_string;
        }
    }

    /*w1c1*/
    next_node[index1]=current_node[index1]-1;
    next_node[index1+1]=current_node[index1+1]-1;

    next_node[index2]=current_node[index2]+1;
    next_node[index2+1]=current_node[index2+1]+1;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];
    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            cost = evaluation_astar(next_node, goal_node, depth);
            pq.push(pipis(cost,pair<int,string>(depth+1, next_node_string)));
            mp[next_node_string] = current_node_string;
        }
    }
    /*w2*/
    next_node[index1]=current_node[index1];
    next_node[index1+1]=current_node[index1+1]-2;
    next_node[index2]=current_node[index2];
    next_node[index2+1]=current_node[index2+1]+2;

    next_node[2]=current_node[5];
    next_node[5]=current_node[2];

    if(check_move(next_node)){
        vector_to_string(next_node, next_node_string);
        auto itr = mp.find(next_node_string);
        if( itr == mp.end() ) {
            cost = evaluation_astar(next_node, goal_node, depth);
            pq.push(pipis(cost,pair<int,string>(depth+1, next_node_string)));
            mp[next_node_string] = current_node_string;
        }
    }

}
void solve_bfs(string i_s, string g_s, string output)
{
    queue<string> que;
    unordered_map<string, string> mp;

    int num_explored = 0;
    string current_state;
    bool found = false;

    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    /* push the initial_state into priority queue and hash table */
    que.push(initial);
    mp[initial] = "0";

    /* loop do */
    while(1){
        /* if the frontier is empty, then return failure  */
        if(que.empty()){
            found = false;
            break;
        }

        /* choose a leaf node and remove it from the frontier */
        current_state = que.front();
        que.pop();

        //cout << "path: " << current_state << endl;
        /* if the node contains a goal state, then return the corresponding solution */
        if(current_state == goal){
            found = true;
            break;
        }
        ++num_explored;

        /* expand the chosen node, adding the resulting nodes to the frontier
           only if not in the frontier or explored set
        ****************************************************************************/
        vector<int> tmp = string_to_vector(current_state, ' ');
        expand_BFS(tmp,que,mp);

    }

    if(found){
        vector<string> path;
        solution_path(mp,path,goal);
        display_result(num_explored,path);
        write_file(output, num_explored, path);
    }else{
        ofstream ofs(output);

        if (!ofs) {
            fprintf(stderr, "invalid output file\n");
            exit(1);
        }
        ofs << "no solution\n";

        ofs.close();
    }




}

void solve_dfs(string i_s, string g_s, string output)
{
    stack<string> st;
    unordered_map<string, string> mp;

    int num_explored = 0;
    string current_state;
    bool found = false;

    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    /* push the initial_state into priority queue and hash table */
    st.push(initial);
    mp[initial] = "0";

    /* loop do */
    while(1){
        /* if the frontier is empty, then return failure  */
        if(st.empty()){
            found = false;
            break;
        }

        /* choose a leaf node and remove it from the frontier */
        current_state = st.top();
        st.pop();

        //cout << "path: " << current_state << endl;


        /* if the node contains a goal state, then return the corresponding solution */
        if(current_state == goal){
            found = true;
            break;
        }

        ++num_explored;

        /* expand the chosen node, adding the resulting nodes to the frontier
           only if not in the frontier or explored set
        ****************************************************************************/
        vector<int> tmp = string_to_vector(current_state, ' ');
        expand_DFS(tmp,st,mp);


    }

    if(found){
        vector<string> path;
        solution_path(mp,path,goal);
        display_result(num_explored,path);
        write_file(output, num_explored, path);
    }else{
        ofstream ofs(output);

        if (!ofs) {
            fprintf(stderr, "invalid output file\n");
            exit(1);
        }
        ofs << "no solution\n";

        ofs.close();
    }



}

void solve_iddfs(string i_s, string g_s, string output)
{
    unordered_map<string, string> mp;

    int num_explored = 0, current_depth;
    bool found = false;
    bool no_solution = false;

    string current_state;


    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    /* loop until find or no_solution == true */
    for(int limit = 0; ;++limit){
        stack<pair<int,string>> st;


        if(found or no_solution){
            break;
        }
        mp.clear();
        //cout << "-------------limit:"<<limit<<endl;
        int max_depth = 0;
        /* push the initial_state into priority queue and hash table */
        st.push(pair<int,string>(0,initial));
        mp[initial] = "0";

        /* loop do */
        while(1){
            /* if the frontier is empty, then return failure  */
            if(st.empty()){
                if(limit > max_depth)
                    no_solution = true;
                break;
            }

            /* choose a leaf node and remove it from the frontier */
            current_state = st.top().second;
            current_depth = st.top().first;
            st.pop();

            max_depth=max(max_depth,current_depth);
            /*
            cout << "path: " << current_state << endl;
            cout << "depth: " << current_depth << endl;
            */
            /* if the node contains a goal state, then return the corresponding solution */
            if(current_state == goal){
                found = true;
                break;
            }

            ++num_explored;

            /* expand the chosen node, adding the resulting nodes to the frontier
            only if not in the frontier or explored set
            ****************************************************************************/
            vector<int> tmp = string_to_vector(current_state, ' ');
            if(limit >= current_depth+1){
                expand_IDDFS(tmp,st,current_depth,mp);
            }
        }

    }

    if(found){
        vector<string> path;
        solution_path(mp,path,goal);
        display_result(num_explored,path);
        write_file(output, num_explored, path);
    }else{
    ofstream ofs(output);

        if (!ofs) {
            fprintf(stderr, "invalid output file\n");
            exit(1);
        }
        ofs << "no solution\n";

        ofs.close();
    }



}
void solve_iddfs_edited(string i_s, string g_s, string output)
{
    unordered_map<string, pair<int,string>> mp;

    int num_explored = 0, current_depth;
    bool found = false;
    bool no_solution = false;

    string current_state;


    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    /* loop until find or no_solution == true */
    for(int limit = 0; ;++limit){
        stack<pair<int,string>> st;


        if(found or no_solution){
            break;
        }
        mp.clear();
        //cout << "-------------limit:"<<limit<<endl;
        fflush(stdout);
        int max_depth = 0;
        /* push the initial_state into priority queue and hash table */
        st.push(pair<int,string>(0,initial));
        mp[initial] = pair<int,string>(0,"0");

        /* loop do */
        while(1){
            /* if the frontier is empty, then return failure  */
            if(st.empty()){
                if(limit > max_depth)
                    no_solution = true;
                break;
            }

            /* choose a leaf node and remove it from the frontier */
            current_state = st.top().second;
            current_depth = st.top().first;
            st.pop();

            max_depth=max(max_depth,current_depth);
            /*
            cout << "path: " << current_state << endl;
            cout << "depth: " << current_depth << endl;
            */
            /* if the node contains a goal state, then return the corresponding solution */
            if(current_state == goal){
                found = true;
                break;
            }

            ++num_explored;

            /* expand the chosen node, adding the resulting nodes to the frontier
            only if not in the frontier or explored set
            ****************************************************************************/
            vector<int> tmp = string_to_vector(current_state, ' ');
            if(limit >= current_depth+1){
                expand_IDDFS_edited(tmp,st,current_depth,mp);
            }
        }

    }

    if(found){
        vector<string> path;
        solution_path_iddfs_edit(mp,path,goal);
        display_result(num_explored,path);
        write_file(output, num_explored, path);
    }else{
    ofstream ofs(output);

        if (!ofs) {
            fprintf(stderr, "invalid output file\n");
            exit(1);
        }
        ofs << "no solution\n";

        ofs.close();
    }



}
/*
    f(n)= g(n) + h(n)
    g(n) = depth;
    h(n) is difference

    h(n) is increasing
    h(n) is decreasing

*/
void solve_astar(string i_s, string g_s, string output)
{
    /* cost, depth, node */
    priority_queue<pipis, vector<pipis>, myComp > pq;
    unordered_map<string, string> mp;

    int num_explored = 0, current_depth, current_cost;
    string current_state;
    bool found = false;

    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    /* push the initial_state into priority queue and hash table */
    pq.push(pipis(0,pair<int,string>(0,initial)));
    mp[initial] = "0";

    /* loop do */
    while(1){
        /* if the frontier is empty, then return failure  */
        if(pq.empty()){
            found = false;
            break;
        }

        /* choose a leaf node and remove it from the frontier */
        current_state = pq.top().second.second;
        current_depth = pq.top().second.first;
        current_cost = pq.top().first;

        pq.pop();
        /*
        cout << "path: " << current_state << endl;
        cout << "depth: " << current_depth<<endl;
        cout << "cost: " << current_cost << endl<<endl;
        */
        /* if the node contains a goal state, then return the corresponding solution */
        if(current_state == goal){
            found = true;
            break;
        }
        ++num_explored;

        /* expand the chosen node, adding the resulting nodes to the frontier
           only if not in the frontier or explored set
        ****************************************************************************/
        vector<int> tmp = string_to_vector(current_state, ' ');
        expand_astar(tmp,goal_state,pq,current_depth,mp);

    }

    if(found){
        vector<string> path;
        solution_path(mp,path,goal);
        display_result(num_explored,path);
        write_file(output, num_explored, path);
    }else{
        ofstream ofs(output);

        if (!ofs) {
            fprintf(stderr, "invalid output file\n");
            exit(1);
        }
        ofs << "no solution\n";

        ofs.close();
    }
}

/*
    < initial state file > < goal state file > < mode > < output file >

*/
int main(int argc, char *argv[])
{

    if(argc < 5){
        fprintf(stderr,"Example usage: ./main <initial state file> <goal state file> <mode> <output file> \n");
        return EXIT_FAILURE;
    }

    if(strcmp(argv[3], "bfs") == 0){
        solve_bfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "dfs") == 0){
        solve_dfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "iddfs") == 0){
        solve_iddfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "astar") == 0){
        solve_astar(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "iddfs_edited") == 0){
        solve_iddfs_edited(argv[1], argv[2], argv[4]);
    }else{
        fprintf(stderr, "invalid mode\n");
        return EXIT_FAILURE;
    }

    return 0;
}
