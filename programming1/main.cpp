//#include <bits/stdc++.h>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

#ifndef DEBUG
#define DEBUG	true
#endif

#define All(obj) (obj).begin(),(obj).end()
#define REP(i,n) for(int i=0;i<(n);++i)
#define REPR(i,n) for(int i=0; i>=(n);--i)
#define FOR(i,b,n) for(int i=(b);i<(n);++i)

typedef long long ll;
typedef pair<int,string> pis;

const int M=2e5+5;
const int INF=2e9;
const int MOD=1e9+7;


struct myComp {
    constexpr bool operator()( pair<int, string> const& a, pair<int, string> const& b)
        const noexcept
    {
        return a.first > b.first;
    }
};


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
void write_file(string output, int num_node, bool solved)
{
    ofstream ofs(output);

    if(solved){
        ofs << num_node;
    }else{
        ofs << "no solution found";
    }
    ofs.close();
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
void expand(vector<int> &current_node, priority_queue<pis, vector<pis>, myComp > &pq, int depth, unordered_map<string, string> &mp)
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
            pq.push(pis(depth+1, next_node_string));
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
            pq.push(pis(depth+1, next_node_string));
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
            pq.push(pis(depth+1, next_node_string));
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
            pq.push(pis(depth+1, next_node_string));
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
            pq.push(pis(depth+1, next_node_string));
            mp[next_node_string] = current_node_string;
        }
    }

}

void solve_bfs(string i_s, string g_s, string output)
{
    priority_queue<pis, vector<pis>, myComp > pq;
    unordered_map<string, string> mp;

    int num_explored = 0, current_depth;
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
    pq.push(pis(0,initial));
    mp[initial] = "0";

    /* loop do */
    while(1){
        /* if the frontier is empty, then return failure  */
        if(pq.empty()){
            found = false;
            break;
        }

        /* choose a leaf node and remove it from the frontier */
        current_state = pq.top().second;
        current_depth = pq.top().first;
        pq.pop();

        cout << "path: " << current_state << endl;
        cout << "depth: " << current_depth<<endl;
        ++num_explored;

        /* if the node contains a goal state, then return the corresponding solution */
        if(current_state == goal){
            found = true;
            break;
        }

        /* expand the chosen node, adding the resulting nodes to the frontier
           only if not in the frontier or explored set
        ****************************************************************************/
        vector<int> tmp = string_to_vector(current_state, ' ');
        expand(tmp,pq,current_depth,mp);

    }

    if(found){
        cout << num_explored;
    }else{

    }




}

void solve_dfc(string i_s, string g_s, string output)
{

}
void solve_iddfs(string i_s, string g_s, string output)
{

}
void solve_astar(string i_s, string g_s, string output)
{

}
void test_expand(priority_queue<pis, vector<pis>, myComp > &pq, unordered_map<string, string> &mp){
    pq.push(pis(5,"3 3 3 3 3 3"));
    mp["test"] = "check";
}
void test(string i_s, string g_s)
{
    priority_queue<pis, vector<pis>, myComp > pq;
    unordered_map<string, string> mp;

    vector<int> v={0,0,0,3,3,1};
    expand(v, pq, 0, mp);
    while(!pq.empty()){
        cout << pq.top().second <<endl;
        pq.pop();
    }
    cout << "previous node: "<< mp["0 1 1 3 2 0"] <<endl;

    /*
    int num_explored = 0;
    bool found = false;

    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string initial, goal;
    vector_to_string(initial_state, initial);
    vector_to_string(goal_state, goal);

    cout << "initial: " << initial <<endl;
    cout << "goal: " << goal <<endl;
    cout << "----------------" <<endl;
    test_expand(pq,mp);
    pq.push(pis(2,"3 1 1 0 2 0"));
    pq.push(pis(0,"3 3 1 0 0 0"));
    pq.push(pis(1,"3 2 0 0 1 1"));
    while(!pq.empty()){

        cout << "depth: " << pq.top().first << endl <<endl;
        cout << "state: " << pq.top().second << endl;

        vector<int> v = string_to_vector(pq.top().second, ' ');

        cout << "test s_to_v function" << endl;
        for(int num: v){
            cout << num << ' ';
        }
        cout<< endl;

        mp[pq.top().second] = "previous node";
        pq.pop();

        cout << "-------------------" <<endl;
    }
    cout << "------------mp-----------------" << endl;
    for(auto itr = mp.begin(); itr != mp.end(); ++itr){
        cout << "mp value: " << itr->first << endl;
        cout << "previous node: " << itr->second <<endl<<"-----------" <<endl;
    }

    cout << "\n--------find-----------" <<endl;
    auto itr = mp.find("3 1 1 0 2 0");
    if( itr != mp.end() ) {
        cout << "there is" << endl;
    } else {
        cout << "there is not" << endl;
    }
    */

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
        //test(argv[1], argv[2]);
        solve_bfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "dfs") == 0){
        solve_dfc(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "iddfs") == 0){
        solve_iddfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "astar") == 0){
        solve_astar(argv[1], argv[2], argv[4]);
    }else{
        fprintf(stderr, "invalid mode\n");
        return EXIT_FAILURE;
    }

    return 0;
}
