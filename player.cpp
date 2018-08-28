#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "battleships.h"

using namespace std;

Player::Player(char* playerName){
	strcpy(name,playerName);
	shotsFired = 0;
	shotsHit = 0;
	shotsMissed = 0;
	shotsOnSameTile = 0;
};

void Player::placeAllShips(){
	//EXPECTING IMPLEMENTATION
}
/*
void Player::placeShip(Game *game, Ship *ship, Board *board){
	
	int *quords;
	bool orientation;
	
	cout << "Enter the quordinates of the Ship (separated by space) : ";
	quords = game->getInputQuordinates();
	cout << "Enter the Orientation of the Ship H/V";
	
	while(1){
		cin << orientation;
		if(!(orientation == HORIZONTAL || orientation == VERTICAL))
			cerr << "Wrong Orientation" << endl;
		else
			break;
	}
		
	if(board->placeShip(*quords, *(quords++), orientation, board) == true){
		placeShip(game, ship, board);
		return;
	}
	
}
		
*/	


	


bool Player::fire(Board *board, int quords[2]){

	//Trap Out of Bounds
	if(quords[0] < 0 || quords[0] < 0){
		cerr << "Error: Wrong quordinates (" <<
		quords[0] << "," << quords[1] << ")" << endl;
		return false;
	}else if(quords[0] >= BOARD_L || quords[0] >= BOARD_L){
		cerr << "Error: Wrong quordinates (" <<
		quords[0] << "," << quords[1] << ")" << endl;
		return false;
	}


	switch(board->getTile(quords[0],quords[1])->get_val()){
		case SEA	: {
			board->getTile(quords[0],quords[1])->set_val(MISS);
			shotsMissed++;
			break;
		}
		case SHIP	: {
			board->getTile(quords[0],quords[1])->set_val(HIT);
			shotsHit++;
			break;
		}
		case MISS	: {
			shotsOnSameTile++;
			break;
		}
		case HIT	: {
			shotsOnSameTile++;
			break;
		}
		default		: {
		cerr << "Error: Tile has unexpected value!" << endl;
		break;
		return false;
		}
	}
	shotsFired++;
	return true;
}

int * Player::getStats(){
	int *stats[4];
	int *ptr;
	stats[0] = &shotsFired;
	stats[1] = &shotsMissed;
	stats[2] = &shotsHit;
	stats[3] = &shotsOnSameTile;
	//*ptr = stats;
	
	return *stats;
}
