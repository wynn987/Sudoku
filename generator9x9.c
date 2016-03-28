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
Easy: 33
Medium: 23
Hard: 17
*/

#define SECTION_LENGTH 3							// Length of one section
#define BOARD_LENGTH SECTION_LENGTH*SECTION_LENGTH	// Length of board
#define TOTAL BOARD_LENGTH*BOARD_LENGTH				// Total size of board

void swap_row9x9(int from, int to);
void swap_col9x9(int from, int to);

//base case solved puzzle
static int source[TOTAL] = {
	1, 3, 4, 5, 2, 8, 6, 9, 7,
	2, 5, 6, 7, 9, 1, 3, 4, 8,
	7, 8, 9, 3, 4, 6, 1, 2, 5,
	3, 1, 2, 4, 6, 7, 5, 8, 9,
	5, 4, 7, 9, 8, 3, 2, 1, 6,
	9, 6, 8, 1, 5, 2, 7, 3, 4,
	4, 7, 5, 2, 1, 9, 8, 6, 3,
	8, 9, 1, 6, 3, 5, 4, 7, 2,
	6, 2, 3, 8, 7, 4, 9, 5, 1
};

int * ini9x9()
{
	//Shuffle at least n^2 times, at most 2(n^2) times where n is the number of cases
	int shuffle = (rand() % ((2 * SECTION_LENGTH) ^ 2)) + ((2 * SECTION_LENGTH) ^ 2); 
	int swap, select; 

		for (int j = 0; j<shuffle; j++){ //each iteration is one shuffle

			select = (rand() % SECTION_LENGTH) * SECTION_LENGTH;//Selects which section to work on
			swap = rand() & 1;//Returns 0 or 1 to choose which neighbour to swap with
			switch (rand() % (SECTION_LENGTH*2)){ //choose either a row or a column to swap
				
			/* Swap entire rows or columns.
			   Two integers,from and to, will be passed to the functions
			   to determine which row/column is swapped with which row/column.*/
			case 0:
				swap_row9x9(select + 0, swap ? select + 1 : select + 2);
				break;
			case 1:
				swap_row9x9(select + 1, swap ? select + 0 : select + 2);
				break;
			case 2:
				swap_row9x9(select + 2, swap ? select + 0 : select + 1);
				break;

				// swap cols 
			case 3:
				swap_col9x9(select + 0, swap ? select + 1 : select + 2);
				break;
			case 4:
				swap_col9x9(select + 1, swap ? select + 0 : select + 2);
				break;
			case 5:
				swap_col9x9(select + 2, swap ? select + 0 : select + 1);
				break;
			}
		}
		return source;
}

void swap_row9x9(int from, int to)
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

void swap_col9x9(int from, int to)
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


