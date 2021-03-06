// TicTacToe.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef const char SYMBOL;
typedef const vector<char>* const BOARD;

SYMBOL X = 'X';
SYMBOL O = 'O';
SYMBOL EMPTY = ' ';
SYMBOL TIE = 'T';
SYMBOL NO_ONE = 'N';

void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(BOARD board);
char winner(BOARD board);
bool isLegal(int move, BOARD board);
int humanMove(BOARD board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);


int main()
{
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;
	displayBoard(&board);
	while (winner(&board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(&board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(&board);
		turn = opponent(turn);
	}
	announceWinner(winner(&board), computer, human);
	return 0;
}

void instructions()
{
	cout << "\n\nWelcome in Tic Tac Toe\n";
	cout << "\n Rule is very simple:\n";
	cout << "\n made vertical or horizontal or diagonal line one type (X / O)\n";
	cout << "Make your move known Ьу entering а number. О - 8. The number\n";
	cout << "corresponds to the desired board position. as illustrated:\n\n";
	cout << " 0 | 1 | 2\n";
	cout << " ---------\n";
	cout << " 3 | 4 | 5\n";
	cout << " ---------\n";
	cout << " 6 | 7 | 8\n\n";
	cout << "Prepare yourself. human. The battle is about to begin.\n\n";
}

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}

int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << " ): ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}

char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	char result = X;
	if (go_first == 'y')
	{
		cout << "\Then take the first move. You will need it.\n";
	}
	else
	{
		result = O;
		cout << "\nYour bravery will be your undoing... I will go first.\n";
	}
	return result;
}

char opponent(char piece)
{
	char result = X;
	if (piece == X)
	{
		result = O;
	}
	return result;
}

void displayBoard(BOARD board)
{
	cout << "\n\t" << (*board)[0] << " | " << (*board)[1] << " | " << (*board)[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*board)[3] << " | " << (*board)[4] << " | " << (*board)[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << (*board)[6] << " | " << (*board)[7] << " | " << (*board)[8];
}

char winner(BOARD board)
{
	const int WINNING_ROWS[8][3] = { {0,1,2},
	{3, 4, 6},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 6},
	{2, 4, 6} };
	const int TOTAL_ROWS = 8;
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if (((*board)[WINNING_ROWS[row][0]] != EMPTY) &&
			((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
			((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]))
		{
			return (*board)[WINNING_ROWS[row][0]];
		}
	}

	if (count(board->begin(), board->end(), EMPTY) == 0)
	{
		return TIE;
	}
	return NO_ONE;
}

inline bool isLegal(int move, BOARD board)
{
	return ((*board)[move] == EMPTY);
}

int humanMove(BOARD board, char human)
{
	int move = askNumber("\nWhere will you move?", ((*board).size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", ((*board).size() - 1));
	}
	cout << "Fine ... \n";
	return move;
}

int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	/* проверяю возможность выигрыша*/
	while (!found && move < board.size())
	{
		if (isLegal(move, &board))
		{
			board[move] = computer;
			found = winner(&board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}
	/*блокирую удачные комбинации оппонента*/
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(move, &board))
			{
				board[move] = human;
				found = winner(&board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}
	/*иначе занять лучшую клетку*/
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, &board))
			{
				found = true;
			}
			++i;
		}
	}
	cout << "\nI shall take square number " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s won!\n";
		cout << "As I predicted, human. I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == computer)
	{
		cout << winner << "'s won!\n";
		cout << "No. по! It cannot Ье! Somehow you tricked me. human. \n";
		cout << "But never again! I. the computer. so swear it!\n";
	}
	else
	{
		cout << "\nIt's a tie.\n";
		cout << "You were most lucky. human. and somehow managed to tie me.\n";
		cout << "Celebrate ... for this is the best you will ever achieve.\n";
	}
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
