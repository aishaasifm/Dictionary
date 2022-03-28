/*
 *
 * File: TicTacToe.cpp
 * By: Aisha Asif 
 * Date: 05/14/2022
 *
 * Description: this code is the tictactoe game!
 *
 */
#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);
int const maximumMoves(9);
int numberOfMoves(0);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
} 
// for winning the game 
bool isWon (char turn, char gamer [] [3]){
	if (gamer [0][0] == turn && gamer[0][1] == turn && gamer[0][2] == turn){
		return true;
	}else if (gamer[1][0] == turn && gamer [1][1] == turn && gamer [1][2] == turn){
		return true;
	}else if (gamer[2][0] == turn && gamer [2][1] == turn && gamer [2][2] == turn){
		return true;
	}else if (gamer[0][0] == turn && gamer [1][0] == turn && gamer [2][0] == turn){
		return true;
	}else if (gamer[0][1] == turn && gamer [1][1] == turn && gamer [2][1] == turn){
		return true;
	}else if (gamer[0][2] == turn && gamer [1][2] == turn && gamer [2][2] == turn){
		return true;
	}else if (gamer[0][0] == turn && gamer [1][1] == turn && gamer [2][2] == turn){
		return true;
	}else if (gamer[2][0] == turn && gamer [1][1] == turn && gamer [0][2] == turn){
		return true;
	}return false;
//when the game is at a draw (when the number of moves is equal to the maximum moves and no one has won yet)
}bool isDraw(char gamer [][3]){
	if (numberOfMoves == maximumMoves){
		return true;
	} 
	return false; 
//the tic tac toe board printed out in a series of arrays and cout hard-coded
}void displayBoard(char gamer[][3]){
		cout << gamer[0][0]<< "|"<< gamer[0][1]<<"|" <<gamer[0][2]<< endl;
		cout << "------------" << endl;
		cout << gamer[1][0]<< "|"<< gamer[1][1]<<"|" <<gamer[1][2]<< endl;
		cout << "------------" << endl;
		cout << gamer[2][0]<< "|"<< gamer[2][1]<<"|" <<gamer[2][2]<< endl;
//if the gamer makes a move and it is not one of the options //voided
}void makeAMove(char gamer[][3], char turn) { 
   ++numberOfMoves;								
    int row;
    int column;
	bool placement = false;
    while(placement == false) {
        cout << "Enter a row (0, 1, 2) for player " << turn << " : ";
        cin >> row;
        cout << "Enter a column (0, 1, 2) for player " << turn  << " : ";
        cin >> column;
		if(row < 0 || row > 2 || column < 0 || column > 2) {
			cout << "Out of Range try again" << endl; 
	//gamer make a move. if the move is in the same spot as another move it is void
		}else {
			if(gamer[row][column] == ' ') {
            	gamer[row][column] = turn;
            	break;
			}else {
				cout << "This position is already occupied. Please enter a new position" << endl;
			}
        }
	}
  

}