#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "battleships.h"

using namespace std;

bool Ship::placeShip(int y, int x, bool orientation, Board *board, bool verbose){
	
	int i,j;
	bool proximity;
	//TRAP OUT OF BOUNDS
	if(orientation == HORIZONTAL){
		if(x+tileNum > BOARD_L){
			if(verbose=true)
				cerr << "Error: Ship out of Bounds, poop at " << x+tileNum << endl;
			return false;
		}
	}else if(orientation == VERTICAL){
		if(y+tileNum > BOARD_L){
			if(verbose=true)
				cerr << "Error: Ship out of Bounds, poop at " << y+tileNum << endl;
			return false;
		}
	}else{
		cerr << "Wrong orentation" << endl;
		return false;
	}
	
	for(i=0;i<tileNum;i++){
		if(orientation == VERTICAL){
			proximity = board->getAdjacentTiles(i+y,x);
				if(proximity==SHIP){
					cerr << "There is another ship in proximity!" <<endl;
					return false;
				}
		}else
		if(orientation == HORIZONTAL){
			proximity = board->getAdjacentTiles(y,x+i);
				if(proximity==SHIP){
					cerr << "There is another ship in proximity!" <<endl;
					return false;
				}
			}
	}
		
	
	
	
	//SHIP PLACEMENT
	for(i=0;i<tileNum;i++){
		if(orientation == VERTICAL){
		board->tile_map[i+y][x].set_val(SHIP);
		}else
		if(orientation == HORIZONTAL){
			board->tile_map[y][x+i].set_val(SHIP);
		}
	}
	
	return true;
};

Carrier::Carrier(){
	tileNum = 5;
};

Battleship::Battleship(){
	tileNum = 4;
};

Cruiser::Cruiser(){
	tileNum=3;
};

Submarine::Submarine(){
	tileNum = 3;
};

Destroyer::Destroyer(){
	tileNum=2;
};
