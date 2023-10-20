#include <stdio.h>;
#include <time.h>;
#include <Windows.h>;
#include "heads.h";


const lengthOfBoard = 25;
int bodyLength = 3;
char lastMove = NULL;
int running = 1;
int interval = 500;

int main()
{
	
	int board[25][25],* pBoard = NULL;
	pBoard = &board;
	SetBoard(pBoard);

	srand(time(0));

	while (running)
	{
		ReadInput(pBoard);
		DrawBoard(pBoard);
		Sleep(interval);
	}
	system("cls");
	printf("Tvoje skore %d", bodyLength - 3);

	return 0;
}

void DrawBoard(int*pBoard)
{
	system("cls");
	
	for (size_t i = 0; i < lengthOfBoard; i++)
	{
		for (size_t j = 0; j < lengthOfBoard; j++)
		{
			if (*(pBoard + i * 25 + j) == -2)
				printf("##");
			else if (*(pBoard + i * lengthOfBoard + j) == -3)
				printf("@@");
			else if (*(pBoard + i * lengthOfBoard + j) == -1)
				printf("XX");
			else if (*(pBoard + i * lengthOfBoard + j) > 1)
				printf("OO");
			else
				printf("  ");
		}printf("\n");
	}
}

void SetBoard(int* pBoard)
{	
	for (int i = 0; i < lengthOfBoard; i++)
	{
		for (int j = 0; j < lengthOfBoard; j++)
		{
			if (i == 0 || i == lengthOfBoard - 1 || j == 0 || j == lengthOfBoard - 1)
				*(pBoard + i * lengthOfBoard + j) = -2;
			else
				*(pBoard + i * lengthOfBoard + j) = 0;
		}
	}
	*(pBoard + 12 * lengthOfBoard + 12) = -3;

	GenerateFood(pBoard);
}

void ReadInput(int * pBoard)
{
	int* pLastPos=pBoard;

	if (kbhit()) {
		char ch = getch();
		if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd')
			lastMove = ch;
	}
		
	

		for (int i = 0; i < lengthOfBoard; i++)
		{
			for (int j = 0; j < lengthOfBoard; j++)
			{
				if (*(pBoard + i * lengthOfBoard + j) > 0)
				{

					*(pBoard + i * lengthOfBoard + j) -= 1;
				}
				if (*(pBoard + i * lengthOfBoard + j) == -3) {
					pLastPos = (pBoard + i * lengthOfBoard + j);
					*(pBoard + i * lengthOfBoard + j) = bodyLength;
				}
			}
		}
		

		switch (lastMove)
		{
		case 'w':
			MoveSnake(pLastPos,-25,pBoard);
			break;
		case 's':
			MoveSnake(pLastPos, 25,pBoard);
			break;
		case 'a':
			MoveSnake(pLastPos, -1, pBoard);
			break;
		case 'd':
			MoveSnake(pLastPos, 1, pBoard);
			break;

		default:*(pLastPos) = -3;
			break;
		}

	
}
void MoveSnake(int* pLastPos, int distance, int*pBoard)
{
	switch (*(pLastPos + distance))
	{
	default:

	case -2:
		running = 0;
		break;
	case -1:
		bodyLength++;
		if (interval > 200)
			interval -= 50;
		GenerateFood(pBoard);
	case 0:
		*(pLastPos + distance) = -3;
		break;
	}
	
}

void GenerateFood(int* pBoard)
{
	int x, y;
	do
	{
		x = abs(rand()) % 25;
		y = abs(rand()) % 25;
	} while (*(pBoard + x * lengthOfBoard + y) !=0);

	*(pBoard + x * lengthOfBoard + y) = -1;
}