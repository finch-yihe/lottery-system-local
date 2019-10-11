#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define BOOM 10
#define SIZE 10
char MAP[SIZE + 2][SIZE + 2];
int visit[SIZE + 2][SIZE + 2];
int x, y;
int stemp[8][2] = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1}, {-1,1} };
void init(int a, int b) {
	int x, y;
	visit[a][b] = 0;
	for (int i = 0; i < 10; i++) {
		do {
			x = rand() % SIZE + 1;
			y = rand() % SIZE + 1;
		} while (visit[x][y] == 0);
		if (visit[x][y] == -1) {
			visit[x][y] = 0;
			MAP[x][y] = '*';
		}
	}
	for (int i = 1; i <= SIZE; i++) {
		for (int j = 1; j <= SIZE; j++) {
			if (MAP[i][j] != '*') {
				MAP[i][j] = '0';
				for (int k = 0; k < 8; k++) {
					if (MAP[i + stemp[k][0]][j + stemp[k][1]] == '*')
						MAP[i][j]++;
				}
			}
		}
	}
}
void dfs(int i, int j) {
	visit[i][j] = 1;
	for (int k = 0; k < 8; k++) {
		if (MAP[i + stemp[k][0]][j + stemp[k][1]] == '0'&&visit[i + stemp[k][0]][j + stemp[k][1]] != 1)
			dfs(i + stemp[k][0], j + stemp[k][1]);
		else if (MAP[i + stemp[k][0]][j + stemp[k][1]] != '*'&&visit[i + stemp[k][0]][j + stemp[k][1]] != 1)
			visit[i + stemp[k][0]][j + stemp[k][1]] = 1;
	}
}
int check() {
	if (MAP[x][y] == '*') {
		visit[x][y] = 1;
		return 1;
	}
	else if (MAP[x][y] == '0') {
		dfs(x, y);
	}
	else
		visit[x][y] = 1;
	int temp = 0;
	for (int i = 1; i <= SIZE; i++)
		for (int j = 1; j <= SIZE; j++) {
			if (visit[i][j] == -1)
				temp++;
		}
	if (temp == BOOM)
		return 2;
	return 0;
}
void show() {
    system("clear");
	printf("\t-------------------------------------------------\n");
	for (int i = 0; i <= SIZE + 1; i++) {
		printf("\t|");
		for (int j = 0; j <= SIZE + 1; j++) {
			if (visit[i][j] == 1) {
				printf(" %c ", MAP[i][j]);
				printf("|");
			}
			else {
				printf("   ");
				printf("|");
			}
		}
		printf("\n");
		printf("\t-------------------------------------------------\n");
	}
}
int game() {
	srand(time(0));
	memset(visit, -1, sizeof(visit));
	MAP[0][0] = ' ';
	for (int i = 1; i <= SIZE; i++) {
		MAP[0][i] = 'A' + i - 1;
		MAP[i][0] = 'a' + i - 1;
		MAP[SIZE + 1][i] = 'A' + i - 1;
		MAP[i][SIZE + 1] = 'a' + i - 1;
	}
	for (int i = 1; i <= SIZE + 1; i++) {
		visit[0][i] = 1;
		visit[i][0] = 1;
		visit[SIZE + 1][i] = 1;
		visit[i][SIZE + 1] = 1;
	}
	show();
	scanf("%d%d", &x, &y);
	init(x, y);
	memset(visit, -1, sizeof(visit));
	for (int i = 1; i <= SIZE + 1; i++) {
		visit[0][i] = 1;
		visit[i][0] = 1;
		visit[SIZE + 1][i] = 1;
		visit[i][SIZE + 1] = 1;
	}
	check();
	system("cls");
	show();
	while (MAP[x][y] != '*') {
		scanf("%d%d", &x, &y);
		int res = check();
		system("cls");
		show();
		if (res == 2) {
			printf("Win\n");
			system("pause");
			return 0;
		}
		else if (res == 1) {
			printf("Lose\n");
			system("pause");
			return 0;
		}
	}
	return 0;
}
