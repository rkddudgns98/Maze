#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
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
	{1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
	{1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1},
	{1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1},
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
	if ((x > 0 && x < 2 * MAZE_SIZE) && (y > 0 && y < MAZE_SIZE))	//�ⱸ
		return 1;
	else
		return 0;

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

//recording
void Record(int x, int y)
{
	static int index = 0;
	rec[index++] = x;
	rec[index++] = y;
}

//�� ����
int DelPath(int i, int j)
{
	int k = i;

	while (rec[j] >= 0)
	{
		rec[i++] = rec[j++];
	}
	rec[i] = -1;

	return k;
}

//Shortest Path
void ShortestPath()
{
	int i = 0, j = 0;
	while (rec[i] >= 0)
	{
		j = i + 2;
		while (rec[j] >= 0)
		{
			if (rec[i] == rec[j] && rec[i +1] == rec[j + 1])
			{
				i=DelPath(i, j);
				break;
			}
			else
				j += 2;
		}
		i += 2;
	}
}

//�����չ�Ģ
void Right_Hand_On_Wall(int m[][MAZE_SIZE], int* x, int* y, int* dir)
{
	while (Still_In_MAZE(*x, *y))
	{
		Record(*x, *y);

		TurnRight(dir);	//��ȸ���Ѵ�

		//Player�տ� ���������� ��ȸ���� �ݺ�
		while (Wall_Ahead(maze, *x, *y, *dir))
			TurnLeft(dir);

		//��ĭ �����Ѵ�
		GoForward(x, y, *dir);
	}
}

//�޼չ�Ģ
void Left_Hand_On_Wall(int m[][MAZE_SIZE], int* x, int* y, int* dir)
{
	while (Still_In_MAZE(*x, *y))
	{
		Record(*x, *y);

		TurnLeft(dir);	//��ȸ���Ѵ�

		//Player�տ� ���������� ��ȸ���� �ݺ�
		while (Wall_Ahead(maze, *x, *y, *dir))
			TurnRight(dir);

		//��ĭ �����Ѵ�
		GoForward(x, y, *dir);
	}
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
void PrintPlayer(int *x,int *y)
{
	static int indexP = 0;

	*x = rec[indexP++];
	*y = rec[indexP++];

	GotoXY(2 * *x, *y);
	printf("��");
}

int main()
{
	//Player�� x,y��ǥ, ����
	int px = sx, py = sy, dir = LEFT;

	rec = (int*)calloc(MAZE_SIZE * MAZE_SIZE, sizeof(int));

	Right_Hand_On_Wall(maze, &px, &py, &dir);

	ShortestPath();
	
	px = sx, py = sy;

	while (Still_In_MAZE(px,py))
	{
		system("cls");

		PrintMaze();

		PrintPlayer(&px,&py);

		Sleep(50);
	}
	
	free (rec);

	return 0;
}