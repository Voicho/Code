#ifndef INFO_H
#define INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_DISCOUNT_LEN 30

extern int CurrentCnt;  //全局变量，存储当前商品的数量

typedef struct info  //商品信息结构的定义
{
	char	good_id[MAX_ID_LEN];
	char	good_name[MAX_NAME_LEN];
	int		good_price;
	char	good_discount[MAX_DISCOUNT_LEN];
	int		good_amount;
	int		good_remain;
}GoodInfo;

typedef struct node  //定义商品链表的结点
{
	GoodInfo *data;
	struct node *next;
}GoodList;

bool check_nullfile(void);
int assign_memory(GoodList **p);
int read_word(char str[], int lenth);
int fread_word(FILE *fp, char str[], int lenth);
int read_data(FILE *fp, GoodList *p);
int input_data(GoodList *p);
int write_data(FILE *fp, GoodList *p);

#endif