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
Easy: 100
Medium: 70
Hard: 55
*/

#define SECTION_LENGTH 4							// Length of one section
#define BOARD_LENGTH SECTION_LENGTH*SECTION_LENGTH	// Length of board
#define TOTAL BOARD_LENGTH*BOARD_LENGTH				// Total size of board

void swap_row16x16(int from, int to);
void swap_col16x16(int from, int to);

//base case solved puzzle
static int source[TOTAL] = {
	7, 15, 14, 10, 3, 16, 4, 12, 9, 13, 5, 2, 11, 8, 6, 1,
	6, 11, 13, 1, 5, 14, 9, 2, 16, 4, 15, 8, 10, 7, 3, 12,
	16, 12, 5, 8, 11, 13, 6, 15, 3, 1, 10, 7, 9, 4, 2, 14,
	3, 4, 2, 9, 8, 7, 10, 1, 12, 6, 11, 14, 13, 5, 15, 16,
	2, 7, 10, 15, 12, 3, 5, 6, 4, 11, 8, 16, 14, 1, 13, 9,
	9, 1, 12, 4, 2, 11, 14, 16, 7, 5, 6, 13, 8, 3, 10, 15,
	5, 14, 3, 6, 9, 1, 13, 8, 10, 15, 2, 12, 16, 11, 4, 7,
	13, 16, 8, 11, 10, 4, 15, 7, 1, 14, 9, 3, 6, 12, 5, 2,
	15, 13, 11, 12, 16, 6, 7, 4, 14, 9, 3, 5, 2, 10, 1, 8,
	1, 10, 6, 7, 14, 5, 2, 13, 11, 8, 16, 15, 3, 9, 12, 4,
	14, 5, 9, 3, 15, 8, 12, 11, 2, 10, 1, 4, 7, 6, 16, 13,
	8, 2, 4, 16, 1, 10, 3, 9, 13, 7, 12, 6, 5, 15, 14, 11,
	10, 9, 7, 5, 6, 12, 1, 14, 15, 2, 13, 11, 4, 16, 8, 3,
	11, 3, 16, 14, 13, 9, 8, 10, 6, 12, 4, 1, 15, 2, 7, 5,
	12, 6, 15, 13, 4, 2, 16, 5, 8, 3, 7, 9, 1, 14, 11, 10,
	4, 8, 1, 2, 7, 15, 11, 3, 5, 16, 14, 10, 12, 13, 9, 6 
};

int * ini16x16()
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
			swap_row16x16(select + 0, swap ? select + 1 : select + 2);
			break;
		case 1:
			swap_row16x16(select + 1, swap ? select + 0 : select + 2);
			break;
		case 2:
			swap_row16x16(select + 2, swap ? select + 0 : select + 1);
			break;
		case 3:
			swap_row16x16(select + 3, swap ? select + 2 : select + 1);
			break;

			// swap cols 
		case 4:
			swap_col16x16(select + 0, swap ? select + 1 : select + 2);
			break;
		case 5:
			swap_col16x16(select + 1, swap ? select + 0 : select + 2);
			break;
		case 6:
			swap_col16x16(select + 2, swap ? select + 0 : select + 1);
			break;
		case 7:
			swap_col16x16(select + 3, swap ? select + 2 : select + 1);
			break;
		}
	}
	return source;
}

void swap_row16x16(int from, int to)
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

void swap_col16x16(int from, int to)
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


