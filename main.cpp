#include <iostream>
#include <windows.h>
#include "blocks.cpp"
#include "unblocked.cpp"

using namespace std;

int main(){

	Game* test = new Game();

	while(test->isGameRunning()){
		test->Display();
		test->Input();
		test->Logic();
	}

}