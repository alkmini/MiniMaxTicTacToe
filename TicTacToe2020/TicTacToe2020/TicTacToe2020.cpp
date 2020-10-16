#include <iostream>
#include<string>
#include<algorithm> 

enum class Player { empty, x, o };

struct Move { int row, col; };


char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
Player enumBoard[3][3] = { { Player::empty, Player::empty, Player::empty },
							{ Player::empty, Player::empty, Player::empty },
							{ Player::empty, Player::empty, Player::empty } };
char currentMarker = ' ';
bool isAvailable = true;


void PlaceMarker(char& P);
void IsSlotAvailable(int slot);
void UpdateEnumBoard();
Move FindBestMove(Player enumBoard[3][3]);

void PrintBoard()
{
	std::cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << std::endl;
	std::cout << "-----------\n";
	std::cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << std::endl;
	std::cout << "-----------\n";
	std::cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << std::endl;

}

void PlaceMarker(char& currentPlayer)
{
	int slot = 0;

	if (currentPlayer == 'x')
	{


		while (!(std::cin >> slot) || slot < 1 || slot > 9)
		{
			system("CLS");
			std::cin.clear();
			std::cin.ignore();
			PrintBoard();
			std::cout << "Invalid symbol or number . Please choose a square: " << std::endl;

		}
		system("CLS");
		IsSlotAvailable(slot);
		if (isAvailable == true)
		{
			board[(slot - 1) / 3][(slot - 1) % 3] = currentPlayer;
			PrintBoard();
		}
		else
		{
			PrintBoard();
			std::cout << " Square taken. Choose an available square" << std::endl;
		}

	}
	else if (currentPlayer == 'o')
	{
		Move bestMove = FindBestMove(enumBoard);
		if (bestMove.row != -1)
		{
			board[bestMove.row][bestMove.col] = 'o';
		}
		system("CLS");
		PrintBoard();
	}

	if (isAvailable)
	{
		if (currentPlayer == 'x')
		{
			currentPlayer = 'o';
		}
		else if (currentPlayer == 'o')
		{
			currentPlayer = 'x';
		}
	}

}

void IsSlotAvailable(int slot)
{
	char result = board[(slot - 1) / 3][(slot - 1) % 3];
	if (result == 'x' || result == 'o')
	{
		isAvailable = false;
	}
	else isAvailable = true;

}

void AssignPlayers(char& playerSymbol)
{
	int player = 2;
	std::cout << "Welcome to my game" << std::endl;
	std::cout << "Assign x or o for Player 1" << std::endl;
	std::string str;

	while (!(std::cin >> str) || (str[0] != 'x' && str[0] != 'o'))
	{
		system("CLS");
		std::cin.ignore();
		std::cin.clear();
		std::cout << "Invalid symbol. Please Select a marker. " << std::endl;

	}

	playerSymbol = str[0];

	if (playerSymbol == 'x')
	{
		std::cout << "Very well. Player " << player << " has the marker o" << std::endl;
	}
	else
	{
		std::cout << "Very well. Player " << player << " has the marker x" << std::endl;
	}
}

Player GetWinningPlayer()
{
	//horizontally
	if ((enumBoard[0][0] == enumBoard[0][1]) && (enumBoard[0][1] == enumBoard[0][2]) && (enumBoard[0][0] != Player::empty))
	{
		return enumBoard[0][0];
	}
	if ((enumBoard[1][0] == enumBoard[1][1]) && (enumBoard[1][1] == enumBoard[1][2]) && (enumBoard[1][0] != Player::empty))
	{
		return enumBoard[1][0];
	}
	if ((enumBoard[2][0] == enumBoard[2][1]) && (enumBoard[2][1] == enumBoard[2][2]) && (enumBoard[2][0] != Player::empty))
	{
		return enumBoard[2][0];
	}

	//vertically
	if ((enumBoard[0][0] == enumBoard[1][0]) && (enumBoard[1][0] == enumBoard[2][0]) && (enumBoard[0][0] != Player::empty))
	{
		return enumBoard[0][0];
	}
	if ((enumBoard[0][1] == enumBoard[1][1]) && (enumBoard[1][1] == enumBoard[2][1]) && (enumBoard[0][1] != Player::empty))
	{
		return enumBoard[0][1];
	}
	if ((enumBoard[0][2] == enumBoard[1][2]) && (enumBoard[1][2] == enumBoard[2][2]) && (enumBoard[0][1] != Player::empty))
	{
		return enumBoard[0][2];
	}

	//diagonally
	if ((enumBoard[0][0] == enumBoard[1][1]) && (enumBoard[1][1] == enumBoard[2][2]) && (enumBoard[0][0] != Player::empty))
	{
		return enumBoard[0][0];
	}
	if ((enumBoard[2][0] == enumBoard[1][1]) && (enumBoard[1][1] == enumBoard[0][2]) && (enumBoard[2][0] != Player::empty))
	{
		return enumBoard[2][0];
	}
	return Player::empty;
}

void UpdateEnumBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (board[i][j])
			{
			case 'x':
				enumBoard[i][j] = Player::x;
				break;
			case 'o':
				enumBoard[i][j] = Player::o;
				break;
			default:
				enumBoard[i][j] = Player::empty;
				break;
			}
		}
	}
}

bool checkSlot(Player enumBoard[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (enumBoard[i][j] == Player::empty)
			{
				return true;
			}
		}
	}
	return false;
}

int Evaluate()
{
	if ((GetWinningPlayer()) == Player::o)
	{
		return +10;
	}
	else if ((GetWinningPlayer()) == Player::x)
	{
		return -10;
	}
	return 0;
}



int MiniMax(Player enumBoard[3][3], int depth, bool isMax)
{
	int scoreResult = Evaluate();


	if (scoreResult == 10)
	{
		return scoreResult;
	}

	if (scoreResult == -10)
	{
		return scoreResult;
	}

	if (checkSlot(enumBoard) == false)
	{
		return 0;
	}

	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (enumBoard[i][j] == Player::empty)
				{
					enumBoard[i][j] = Player::o;

					best = std::max(best, MiniMax(enumBoard, depth + 1, !isMax));

					enumBoard[i][j] = Player::empty;
				}
			}
		}

		return best;
	}

	else
	{
		int best = 1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (enumBoard[i][j] == Player::empty)
				{
					enumBoard[i][j] = Player::x;

					best = std::min(best, MiniMax(enumBoard, depth + 1, !isMax));

					enumBoard[i][j] = Player::empty;
				}
			}
		}
		return best;
	}
}

Move FindBestMove(Player enumBoard[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != 'x' && board[i][j] != 'o')
			{
				enumBoard[i][j] = Player::o;

				int moveVal = MiniMax(enumBoard, 0, false);

				enumBoard[i][j] = Player::empty;

				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

		return bestMove;
}


int main()
{
	AssignPlayers(currentMarker);
	PrintBoard();

	Player winningPlayer;
	while (true)
	{
		winningPlayer = GetWinningPlayer();
		if (!checkSlot(enumBoard) || winningPlayer != Player::empty)
		{
			break;
		}

		PlaceMarker(currentMarker);
		UpdateEnumBoard();
	}
	if (winningPlayer == Player::x)
	{
		std::cout << "You won Player x" << std::endl;
	}
	else if (winningPlayer == Player::o)
	{
		std::cout << "You are defeated by Player o" << std::endl;
	}
	else if (winningPlayer == Player::empty)
	{
		std::cout << "No one won" << std::endl;
	}

	std::cout << '\n';
	std::cin.get();
}
