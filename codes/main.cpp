//#include <bits/stdc++.h>
#include<iostream>
#include<string>
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

const int M=2e5+5;
const int INF=2e9;
const int MOD=1e9+7;

/*
template<typename T>
void hash_combine(size_t & seed, T const& v){
    seed ^= std::hash<T>{}(v) + 0x9e3779b97f4a7c15LLU + (seed<<12) + (seed>>4);
}
*/

/*
    I assumed that
    boat = 1 for right side,
    boat = -1 for left side
******************************/
class Node{
    public:
    int r_chickens;
    int r_wolves;
    int l_chickens;
    int l_wolves;
    int boat;
    /* this depth is for priprity queue */
    int depth;

};
/*
bool operator==(const Node &left, const Node &right){
    return  left.r_chickens == right.r_chickens and
            left.r_wolves == right.r_wolves and
            left.boat == right.boat;
}
namespace std{
    template<>
    struct hash<Node>{
    public:
        size_t operator()(const Node &data)const {

            std::size_t seed = 0;
            hash_combine(seed, data.r_chickens);
            hash_combine(seed, data.r_wolves);
            hash_combine(seed, data.boat);
            return seed;
        }

    };
}
*/

/* overloaded for priority queue with Node class */
bool operator> (const Node &node1, const Node &node2){
    return node1.depth > node2.depth;
};
bool operator< (const Node &node1, const Node &node2){
    return node1.depth < node2.depth;
};

void read_file(string input, vector<vector<int>> &vv)
{
    ifstream ifs(input);
    if(ifs.fail()){
        fprintf(stderr,"Invalid input file name\n");
        exit(2);
    }
    char c;
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 3; ++j){
            ifs >> vv[i][j];
            if(j!=2){
                ifs >> c;
            }
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

void solve_bfs(string i_s, string g_s, string output)
{
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> map;
    //unordered_map<Node, int> map;

    vector<vector<int>> initial_state(2,vector<int>(3));
    vector<vector<int>> goal_state(2,vector<int>(3));


    read_file(i_s, initial_state);
    read_file(g_s, goal_state);

    /* c1 w1 c2 w2 b1-b2 depth*/
    //map[ {initial_state[0][0],initial_state[0][1],initial_state[1][0],initial_state[1][1], (initial_state[0][2]-initial_state[1][2]) , 0} ] = 0;
    //pq.push({initial_state[0][0],initial_state[0][1],initial_state[1][0],initial_state[1][1], (initial_state[0][2]-initial_state[1][2]) , 0});

    /* debug */
    /*
    map["3 1 0 2 -1"] = 2;
    map["0 0 3 3 1"] = 0;
    map["3 3 0 0 -1"] = 1;
    */
    pq.push({3,1,0,2,-1,2});
    pq.push({0,0,3,3,1,0});
    pq.push({3,3,0,0,-1,1});
    while(!pq.empty()){

        cout << "depth: " << pq.top().depth << endl <<endl;
        cout << "right side: " << pq.top().r_chickens << " : " << pq.top().r_wolves << endl;
        cout << "left side: " << pq.top().l_chickens << " : " << pq.top().l_wolves << endl;
        cout << pq.top().boat << endl;

        string tmp = to_string(pq.top().r_chickens)+' '+to_string(pq.top().r_wolves)+' '+to_string(pq.top().l_chickens)+' '+to_string(pq.top().l_wolves)+' '+to_string(pq.top().boat);
        cout << "tmp: " << tmp << endl << "--"<< endl;;
        map[tmp] = pq.top().depth;
        pq.pop();

    }
    cout << "------------map-----------------" << endl;
    for(auto itr = map.begin(); itr != map.end(); ++itr){
        cout << "map value: " << itr->first << endl;
        cout << "depth: " << itr->second <<endl;
    }
    /*
    for(auto itr = map.begin(); itr != map.end(); ++itr) {
        cout << "right side: " << itr->first.r_chickens << " : " << itr->first.r_wolves << endl;
        cout << "left side: " << itr->first.l_chickens << " : " << itr->first.l_wolves << endl;
        cout << itr->first.boat << endl << endl;
        cout << "depth: " << itr->first.depth << " and " << itr->second << endl << "--"<< endl;
    }
    */

    auto itr = map.find("3 1 0 2 -1");
    if( itr != map.end() ) {
        cout << "there is" << endl;
    } else {
        cout << "there is not" << endl;
    }


}

void solve_dfc(string i_s, string g_s, string output)
{
    priority_queue<Node> pq;


    vector<vector<int>> initial_state(2,vector<int>(3));
    vector<vector<int>> goal_state(2,vector<int>(3));

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);
}
void solve_iddfs(string i_s, string g_s, string output)
{
    vector<vector<int>> initial_state(2,vector<int>(3));
    vector<vector<int>> goal_state(2,vector<int>(3));

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);
}
void solve_astar(string i_s, string g_s, string output)
{
    vector<vector<int>> initial_state(2,vector<int>(3));
    vector<vector<int>> goal_state(2,vector<int>(3));

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);
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
