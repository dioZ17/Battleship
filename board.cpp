#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <random>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "battleships.h"

#define SEARCH_LIMIT 64

using namespace std;


//random generator

	default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed
	int random (int lim)
	{
		uniform_int_distribution<int> uid {0,lim};   // help dre to generate nos from 0 to lim (lim included);
		return uid(dre);    // pass dre as an argument to uid to generate the random no
	}



Board::Board(){
	int i,j;
	for(i=0;i<BOARD_L;i++){
		for(j=0;j<BOARD_L;j++){
			tile_map[i][j].set_xy(i,j);
			tile_map[i][j].set_val(SEA);
		}
	}
	//hidden = true;
};

Tile* Board::getTile(int y, int x){
	Tile *ptr;
	ptr = &tile_map[y][x];
	return ptr;
}

void Board::clearBoard(){
	int i,j;
	for(i=0;i<BOARD_L;i++){
		for(j=0;j<BOARD_L;j++){
			tile_map[i][j].set_val(SEA);
		}
	}	
}

bool Board::getAdjacentTiles(int y, int x){

//Note: Do not try to read xy from returned tiles.
//Val is correct though

	Tile *adjacent[8];
	//Proximity: 0 free, 1 occupied
	bool proximity = 0;
	
	if(y==0){
		adjacent[0]=NULL;
		adjacent[1]=NULL;
		adjacent[2]=NULL;
	}else{ 
		adjacent[0]=this->getTile(y-1,x-1);
		adjacent[1]=this->getTile(y-1,x);
		adjacent[2]=this->getTile(y-1,x+1);
	}
	
	if(x==0){
		adjacent[0]=NULL;
		adjacent[3]=NULL;
		adjacent[5]=NULL;
	}else{
		if(adjacent[0]!=NULL)
		adjacent[0]=this->getTile(y-1,x-1);
		adjacent[3]=this->getTile(y,x-1);
		if(adjacent[5]!=NULL)
		adjacent[5]=this->getTile(y+1,x-1);
	}
		
	if(y==6){
		adjacent[5]=NULL;
		adjacent[6]=NULL;
		adjacent[7]=NULL;
	}else{ 
		adjacent[5]=this->getTile(y+1,x-1);
		adjacent[6]=this->getTile(y+1,x);
		adjacent[7]=this->getTile(y+1,x+1);
	}
	
	if(x==6){
		adjacent[2]=NULL;
		adjacent[4]=NULL;
		adjacent[7]=NULL;
	}else{
		if(adjacent[2]!=NULL)
		adjacent[2]=this->getTile(y-1,x+1);
		adjacent[4]=this->getTile(y,x+1);
		if(adjacent[7]!=NULL)
		adjacent[7]=this->getTile(y+1,x+1);
	}
		//Check output
		int i;
		for(i=0;i<8;i++){
			if(adjacent[i]==NULL)
				cout << "NULL Tile at cell " << i << endl;
			else{
				//cout << "Tile at " << i << " is "<< adjacent[i]->get_y() << ":" <<adjacent[i]->get_y() << endl; 
				cout << "Tile at " << i << " has a value of " << adjacent[i]->get_val() << endl;
				if(adjacent[i]->get_val() == SHIP)
					proximity = 1;
			}
		}

return proximity;
	
}

void Board::drawBoards(Board *op_board){

	int i,j;

	cout << " - - Y O U - -   - O P P O N E N T - " << endl;
	cout << "  0 1 2 3 4 5 6     0 1 2 3 4 5 6    " << endl;

	for(i=0;i<BOARD_L;i++){
		cout << i;
		for(j=0;j<BOARD_L;j++){
			cout << " ";
			tile_map[i][j].draw(false);
		}
		cout << "   ";
		cout << i;
		for(j=0;j<BOARD_L;j++){
			cout << " ";
			op_board->tile_map[i][j].draw(true);
		}
		cout << "    " << endl;
	}	
	cout << "                                     " << endl;
}

void Board::drawBoards(){

	int i,j;

	cout << " - - Y O U - -  "<< endl;
	cout << "  0 1 2 3 4 5 6 " << endl;

	for(i=0;i<BOARD_L;i++){
		cout << i;
		for(j=0;j<BOARD_L;j++){
			cout << " ";
			tile_map[i][j].draw(false);
		}
		cout << endl;
	}	
	cout << "                                     " << endl;
}


Tile* Board::getAdjacentTiles(Tile *tile){
	//EXPECTED IMPLEMENTATION
}

void Board::placeAllShips(){
	
	bool orientation, success=false;
	int x;
	int y;
	int counter;
	Carrier carrier;
	Battleship battleship;
	Cruiser cruiser;
	Submarine submarine;
	Destroyer destroyer;
	
	//Place Carrier
	while(1){
		if(random(2)==1){
			orientation = HORIZONTAL;
			x = random(BOARD_L-5);
			y = random(6);
		}else{
			orientation = VERTICAL;
			y = random(BOARD_L-5);
			x = random(6);
		}
		//cout << "Placing Carrier at " << y << ":" << x <<endl;
		if(carrier.placeShip(y,x,orientation,this,true)==true)
			break;
	}	
	//Place Battleship
	while(1){			
		if(random(2)==1){
			orientation = HORIZONTAL;
			x = random(BOARD_L-4);
			y = random(6);
		}else{
			orientation = VERTICAL;
			y = random(BOARD_L-4);
			x = random(6);
		}
		cout << "Placing Battleship at " << y << ":" << x <<endl;
		if(battleship.placeShip(y,x,orientation,this,true)==true)
			break;
	}
	//Place Cruiser
	while(1){			
		if(random(2)==1){
			orientation = HORIZONTAL;
			x = random(BOARD_L-3);
			y = random(6);
		}else{
			orientation = VERTICAL;
			y = random(BOARD_L-3);
			x = random(6);
		}
		cout << "Placing Battleship at " << y << ":" << x <<endl;
		if(cruiser.placeShip(y,x,orientation,this,true)==true)
			break;
	}
	//Place Submarine
	for(counter=0;counter<SEARCH_LIMIT;counter++){	
		if(random(2)==1){
			orientation = HORIZONTAL;
			x = random(BOARD_L-3);
			y = random(6);
		}else{
			orientation = VERTICAL;
			y = random(BOARD_L-3);
			x = random(6);
		}
		cout << "Placing Battleship at " << y << ":" << x <<endl;
		if((success=submarine.placeShip(y,x,orientation,this,true))==true)
			break;
	}
	if(success == false){
		cout << "Failed to place ship, Repeating place ships";
		clearBoard();
		placeAllShips();
		return;
	}
	//Place Destroyer
	for(counter=0;counter<SEARCH_LIMIT;counter++){
		if(random(2)==1){
			orientation = HORIZONTAL;
			x = random(BOARD_L-2);
			y = random(6);
		}else{
			orientation = VERTICAL;
			y = random(BOARD_L-2);
			x = random(6);
		}
		cout << "Placing Battleship at " << y << ":" << x <<endl;
		if((success=destroyer.placeShip(y,x,orientation,this,true))==true)
			break;
	}
	if(success == false){
		cout << "Failed to place ship, Repeating place ships";
		clearBoard();
		placeAllShips();
		return;
	}
}

bool Board::allShipsSunk(bool win){
	char gameOver1[7+4][38] = {
		"-OOO---OOO-----OOOOOO-----OOO----OOO-",
		"--OO---OO-----OOO--OOO----OOO----OOO-",
		"---OOOOO------OOO--OOO----OOO----OOO-",
		"----OOO-------OOO--OOO----OOOOOOOOOO-",
		"---OOOOO-------OOOOOO-----OOOOOOOOOO-",
		
		"-------------------------------------",

		"-OOO-----OOOOOOO----OOOOOO---OOOOOOO-",
		"-OOO-----OO---OO---OOO-------OOO-----",
		"-OOO-----OO---OO----OOOO-----OOOOO---",
		"-OOOOO---OO---OO-------OOO---OOO-----",
		"-OOOOO---OOOOOOO---OOOOOO----OOOOOOO-"};

	char gameOver2[7+4][38] = {
		"-OOO---OOO-----OOOOOO-----OOO----OOO-",
		"--OO---OO-----OOO--OOO----OOO----OOO-",
		"---OOOOO------OOO--OOO----OOO----OOO-",
		"----OOO-------OOO--OOO----OOOOOOOOOO-",
		"---OOOOO-------OOOOOO-----OOOOOOOOOO-",
		
		"-------------------------------------",

		"-OOO-------OOO---OOOOO---OOOO----OOO-",
		"-OOO-------OOO----OOO----OOOOO---OOO-",
		"-OOO---O---OOO----OOO----OOO-OO--OOO-",
		"--OOO-OOO-OOO-----OOO----OOO--OOOOOO-",
		"---OOO---OOO-----OOOOO---OOO----OOOO-"};
	int k,i,j;
	unsigned int micro = 10000;
	cout << " - - Y O U - -   - O P P O N E N T - " << endl;
	cout << "  0 1 2 3 4 5 6     0 1 2 3 4 5 6    " << endl;
	for(k=0; k<11*37;k++){
		for(i=0;i<BOARD_L+4;i++){
			//cout << i;
			for(j=0;j<37;j++){
				if(j*i<k+1){
					if(win == true)
					cout << gameOver2[i][j];
					else 
					cout << gameOver1[i][j];					
				}
				else{
				cout << "-";
				}

			}/*
			cout << "   ";
			cout << i;
			for(j=0;j<BOARD_L;j++){
				if((j+3+BOARD_L)<=k){
				cout << gameOver[i][j+3+BOARD_L];
				cout << gameOver[i][j+3+BOARD_L+1];}
				else{
				cout << " ";
				tile_map[i][j].draw(true);
				}
			}*/
			cout << "    " << endl;
		}	
		usleep(micro);
		cout << "                                     " << endl;
		
		//std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
	}	

//ACTUAL FUNCTION
		cout << "GAME OVER!" << endl;
			exit(EXIT_SUCCESS);



}
