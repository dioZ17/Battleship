battleship: tile.cpp board.cpp ship.cpp main.cpp
	g++ -o battleship tile.cpp board.cpp ship.cpp player.cpp game.cpp main.cpp -std=c++11 -I.
