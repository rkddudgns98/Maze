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
//���� x,y��ǥ
int sx = MAZE_SIZE - 1;
int sy = MAZE_SIZE - 2;


//�̷� ����
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

//��ǥ ���� �Լ�
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//�̷����� �ƴ���
int Still_In_MAZE(int x, int y)
{
	if (x ==0 && y==1)
		return 0;
	else
		return 1;
}

//�ش� ������ ������ �ƴ���
int Wall_Ahead(int m[][MAZE_SIZE], int x, int y, int dir)
{
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;

	return m[y][x];
}

//������ȯ
void TurnRight(int* dir)
{
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}
void TurnLeft(int* dir)
{
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}

//��ĭ����
void GoForward(int* x, int* y, int dir)
{
	*x = (dir == LEFT) ? --(*x) : (dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) : (dir == DOWN) ? ++(*y) : *y;
}

//�����չ�Ģ
void Right_Hand_On_Wall(int m[][MAZE_SIZE], int* x, int* y, int* dir)
{
	TurnRight(dir);	//��ȸ���Ѵ�

	//Player�տ� ���������� ��ȸ���� �ݺ�
	while (Wall_Ahead(maze, *x, *y, *dir))	
		TurnLeft(dir);	

	//��ĭ �����Ѵ�
	GoForward(x, y, *dir);
}

void ShortestPath()
{

}

//�̷� ���
void PrintMaze()
{
	for (int x = 0; x < MAZE_SIZE; x++)
	{
		for (int y = 0; y < MAZE_SIZE; y++)
		{
			if (maze[y][x] == 1)
			{
				GotoXY(2 * x, y);
				printf("��");
			}
		}
	}
}

//�÷��̾� ���
void PrintPlayer(int px, int py)
{
	GotoXY(2 * px, py);
	printf("��");
}

int main()
{
	//Player�� x,y��ǥ, ����
	int px = sx, py = sy, dir = LEFT;

	while (Still_In_MAZE(px,py))
	{
		system("cls");

		PrintMaze();

		PrintPlayer(px, py);

		Right_Hand_On_Wall(maze, &px, &py, &dir);
;
		Sleep(50);
	}

	return 0;
}