/*
Lab 2 - TicTacToe
Jiali Chen
Description: A game of Tic-Tac-Toe created using classes.
*/

#include <iostream>

using namespace std;

class TTTClass {
	char board[3][3];
	char curplayer;
	int userInput[2];
	int turncount;
	bool game_end;

	bool userInput_isInvalid();
		//POST: If userInput is VALID, return 'false'. If userInput is INVALID, return 'true'.
	void print_board();
		//POST: Print the game board and the ownership status of each tile
	void userInput_fix();
		//POST: Subtracts 1 from userInputs in order to align with array numbers
	bool winner();
		//POST: Return false if there is no winner. Return true if the currentplayer has made a winning move.
		//Decides possibility checkers to use based on the most recent move.

	//Possibility Checkers
		//POST: All possibility checkers (except for check_poss) return 'true' when all of the coordinates in the provided set are owned by the curplayer.
		//Naming: check_poss_XY_XY_XY; XY = coordinates of one of the members of the winning combination
	//Possibility Template
	bool check_poss(int[], int[], int[]);
	//Possibility Lists
	bool check_poss_00_01_02();
	/*
	00_01_02:
	[ X ] [   ] [   ]
	[ X ] [   ] [   ]
	[ X ] [   ] [   ]
	*/
	bool check_poss_10_11_12();
	/*
	10_11_12:
	[   ] [ X ] [   ]
	[   ] [ X ] [   ]
	[   ] [ X ] [   ]
	*/
	bool check_poss_20_21_22();
	/*
	20_21_22:
	[   ] [   ] [ X ]
	[   ] [   ] [ X ]
	[   ] [   ] [ X ]
	*/
	bool check_poss_00_10_20();
	/*
	00_10_20
	[ X ] [ X ] [ X ]
	[   ] [   ] [   ]
	[   ] [   ] [   ]
	*/
	bool check_poss_01_11_21();
	/*
	01_11_21
	[   ] [   ] [   ]
	[ X ] [ X ] [ X ]
	[   ] [   ] [   ]
	*/
	bool check_poss_02_12_22();
	/*
	02_12_22:
	[   ] [   ] [   ]
	[   ] [   ] [   ]
	[ X ] [ X ] [ X ]
	*/
	bool check_poss_00_11_22();
	/*
	00_11_22:
	[ X ] [   ] [   ]
	[   ] [ X ] [   ]
	[   ] [   ] [ X ]
	*/
	bool check_poss_20_11_02();
	/*
	20_11_02:
	[   ] [   ] [ X ]
	[   ] [ X ] [   ]
	[ X ] [   ] [   ]
	*/
public:
	void play();
	void boardInit();
	//POST: Initializes or replaces (clean) all values of board[][] with ' '.
};

int main() {

	//Declare variables
	TTTClass mainBoard;
	char userInput_again;

	do {
		//Clean up board
		mainBoard.boardInit();

		//Play
		mainBoard.play();

		cout << "Play again? (Y/N): ";
		cin >> userInput_again;
	} while (userInput_again == 'Y' || userInput_again == 'y'); //Keep playing until the user does not input Y/y


	return 0;

}


void TTTClass::userInput_fix() {
	for (int i = 0; i < 2; i++) {
		userInput[i]--;
	}
}
bool TTTClass::userInput_isInvalid() {
	//Check 1: Check that the provided numbers are not out of bounds
	if (!(userInput[0] < 0 || userInput[0] > 2 || userInput[1] < 0 || userInput[1] > 2)) {
		//Check 2: Check that the chosen coordinate is unoccupied
		if (board[userInput[0]][userInput[1]] != ' ') {
			cout << "Invalid move. Coordinate [" << userInput[0] + 1 << ", " << userInput[1] + 1 << "] is in Player " << board[userInput[0]][userInput[1]] << "'s posession. Please try again." << endl;
			return true;
		}
		else
			return false;
	}
	else {
		cout << "Provided coordinates are out of bounds. Please try again." << endl;
		return true;
	}
}
void TTTClass::print_board() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << "[ " << board[j][i] << " ]"; // j = X, i = Y
		cout << '\n';
	}
}
bool TTTClass::winner() {
	switch (userInput[0]) {
	case 0:
		switch (userInput[1]) {
		case 0: //0, 0
			if (check_poss_00_01_02() || check_poss_00_10_20() || check_poss_00_11_22())
				return true;
			break;
		case 1: //0, 1
			if (check_poss_00_01_02() || check_poss_01_11_21())
				return true;
			break;
		case 2: //0, 2
			if (check_poss_00_01_02() || check_poss_02_12_22())
				return true;
			break;
		}
		break;
	case 1:
		switch (userInput[1]) {
		case 0: //1, 0
			if (check_poss_10_11_12() || check_poss_00_10_20())
				return true;
			break;
		case 1: //1, 1
			if (check_poss_10_11_12() || check_poss_01_11_21() || check_poss_00_11_22() || check_poss_20_11_02())
				return true;
			break;
		case 2: //1, 2
			if (check_poss_10_11_12() || check_poss_02_12_22())
				return true;
			break;
		}
		break;
	case 2:
		switch (userInput[1]) {
		case 0: //2, 0
			if (check_poss_20_21_22() || check_poss_00_10_20())
				return true;
			break;
		case 1: //2, 1
			if (check_poss_20_21_22() || check_poss_01_11_21())
				return true;
			break;
		case 2: //2, 2
			if (check_poss_20_21_22() || check_poss_02_12_22() || check_poss_00_11_22())
				return true;
			break;
		}
		break;

		//If no possibilities are found to be true, return false
		return false;
	}
}
void TTTClass::play() {
	//Initialize the current player
	curplayer = 'X';
	turncount = 1;
	bool game_end = false;

	do {

		//Print currentplayer
		cout << "TURN - " << turncount << " | The current player is " << curplayer << "." << endl;

		//Ask for input
		do {
			cout << "Player " << curplayer << "'s input: ";
			cin >> userInput[0] >> userInput[1];

			//Adjust userInput to array numbers
			userInput_fix();

		} while (userInput_isInvalid());


		//Place userInput information in to the board
		board[userInput[0]][userInput[1]] = curplayer;

		//Display the board
		print_board();

		/*Check if there current player has scored a winning combination
		If turn count is < 5, there is no need to check for winner*/
		if (turncount >= 5) {
			game_end = winner(); //Placed in variable to avoid needless additional executions of function winner()
			if (game_end) {
				cout << "\nPlayer " << curplayer << " has won the game!" << endl;
			}
			else if (turncount >= 9) {
				cout << "\nThe game has ended in a draw!" << endl;
				game_end = true;
			}
		}

		//Switch Players
		if (curplayer == 'X')
			curplayer = 'O';
		else
			curplayer = 'X';

		turncount++;
		cout << '\n';

	} while (!game_end);




}
void TTTClass::boardInit() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

bool TTTClass::check_poss(int a[], int b[], int c[]) {
	if (board[a[0]][a[1]] == curplayer && board[b[0]][b[1]] == curplayer && board[c[0]][c[1]] == curplayer)
		return true;
	else
		return false;
}
bool TTTClass::check_poss_00_01_02() {
	int a[2] = { 0, 0 },
		b[2] = { 0, 1 },
		c[2] = { 0, 2 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_10_11_12() {
	int a[2] = { 1, 0 },
		b[2] = { 1, 1 },
		c[2] = { 1, 2 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_20_21_22() {
	int a[2] = { 2, 0 },
		b[2] = { 2, 1 },
		c[2] = { 2, 2 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_00_10_20() {
	int a[2] = { 0, 0 },
		b[2] = { 1, 0 },
		c[2] = { 2, 0 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_01_11_21() {
	int a[2] = { 0, 1 },
		b[2] = { 1, 1 },
		c[2] = { 2, 1 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_02_12_22() {
	int a[2] = { 0, 2 },
		b[2] = { 1, 2 },
		c[2] = { 2, 2 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_00_11_22() {
	int a[2] = { 0, 0 },
		b[2] = { 1, 1 },
		c[2] = { 2, 2 };
	return check_poss(a, b, c);
}
bool TTTClass::check_poss_20_11_02() {
	int a[2] = { 2, 0 },
		b[2] = { 1, 1 },
		c[2] = { 0, 2 };
	return check_poss(a, b, c);
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
OUTPUT:
-Check if out-of-bounds data validation is working
-Check if occupied data validation is working
-Check if replay is working
-Result is a draw
-X wins
-O wins
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

TURN - 1 | The current player is X.
Player X's input: 1 1
[ X ][   ][   ]
[   ][   ][   ]
[   ][   ][   ]

TURN - 2 | The current player is O.
Player O's input: 1 1
Invalid move. Coordinate [1, 1] is in Player X's posession. Please try again.
Player O's input: 1 4
Provided coordinates are out of bounds. Please try again.
Player O's input: 2 1
[ X ][ O ][   ]
[   ][   ][   ]
[   ][   ][   ]

TURN - 3 | The current player is X.
Player X's input: 1 2
[ X ][ O ][   ]
[ X ][   ][   ]
[   ][   ][   ]

TURN - 4 | The current player is O.
Player O's input: 2 2
[ X ][ O ][   ]
[ X ][ O ][   ]
[   ][   ][   ]

TURN - 5 | The current player is X.
Player X's input: 1 3
[ X ][ O ][   ]
[ X ][ O ][   ]
[ X ][   ][   ]

Player X has won the game!

Play again? (Y/N): Y
TURN - 1 | The current player is X.
Player X's input: 2 1
[   ][ X ][   ]
[   ][   ][   ]
[   ][   ][   ]

TURN - 2 | The current player is O.
Player O's input: 1 1
[ O ][ X ][   ]
[   ][   ][   ]
[   ][   ][   ]

TURN - 3 | The current player is X.
Player X's input: 2 2
[ O ][ X ][   ]
[   ][ X ][   ]
[   ][   ][   ]

TURN - 4 | The current player is O.
Player O's input: 1 2
[ O ][ X ][   ]
[ O ][ X ][   ]
[   ][   ][   ]

TURN - 5 | The current player is X.
Player X's input: 3 1
[ O ][ X ][ X ]
[ O ][ X ][   ]
[   ][   ][   ]

TURN - 6 | The current player is O.
Player O's input: 1 3
[ O ][ X ][ X ]
[ O ][ X ][   ]
[ O ][   ][   ]

Player O has won the game!

Play again? (Y/N): Y
TURN - 1 | The current player is X.
Player X's input: 1 1
[ X ][   ][   ]
[   ][   ][   ]
[   ][   ][   ]

TURN - 2 | The current player is O.
Player O's input: 3 3
[ X ][   ][   ]
[   ][   ][   ]
[   ][   ][ O ]

TURN - 3 | The current player is X.
Player X's input: 2 2
[ X ][   ][   ]
[   ][ X ][   ]
[   ][   ][ O ]

TURN - 4 | The current player is O.
Player O's input: 3 1
[ X ][   ][ O ]
[   ][ X ][   ]
[   ][   ][ O ]

TURN - 5 | The current player is X.
Player X's input: 1 3
[ X ][   ][ O ]
[   ][ X ][   ]
[ X ][   ][ O ]

TURN - 6 | The current player is O.
Player O's input: 1 2
[ X ][   ][ O ]
[ O ][ X ][   ]
[ X ][   ][ O ]

TURN - 7 | The current player is X.
Player X's input: 3 2
[ X ][   ][ O ]
[ O ][ X ][ X ]
[ X ][   ][ O ]

TURN - 8 | The current player is O.
Player O's input: 2 1
[ X ][ O ][ O ]
[ O ][ X ][ X ]
[ X ][   ][ O ]

TURN - 9 | The current player is X.
Player X's input: 2 3
[ X ][ O ][ O ]
[ O ][ X ][ X ]
[ X ][ X ][ O ]

The game has ended in a draw!

Play again? (Y/N): N
Press any key to continue . . .


*/