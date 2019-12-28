#include "blocks.h"

using namespace std;

void Block::MoveUp(){
	if(canMoveVertical && posY > 0)
		posY--;
}
void Block::MoveLeft(){
	if(canMoveHorizontal && posX > 0)
		posX--;
}
void Block::MoveDown(){
	if(canMoveVertical && posY + height - 1 < 5)
		posY++;
}
void Block::MoveRight(){
	if(canMoveHorizontal && posX + width - 1 < 5)
		posX++;
	else if(canMoveHorizontal && posX + width - 1 == 5 && posY == 2)
		posX++;
}