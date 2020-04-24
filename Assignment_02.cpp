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
//시작 x,y좌표
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

//좌표 설정 함수
void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//미로인지 아닌지
int Still_In_MAZE(int x, int y)
{
	if ((x > 0 && x < 2 * MAZE_SIZE) && (y > 0 && y < MAZE_SIZE))	//출구
		return 1;
	else
		return 0;

}

//해당 방향이 벽인지 아닌지
int Wall_Ahead(int m[][MAZE_SIZE], int x, int y, int dir)
{
	x = (dir == LEFT) ? --x : (dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y : (dir == DOWN) ? ++y : y;

	return m[y][x];
}

//방향전환
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

//한칸전진
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

//길 삭제
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

//오른손법칙
void Right_Hand_On_Wall(int m[][MAZE_SIZE], int* x, int* y, int* dir)
{
	while (Still_In_MAZE(*x, *y))
	{
		Record(*x, *y);

		TurnRight(dir);	//우회전한다

		//Player앞에 벽이있으면 좌회전을 반복
		while (Wall_Ahead(maze, *x, *y, *dir))
			TurnLeft(dir);

		//한칸 전진한다
		GoForward(x, y, *dir);
	}
}

//왼손법칙
void Left_Hand_On_Wall(int m[][MAZE_SIZE], int* x, int* y, int* dir)
{
	while (Still_In_MAZE(*x, *y))
	{
		Record(*x, *y);

		TurnLeft(dir);	//우회전한다

		//Player앞에 벽이있으면 좌회전을 반복
		while (Wall_Ahead(maze, *x, *y, *dir))
			TurnRight(dir);

		//한칸 전진한다
		GoForward(x, y, *dir);
	}
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
				GotoXY(2 * x, y);
				printf("■");
			}
		}
	}
}

//플레이어 출력
void PrintPlayer(int *x,int *y)
{
	static int indexP = 0;

	*x = rec[indexP++];
	*y = rec[indexP++];

	GotoXY(2 * *x, *y);
	printf("☆");
}

int main()
{
	//Player의 x,y좌표, 방향
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