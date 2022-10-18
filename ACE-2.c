/**************************************************************************
 * Assessment Title: CS210 ACE 2
 *
 * Number of Submitted C Files: 1
 *
 * Date: 26/10/2018
 *
 * 
 * Author: Erin Macfarlane, Reg no: 201707815
 *
 *
 * Personal Statement: I confirm that this submission is all my own work.
 *
 *          Erin Macfarlane
 *
 * 
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define X 3
#define Y 3

/*
  This program implements a Tic-tac-toe game where the user can play against another user
  or play against the computer, which uses AI to win or tie with the user each time. The user
  can play the game as many times as they want, keeping tracking of the scores throughout.
*/

void user_prompt(char *message, char *answer);
void numbered_board();
void clear_board(char b[Y][X]);
void display_board(char b[Y][X]);
void set_players(char *input, char *u1, char *u2);
void choose_xo(char *u1_s, char *u2_s, char *u1, char *u2);
void prompt_move(char *u1_s, char *u2_s, char *u1, char *u2, char b[Y][X], int *u1_score, int *u2_score);
void user_move(char b[Y][X]);
void computer_move(char b[Y][X]);
void first_com_move(char b[Y][X]);
void block_win(char b[Y][X]);
void try_win(char b[Y][X]);
int detect_win(char b[Y][X]);
void quit(char *input);

char xo[2];

/*
  Prints meaningful messages out to the user at the beginning of the game to receive input and inform them
  of what to do with the game, as well as showing the initial game board.
*/
int main() {

 		char a[2], u1_symbol[2], u2_symbol[2], user1[20], user2[20], board[Y][X];
		int u1_score = 0, u2_score = 0;

		user1[0] = ' ';
		user2[0] = ' ';
		strcpy(u2_symbol, " ");
		

		printf("Welcome to Tic-tac-toe!\n");
		printf("-> Enter 0 to quit the game at anytime\n");
		printf("\n");

		int i = 0;
		for (i; i < 1; i) {
			user_prompt("Enter 'c' to play against the computer or enter 'u' to play against another user: ", a);
			set_players(a, user1, user2);
			if ((user1[0] != ' ') && (user2[0] != ' ')) {
				i++;
			}
		}

		int j = 0;
		for (j; j < 1; j) {
			user_prompt("Type 'X' if you would like to be crosses, or 'O' if you'd like to be noughts: ", u1_symbol);
			choose_xo(u1_symbol, u2_symbol, user1, user2);
		        if (u1_symbol[0] == 'X' || u1_symbol[0] == 'O') {
				j++;
			}	
		}
		
		printf("\nThis numbered board below represents what number to type when choosing where to place your move.\n");
		printf("-> For example you would type 5, when prompted, to place a move in the middle of the board.\n"); 
		printf("\n");
		numbered_board();

		printf("\nHere is the initial board below, start playing!\n");
		printf("\n");
		clear_board(board);
		display_board(board);

		prompt_move(u1_symbol, u2_symbol, user1, user2, board, &u1_score, &u2_score);

		return 0;
}

/*
  Prints a message and asks for an input for that specifc message.
  	Parameters: *message, *answer
*/
void user_prompt(char *message, char *answer) {

	printf("%s", message);
	fgets(answer, 20, stdin);
        quit(answer);
	
}

/*
  Prints a numbered board in order to show which number refers to each section of 
  grid, so the user knows what to type when prompted.
*/
void numbered_board() {

	printf("\t     |     |     \n");
	printf("\t  1  |  2  |  3  \n");
	printf("\t_____|_____|_____\n");			
	printf("\t     |     |     \n");
	printf("\t  4  |  5  |  6  \n");
	printf("\t_____|_____|_____\n");
	printf("\t     |     |     \n");
	printf("\t  7  |  8  |  9  \n");
	printf("\t     |     |     \n\n");

}

/* 
  Clears all the values in each section of the game board grid.
	Parameter: b[Y][X]
*/
void clear_board(char b[Y][X]) {
	
	int x, y;
	
	for(x = 0; x < 3; x++) {
		for(y = 0; y < 3; y++) {
			b[y][x] = ' ';
		}
	}

}

/*
  Prints the game board, in a simple grid design, along with the current values in 
  each box of the grid.
	Parameter: b[Y][X]
*/
void display_board(char b[Y][X]) {
	
	printf("\t     |     |     \n");
	printf("\t  %c  |  %c  |  %c \n", b[0][0], b[0][1], b[0][2]);
	printf("\t_____|_____|_____\n");			
	printf("\t     |     |     \n");
	printf("\t  %c  |  %c  |  %c \n", b[1][0], b[1][1], b[1][2]);
	printf("\t_____|_____|_____\n");
	printf("\t     |     |     \n");
	printf("\t  %c  |  %c  |  %c \n", b[2][0], b[2][1], b[2][2]);
	printf("\t     |     |     \n\n");
	

}

/*
  Sets the players for the game, depending on whether the user wanst to play against the
  computer or another player. Error checks to make sure the user has entered c or u. 
  	Parameters: *input, *u1, *u2
*/
void set_players(char *input, char *u1, char *u2) {
	
	int size1, size2;

	if (input[0] == 'u' || input[0] == 'U') {
		user_prompt("Enter a nickname for yourself: ", u1);
		user_prompt("Enter a nickname for player 2: ", u2);
		size1 = strlen(u1);
		size2 = strlen(u2);
		u1[size1 - 1] = '\0';
		u2[size2 - 1] = '\0';
		printf("\nYour nickname is %s and you will play against %s.\n", u1, u2);	
	}
	else if (input[0] == 'c' || input[0] == 'C') {
		user_prompt("Enter a nickname for yourself: ", u1);
		strcpy(u2, "computer");
		size1 = strlen(u1);
		u1[size1 - 1] = '\0';
		printf("\nYour nickname is %s, and you will play against the computer.\n", u1);
	}
	else {
		printf("\nIncorrect input, please try again.\n");
	}
}

/*
  Checks what symbol the user/s have chosen and prints a message confirming their choice.
  Error checks to make sure their input is valid.
 	 Parameters: *u1_s, *u2_s, *u1, *u2
*/
void choose_xo(char *u1_s, char *u2_s, char *u1, char *u2) {

	quit(u1_s);
	if (u1_s[0] == 'X' || u1_s[0] == 'x') {
		strcpy(u1_s, "X");
		printf("\nYou will play using crosses and %s will use noughts.\n", u2);
		strcpy(u2_s, "O");
	}	
	else if (u1_s[0] == 'O' || u1_s[0] == 'o') {
		strcpy(u1_s, "O");
		printf("\nYou will play using noughts and %s will use crosses.\n", u2);
		strcpy(u2_s, "X");
	}
	else {
		printf("\nIncorrect input, please try again.\n");
	}
}

/*
  Prompts the current user to enter their move and prints if a user/computer has won game or if
  there was a tie. It also prints the current score between the 2 players or the user and computer
  after each game is complete and then asks if they would like to play again.
  	Parameters: u1_s, u2_s, u1, u2, b[Y][X], u1_score, u2_score
*/
void prompt_move(char *u1_s, char *u2_s, char *u1, char *u2, char b[Y][X], int *u1_score, int *u2_score) {

	int win, i = 0;
	for (i = 0; i < 9; i++) {
		if (i % 2 == 0) {
			printf("Enter your move %s: ", u1);
			strcpy(xo, u1_s);
			user_move(b);	
		}
		else if ((strcmp(u2, "computer")) == 0) {
			strcpy(xo, u2_s);
			printf("\nComputers move:\n");
			computer_move(b);
		}
		else {
			printf("Enter your move %s: ", u2);
			strcpy(xo, u2_s);
			user_move(b);
		}
		display_board(b);
		win = detect_win(b);
		if (win == 1) {
			if(u1_s[0] == xo[0]) {
				printf("Well done %s, you have won!\n", u1);
				*u1_score = *u1_score + 1;
				i = 9;
			}
			else {
				printf("Sorry %s, %s has won!\n", u1, u2);
				*u2_score = *u2_score + 1;
				i = 9;
			}	
		}
	}
	if (win == 0) {
		printf("\nIt was a tie!\n");
	}

	win = 0;
	printf("The score is:\n");
	printf("\t%s: %d\n", u1, *u1_score);
	printf("\t%s: %d\n", u2, *u2_score);

	char answer[2], yes[2];

	printf("\nWould you like to play again? (Type 'Y' or 'N'): ");
	scanf("%s", answer);
	quit(answer);
	if(answer[0] == 'Y' || answer[0] == 'y') {
		printf("\n");
	 	clear_board(b);
		display_board(b);
		prompt_move(u1_s, u2_s, u1, u2, b, u1_score, u2_score);
	}
	else if(answer[0] == 'N' || answer[0] == 'n') {
		printf("\nThanks for playing.");
		strcpy(yes, "0");
		quit(yes);
	}
	else {
	 	printf("\nIncorrect input, please try again.");
	}	   
}


/*
  Simulates a user's move and displays their new move on the board afterwards. The function 
  error checks to make sure they have entered a correct value or an occupied space on the board.
	Parameter: b[Y][X]
*/
void user_move(char b[Y][X]) {
	
	int place, i;

	scanf("%d", &place);
		
		if (place == 0) {
			printf("\nGoodbye!\n");
			exit(0);	
		}
		else if (place == 1 || place == 2 || place == 3) {
			if (b[0][(place - 1)] == 'X' || b[0][(place - 1)] == 'O') {
			 	printf("\nSorry this place is occupied, try again!\n");
				printf("Enter a number from 1 -> 9: ");
				user_move(b);
			}	
			else {
				b[0][(place - 1)] = xo[0];
			}
		}
		else if (place == 4 || place == 5 || place == 6) {
			if (b[1][(place - 4)] == 'X' || b[1][(place - 4)] == 'O') {
				printf("\nSorry this place is occupied, try again!\n");
				printf("Enter a number from 1 -> 9: ");
				user_move(b);
			}	
			else {	
				b[1][(place - 4)] = xo[0];
			}		
		}
		else if (place == 7 || place == 8 || place == 9) {
			if (b[2][(place - 7)] == 'X' || b[2][(place - 7)] == '0') {
				printf("\nSorry this place is occupied, try again!\n");
				printf("Enter a number from 1 -> 9: ");
				user_move(b);		
			}	
			else {
		 		b[2][(place - 7)] = xo[0]; 
			}	
		}
		else {
			printf("Incorrect input, please enter a number from 1 -> 9: ");
			user_move(b);
		}		
}		

/*
  Simulates a comupter move on the game board, depending on the number of moves the computer has
  placed or not placed before.
	Parameter: b[Y][X]
*/
void computer_move(char b[Y][X]) {

	int x, y, count = 0;

	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			if (b[x][y] != ' ') {
				count++;
			}
		}
	}

	if(count == 1) {
		first_com_move(b);
	}
	else if(count == 3) {
		block_win(b);
	}		
	else if(count == 5) {
		try_win(b);
	}
	else if(count == 7) {
		try_win(b);
	}
	
}

/*
  Chooses the computer's first move using AI to place the best move possible by checking what the 
  user placed on the board first. 
	Parameter: b[Y][X]
*/
void first_com_move(char b[Y][X]) {

	if (b[1][1] != ' ') {
		b[0][0] = xo[0];
	}
	else {
		b[1][1] = xo[0];
	}
}

/*
  Chooses the computer's second move by trying to block the user from winning (getting 3 in a row,
  column or diagonally) and if not, it will tactically place their 2nd move.
	Parameter: b[Y][X]
*/
void block_win(char b[Y][X]) {

	//Checks if computer can block at corners
	if ( (b[0][2] == ' ') && ((((b[0][0] != ' ') && (b[0][0] != xo[0])) && ((b[0][1] != ' ') && (b[0][1] != xo[0]))) || 
	       (((b[1][2] != ' ') && (b[1][2] != xo[0])) && ((b[2][2] != ' ') && (b[2][2] != xo[0])))) ) {
			b[0][2] = xo[0];
	}
	else if ( (b[2][2] == ' ') && ((((b[2][0] != ' ') && (b[2][0] != xo[0])) && ((b[2][1] != ' ') && (b[2][1] != xo[0]))) || 
	     	(((b[0][2] != ' ') && (b[0][2] != xo[0])) && ((b[1][2] != ' ') && (b[1][2] != xo[0])))) ) {
			b[2][2] = xo[0];
	} 
	else if ( (b[2][0] == ' ') && ((((b[0][0] != ' ') && (b[0][0] != xo[0])) && ((b[1][0] != ' ') && (b[1][0] != xo[0]))) || 
	     	(((b[2][1] != ' ') && (b[2][1] != xo[0])) && ((b[2][2] != ' ') && (b[2][2] != xo[0])))) ) {
			b[2][0] = xo[0];
	}
	else if ( (b[0][0] == ' ') && ((((b[0][1] != ' ') && (b[0][1] != xo[0])) && ((b[0][2] != ' ') && (b[0][2] != xo[0]))) || 
	     	(((b[1][0] != ' ') && (b[1][0] != xo[0])) && ((b[2][0] != ' ') && (b[2][0] != xo[0])))) ) {
			b[0][0] = xo[0];
	}

	//Checks if computer can block in middle of rows
	else if ( (b[0][1] == ' ') && (((b[0][0] != ' ') && (b[0][0] != xo[0])) && ((b[0][2] != ' ') && (b[0][2] != xo[0]))) ) {	
			b[0][1] = xo[0];
	}
	else if ( (b[1][1] == ' ') && (((b[1][0] != ' ') && (b[1][0] != xo[0])) && ((b[1][2] != ' ') && (b[1][2] != xo[0]))) ) {
			b[1][1] = xo[0];
	} 
	else if ( (b[2][1] == ' ') && (((b[2][0] != ' ') && (b[2][0] != xo[0])) && ((b[2][2] != ' ') && (b[2][2] != xo[0]))) ) {
			b[2][1] = xo[0];
	}

	//Checks if computer can block in middle of columns
	else if ( (b[1][0] == ' ') && (((b[0][0] != ' ') && (b[0][0] != xo[0])) && ((b[2][0] != ' ') && (b[2][0] != xo[0]))) ) {	
			b[1][0] = xo[0];
	}
	else if ( (b[1][1] == ' ') && (((b[0][1] != ' ') && (b[0][1] != xo[0])) && ((b[2][1] != ' ') && (b[2][1] != xo[0]))) ) {			
			b[1][1] = xo[0];
	}
	else if ( (b[1][2] == ' ') && (((b[0][2] != ' ') && (b[0][2] != xo[0])) && ((b[2][2] != ' ') && (b[2][2] != xo[0]))) ) {
			b[1][2] = xo[0];
	}

	//Checks if computer can block middle row at opposite sides
	else if ( (b[1][2] == ' ') && (((b[1][0] != ' ') && (b[1][0] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[1][2] = xo[0];
	}	
	else if ( (b[1][0] == ' ') && (((b[1][2] != ' ') && (b[1][2] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[1][0] = xo[0];
	}

	//Checks if computer can block middle column at opposite sides
	else if ( (b[2][1] == ' ') && (((b[0][1] != ' ') && (b[0][1] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {	
			b[2][1] = xo[0];
	}
	else if ( (b[0][1] == ' ') && (((b[2][1] != ' ') && (b[2][1] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ){	
			b[0][1] = xo[0];
	}
	
	//Checks if computer can block at corners diagonally (/)
	else if ( (b[2][0] == ' ') && (((b[0][2] != ' ') && (b[0][2] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[2][0] = xo[0];
	}
	else if ( (b[0][2] == ' ') && (((b[2][0] != ' ') && (b[2][0] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[0][2] = xo[0];
	}

	//Checks if computer can block at corners diagonally (\)
	else if ( (b[2][2] == ' ') && (((b[0][0] != ' ') && (b[0][0] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[2][2] = xo[0];
	}
	else if ( (b[0][0] == ' ') && (((b[2][2] != ' ') && (b[2][2] != xo[0])) && ((b[1][1] != ' ') && (b[1][1] != xo[0]))) ) {
			b[0][0] = xo[0];
	}
	
	//If unable to block a user win then try win
	else if((b[0][0] == xo[0]) && (b[0][1] == ' ')) {
			b[0][1] = xo[0];
	}
	else if ((b[0][0] == xo[0]) && (b[1][0] == ' ')) {
			b[1][0] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[0][1] == ' ')) {
			b[0][1] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[1][0] == ' ')) {
			b[1][0] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[1][2] == ' ')) {
			b[1][2] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[2][1] == ' ')) {
			b[2][1] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[0][0] == ' ')) {
			b[0][0] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[0][2] == ' ')) {
			b[0][2] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[2][0] == ' ')) {
			b[2][0] = xo[0];
	}
	else if((b[1][1] == xo[0]) && (b[2][2] == ' ')) {
			b[2][2] = xo[0];
	}

}

/*
  Chooses the computer's 3rd and 4th move by trying to win based on the current board places 
  and if not the computer wil tie with the user.
  	Parameter: b[Y][X]
*/
void try_win(char b[Y][X]) {

	//Checks first column
	if ( (b[0][0] == ' ') && ((b[1][0] == xo[0]) && (b[2][0] == xo[0])) ) {	
			b[0][0] = xo[0];
	}
	else if ( (b[1][0] == ' ') && ((b[2][0] == xo[0]) && (b[0][0] == xo[0])) ) {	
			b[1][0] = xo[0];
	}
	else if ( (b[2][0] == ' ') && ((b[1][0] == xo[0]) && (b[0][0] == xo[0])) ) {	
			b[2][0] = xo[0];
	}
	
	//Checks middle column
	else if ( (b[0][1] == ' ') && ((b[1][1] == xo[0]) && (b[2][1] == xo[0])) ) {	
			b[0][1] = xo[0];
	}
	else if ( (b[1][1] == ' ') && ((b[2][1] == xo[0]) && (b[0][1] == xo[0])) ) {	
			b[1][1] = xo[0];
	}
	else if ( (b[2][1] == ' ') && ((b[1][1] == xo[0]) && (b[0][1] == xo[0])) ) {	
			b[2][1] = xo[0];
	}

	//Checks bottom column
	else if ( (b[0][2] == ' ') && ((b[1][2] == xo[0]) && (b[2][2] == xo[0])) ) {	
			b[0][2] = xo[0];
	}
	else if ( (b[1][2] == ' ') && ((b[2][2] == xo[0]) && (b[0][2] == xo[0])) ) {	
			b[1][2] = xo[0];
	}
	else if ( (b[2][2] == ' ') && ((b[1][2] == xo[0]) && (b[0][2] == xo[0])) ) {	
			b[2][2] = xo[0];
	}

	//Checks top row
	else if ( (b[0][1] == ' ') && ((b[0][0] == xo[0]) && (b[0][2] == xo[0])) ) {	
			b[0][1] = xo[0];
	}
	else if ( (b[0][0] == ' ') && ((b[0][1] == xo[0]) && (b[0][2] == xo[0])) ) {	
			b[0][0] = xo[0];
	}
	else if ( (b[0][2] == ' ') && ((b[0][0] == xo[0]) && (b[0][1] == xo[0])) ) {	
			b[0][2] = xo[0];
	}
	
	//Checks middle row
	else if ( (b[1][1] == ' ') && ((b[1][0] == xo[0]) && (b[1][2] == xo[0])) ) {	
			b[1][1] = xo[0];
	}
	else if ( (b[1][0] == ' ') && ((b[1][1] == xo[0]) && (b[1][2] == xo[0])) ) {	
			b[1][0] = xo[0];
	}
	else if ( (b[1][2] == ' ') && ((b[1][1] == xo[0]) && (b[1][0] == xo[0])) ) {	
			b[1][2] = xo[0];
	}

	//Checks bottom row
	else if ( (b[2][1] == ' ') && ((b[2][0] == xo[0]) && (b[2][2] == xo[0])) ) {	
			b[2][1] = xo[0];
	}
	else if ( (b[2][0] == ' ') && ((b[2][1] == xo[0]) && (b[2][2] == xo[0])) ) {	
			b[2][0] = xo[0];
	}
	else if ( (b[2][2] == ' ') && ((b[2][1] == xo[0]) && (b[2][0] == xo[0])) ) {	
			b[2][2] = xo[0];
	}

	//Checks diagonally (left -> right)
	else if ( (b[0][0] == ' ') && ((b[1][1] == xo[0]) && (b[2][2] == xo[0])) ) {	
			b[0][0] = xo[0];
	}
	else if ( (b[1][1] == ' ') && ((b[2][2] == xo[0]) && (b[0][0] == xo[0])) ) {	
			b[1][1] = xo[0];
	}
	else if ( (b[2][2] == ' ') && ((b[0][0] == xo[0]) && (b[1][1] == xo[0])) ) {	
			b[2][2] = xo[0];
	}
	
	//Checks diagonally (right -> left)  
	else if ( (b[2][0] == ' ') && ((b[1][1] == xo[0]) && (b[0][2] == xo[0])) ) {	
			b[2][0] = xo[0];
	}
	else if ( (b[1][1] == ' ') && ((b[0][2] == xo[0]) && (b[2][0] == xo[0])) ) {	
			b[1][1] = xo[0];
	}
	else if ( (b[0][2] == ' ') && ((b[2][0] == xo[0]) && (b[1][1] == xo[0])) ) {	
			b[0][2] = xo[0];
	}
	else { 

		block_win(b);	
	}

}

/*
 Checks all the possible winning positions for X and O and returns 1 if there has been 
 a win, 0 if not and detects what symbol (X/O) has won. 
	Parameter: b[Y][X]
*/
int detect_win(char b[Y][X]) {

	int win = 0;

	if (  ((b[0][0] == 'X') && (b[0][1] == 'X') && (b[0][2] == 'X'))
	   || ((b[1][0] == 'X') && (b[1][1] == 'X') && (b[1][2] == 'X'))
	   || ((b[2][0] == 'X') && (b[2][1] == 'X') && (b[2][2] == 'X'))
	   || ((b[0][0] == 'X') && (b[1][0] == 'X') && (b[2][0] == 'X'))
	   || ((b[0][1] == 'X') && (b[1][1] == 'X') && (b[2][1] == 'X'))
           || ((b[0][2] == 'X') && (b[1][2] == 'X') && (b[2][2] == 'X'))
	   || ((b[0][0] == 'X') && (b[1][1] == 'X') && (b[2][2] == 'X'))
	   || ((b[0][2] == 'X') && (b[1][1] == 'X') && (b[2][0] == 'X')) ) {

			xo[0] = 'X';
			win = 1;
	}

	if (  ((b[0][0] == 'O') && (b[0][1] == 'O') && (b[0][2] == 'O'))
	   || ((b[1][0] == 'O') && (b[1][1] == 'O') && (b[1][2] == 'O'))
	   || ((b[2][0] == 'O') && (b[2][1] == 'O') && (b[2][2] == 'O'))
	   || ((b[0][0] == 'O') && (b[1][0] == 'O') && (b[2][0] == 'O'))
	   || ((b[0][1] == 'O') && (b[1][1] == 'O') && (b[2][1] == 'O'))
           || ((b[0][2] == 'O') && (b[1][2] == 'O') && (b[2][2] == 'O'))
	   || ((b[0][0] == 'O') && (b[1][1] == 'O') && (b[2][2] == 'O'))
	   || ((b[0][2] == 'O') && (b[1][1] == 'O') && (b[2][0] == 'O')) ) {

			xo[0] = 'O';
			win = 1;
	}

	return win;
}

/*
  Makes the program terminate if the user wants to.
  	Parameter: *input
*/
void quit(char *input) {

	if(input[0] == '0') {
		printf("\nGoodbye!\n");
		exit(0);
	}

}




