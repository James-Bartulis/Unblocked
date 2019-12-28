#include "unblocked.h"
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

Game::Game(){
	Win = false;
	currentMap = 0;
	currentBlock = 0;
	gameRunning = true;
	cursorActive = false;
	cursorX = 0;
	cursorY = 0;
	Width = 6;
	Height = 6;
	ifstream read;
	int numOfMaps, numOfBlocks, bx, by, type;
	Factory = NULL;
	Solved.clear();
	read.open("Unblocked.txt");
		read >> numOfMaps;
		Maps.resize(numOfMaps);
		for(int i = 0; i < numOfMaps; i++){
			Solved.push_back(false);
			Maps[i] = new Map();
			read >> numOfBlocks;
			for(int j = 0; j < numOfBlocks; j++){
				read >> bx >> by >> type;
				delete Factory;
				switch(type){
					case 1:
						Factory = new B12Factory();
						break;
					case 2:
						Factory = new B13Factory();
						break;
					case 3:
						Factory = new B21Factory();
						break;
					case 4:
						Factory = new B31Factory();
						break;
					default:
						break;
				}
				Maps[i]->Blocks.push_back(Factory->generateBlock(bx,by));
			}
		}
	read.close();
}

void Game::Display(){
	system("CLS");

	bool nothing = true;


	for(int i = 0; i < Width + 2; i++)
		cout << char(178);
	if(Solved[currentMap])
		cout << "Solved!\t" << currentMap << endl;
	else
		cout << "\t" << currentMap << endl;
	for(int i = 0; i < Width; i++){
		for(int j = 0; j < Height; j++){
			if(j == 0)
				cout << char(178);
			if(cursorActive && cursorX == j && cursorY == i)
				cout << char(233);
			else{
				nothing = true;
				for(int k = 0; k < Maps[currentMap]->Blocks.size(); k++){
					if(Maps[currentMap]->Blocks[k]->posX <= j && Maps[currentMap]->Blocks[k]->posY <= i &&
						Maps[currentMap]->Blocks[k]->posX + Maps[currentMap]->Blocks[k]->width > j &&
						Maps[currentMap]->Blocks[k]->posY + Maps[currentMap]->Blocks[k]->height > i
						){
						if(currentBlock == k)
							cout << char(65 + k);
						else
							cout << char(97 + k);
						nothing	= false;
					}
				}
				if(nothing)
					cout << " ";
			}
			if(j == Height - 1 && i != 2)
				cout << char(178);
		}
		cout << endl;
	}
	for(int i = 0; i < Width + 2; i++)
		cout << char(178);
	cout << "\nHow to Play : H" << endl;
}

void Game::CycleLeft()
{
	if(currentBlock > 0)
		currentBlock--;
	else
		currentBlock = Maps[currentMap]->Blocks.size() - 1;
}
void Game::CycleRight()
{
	if(currentBlock < Maps[currentMap]->Blocks.size() - 1)
		currentBlock++;
	else
		currentBlock = 0;
}

void Game::MoveUp()
{
	if(canMoveTo(Maps[currentMap]->Blocks[currentBlock]->posX,Maps[currentMap]->Blocks[currentBlock]->posY - 1))
		Maps[currentMap]->Blocks[currentBlock]->MoveUp();
}
void Game::MoveLeft()
{
	if(canMoveTo(Maps[currentMap]->Blocks[currentBlock]->posX - 1,Maps[currentMap]->Blocks[currentBlock]->posY))
		Maps[currentMap]->Blocks[currentBlock]->MoveLeft();
}
void Game::MoveDown()
{
	if(canMoveTo(Maps[currentMap]->Blocks[currentBlock]->posX,Maps[currentMap]->Blocks[currentBlock]->posY + Maps[currentMap]->Blocks[currentBlock]->height))
		Maps[currentMap]->Blocks[currentBlock]->MoveDown();
}
void Game::MoveRight()
{
	if(canMoveTo(Maps[currentMap]->Blocks[currentBlock]->posX + Maps[currentMap]->Blocks[currentBlock]->width,Maps[currentMap]->Blocks[currentBlock]->posY))
		Maps[currentMap]->Blocks[currentBlock]->MoveRight();
}

void Game::Input(){
	switch(getch()){
		case 'Q': /// cycle left
		case 'q': /// cycle left
			CycleLeft();
			break;
		case 'E': /// cycle right
		case 'e': /// cycle right
			CycleRight();
			break;
		case 'W': /// move up
		case 'w': /// move up
			MoveUp();
			break;
		case 'A': /// move left
		case 'a': /// move left
			MoveLeft();
			break;
		case 'S': /// move down
		case 's': /// move down
			MoveDown();
			break;
		case 'D': /// move right
		case 'd': /// move right
			MoveRight();
			break;
		case '/': /// Edit
			Edit();
			break;
		case 'C': /// ends game
			gameRunning = false;
			break;
		case ']': /// next map
			if(currentMap < Maps.size() - 1){
				currentMap++;
				currentBlock = 0;
			}
			break;
		case '[': /// previous map
			if(currentMap > 0){
				currentMap--;
				currentBlock = 0;
			}
			break;
		case '.': /// jump to char
			char temp;
			cout << "Piece to control: _" << endl;
			temp = getch();
			if(temp >= 97 && temp <= 97 + Maps[currentMap]->Blocks.size() - 1)
				currentBlock = int(temp) - 97;
			break;
		case 'H':
			Help();
			break;
		case 'R':
			reloadCurrentMap();
			break;
		default:
			break;
	}
}
void Game::Logic(){
	if(!canMoveTo(Width, (Height - 1) / 2)){ ///checks if you beat the map
		int nextToBeSolved;
		Win = true;
		for(int i = 0; i < Solved.size(); i++){
			if(Solved[i] == false){
				nextToBeSolved = i;
				Win = false;
				break;
			}
		}
		if(Win){
			gameRunning = false;
			cout << endl << "You won!\nPress c to Continue";
			while(getch() != 'c'){}
		}
		Solved[currentMap] = true;
		reloadCurrentMap();
		if(currentMap < Maps.size() - 1)
			currentMap++;
		else
			currentMap = nextToBeSolved;
		currentBlock = 0;
	}
	if(gameRunning == false){
		cout << endl << "You quit!\n";
	}
}

bool Game::isGameRunning(){
	return gameRunning;
}
void Game::Edit(){
	cursorActive = true;
	bool editing = true;
	char input;
	while(editing){
		Display();
		cout << "Edit Info:" << endl;
		cout << "\t(1-4) will generate a new piece with given dimensions\n\toriginating from the cursor to the right or below the cursor" << endl;
		cout << "\t1 : XX" << endl;
		cout << "\t2 : XXX" << endl;
		cout << endl;
		cout << "\t3 : \tX\n\t\tX" << endl;
		cout << endl;
		cout << "\t4 : \tX\n\t\tX\n\t\tX" << endl;
		cout << endl;
		cout << "\t+ : create new map" << endl;
		cout << "\t- : deletes block sharing a location with the cursor" << endl;
		cout << "\t| : save changes" << endl;
		cout << "\t_ : delete current map" << endl;
		input = getch();
		switch(input){
			case 'W':
			case 'w':
				if(cursorY > 0)
				cursorY--;
				break;
			case 'A':
			case 'a':
				if(cursorX > 0)
					cursorX--;
				break;
			case 'S':
			case 's':
				if(cursorY < Height - 1)
					cursorY++;
				break;
			case 'D':
			case 'd':
				if(cursorX < Width - 1)
					cursorX++;
				break;
			case '1':
				if(canMoveTo(cursorX, cursorY) && canMoveTo(cursorX + 1, cursorY) && inBoundsOfMap(cursorX, cursorY, 2, 1)){
					Factory = new B12Factory();
					Maps[currentMap]->Blocks.push_back(Factory->generateBlock(cursorX,cursorY));
				}
				break;
			case '2':
				if(canMoveTo(cursorX, cursorY) && canMoveTo(cursorX + 1, cursorY) && canMoveTo(cursorX + 2, cursorY) && inBoundsOfMap(cursorX, cursorY, 3, 1)){
					Factory = new B13Factory();
					Maps[currentMap]->Blocks.push_back(Factory->generateBlock(cursorX,cursorY));
				}
				break;
			case '3':
				if(canMoveTo(cursorX, cursorY) && canMoveTo(cursorX, cursorY + 1) && inBoundsOfMap(cursorX, cursorY, 1, 2)){
					Factory = new B21Factory();
					Maps[currentMap]->Blocks.push_back(Factory->generateBlock(cursorX,cursorY));
				}
				break;
			case '4':
				if(canMoveTo(cursorX, cursorY) && canMoveTo(cursorX, cursorY + 1) && canMoveTo(cursorX, cursorY + 2) && inBoundsOfMap(cursorX, cursorY, 1, 3)){
					Factory = new B31Factory();
					Maps[currentMap]->Blocks.push_back(Factory->generateBlock(cursorX,cursorY));
				}
				break;
			case '+': /// creates new map
				Maps.push_back(new Map());
				currentMap++;
				Solved.push_back(false);
				break;
			case 'Z': /// exits editing
				editing = false;
				break;
			case '|': /// saves progress
				saveMaps();
				break;
			case '-': /// deletes block sharing same location
				deleteBlock();
				break;
			case '_':
				removeMap();
				break;
			case 'H':
				Help();
				break;
			default:
				break;
		}
	}
		cursorActive = false;
}

bool Game::inBoundsOfMap(int x, int y, int width, int height){
	if(x >= 0 && y >= 0 &&
		x + width - 1 < Width &&
		y + height - 1 < Height)
	{
		return true;
	}
	return false;
}

bool Game::canMoveTo(int x, int y){
	for(int i = 0; i < Maps[currentMap]->Blocks.size(); i++){
		if(Maps[currentMap]->Blocks[i]->posX <= x && Maps[currentMap]->Blocks[i]->posY <= y &&
		Maps[currentMap]->Blocks[i]->posX + Maps[currentMap]->Blocks[i]->width - 1 >= x &&
		Maps[currentMap]->Blocks[i]->posY + Maps[currentMap]->Blocks[i]->height - 1 >= y
		){
			return false;
		}
	}
	return true;
}

void Game::saveMaps(){
	ofstream write;
	write.open("Unblocked.txt");
		write << Maps.size() << " ";
		for(int i = 0; i < Maps.size(); i++){
			write << Maps[i]->Blocks.size() << endl;
			for(int j = 0; j < Maps[i]->Blocks.size(); j++){
				write << Maps[i]->Blocks[j]->posX << " " << Maps[i]->Blocks[j]->posY << " ";
				if(Maps[i]->Blocks[j]->width == 2)
					write << 1;
				else if(Maps[i]->Blocks[j]->width == 3)
					write << 2;
				else if(Maps[i]->Blocks[j]->height == 2)
					write << 3;
				else if(Maps[i]->Blocks[j]->height == 3)
					write << 4;
				write << endl;
			}
		}
	write.close();
}

void Game::deleteBlock(){
	for(int i = 0; i < Maps[currentMap]->Blocks.size(); i++){
		if(Maps[currentMap]->Blocks[i]->posX <= cursorX && Maps[currentMap]->Blocks[i]->posY <= cursorY &&
		Maps[currentMap]->Blocks[i]->posX + Maps[currentMap]->Blocks[i]->width - 1 >= cursorX &&
		Maps[currentMap]->Blocks[i]->posY + Maps[currentMap]->Blocks[i]->height - 1 >= cursorY
		){
			// delete Maps[currentMap]->Blocks[i];
			for(; i < Maps[currentMap]->Blocks.size(); i++)
				Maps[currentMap]->Blocks[i] = Maps[currentMap]->Blocks[i + 1];
			Maps[currentMap]->Blocks.erase(Maps[currentMap]->Blocks.end() - 1);
		}
	}
}

void Game::Help(){
	system("CLS");

	cout << "How to play :" << endl;
	cout << "\tHorizontal pieces\n\t\tMove : left or right" << endl;
	cout << "\tVertical pieces\n\t\tMove : up or down" << endl;
	cout << "\tw : UP" << endl;
	cout << "\ta : DOWN" << endl;
	cout << "\ts : LEFT" << endl;
	cout << "\td : RIGHT" << endl;
	cout << "\t. : pick piece to control _\n\t\t(a-z, if exisits)" << endl;
	cout << "\t[ : previous map" << endl;
	cout << "\t] : next map" << endl;
	cout << "\tR : reset current map" << endl;
	cout << "\tq : cycle pieces backwards" << endl;
	cout << "\te : cycle pieces forwards" << endl;
	cout << "\tC : quits game" << endl;
	cout << endl;
	cout << endl;
	cout << "How to edit :" << endl;
	cout << "\t/ : to enter editing mode (cursor will appear)" << endl;
	cout << "\tZ : to exit editing mode" << endl;
	cout << endl;
	cout << "Once in editing mode:" << endl;
	cout << "\tw : UP" << endl;
	cout << "\ta : DOWN" << endl;
	cout << "\ts : LEFT" << endl;
	cout << "\td : RIGHT" << endl;
	cout << endl;
	cout << "\t(1-4) will generate a new piece with given dimensions\n\toriginating from the cursor to the right or below the cursor" << endl;
	cout << "\t1 : height = 1\twidth = 2" << endl;
	cout << "\t2 : height = 1\twidth = 3" << endl;
	cout << "\t3 : height = 2\twidth = 1" << endl;
	cout << "\t4 : height = 3\twidth = 1" << endl;
	cout << endl;
	cout << "\t+ : create new map" << endl;
	cout << "\t- : deletes block sharing a location with the cursor" << endl;
	cout << "\t| : save changes" << endl;
	cout << "\t_ : delete current map" << endl;

	system("PAUSE");
}

void Game::removeMap(){
	Solved.erase(Solved.begin() + currentMap);
	for(int i = 0; i < Maps[currentMap]->Blocks.size(); i++)
		delete Maps[currentMap]->Blocks[i];
	delete Maps[currentMap];
	for(int i = currentMap; i < Maps.size() - 1; i++)
		Maps[i] = Maps[i + 1];
	Maps.resize(Maps.size() - 1);
	currentMap--;
}

void Game::reloadCurrentMap(){
	ifstream read;
	int tblocks = 0, garbage, type;
	read.open("Unblocked.txt");
		read >> garbage;
		for(int i = 0; i < currentMap; i++){
			read >> tblocks;
			for(int j = 0; j < tblocks ; j++){
				read >> garbage;
				read >> garbage;
				read >> garbage;
			}
		}
		read >> tblocks;
		for(int i = 0; i < tblocks; i++){
			read >> Maps[currentMap]->Blocks[i]->posX;
			read >> Maps[currentMap]->Blocks[i]->posY;
			read >> type;
			switch(type){
				case '1':
					Maps[currentMap]->Blocks[i]->height = 1;
					Maps[currentMap]->Blocks[i]->width = 2;
					Maps[currentMap]->Blocks[i]->canMoveHorizontal = true;
					Maps[currentMap]->Blocks[i]->canMoveVertical = false;
					break;
				case '2':
					Maps[currentMap]->Blocks[i]->height = 1;
					Maps[currentMap]->Blocks[i]->width = 3;
					Maps[currentMap]->Blocks[i]->canMoveHorizontal = true;
					Maps[currentMap]->Blocks[i]->canMoveVertical = false;
					break;
				case '3':
					Maps[currentMap]->Blocks[i]->height = 2;
					Maps[currentMap]->Blocks[i]->width = 1;
					Maps[currentMap]->Blocks[i]->canMoveHorizontal = false;
					Maps[currentMap]->Blocks[i]->canMoveVertical = true;
					break;
				case '4':
					Maps[currentMap]->Blocks[i]->height = 3;
					Maps[currentMap]->Blocks[i]->width = 1;
					Maps[currentMap]->Blocks[i]->canMoveHorizontal = false;
					Maps[currentMap]->Blocks[i]->canMoveVertical = true;
					break;
			}
		}
	read.close();
}

// void Game::Rules(){
// 	system("CLS");
// 	cout << "Horizontal pieces\n\tCan Move : left or right" << endl;
// 	cout << "Vertical pieces\n\tCan Move : up or down" << endl;
// 	cout << "Objective\n\tMove piece 'a' through opening on the right" << endl;
// }