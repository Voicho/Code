#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"

int CurrentCnt = 0;  //全局变量定义，存储当前商品的数量

bool check_nullfile(void)  //检查商品文件是否存在或者是否为空
{
	FILE *fp = fopen("goodinfo.txt", "r");
	if(!fp)  //file not exist
	{
		printf("商品信息初始化文件不存在！程序将为您新建一个.\n");
		FILE *fp = fopen("goodinfo.txt", "w");
		fclose(fp);
		return false;
	}
	else  //file already exist
	{
		//res for try to read file if file null feof() can't determine whether file is null or not
		int res = fscanf(fp, "%s");
		fclose(fp);
		if (res <= 0)
			return false;
		else
			return true;
	}
}

int read_word(char str[], int lenth)
{
	int ch = ' ', i = 0, n = lenth-1;
	while(ch == ' ' || ch == '\t' || ch == '\n')
		ch = getchar();
	while(ch != EOF && ch != '\t' && ch != '\n' && i < n)
	{
		str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

int fread_word(FILE *fp, char str[], int lenth)
{
	int ch = ' ', i = 0, n = lenth-1;
	while(ch == ' ' || ch == '\t' || ch == '\n')
		ch = fgetc(fp);
	while(ch != EOF && ch != '\t' && ch != '\n' && i < n)
	{
		str[i++] = ch;
		ch = fgetc(fp);
	}
	str[i] = '\0';
	return i;
}

