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
Easy: 276
Medium: 201
Hard: 151
*/
#define SECTION_LENGTH 5							// Length of one section
#define BOARD_LENGTH SECTION_LENGTH*SECTION_LENGTH	// Length of board
#define TOTAL BOARD_LENGTH*BOARD_LENGTH				// Total size of board

void swap_row25x25(int from, int to);
void swap_col25x25(int from, int to);

//base case solved puzzle
static int source[TOTAL] = {
	15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12,
	12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24,
	24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17,
	17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3,
	3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22,
	22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14,
	14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13,
	13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5,
	5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7,
	7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4,
	4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21,
	21, 14, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2,
	2, 13, 24, 8, 20, 21, 12, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16,
	16, 5, 17, 23, 10, 2, 13, 24, 8, 20, 21, 14, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18,
	18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 20, 21, 14, 12, 25, 1, 4, 22, 15, 9, 11,
	11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 29, 21, 14, 12, 25, 1,
	1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 20,
	20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10,
	10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19,
	19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9,
	9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25,
	25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8,
	8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23,
	23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6,
	6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15 
};

int * ini25x25()
{
	//Shuffle at least n^2 times, at most 2(n^2) times where n is the number of cases
	int shuffle = (rand() % ((2 * SECTION_LENGTH) ^ 2)) + ((2 * SECTION_LENGTH) ^ 2);
	int swap, select;

	for (int j = 0; j<shuffle; j++){ //each iteration is one shuffle

		select = (rand() % SECTION_LENGTH) * SECTION_LENGTH;//Selects which section to work on
		swap = rand() & 1;//Returns 0 or 1 to choose which neighbour to swap with
		switch (rand() % (SECTION_LENGTH * 2)){ //choose either a row or a column to swap

			/* Swap entire rows or columns.
			Two integers,from and to, will be passed to the functions
			to determine which row/column is swapped with which row/column.*/
		case 0:
			swap_row25x25(select + 0, swap ? select + 1 : select + 2);
			break;
		case 1:
			swap_row25x25(select + 1, swap ? select + 0 : select + 2);
			break;
		case 2:
			swap_row25x25(select + 2, swap ? select + 0 : select + 1);
			break;
		case 3:
			swap_row25x25(select + 3, swap ? select + 2 : select + 1);
			break;
		case 4:
			swap_row25x25(select + 4, swap ? select + 2 : select + 3);
			break;

			// swap cols 
		case 5:
			swap_col25x25(select + 0, swap ? select + 1 : select + 2);
			break;
		case 6:
			swap_col25x25(select + 1, swap ? select + 0 : select + 2);
			break;
		case 7:
			swap_col25x25(select + 2, swap ? select + 0 : select + 1);
			break;
		case 8:
			swap_col25x25(select + 3, swap ? select + 2 : select + 1);
			break;
		case 9:
			swap_col25x25(select + 4, swap ? select + 2 : select + 3);
			break;
		}
	}
	return source;
}

void swap_row25x25(int from, int to)
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

void swap_col25x25(int from, int to)
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


