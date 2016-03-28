#include "Sudoku.h"
#include "GUI.h"
#include <stdlib.h>
#include "graphics2.h"

/*You cannot change the name of these constants but you can change their definition*/
#define MARGIN 120
#define GRId_SIZE 30 //magic number to set the grid to appear nicely on the screen
#define STEP ((MAX_X)/(GRId_SIZE*(BOARD_SIZE)))
#define X_START_OFFSET MARGIN
#define X_END_OFFSET (GRId_SIZE + MARGIN)
#define Y_START_OFFSET MARGIN
#define Y_END_OFFSET (MARGIN+GRId_SIZE)
#define BORDER_OFFSET GRId_SIZE/20

//This function draws sections. It is called everytime a grid is set except when the board is first initialised
//Use the boardSize to determine length of line drawn and sectionSize to determine interval between each size
void drawSections(int boardSize, int sectionSize)
{
	//winbgi graphics 
	setcolor(CYAN);
	setlinestyle(SOLID_LINE, 0, GRId_SIZE / 10);
	setfillstyle(SOLID_FILL, CYAN);

	//draw row maths formula 
	for (int i = sectionSize; i >= 0; i--)
	{ 
		//winbgi graphics
		rectangle(X_START_OFFSET,
			Y_START_OFFSET + (GRId_SIZE*sectionSize*i), 
			X_START_OFFSET+(GRId_SIZE*(boardSize)),
			Y_START_OFFSET + (GRId_SIZE*(sectionSize)));
	}

	//draw column maths formula 
	for (int i = sectionSize; i >= 0; i--)
	{
		//winbgi graphics
		rectangle(X_START_OFFSET + (GRId_SIZE*sectionSize*i),
			Y_START_OFFSET, 
			X_START_OFFSET + (GRId_SIZE*sectionSize*i),
			Y_START_OFFSET + (GRId_SIZE*(boardSize)));
	}
}

//draw selection grid
void drawSelectionGrid(int boardSize)
{
	int i, j;
	j = boardSize + 1;
	for (i = 1; i <= boardSize; i++) {
		setGridValue(i - 1, j, i);
	}
}

//This function checks if user clicked out of the board
int isClickOutOfBoard(int board){
	int mouseX = mouseclickx(), mouseY = mouseclicky();
	if ((mouseX > X_START_OFFSET && mouseX < X_START_OFFSET + (GRId_SIZE*board)&& //Check if in board
		mouseY > Y_START_OFFSET && mouseY < Y_START_OFFSET + (GRId_SIZE*(board))))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//This function checks if user clicked to select a value
int isClickInSelection(int board){
	int mouseX = mouseclickx(), mouseY = mouseclicky();
	if ((mouseX > X_START_OFFSET && mouseX < X_START_OFFSET + (GRId_SIZE*board) && //Check if in input board
		mouseY > Y_START_OFFSET + (GRId_SIZE*(board + 1)) && mouseY < Y_START_OFFSET + (GRId_SIZE*(board + 2))))
		return TRUE;
	else
		return FALSE;
}

//Get x of grid that user chose
int getMouseX(){
	int mc = mouseclickx();
	mc -= X_START_OFFSET;
	int gz = GRId_SIZE;
	mc = mc / gz;
	return mc;
}

//Get y of grid that user chose
int getMouseY(){
	int mc = mouseclicky();
	mc -= Y_START_OFFSET;
	int gz = GRId_SIZE;
	mc = mc / gz;
	return mc;
}

//Print a text beside the selection board
void printAtBottom(char *text,int board){
	/*You can change this function*/
	setcolor(RED);
	settextstyle(10, HORIZ_DIR, GRId_SIZE / 14);
	outtextxy(X_START_OFFSET + (GRId_SIZE*board)+10, Y_START_OFFSET + (GRId_SIZE*(board + 1)), text);
}

//Open GUI
void initializeGraphics(){
	int GraphDriver = 0, GraphMode = 0;
	initgraph(&GraphDriver, &GraphMode, "", MAX_X, MAX_Y); // Start Window
	cleardevice();
}

//Top headers
void drawHeader(){
	/*You can change this function*/
	setcolor(WHITE);
	settextstyle(10, HORIZ_DIR, 5);
	outtextxy(20, 20, "SuDOkU - ICT1002");
	settextstyle(10, HORIZ_DIR, 2);
	setcolor(RED);
	outtextxy(20, 70, "Copyright © SIT/ICT 2015 ");

	//hint
	setcolor(WHITE);
	settextstyle(10, HORIZ_DIR, 3);
	outtextxy(650, 50, "Press 'H' for hint!");
}

//Draws grid cells
void drawGridCell(int x, int y, int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 0, GRId_SIZE / 20);
	setfillstyle(SOLID_FILL, color);

	bar(x*GRId_SIZE + X_START_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET,
		x * GRId_SIZE + X_END_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET);
	setcolor(WHITE);
	rectangle(x*GRId_SIZE + X_START_OFFSET,
		y * GRId_SIZE + Y_START_OFFSET,
		x * GRId_SIZE + X_END_OFFSET,
		y * GRId_SIZE + Y_END_OFFSET); //Outline
}

//2 case condtional that will set the grid cells
void setGridValue(int x, int y, int g){
	int color;
	switch (g) {
	case EMPTY:
		color = DARKGRAY;
		drawGridCell(x, y, color);
		break;
	case SELECTED:
		drawGridCell(x, y, LIGHTGRAY);
		break;
	default:	
		color = BLACK;
		drawGridCell(x, y, color);
		settextstyle(10, HORIZ_DIR, GRId_SIZE /13);
		char value[10]="";
		_itoa(g, value, 10);
		outtextxy(x*GRId_SIZE + X_START_OFFSET+GRId_SIZE/5.5,
			y * GRId_SIZE + Y_START_OFFSET + GRId_SIZE / 5.5, value);
		break;
	}
}

//Ask user for board size WYNN
int getBoardSize(){
	setcolor(CYAN);
	settextstyle(10, HORIZ_DIR, 5);
	outtextxy(20, 20, "Choose Board Size:");
	setcolor(WHITE);
	settextstyle(10, HORIZ_DIR, 2);
	outtextxy(20, 100, "1. 4x4");
	outtextxy(20, 130, "2. 9x9");
	outtextxy(20, 160, "3. 16x16");
	outtextxy(20, 190, "4. 25x25");
	int nVal;
	char userInput;
	while (TRUE){
		userInput = getch();//vaildate userInput
		if (userInput == '1')
		{
			nVal = 4;
			break;
		}
		else if (userInput == '2')
		{
			nVal = 9;
			break;
		}
		else if (userInput == '3')
		{
			nVal = 16;
			break;
		}
		else if (userInput == '4')
		{
			nVal = 25;
			break;
		}
		else{
			//if userinput don't match 1,2,3,4
			setcolor(RED);
			settextstyle(10, HORIZ_DIR, 2);
			outtextxy(20, 230, "Invalid option!");
		}
	}
	return nVal;
}

//Ask user for difficulty level WYNN
int getDiffLevel(){
	setcolor(CYAN);
	settextstyle(10, HORIZ_DIR, 5);
	outtextxy(20, 20, "Choose Difficulty Level:");
	setcolor(WHITE);
	settextstyle(10, HORIZ_DIR, 2);
	outtextxy(20, 100, "1. Easy");
	outtextxy(20, 130, "2. Medium");
	outtextxy(20, 160, "3. Hard");
	int difficulty;
	char userInput;
	while (TRUE){
		userInput = getch();//vaildate userInput
		if (userInput == '1')
		{
			difficulty = 0;
			break;
		}
		else if (userInput == '2')
		{
			difficulty = 1;
			break;
		}
		else if (userInput == '3')
		{
			difficulty = 2;
			break;
		}
		else{
			//if userinput don't match 1,2,3,4
			setcolor(RED);
			settextstyle(10, HORIZ_DIR, 2);
			outtextxy(20, 200, "Invalid option!");
		}
	}
	return difficulty;
}
