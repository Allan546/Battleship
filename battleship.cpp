#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
using namespace std;

//Initialize Variables
int hits = 0;

//Initialize arrays
char board[10][10];
char cpubd[10][10];

//Void function, using a nested-for loop, to fill arrays with '_'
void fill(char b[10][10]){
	for (int i = 0; i < 10; i++){
		for (int a = 0; a < 10; a++){
			b[i][a] += '_';
		}
	}
}

//Void function, using a nested-for loop, to print out the arrays. 
void display(char b[10][10]){
	cout << "\tA B C D E F G H I J";
	cout << endl;
	int introw = 0;
	
	for (int i = 0; i < 10; i++){
		cout << "     " << ++introw << "\t";
		for (int a = 0; a < 10; a++){
			cout << b[i][a] << " ";
		}
		cout << endl;
	}
}

//Void function determines if the randomized point allows for the various sized battleships, vertical.
void verticalplace(char b[10][10], int shipsize, char shipChar){
	bool open = false;
	int row1;
	int col1;
	while (open == false){;
		row1 = rand()%10;
		col1 = rand()%(10-shipsize+1);
		int avail = 0;
		
		for (int i = 0; i < shipsize; i++){
			if (b[row1+i][col1] == '_'){
				avail++;
			}
		}
		if (avail == shipsize){
			open = true;
		}
	}
	
	if (open == true){
		for (int i = 0; i < shipsize; i++){
			b[row1+i][col1] = shipChar;
		}
	}
	
}

//Void function determines if the randomized point allows for the various sized battleships, horizontal.
void horizontalplace(char b[10][10], int shipsize, char shipChar){
	bool open = false;
	int row1;
	int col1;
	int row2;
	int col2;
	while (open == false){;
		row1 = rand()%10;
		col1 = rand()%(10-shipsize+1);

		int avail = 0;
		
		for (int i = 0; i < shipsize; i++){
			if (b[row1][col1+i] == '_'){
				avail++;
			}
		}
		if (avail == shipsize){
			open = true;
		}
	}
	
	if (open == true){
		for (int i = 0; i < shipsize; i++){
			b[row1][col1+i] = shipChar;
		}
	}	
	
}

//Void function determines the direction of the battleships.
void direction(char board[10][10], int shipsize, char shipChar){
	int chance = rand()%2;//rand()%2;
		
	if (chance == 0){
		verticalplace(board, shipsize, shipChar);
	}
	if (chance == 1){
		horizontalplace(board, shipsize, shipChar);
	}
	
}

//Void function determines the player input into numeric values, determining if it was a hit or a miss.
void attack(char b[10][10], string pick, char cpubd[10][10]){
	int row = 0;
	int col = 0;
	char letters[10] = {'A','B','C','D','E','F','G','H','I','J'};
	char letter[10] = {'a','b','c','d','e','f','g','h','i','j'};	
	char numbers[10] = {'1','2','3','4','5','6','7','8','9'};
	if (pick.length() == 3){
		for (int i = 0; i < 10; i++){
			if (letters[i] == pick[0] or letters[i] == pick[2]){
				col = i;
				row = 9;
			}
		}
	}
	if (pick.length() == 2){
		for (int i = 0; i < 10; i++){
			if (letters[i] == pick[0] or letter[i] == pick[0]){
				col = i;	
			}
		}
		for (int a = 0; a < 10; a++){
			if (numbers[a] == pick[0]){
				row = a;	
			}
		}
		
		for (int d = 0; d < 10; d++){
			if (letters[d] == pick[1] or letter[d] == pick[1]){
				col = d;	
			}
		}
		for (int c = 0; c < 10; c++){
			if (numbers[c] == pick[1]){
				row = c;	
			}
		}
	}
	b[row][col] = 'O';
	if (cpubd[row][col] != '_'){
		b[row][col] = 'O';
		hits++;
	}
	else {
		b[row][col] = 'X';
	}
}



int main(){
	srand(time(0));
	
	//Initialize variables.
	string pick;
	int counter = 0;
	int slots;
	char shipChar;
	char shipChar1[5] = {'D','S','C','B','A'};
	
	int shipsize1[5] = {2,3,3,4,5};
	int shipsize;
	
	//Call for the fill function of board and cpubd
	fill(board);
	fill(cpubd);
	///*
	
	//For loop to determine the place of battleships on the cpubd.
	for (int i = 0; i < 5; i++){
		shipsize = shipsize1[i];
		shipChar = shipChar1[i];
		direction(cpubd, shipsize, shipChar);
		//display(cpubd);
		//cout << endl;
	}
	cout << "Please select the number of turns." << endl;
	cout << "Turn Amount:  20,  40,  60,  80,  100" << endl;
	cin >> slots;
	
	display(board);
	
	//While loop to set how long the game will be played for.
	while (hits != 17 and counter != slots){
		cout << "\tCoordinates: ";
		cin >> pick;
		cout << endl;
		
		attack(board, pick, cpubd);
		display(board);
		counter++;
	}
	
	//If-statements, prints out whether you won or lost.
	if (hits == 17){
		cout << endl << "\tYou Won! Thank you for playing";
	}
	if (hits != 17 and counter == slots){
		cout << endl << "\tYou Lost! Try Another Game";
	}
	
	//Display function prints out the cpubd array.
	display(cpubd);
}
