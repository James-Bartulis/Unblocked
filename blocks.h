#ifndef _blocks_h_
#define _blocks_h_

class Block{
protected:
	int posX, posY, width, height;
	bool canMoveHorizontal, canMoveVertical;
public:
	Block(){}
	Block(Block* b)
	{
		this->posX = b->posX;
		this->posY = b->posY;
		this->width = b->width;
		this->height = b->height;
		this->canMoveHorizontal = b->canMoveHorizontal;
		this->canMoveVertical = canMoveVertical;
	}
	Block(int x, int y) : posX(x), posY(y){}

	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();

	friend class Game;
};
class BlockFactory{
public:
	BlockFactory(){}

	virtual Block* generateBlock(int x, int y) = 0;
};


class B12 : public Block{
public:
	B12(){}
	B12(int x, int y){
		posX = x;
		posY = y;
		height = 1;
		width = 2;
		canMoveHorizontal = true;
		canMoveVertical = false;
	}
};
class B12Factory : public BlockFactory{
public:
	B12Factory(){}

	Block* generateBlock(int x, int y){
		return new B12(x,y);
	}
};
class B13 : public Block{
public:
	B13(int x, int y){
		posX = x;
		posY = y;
		height = 1;
		width = 3;
		canMoveHorizontal = true;
		canMoveVertical = false;
	}
};
class B13Factory : public BlockFactory{
public:
	B13Factory(){}

	Block* generateBlock(int x, int y){
		return new B13(x,y);
	}
};
class B21 : public Block{
public:
	B21(int x, int y){
		posX = x;
		posY = y;
		height = 2;
		width = 1;
		canMoveHorizontal = false;
		canMoveVertical = true;
	}
};
class B21Factory : public BlockFactory{
public:
	B21Factory(){}

	Block* generateBlock(int x, int y){
		return new B21(x,y);
	}
};
class B31 : public Block{
public:
	B31(int x, int y){
		posX = x;
		posY = y;
		height = 3;
		width = 1;
		canMoveHorizontal = false;
		canMoveVertical = true;
	}
};
class B31Factory : public BlockFactory{
public:
	B31Factory(){}

	Block* generateBlock(int x, int y){
		return new B31(x,y);
	}
};

#endif