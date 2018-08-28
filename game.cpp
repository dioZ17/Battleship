#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include <random>
#include <chrono>
#include <climits>
#include "battleships.h"

using namespace std;

Game::Game(){};

int* Game::getInputQuordinates(){
	int *ptr;
	int input[2];
	string input_ar;
	cin.clear();
	getline(cin,input_ar);
	
	if(input_ar[1] != ' '){
		cerr << "Wrong Input Format" << endl;
		return NULL;
	}
	
	input[0] = (int)input_ar[0]-48;
	input[1] = (int)input_ar[2]-48;

	if(input[0] < 0 || input[0] >= BOARD_L || input[1] < 0 || input[1] >= BOARD_L){
		cerr << "Input Out of Bounds" << endl;
		return NULL;	
	}
	ptr = input;
	return ptr;	
}

bool Game::getYNInput(){
	char inputChar;
	bool input;
	cin >> inputChar;

	if(inputChar =='Y'){
		input = true;
	}else if(inputChar =='N'){
		input = false;
	}else{
		cerr << "Wrong Input Format" << endl;
		cout << inputChar;
		return NULL;
	}

	return input;
}

int Game::getRandom(int limit){
	return random(limit);
}

void Game::placeShipsManually(Board* board){
	
	Ship ships[5];
	
	Carrier carrier;
	Battleship battleship;
	Cruiser cruiser;
	Submarine submarine;
	Destroyer destroyer;
	
	ships[0] = carrier;
	ships[1] = battleship;
	ships[2] = cruiser;
	ships[3] = submarine;
	ships[4] = destroyer;
	
	string shipNames[5];
	
	shipNames[0] = "Carrier";
	shipNames[1] = "Battleship";
	shipNames[2] = "Cruiser";
	shipNames[3] = "Submarine";
	shipNames[4] = "Destroyer";
	
	int* xy;
	char orientationInput;
	bool orientation;
	int i;
	
	for(i = 0; i<5; i++){
		board->drawBoards();
		cout << "Place " << shipNames[i] << endl;
		while(1){
			cout << "Enter the Ship's Bow Quordinates (separated by space) Y X" << endl;
			cin.clear();
			cin.ignore(INT_MAX,'\n');	
	
			while(1){
				if((xy = getInputQuordinates())!=NULL)
					break;
			}
			cout << "Enter the Ship's Orientation H/V: ";
			while(1){
				cin >> orientationInput;
				if(orientationInput != 'H' && orientationInput != 'V')
					cout << "Try again! H:Horizontal, V:Vertical" << endl;
				else if(orientationInput == 'H'){
					orientation = true;
					break;
				}else if(orientationInput == 'V'){
					orientation = false;
					break;
				}
			}	
			if(ships[i].placeShip(xy[0],xy[1],orientation,board,true)){
			
			break;
			}
		}
	}
	cout << "Placed All Shipts";
}

bool Game::gameOver(Player *player, Board *board, bool win){
			//GAME OVER//
		//Total Ship Squares = 5+4+3+3+2 = 17
		int i,j;
		int *playerStats = player->getStats();
		bool endGame = true;
		if(*playerStats >= 17){
			for(i=0;i<BOARD_L;i++){
				for(j=0;j<BOARD_L;j++){
					if(board->getTile(i,j)->get_val() == SHIP){
						endGame = false;
						break;
					}
					
				}
			}
			if(endGame == true){
				board->allShipsSunk(win);
			}
		}
}

	

void Game::mainGame(){
	
	int pcQuords[2];
	int *playerStats;
	int *pcStats;
	int *xy;
	int i,j;
	char orientationInput;
	bool choice;
	Player player("DioZ");
	Player pc("PC");
	
	Board board;
	Board op_map;
	//Initialize Game
	while(1){

		cout << "Automatically Place All Ships? Y/N ";
		if((choice = getYNInput())==true){
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		
		board.placeAllShips();	
		break;
		}
		else if(choice == false){
		placeShipsManually(&board);
		break;
		}else 
			cout << "Wrong Value!" << endl;
	}	
	cout << "OK, now play the game NIBBA!"<<endl;
	//PLAY GAME
	op_map.placeAllShips();
	
	board.drawBoards(&op_map);
	
	while(1){
		cout << "Enter Firing Quordinates (X Y) : ";
		while(1){
				if((xy = getInputQuordinates())!=NULL){
					if(player.fire(&op_map, xy)==true){
					break;
					}
				}
			cout << "Try again (Hint:Num-space-Num) :";
		}
		//aim randomly & fire PC
		pcQuords[0] = getRandom(6);
		pcQuords[1] = getRandom(6);
		pc.fire(&board, pcQuords);
		playerStats = player.getStats();
		pcStats = pc.getStats();
		
		board.drawBoards(&op_map);
		/*cout << "\t\t -PLAYER-STATS - - -OPPONENT-STATS - " << endl;
		cout << "Shots Fired: \t" << *playerStats << "\t\t" << pcStats << endl;
		cout << "Shots Missed: \t" << *playerStats++ << "\t\t" << pcStats++ << endl;
		cout << "Shots Hit: \t\t" << *playerStats++ << "\t\t" << pcStats++ << endl;
		cout << "ShotsOnSameTile: " << *playerStats++ << "\t\t" << pcStats++ << endl;
		*/
		cout << "\t -PLAYER-STATS - OPPONENT-STATS - " << endl;
		cout << "Shots Fired: \t" << *playerStats << "\t\t" << *pcStats << endl;
		playerStats++;pcStats++;
		cout << "Shots Hit: \t" << *playerStats << "\t\t" << *pcStats << endl;
		playerStats++;pcStats++;
		cout << "Shots Miss: \t" << *playerStats << "\t\t" << *pcStats << endl;
		playerStats++;pcStats++; 
		cout << "ShotsOnSameTile:" << *playerStats << "\t\t" << *pcStats << endl;
		
		gameOver(&player, &op_map, true);
		gameOver(&pc, &board, false);
		
		
	}
}










