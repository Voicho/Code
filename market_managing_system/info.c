#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"

int CurrentCnt = 0;  //全局变量定义，存储当前商品的数量

bool check_nullfile(void)  //检查商品文件是否存在或者是否为空
{
	FILE *fp = fopen("goodinfo.txt", "r");\
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
		int res = fgetc(fp);
		fclose(fp);
		if (res <= 0)
			return false;
		else
			return true;
	}
}

int assign_memory(GoodList **p)
{
	*p = (GoodList *)malloc(sizeof(GoodList));
	if(*p == NULL)  //没内存就直接退了
	{
		printf("Insufficient memory\n");
		exit(0);
	}
	(*p)->data = (GoodInfo *)malloc(sizeof(GoodInfo));
	if((*p)->data == NULL)  //没内存就直接退了
	{
		printf("Insufficient memory\n");
		exit(0);
	}
	(*p)->next = NULL;
	return 0;
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

int read_data(FILE *fp, GoodList *p)
{
	fread_word(fp,p->data->good_id,MAX_ID_LEN);
	fread_word(fp,p->data->good_name,MAX_NAME_LEN);
	fscanf(fp,"%d",&p->data->good_price);
	fread_word(fp,p->data->good_discount,MAX_DISCOUNT_LEN);
	fscanf(fp,"%d",&p->data->good_amount);
	fscanf(fp,"%d",&p->data->good_remain);
	fscanf(fp,"\n");
	return 0;
}

int input_data(GoodList *p)
{
	printf("Input product id: ");
	read_word(p->data->good_id,MAX_ID_LEN);
	printf("Input product name: ");
	read_word(p->data->good_name,MAX_NAME_LEN);
	printf("Input product price: ");
	scanf("%d",&p->data->good_price);
	printf("Input product discount: ");
	read_word(p->data->good_discount,MAX_DISCOUNT_LEN);
	printf("Input product amount: ");
	scanf("%d",&p->data->good_amount);
	printf("Input product remain: ");
	scanf("%d",&p->data->good_remain);
	return 0;
}

int write_data(FILE *fp, GoodList *p)
{
	fprintf(fp,"%s\t",p->data->good_id);
	fprintf(fp,"%s\t",p->data->good_name);
	fprintf(fp,"%d\t",p->data->good_price);
	fprintf(fp,"%s\t",p->data->good_discount);
	fprintf(fp,"%d\t",p->data->good_amount);
	fprintf(fp,"%d\n",p->data->good_remain);
	return 0;
}
