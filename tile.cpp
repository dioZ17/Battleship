#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "battleships.h"

using namespace std;

Tile::Tile(){};

Tile::Tile(int yi, int xi, int value){
	x = xi;
	y = yi;
	val = value;
};

int Tile::get_val(){return val;}
int Tile::get_x(){return x;}
int Tile::get_y(){return y;}

void Tile::set_xy(int yi, int xi){
	this->x = xi;
	this->y = yi;
}

void Tile::set_val(int value){
	val = value;
}

void Tile::draw(bool hidden){
	
		switch(val){
			case SEA :
				cout << "~";
				break;
			case SHIP : {
				if(hidden == true)
				cout << "~";
				else
				cout << "s";
			}
				break;
			case MISS :
				cout << "o";
				break;
			case HIT :
				cout << "x";
				break;
		}		
}
