#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
int N, M;
int recursionState;
int solutionState;

int*** boardMoves;
int* nElements;
vector<int> values;
bool change;

void makeMove(int move)
{
	if (nElements[recursionState] == 0)
		boardMoves[recursionState] = new int* [N];

	for (int i = 0; i < N; i++)
	{
		if (nElements[recursionState] == 0)
			boardMoves[recursionState][i] = new int[N];

		for (int j = 0; j < N; j++)
			boardMoves[recursionState][i][j] = boardMoves[recursionState - 1][i][j];
	}

	nElements[recursionState] = nElements[recursionState - 1];

	//UP
	if (move == UP)
	{
		for (int i = 0; i < N; i++)
		{
			int temp = 0;

			for (int j = 1; j < N; j++)
			{
				if (boardMoves[recursionState][j][i] != 0)
				{
					if (boardMoves[recursionState][temp][i] == boardMoves[recursionState][j][i])
					{
						boardMoves[recursionState][temp][i] *= 2;
						boardMoves[recursionState][j][i] = 0;
						temp = j;
						nElements[recursionState] -= 1;
						change = true;
					}
					else if (boardMoves[recursionState][temp][i] != boardMoves[recursionState][j][i])
					{
						temp = j;
					}
					else if (boardMoves[recursionState][temp][i] == 0)
					{
						temp++;
					}
				}
			}

			for (int j = 0; j < N; j++)
			{
				if (boardMoves[recursionState][j][i] == 0)
				{
					temp = j;
					break;
				}
			}

			for (int j = temp + 1; j < N; j++)
			{
				if (boardMoves[recursionState][j][i] != 0)
				{
					boardMoves[recursionState][temp][i] = boardMoves[recursionState][j][i];
					boardMoves[recursionState][j][i] = 0;
					temp++;
					change = true;
				}
			}
		}
	}

	//DOWN
	if (move == DOWN)
	{
		for (int i = 0; i < N; i++)
		{
			int temp = N - 1;
			for (int j = N - 2; j >= 0; j--)
			{
				if (boardMoves[recursionState][j][i] != 0)
				{
					if (boardMoves[recursionState][temp][i] == boardMoves[recursionState][j][i])
					{
						boardMoves[recursionState][temp][i] *= 2;
						boardMoves[recursionState][j][i] = 0;
						temp = j;
						nElements[recursionState] -= 1;
						change = true;
					}
					else if (boardMoves[recursionState][temp][i] != boardMoves[recursionState][j][i])
					{
						temp = j;
					}
					else if (boardMoves[recursionState][temp][i] == 0)
					{
						temp--;
					}
				}
			}

			for (int j = N - 1; j >= 0; j--)
			{
				if (boardMoves[recursionState][j][i] == 0)
				{
					temp = j;
					break;
				}
			}

			for (int j = temp - 1; j >= 0; j--)
			{
				if (boardMoves[recursionState][j][i] != 0)
				{
					boardMoves[recursionState][temp][i] = boardMoves[recursionState][j][i];
					boardMoves[recursionState][j][i] = 0;
					temp--;
					change = true;
				}
			}
		}
	}

	//LEFT
	if (move == LEFT)
	{
		for (int i = 0; i < N; i++)
		{
			int temp = 0;

			for (int j = 1; j < N; j++)
			{
				if (boardMoves[recursionState][i][j] != 0)
				{
					if (boardMoves[recursionState][i][temp] == boardMoves[recursionState][i][j])
					{
						boardMoves[recursionState][i][temp] *= 2;
						boardMoves[recursionState][i][j] = 0;
						temp = j;
						nElements[recursionState] -= 1;
						change = true;
					}
					else if (boardMoves[recursionState][i][temp] != boardMoves[recursionState][i][j])
					{
						temp = j;
					}
					else if (boardMoves[recursionState][i][temp] == 0)
					{
						temp++;
					}
				}
			}

			for (int j = 0; j < N; j++)
			{
				if (boardMoves[recursionState][i][j] == 0)
				{
					temp = j;
					break;
				}
			}

			for (int j = temp + 1; j < N; j++)
			{
				if (boardMoves[recursionState][i][j] != 0)
				{
					boardMoves[recursionState][i][temp] = boardMoves[recursionState][i][j];
					boardMoves[recursionState][i][j] = 0;
					temp++;
					change = true;
				}
			}
		}
	}

	//RIGHT
	if (move == RIGHT)
	{
		for (int i = 0; i < N; i++)
		{
			int temp = N - 1;
			for (int j = N - 2; j >= 0; j--)
			{
				if (boardMoves[recursionState][i][j] != 0)
				{
					if (boardMoves[recursionState][i][temp] == boardMoves[recursionState][i][j])
					{
						boardMoves[recursionState][i][temp] *= 2;
						boardMoves[recursionState][i][j] = 0;
						temp = j;
						nElements[recursionState] -= 1;
						change = true;
					}
					else if (boardMoves[recursionState][i][temp] != boardMoves[recursionState][i][j])
					{
						temp = j;
					}
					else if (boardMoves[recursionState][i][temp] == 0)
					{
						temp--;
					}
				}
			}

			for (int j = N - 1; j >= 0; j--)
			{
				if (boardMoves[recursionState][i][j] == 0)
				{
					temp = j;
					break;
				}
			}

			for (int j = temp - 1; j >= 0; j--)
			{
				if (boardMoves[recursionState][i][j] != 0)
				{
					boardMoves[recursionState][i][temp] = boardMoves[recursionState][i][j];
					boardMoves[recursionState][i][j] = 0;
					temp--;
					change = true;
				}
			}
		}
	}
}

bool inCicle()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (boardMoves[recursionState][i][j] != boardMoves[recursionState - 2][i][j])
				return false;
		}
	}

	return true;
}

void solveBoard()
{
	int move = 0;
	int bestMove = 0;
	bool cicle = false;
	vector<int> scores;

	if (recursionState < M)
	{
		recursionState++;

		if (solutionState <= recursionState && solutionState != 0)
		{
			recursionState--;
			return;
		}

		for (int i = 0; i < 4; i++, move++)
		{
			makeMove(move);

			if (nElements[recursionState] == 1)	//Just one element
			{
				solutionState = recursionState;
				recursionState--;
				return;
			}

			scores.push_back(N * N - nElements[recursionState]);
		}

		if (count(scores.begin(), scores.end(), 0) == 4)	//Board is blocked
		{
			recursionState--;
			return;
		}

		int counter = 0;

		while (counter < 4)
		{
			bestMove = max_element(scores.begin(), scores.end()) - scores.begin();
			change = false;
			makeMove(bestMove);

			if (recursionState >= 2)
			{
				if (inCicle())
					cicle = true;
				else
					cicle = false;
			}

			if (change && !cicle)
				solveBoard();

			scores[bestMove] = -1;
			counter++;
		}

		recursionState--;
	}
}

bool canCombine()
{
	while (1)
	{
		sort(values.begin(), values.end());

		if (values.size() == 1)
		{
			values.clear();
			return true;
		}

		if (values[0] == values[1])
		{
			values[1] *= 2;
			values.erase(values.begin());
		}
		else
		{
			values.clear();
			return false;
		}
	}
}

int main()
{
	int nBoards;
	int input;

	cin >> nBoards;

	while (nBoards > 0)
	{
		cin >> N;
		cin >> M;

		boardMoves = new int** [M + 1];
		boardMoves[0] = new int* [N];

		for (int i = 0; i < N; i++)
		{
			boardMoves[0][i] = new int[N];
			for (int j = 0; j < N; j++)
			{
				cin >> input;
				boardMoves[0][i][j] = input;
				if (input != 0)
					values.push_back(boardMoves[0][i][j]);
			}
		}

		nElements = new int[M + 1]
		{ 0 };
		nElements[0] = values.size();

		recursionState = 0;
		solutionState = 0;

		if (canCombine())
			solveBoard();

		if (solutionState > 0)
			cout << solutionState << "\n";
		else
			cout << "no solution\n";

		nBoards--;
	}

	return 0;
}