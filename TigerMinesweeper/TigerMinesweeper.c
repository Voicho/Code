#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "TigerMinesweeper.h"

int g_i = MAX_HIGHT/2;
int g_j = MAX_WIDTH/2;
int g_dead= 0;
int g_win = 0;
int g_first_click = 1;
char gkey;
char g_map[MAX_HIGHT+2][MAX_WIDTH+2];

int start()
{
	printf("GAME START\n");
	printf("press asdw to move\n");
	printf("press x to click\n");
	printf("press q to exit\n");
	return 0;
}

int end()
{
	show();
	printf("GAME OVER\n");
	if(g_win)
		printf("YOU WIN\n");
	else
		printf("YOU LOSE\n");
	system("pause");
	return 0;
}

int init_g_map()  //-1边界 0-8揭示后雷数 9未揭示的雷 10为未揭示无雷
{
	int i=0, j=0, k=0;
	srand((unsigned)time(NULL));
	for (i=0; i<MAX_HIGHT+2; i++)
	{
		for (j=0; j<MAX_WIDTH+2; j++)
		{
			if(i==0 || i==MAX_HIGHT+1 || j==0 || j==MAX_WIDTH+1)
			{
				g_map[i][j] = -1;
			}
			else
			{
				g_map[i][j] = 10;
			}
		}
	}
	while(k<MAX_BUMB)
	{
		i = rand() % MAX_HIGHT +1;
		j = rand() % MAX_WIDTH +1;
		if(g_map[i][j] == 9)
		{
			continue;
		}
		g_map[i][j] = 9;
		k++;
	}
	return 0;
}

int show()
{
	int i=0, j=0, k=0;
	for(i=0; i<MAX_HIGHT+2; i++)
	{
		for(j=0; j<MAX_WIDTH+2; j++)
		{
			if(g_i==i && g_j==j)
				printf("[");
			else
				printf(" ");
			{  //show content
				if(g_map[i][j] == -1)
				{
					printf("#");
				}
				else if(g_map[i][j] == 9)
				{
					if(g_dead==1 || g_win==1)
						printf("X");
					else
						printf(" ");
				}
				else if(g_map[i][j] == 10)
				{
					printf(" ");
				}
				else
				{
					printf("%d",g_map[i][j]);
				}
			}
			if(g_i==i && g_j==j)
				printf("]");
			else
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}

char _getkey()
{
	while(kbhit())
		getch();
	gkey = getch();
	return gkey;
}

int judge()
{
	int i,j;
	if(gkey == 'x')
	{
		if(g_first_click && g_map[g_i][g_j]==9)
		{
			init_g_map();
			judge();
		}
		g_first_click = 0;
		click(g_i,g_j);
		g_win=1;
		for(i=0; i<MAX_HIGHT+2; i++)
		{
			for(j=0; j<MAX_WIDTH+2; j++)
			{
				if(g_map[i][j] == 10)
					g_win = 0;
			}
		}
	}
	else if(gkey == 'q')
		exit(0);
	else if(gkey =='a')
	{
		if(g_map[g_i][g_j-1] != -1)
			g_j--;
	}
	else if (gkey =='s')
	{
		if(g_map[g_i+1][g_j] != -1)
			g_i++;
	}
	else if (gkey =='d')
	{
		if(g_map[g_i][g_j+1] != -1)
			g_j++;
	}
	else if (gkey =='w')
	{
		if(g_map[g_i-1][g_j] != -1)
			g_i--;
	}
	return 0;
}

int click(int i, int j)
{
	int _i,_j,bumb_number=0;
	if(g_map[i][j]==9)
	{
		g_dead = 1;
		return 0;
	}
	else if(g_map[i][j]==-1)
	{
		return 0;
	}
	else
	{
		get_bumb_number(i,j,&bumb_number);
		g_map[i][j] = bumb_number;
	}

	if(bumb_number == 0)
	{
		for(_i=i-1;_i<=i+1;_i++)
		{
			for(_j=j-1;_j<=j+1;_j++)
			{
				if(g_map[_i][_j]==10)
					click(_i,_j);
			}
		}
	}

	return 0;
}

int get_bumb_number(int i, int j, int *bumb_number)
{
	int _i,_j;
	for(_i=i-1;_i<=i+1;_i++)
	{
		for(_j=j-1;_j<=j+1;_j++)
		{
			if(g_map[_i][_j]==9)
				(*bumb_number)++;
		}
	}
	return 0;
}

int play()
{
	init_g_map();
	start();
	while(1)
	{
		show();
		_getkey();
		judge();
		system("cls");
		if(g_dead==1 || g_win==1)
		{
			break;
		}
	}
	end();
	return 0;
}

int main(int argc, char const *argv[])
{
	play();
	return 0;
}
