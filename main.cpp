#include <iostream>
#include <windows.h>
#include "blocks.cpp"
#include "unblocked.cpp"

using namespace std;

void SetFontSize(int size){
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = size;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

int main(){

	SetFontSize(36);
	Game* test = new Game();

	while(test->isGameRunning()){
		test->Display();
		test->Input();
		test->Logic();
	}
	SetFontSize(16);
}