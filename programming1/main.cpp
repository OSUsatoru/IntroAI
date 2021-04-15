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
        if(i!=5){
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


string vector_to_string(vector<int> v)
{
    string tmp = to_string(v[0])+' '+to_string(v[1])+' '+to_string(v[2])+' '+to_string(v[3])+' '+to_string(v[4])+' '+to_string(v[5]);
    return tmp;
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

void solve_bfs(string i_s, string g_s, string output)
{
    priority_queue<pair<int,string>> pq;
    unordered_map<string, int> map;
    //unordered_map<Node, int> map;

    vector<int> initial_state(6);
    vector<int> goal_state(6);

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    string goal = vector_to_string(goal_state);


    /* debug */

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

        map[pq.top().second] = pq.top().first;
        pq.pop();

        cout << "-------------------" <<endl;
    }
    cout << "------------map-----------------" << endl;
    for(auto itr = map.begin(); itr != map.end(); ++itr){
        cout << "map value: " << itr->first << endl;
        cout << "depth: " << itr->second <<endl<<"-----------" <<endl;
    }

    cout << "\n--------find-----------" <<endl;
    auto itr = map.find("3 1 1 0 2 0");
    if( itr != map.end() ) {
        cout << "there is" << endl;
    } else {
        cout << "there is not" << endl;
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
