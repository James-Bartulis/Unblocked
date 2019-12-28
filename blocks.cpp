#include "blocks.h"

using namespace std;

void Block::MoveUp(){
	if(canMoveVertical)
		posY--;
}
void Block::MoveLeft(){
	if(canMoveHorizontal)
		posX--;
}
void Block::MoveDown(){
	if(canMoveVertical)
		posY++;
}
void Block::MoveRight(){
	if(canMoveHorizontal)
		posX++;
}