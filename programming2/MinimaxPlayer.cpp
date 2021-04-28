/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}
int min_value(OthelloBoard* b, char player, char opponent);

int Utility(OthelloBoard* b, char player, char opponent)
{
	return (b->count_score(player)) - (b->count_score(opponent));
}

void Successor(OthelloBoard* b, std::vector<OthelloBoard> &v, char player)
{
	int index = 0;
	int num_cols = 4, num_rows = 4;


	for (int c = 0; c < num_cols; c++) {
		for (int r = 0; r < num_rows; r++) {
			if (b->is_cell_empty(c, r) && b->is_legal_move(c, r, player)) {
				v.push_back(OthelloBoard(*b));
				v[index].play_move(c,r,player);

					//std::cout << "c:" << c << "\nr: " <<r <<'\n';


				++index;
			}
		}
	}
	//std::cout << "a" <<v[0].count_score(player);
}

int max_value(OthelloBoard* b, char player, char opponent)
{

	/*terminal test*/
	if( b->has_legal_moves_remaining(player) == false and
		b->has_legal_moves_remaining(opponent) == false){
			return Utility(b,player,opponent);
		}

	int max_v = -1000, tmp;
	std::vector<OthelloBoard> v;
	/* create player's next move */
	Successor(b,v, player);
	int size = v.size();

	for(int i = 0; i < size; ++i){
		tmp = min_value(&v[i], player, opponent);
		//int tmp = v[i].count_score(player);
		if(tmp > max_v){
			max_v = tmp;
		}
	}

	return max_v;

}
int min_value(OthelloBoard* b, char player, char opponent)
{
	/*terminal test*/
	if( b->has_legal_moves_remaining(player) == false and
		b->has_legal_moves_remaining(opponent) == false){
			return Utility(b,player,opponent);
		}
	int min_v = 1000, tmp;
	std::vector<OthelloBoard> v;
	/* create opponent's next move */
	Successor(b,v,opponent);
	int size = v.size();

	for(int i = 0; i < size; ++i){
		tmp = max_value(&v[i], player, opponent);

		if(tmp < min_v){
			min_v = tmp;
		}
	}

	return min_v;

}

void minimaxDecision(OthelloBoard* b,char player)
{
	std::cout << b->count_score(player);
}




/*
	This function is called after it checks there is a legal move

	to get score
	board->count_score(this->get_symbol(););

	to check the legal move
	board->is_legal_move(col, row, this->get_symbol();)

	is_legal_move
	flip_pieces
	has_legal_moves_remaining
	count_score
	play_move
	get_p1_symbol
	get_p2_symbol
	set_coords_in_direction
	check_endpoint
	flip_pieces_helper
***********************************************************/
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {

	char player = this->get_symbol();
	char opponent = 'O';
	if(player == 'O'){
		opponent = 'X';
	}
	//std::cout <<player<<'\n'<<opponent<<'\n';
	std::cout << max_value(b,player,opponent);
	std::vector<OthelloBoard> v;
	/*
	Successor(b,v,player);
	minimaxDecision(&v[0],player);
	*/
	/*
	OthelloBoard b2 = OthelloBoard(*b);
	std::vector<OthelloBoard> v;

	std::cout << v[0].get_cell(1,1);
	*/
    std::cout << "Enter col: ";
    std::cin >> col;
    std::cout << "Enter row: ";
    std::cin >> row;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
