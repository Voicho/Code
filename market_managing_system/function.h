#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void Goodprint(GoodList *p);   //模板标准函数
void DestroyGoods(GoodList **L);
void DelAll(GoodList **L);
void info_init(GoodList **L);
void info_flush(GoodList **L);
void OutputAll(GoodList **L);
void info_insert(GoodList **L);
void info_delete(GoodList **L);
void info_search(GoodList **L);
void info_change(GoodList **L);
void bubble_sort(GoodList **L);

int show_menu();  //显示菜单
int getkey();  //接受键盘上一个按键，清空屏幕，返回ASCII
int quite();  //不存盘退出

#endif