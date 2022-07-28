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

/*
	returns the difference of score
***************************************/
int Utility(OthelloBoard* b, char player, char opponent)
{
	return (b->count_score(player)) - (b->count_score(opponent));
}
/*
	exoand all next move for player and store informaion
	into the vector
**************************************************/
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
/*
	this function check all next player's move
	using accessor funciont
	and send info to min_value function
	these connection continue until game is over
*************************************************/
int max_value(OthelloBoard* b, char player, char opponent)
{
	bool no_move = false;
	/*terminal test*/
	if( b->has_legal_moves_remaining(player) == false){
		no_move = true;
		if(b->has_legal_moves_remaining(opponent) == false){
			return Utility(b,player,opponent);
		}
	}

	int max_v = -1000, tmp;
	std::vector<OthelloBoard> v;
	/* create player's next move */
	/* if there is a move */
	if(!no_move){
		Successor(b,v, player);
	}else{
		v.push_back(OthelloBoard(*b));
	}

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
/*
	this function check all next opponent's move
	using accessor funciont
	and send info to max_value function
	these connection continue until game is over
*************************************************/
int min_value(OthelloBoard* b, char player, char opponent)
{
	bool no_move = false;
	/*terminal test*/
	if( b->has_legal_moves_remaining(opponent) == false){
		no_move = true;
		if(b->has_legal_moves_remaining(player) == false){
			return Utility(b,player,opponent);
		}
	}

	int min_v = 1000, tmp;
	std::vector<OthelloBoard> v;
	/* create opponent's next move */
	if(!no_move){
		Successor(b,v, opponent);
	}else{
		v.push_back(OthelloBoard(*b));
	}
	int size = v.size();

	for(int i = 0; i < size; ++i){
		tmp = max_value(&v[i], player, opponent);

		if(tmp < min_v){
			min_v = tmp;
		}
	}

	return min_v;

}

/*
	when this called, there is atleast one proper movement for player
	this function expands player's next move with col and row information
	if this function finds better max value, this updatas col and row for solution path
***********************************************************************/
void minimaxDecision(OthelloBoard* b, char player, char opponent, int& col, int& row)
{

	int max_v = -1000, tmp;
	std::vector<OthelloBoard> v;
	std::vector<int> v_col, v_row;

	v.push_back(OthelloBoard(*b));
	int index = 0;
	int num_cols = 4, num_rows = 4;

	for (int c = 0; c < num_cols; c++) {
		for (int r = 0; r < num_rows; r++) {
			if (b->is_cell_empty(c, r) && b->is_legal_move(c, r, player)) {
				v.push_back(OthelloBoard(*b));
				v[index].play_move(c,r,player);
				v_col.push_back(c);
				v_row.push_back(r);
				//std::cout << v_col[index] << v_row[index];
				++index;
			}
		}
	}


	for(int i = 0; i < index; ++i){
		tmp = min_value(&v[i], player, opponent);
		//int tmp = v[i].count_score(player);
		if(tmp > max_v){
			max_v = tmp;
			col = v_col[i];
			row = v_row[i];
		}
	}

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
	int tmp_col, tmp_row;
	minimaxDecision(b,player,opponent,tmp_col,tmp_row);
	col = tmp_col;
	row = tmp_row;
	/* Debug comments */
	//std::cout << col << row;
	//std::cout <<player<<'\n'<<opponent<<'\n';
	/*
	std::cout << max_value(b,player,opponent);
	std::vector<OthelloBoard> v;
	*/
	/*
	Successor(b,v,player);
	minimaxDecision(&v[0],player);
	*/
	/*
	OthelloBoard b2 = OthelloBoard(*b);
	std::vector<OthelloBoard> v;

	std::cout << v[0].get_cell(1,1);
	*/
	/*
    std::cout << "Enter col: ";
    std::cin >> col;
    std::cout << "Enter row: ";
    std::cin >> row;
	*/
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
