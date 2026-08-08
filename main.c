#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 25
#define COLUMNS 30

void generateInitialState(char grid[][COLUMNS]) {
	int row, column;
	for ( row=0; row < ROWS; row++) {
		for ( column=0; column < COLUMNS; column++){
			int choice = rand() % 2;
			if (choice == 0) {
				grid[row][column] = '.';
		    	} else {
				grid[row][column] = '#';
		    	}
		}
	}
}

void render(char grid[][COLUMNS]){
	char buf[8192];
	int row, column;
	int pos=0;
	for ( row=0; row < ROWS; row++) {
		for ( column=0; column < COLUMNS; column++){
			buf[pos++] = grid[row][column];
			buf[pos++] = ' ';
		}
		buf[pos++] = '\n';
	}
	buf[pos] = '\0';
	printf("\033[H%s", buf);
	fflush(stdout);
}

/* 1 if alive, 0 if dead */
int checkStatus(char grid[][COLUMNS], int row, int column){
	if (grid[row][column] == '#'){
		return 1;
	}
	return 0;
}

void computeNextGen(char grid[][COLUMNS]){
	char buffer[ROWS][COLUMNS];
	int row, column;
	for ( row=0; row < ROWS; row++) {
		for ( column=0; column < COLUMNS; column++){
			int alive_count=0;
			alive_count += checkStatus(grid, (row-1+ROWS)%ROWS, (column-1+COLUMNS)%COLUMNS);
			alive_count += checkStatus(grid, (row-1+ROWS)%ROWS, column);
			alive_count += checkStatus(grid, (row-1+ROWS)%ROWS, (column+1+COLUMNS)%COLUMNS);
			alive_count += checkStatus(grid, row, (column-1+COLUMNS)%COLUMNS);
			alive_count += checkStatus(grid, row, (column+1+COLUMNS)%COLUMNS);
			alive_count += checkStatus(grid, (row+1+ROWS)%ROWS, (column-1+COLUMNS)%COLUMNS);
			alive_count += checkStatus(grid, (row+1+ROWS)%ROWS, column);
			alive_count += checkStatus(grid, (row+1+ROWS)%ROWS, (column+1+COLUMNS)%COLUMNS);
			switch (grid[row][column]) {
				case '.':
					if(alive_count == 3) {
						buffer[row][column] = '#';
					}else{
						buffer[row][column] = '.';
					}
					break;
				case '#':
					if (alive_count < 2){
						buffer[row][column] = '.';
					}else if (alive_count > 3) {
						buffer[row][column] = '.';
					}else{
						buffer[row][column] = '#';
					}
					break;
			}
		}
	}
	for ( row=0; row < ROWS; row++) {
		for ( column=0; column < COLUMNS; column++){
			grid[row][column] = buffer[row][column];
		}
	}
}

int main() {
	char grid[ROWS][COLUMNS];
	system("clear");
	srand(time(NULL));
	generateInitialState(grid);
	while(1){
		render(grid);
		usleep(200000);
		computeNextGen(grid);
	}
	return 0;
}
