/*You are not allowed to remove code from this file
You can ADD more code as you like*/

#define MAX_X 1000
#define MAX_Y 1000
#define ESC 0x1b

void initializeGraphics();
void drawSelectionGrid(int boardSize);
void drawHeader();
void drawSections(int boardSize, int sectionSize);
void drawGridCell(int x, int y, int color);


void setGridValue(int x, int y, int g);
int isClickOutOfBoard(int board);
void printAtBottom(char *text,int board);
int getMouseX();
int getMouseY();
int isClickInSelection(int board);
int getBoardSize();
int getDiffLevel();