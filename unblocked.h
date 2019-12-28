#ifndef _unblocked_h_
#define _unblocked_h_
#include <vector>

class Map{
private:
	std::vector<Block*> Blocks;
public:
	Map(){}
	Map(Map* m)
	{
		for(int i = 0; i < m->Blocks.size(); i++)
			this->Blocks.push_back(new Block(m->Blocks[i]));
	}

	friend class Game;	
};

class Game{
private:
	BlockFactory* Factory;
	int currentMap, currentBlock;
	std::vector<Map*> Maps;
	std::vector<bool> Solved;
	bool gameRunning, cursorActive, Win;
	int cursorX, cursorY, Width, Height;
public:
	Game();

	void Display();
	void Input();
	void Logic();

	void CycleLeft();
	void CycleRight();

	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();

	bool isGameRunning();
	void Edit();
	bool inBoundsOfMap(int x, int y, int width = 1, int height = 1);
	bool canMoveTo(int x, int y);
	void saveMaps();
	void deleteBlock();
	void Help();
	void removeMap();
	void reloadCurrentMap();
};

#endif