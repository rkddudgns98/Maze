#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAZE_SIZE 19
#define MOUSE 2

#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8

int* rec;
int sx = MAZE_SIZE - 1;
int sy = MAZE_SIZE - 2;


//미로 선언
int maze[MAZE_SIZE][MAZE_SIZE] =
{	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
	{1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//좌표 설정 함수
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitPlayer()
{
	int dir = LEFT;
	int px = sx;
	int py = sy;
}

void RightHand(int* px, int* py, int& dir)
{

}

void GoForward(int* px, int* py, int& dir)
{
	
}

void ShortestPath()
{

}

//미로 출력
void PrintMaze()
{
	for (int x = 0; x < MAZE_SIZE; x++)
	{
		for (int y = 0; y < MAZE_SIZE; y++)
		{
			if (maze[y][x] == 1)
			{
				GotoXY( 2*x, y);
				printf("■");
			}
		}
	}
}

//플레이어 출력
void PrintPlayer()
{
	GotoXY(2*sx, sy);
	printf("☆");
}

int main()
{
	while (1)
	{
		system("cls");

		PrintMaze();

		PrintPlayer();

		Sleep(50);
	}

	return 0;
}