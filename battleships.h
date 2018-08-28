#define BOARD_L 7

#define SEA 	0
#define SHIP 	1
#define MISS 	2
#define HIT 	3

#define HORIZONTAL 	true
#define VERTICAL	false

int random(int limit);

class Tile{

private:
	int x,y;
	int val;

public:
	Tile();
	Tile(int y, int x, int val);
	int get_x();
	int get_y();
	int get_val();
	
	void set_xy(int yi, int xi);
	void set_val(int value);

	void draw(bool hidden);
};


class Board{
	public:
	Tile tile_map[BOARD_L][BOARD_L];
	bool hidden;
	
	public:
		Board();
		void clearBoard();
		Tile* getTile(int y, int x);
		void drawBoards(Board *op_board);
		void drawBoards();
		Tile* getAdjacentTiles(Tile *tile);
		bool getAdjacentTiles(int y, int x);
		void placeAllShips();
		bool allShipsSunk(bool win);
		Tile* getMap();
};

class Ship{
	protected:
	Tile *start;
	bool orientation;
	int tileNum;
	public:
	bool placeShip(int x, int y, bool orientation, Board *board, bool verbose);
};
class Carrier:public Ship{
	public:
	Carrier();
};
class Battleship:public Ship{
	public:
	Battleship();
};
class Cruiser:public Ship{
	public:
	Cruiser();
};
class Submarine:public Ship{
	public:
	Submarine();
};
class Destroyer:public Ship{
	public:
	Destroyer();
};

class Player{
	
	public:
	char name[];
	//Statistics
	int shotsFired;
	int shotsHit;
	int shotsMissed;
	int shotsOnSameTile;
	
	Player(char name[]);
	
	void placeAllShips();
	bool fire(Board *board, int quords[2]);
	int* getStats();
};

class Game{
	
	public:
	Game();
	void mainGame();
	int* getInputQuordinates();
	void readInput();
	bool getOrientation();
	bool getYNInput();
	int getRandom(int limit);
	bool gameOver(Player *player, Board *board, bool win);
	void placeShipsManually(Board *board);
};
