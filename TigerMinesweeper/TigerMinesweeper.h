#ifndef TigerMinesweeper_H
#define TigerMinesweeper_H

#define MAX_HIGHT 15
#define MAX_WIDTH 10
#define MAX_BUMB 20

int start();
int end();
int init_g_map();
int show();
char _getkey();
int judge();
int click(int i, int j);
int get_bumb_number(int i, int j, int *bumb_number);
int play();

#endif