#include "generator4x4.h"
#include "generator9x9.h"
#include "generator16x16.h"
#include "Sudoku.h"
#include "GUI.h"
#include <time.h> 
#include <math.h>

//global variable declaration 
int board[25][25] = { 25 };// Store current values of the board
int solution[25][25]; // Store complete solution
int given[25][25] = { 0 }; // Store pre-defined numbers
int mouseX = -1, mouseY = -1; // Store value of mouse clicks
int randI, randJ; // Random generator for hints
int boardSize, sectionSize, difficulty; // To decide what kind of board to generate
int pmouseX = -1, pmouseY = -1, pvalue = 0, check; // To store previous data
int selection; // To store currect selection
int counter; // Count of numbers currently on the board

//Check for conflict in section
int checkSection(int x, int y, int value){
	////Get first cell of section
	int xFirst = x;
	int yFirst = y;
	while (xFirst % sectionSize != 0)
		xFirst--;
	while (yFirst % sectionSize != 0)
		yFirst--;

	//runthrough section to check if value has been used already
	for (int i = xFirst; i < sectionSize + xFirst; i++)
	{
		for (int j = yFirst; j < sectionSize + yFirst; j++)
		{
			if (!(i == x && j == y) && board[i][j] == value)
			{
				printAtBottom("                   ", boardSize);
				printAtBottom("Section Conflict!", boardSize);
				return FALSE;
			}
		}
	}
	return TRUE;
}

//Check for conflicts in row
int checkRow(int row, int value)
{
	//Run through the row to check for conflict
	for (int i = 0; i < boardSize; i++)
	{
		if (board[i][row] == value)
		{
			printAtBottom("                   ", boardSize);
			printAtBottom("Row Conflict!", boardSize);
			return FALSE;
		} 
	}
	return TRUE;
}

//Check for conflicts in column
int checkColumn(int col, int value)
{
	//Run through the column to check for conflict
	for (int i = 0; i < boardSize; i++)
	{
		if (board[col][i] == value)
		{
			printAtBottom("                   ", boardSize);
			printAtBottom("Column Conflict!", boardSize);
			return FALSE;
		}
	}
	return TRUE;
}

//This function returns the amount of predefined numbers that should be given based on the
//difficulty and the board size. The minimum size returned is the minimum size required for a unique solution
int getHints(){//wynn
	int hints = 0;
	if (boardSize == 4){
		if (difficulty == 0)
			hints = 8;
		else if (difficulty == 1)
			hints = 7;
		else if (difficulty == 2)
			hints = 6;
	}
	else if (boardSize == 9){
		if (difficulty == 0)
			hints = 33;
		else if (difficulty == 1)
			hints = 23;
		else if (difficulty == 2)
			hints = 17;
	}
	else if (boardSize == 16){
		if (difficulty == 0)
			hints = 100;
		else if (difficulty == 1)
			hints = 70;
		else if (difficulty == 2)
			hints = 55;
	}
	else if (boardSize == 25){
		if (difficulty == 0)
			hints = 276;
		else if (difficulty == 1)
			hints = 201;
		else if (difficulty == 2)
			hints = 156;
	}
	return hints;
}

//This function draws out the GUI and initialises the logic behind it
void initializeGame()
{
	//get amount of pre-defined values to initialise
	int hints = getHints();

	//initialize both logic board and gui board
	int i, j;
	for (i = 0; i < boardSize; i++){
		for (j = 0; j < boardSize; j++){
				setGridValue(i, j, EMPTY);
				board[i][j] = EMPTY;
		}
	}
	//Initialise solution
	setGame();
	randomBoardNumber(counter);
	drawSelectionGrid(boardSize);
	drawHeader();
	drawSections(boardSize,sectionSize);
}

int randomBoardNumber(int counters)
{
	int hints = getHints();
	//give random predefined numbers based on how many hints should be given.
	while (hints != 0) {
		randI = rand() % boardSize;
		randJ = rand() % boardSize;
		if (board[randI][randJ] == EMPTY) {
			board[randI][randJ] = solution[randI][randJ];
			given[randI][randJ] = solution[randI][randJ];
			setGridValue(randI, randJ, solution[randI][randJ]);
			hints--;

			//Increment the counter every hint to keep track of numbers on board
			counter++;
		}
	}
	return counter;
}

//Returns the number chosen by the user
int getSelection()
{
		return getMouseX()+1;
}

// This function generate a solved solution based on board size
void setGame()//wynn
{
	int count = 0;
	if (boardSize == 4)
	{
		int *solution4x4 = ini4x4(); //get solution for 4x4 board

		//convert into multi dimensional array
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				solution[i][j] = solution4x4[count];
				count++;
			}
		}
	}
	else if (boardSize == 9){
		int *solution9x9 = ini9x9(); //get solution for 9x9 board

		//convert into multi dimensional array
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				solution[i][j] = solution9x9[count];
				count++;
			}
		}
	}
	else if (boardSize == 16){
		int *solution16x16 = ini16x16(); //get solution for 16x16 board

		//convert into multi dimensional array
		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++){
				solution[i][j] = solution16x16[count];
				count++;
			}
		}
	}
	else if (boardSize == 25){
		int *solution25x25 = ini25x25(); //get solution for 25x25 board

		//convert into multi dimensional array
		for (int i = 0; i < 25; i++){
			for (int j = 0; j < 25; j++){
				solution[i][j] = solution25x25[count];
				count++;
			}
		}
	}
}

//Returns TRUE if user's selected cell is not pre-defined
int isNotGiven(int mouseX,int mouseY)
{
	if (given[mouseX][mouseY] == 0)
		return TRUE;
	else
		return FALSE;
}

void generateHint()//wynn
{
	//If 'h' is pressed, generate hint
	if (kbhit() && getch() == 'h') {

		//If board is solvable, print hint in random location
		//Else print error message
		while (checkSolvable()) {
			randI = rand() % boardSize;
			randJ = rand() % boardSize;
			if (board[randI][randJ] == EMPTY) {
				board[randI][randJ] = solution[randI][randJ];
				setGridValue(randI, randJ, solution[randI][randJ]);
				drawSections(boardSize, sectionSize);
				pvalue = solution[randI][randJ];
				pmouseX = randI;
				pmouseY = randJ;
				counter++;
				break;
			}
		}
	}
}

//This function checks if current board is solvable by checking if user has entered any values
//that is different from the pre-generated solution as the board has only one way of being solved
int checkSolvable(){
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			if (board[i][j] != EMPTY&&board[i][j] != solution[i][j])
			{
				printAtBottom("                     ", boardSize);
				printAtBottom("Board Unsolvable!", boardSize);
				return FALSE;
			}
		}
	}
	return TRUE;
}

//This function handles mouse clicks and keyboard inputs during the game
void startGame(){
	/*You have to use this function in your implementation
	You can add more code to this function*/

	//When mouse is clicked, get the X and Y position
	if (mouseup()) {
		mouseX = getMouseX();
		mouseY = getMouseY();

		//Check if what is clicked is not out board and is not a pre-defined number
		if (!isClickOutOfBoard(boardSize) && isNotGiven(mouseX, mouseY))
		{

			//Check if there has been a previous selection or not. pmouse = previouse mouse click
			if (pmouseX < 0 && pmouseY < 0)
			{
				//If user selects a cell that already has a value, store the value so it can be restored later
				if (board[mouseX][mouseY] != EMPTY)
					pvalue = board[mouseX][mouseY];
				//Highlight selected cell
				setGridValue(mouseX, mouseY, SELECTED);
			}
			//If there has been a previous selection
			else 
			{
				//If user previously selected a filled cell and decides to select another cell
				//Restore the previous cell's value
				if (pvalue != EMPTY)
				{
					setGridValue(pmouseX, pmouseY, pvalue);
					//Reset pvalue						
					pvalue = EMPTY;
				}
				//Else let user highlight another cell and revert current cell to original
				else
				{
					setGridValue(pmouseX, pmouseY, EMPTY);
				}
				printAtBottom("                   ", boardSize);

				//If user selects a cell that already has a value, store the value so it can be restored later
				if (board[mouseX][mouseY] != EMPTY)
				{
					pvalue = board[mouseX][mouseY];
				}
				//Highlight the cell selected by user
				setGridValue(mouseX, mouseY, SELECTED);

				//drawSection has to be called every time a grid is set to maintain it's lines
				drawSections(boardSize, sectionSize);
			}

			//Store current mouse click so that the selected cell's location can be used later
			pmouseX = mouseX;
			pmouseY = mouseY;
		}

		//If user chooses a number after selecting a cell in the board
		else if (isClickInSelection(boardSize) && (pmouseX >= 0 && pmouseY >= 0))
		{

			//store the number chosen
			selection = getSelection();

			//If selected value is what has been previously selected, restore the selection
			if (selection == pvalue)
			{
				setGridValue(pmouseX, pmouseY, pvalue);
				//drawSection has to be called every time a grid is set to maintain it's lines
				drawSections(boardSize, sectionSize);
				printAtBottom("                   ", boardSize);

				//Reset past storage variables
				pvalue = EMPTY;
				pmouseX = -1;
				pmouseY = -1;
			}

			// Else check if the new value will conflict with any other column/row/section cell
			else if (checkColumn(pmouseX, selection) &&
				checkRow(pmouseY, selection) &&
				checkSection(pmouseX, pmouseY, selection))
			{
				//If no conflict, set new value in GUI
				setGridValue(pmouseX, pmouseY, selection);

				//Store new value in background logic board
				board[pmouseX][pmouseY] = selection;

				//drawSection has to be called every time a grid is set to maintain it's lines
				drawSections(boardSize, sectionSize);
				printAtBottom("                   ", boardSize);

				//If what was entered is a new value on the board and not just a replacement, increment counter
				if (pvalue == EMPTY)
					counter++;

				//Reset past storage variables
				pmouseX = -1;
				pmouseY = -1;
				pvalue = EMPTY;
			}
		}
	}
	generateHint();
}

void isGameWon()
{
	while (TRUE) 
	{
		startGame();
		//Loop until game has been won
		if (counter == boardSize * boardSize)
			break;
	}
	printAtBottom("                      ", boardSize);
	printAtBottom("You Won! Press any key to continue", boardSize);
	getch();
}


void main()
{	
	srand(time(NULL));  //initialise random generator

	//Open GUI
	initializeGraphics();
	//set device to 0,0
	cleardevice();
	//clearmouse input
	clearmouse();

	//request board size
	boardSize = getBoardSize();
	sectionSize = sqrt(boardSize);
	cleardevice();
	//request difficulty level
	difficulty = getDiffLevel();
	cleardevice();
	clearmouse();

	//Set up board
	initializeGame();

	//inform user if game is won
	isGameWon();

	
}
