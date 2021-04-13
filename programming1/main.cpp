#include <bits/stdc++.h>
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

typedef pair<int,int> pii;
typedef pair<int,pair<int,int>> pipii;

/* for priority queue */
struct myComp {
    constexpr bool operator()( pair<int, pair<int, int>> const& a, pair<int, pair<int, int>> const& b)
        const noexcept
    {
        return a.first > b.first;
    }
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
    vector<vector<int>> initial_state(2,vector<int>(3));
    vector<vector<int>> goal_state(2,vector<int>(3));

    read_file(i_s, initial_state);
    read_file(g_s, goal_state);
    write_file(output, 0, false);



}
/*
void solve_dfc(string i_s, string g_s, string output);
void solve_iddfs(string i_s, string g_s, string output);
void solve_astar(string i_s, string g_s, string output);
*/

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
        //solve_dfc(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "iddfs") == 0){
        //solve_iddfs(argv[1], argv[2], argv[4]);
    }else if(strcmp(argv[3], "astar") == 0){
        //solve_astar(argv[1], argv[2], argv[4]);
    }else{
        fprintf(stderr, "invalid mode\n");
        return EXIT_FAILURE;
    }

    return 0;
}
