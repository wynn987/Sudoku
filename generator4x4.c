/* This algorithm is based 2 assumptions:
1. There are sudoku boards that have only one way of solving and not many ways.
2. Entire rows and entire columns can be shuffled as long as they are not shuffled out of a section

   This algorithm uses a solved unique sudoku puzzle as a base case and swaps the rows and columns
   within a section producing an entirely new board in a short amount of time.

   This algorithm shuffles the board a random amount of times, ensuring that each new
   instance of the game is unique.
*/

/*
Hints to give:
Easy: 8
Medium: 7
Hard: 6
*/

#define SECTION_LENGTH 2							// Length of one section
#define BOARD_LENGTH SECTION_LENGTH*SECTION_LENGTH	// Length of board
#define TOTAL BOARD_LENGTH*BOARD_LENGTH				// Total size of board

void swap_row4x4(int from, int to);
void swap_col4x4(int from, int to);

//base case solved puzzle
static int source[TOTAL] = {
	4, 2, 3, 1,
	1, 3, 4, 2,
	2, 4, 1, 3,
	3, 1, 2, 4 
};

int * ini4x4()
{
	//Shuffle at least n^2 times, at most 2(n^2) times where n is the number of cases
	int shuffle = (rand() % ((2 * SECTION_LENGTH) ^ 2)) + ((2 * SECTION_LENGTH) ^ 2);
	int select;

	for (int j = 0; j<shuffle; j++){ //each iteration is one shuffle

		select = (rand() % SECTION_LENGTH) * SECTION_LENGTH;//Selects which section to work on
		switch (rand() % (SECTION_LENGTH * 2)){ //choose either a row or a column to swap

			/* Swap entire rows or columns.
			Two integers,from and to, will be passed to the functions
			to determine which row/column is swapped with which row/column.*/
		case 0:
			swap_row4x4(select + 0, select + 1);
			break;
		case 1:
			swap_row4x4(select + 1, select + 0);
			break;

			// swap cols 
		case 2:
			swap_col4x4(select + 0,select + 1);
			break;
		case 3:
			swap_col4x4(select + 1,select + 0);
			break;
		}
	}
	return source;
}

void swap_row4x4(int from, int to)
{
	//swap entire row
	int *ptr1, *ptr2, i, temp;
	ptr1 = source + (BOARD_LENGTH * from);
	ptr2 = source + (BOARD_LENGTH * to);
	for (i = 0; i<BOARD_LENGTH; i++){
		temp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = temp;
		ptr1++;
		ptr2++;
	}
}

void swap_col4x4(int from, int to)
{
	//swap entire column
	int *ptr1, *ptr2, i, temp;
	ptr1 = source + from;
	ptr2 = source + to;
	for (i = 0; i<BOARD_LENGTH; i++){
		temp = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = temp;
		ptr1 += BOARD_LENGTH;
		ptr2 += BOARD_LENGTH;
	}
}


