#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"
#include "function.h"

void info_init(GoodList **L)  //读取商品文件goodinfo.txt的内容,并建立链表L
{
	bool is_first = true;
	bool res = check_nullfile();  //1.判断goodinfo.txt是否存在，不存在则新建一个goodinfo.txt

	*L = NULL;
	FILE *fp = fopen("goodinfo.txt","r");
	GoodList *p_now = NULL;
	GoodList *p_before = NULL;

	while( res && !feof(fp) )  //3.然后新建链表
	{
		if(is_first)  //将*L指向第一个节点
		{
			p_now = (GoodList *)malloc(sizeof(GoodList));
			if(p_now == NULL)  //没内存就直接退了
			{
				printf("Insufficient memory\n");
				return;
			}
			p_now->data = (GoodInfo *)malloc(sizeof(GoodInfo));
			if(p_now->data == NULL)  //没内存就直接退了
			{
				printf("Insufficient memory\n");
				return;
			}
			is_first = false;
			*L = p_now;
			p_before = p_now;
			CurrentCnt++;
		}
		else  //制作链表
		{
			p_now = (GoodList *)malloc(sizeof(GoodList));
			if(p_now == NULL)  //没内存就直接退了
			{
				printf("Insufficient memory\n");
				return;
			}
			p_now->data = (GoodInfo *)malloc(sizeof(GoodInfo));
			if(p_now->data == NULL)  //没内存就直接退了
			{
				printf("Insufficient memory\n");
				return;
			}
			p_before->next = p_now;  //上一个节点p->next = 新节点p
			p_before = p_now;
			CurrentCnt++;
		}
		//2.在未达到文件尾的情况下，从文件中读取商品信息
		fread_word(fp,p_now->data->good_id,MAX_ID_LEN);
		fread_word(fp,p_now->data->good_name,MAX_NAME_LEN);
		fscanf(fp,"%d",&p_now->data->good_price);
		fread_word(fp,p_now->data->good_discount,MAX_DISCOUNT_LEN);
		fscanf(fp,"%d",&p_now->data->good_amount);
		fscanf(fp,"%d",&p_now->data->good_remain);
		fscanf(fp,"\n");
	}
	if(res)  //如果文件存在，且不为空，就将最后一节点的next指向NULL
	{
		p_now->next = NULL;
	}
	fclose(fp);

	printf("商品的链表文件已建立，有%d个商品记录\n", CurrentCnt);
}

void OutputAll(GoodList **L)  //在屏幕上输出所有商品信息
{
	GoodList *p_now = *L;

	printf("OutputAll\n");
	if(*L == NULL)  //空链表特殊处理
	{
		printf("NO DATA\n");
	}
	while(p_now != NULL)  //1.对链表内容进行读取，然后输出商品信息
	{
		Goodprint(p_now);
		p_now = p_now->next;
	}
}

void info_change(GoodList **L)  //修改一条商品记录
{
	bool repeat = false;
	GoodList *p_now = *L;
	char good_name[MAX_NAME_LEN];
	printf("info_change\n");

	if(*L == NULL)  //如果是个空链表，直接弹回去，免得崩掉
	{
		printf("NO DATA\n");
		return;
	}
	printf("Input good_name: ");  //1.输入商品的名称，如果名称存在则打印商品信息
	read_word(good_name,MAX_NAME_LEN);
	while(p_now != NULL)
	{
		if(strcmp(good_name,p_now->data->good_name) == 0)
		{
			repeat = true;
			break;
		}
		p_now = p_now->next;
	}

	if(repeat)  //2.然后用户输入新的商品信息
	{
		Goodprint(p_now);
		printf("Input product id: ");
		read_word(p_now->data->good_id,MAX_ID_LEN);
		printf("Input product name: ");
		read_word(p_now->data->good_name,MAX_NAME_LEN);
		printf("Input product price: ");
		scanf("%d",&p_now->data->good_price);
		printf("Input product discount: ");
		read_word(p_now->data->good_discount,MAX_DISCOUNT_LEN);
		printf("Input product amount: ");
		scanf("%d",&p_now->data->good_amount);
		printf("Input product remain: ");
		scanf("%d",&p_now->data->good_remain);
		printf("Change successfully");  //3.如果要修改的商品存在并且信息输入结束后则出现修改成功并且重新打印出软件选择界面
	}
	else
	{
		printf("Name does not exsist.\n");
	}
}

void info_insert(GoodList **L)  //添加一条商品记录
{
	int position = 0, i=0;
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	GoodList *p_new = NULL;  //新建节点存数据
	printf("info_insert\n");

	p_new = (GoodList *)malloc(sizeof(GoodList));
	if(p_new == NULL)  //没内存就直接退了
	{
		printf("Insufficient memory\n");
		return;
	}
	p_new->data = (GoodInfo *)malloc(sizeof(GoodInfo));
	if(p_new->data == NULL)  //没内存就直接退了
	{
		printf("Insufficient memory\n");
		return;
	}
	p_new->next = NULL;
	//1.接收输入的某一条商品的信息，包括ID、名称、价格、折扣、数量、剩余
	printf("Input product id: ");
	read_word(p_new->data->good_id,MAX_ID_LEN);
	printf("Input product name: ");
	read_word(p_new->data->good_name,MAX_NAME_LEN);
	printf("Input product price: ");
	scanf("%d",&p_new->data->good_price);
	printf("Input product discount: ");
	read_word(p_new->data->good_discount,MAX_DISCOUNT_LEN);
	printf("Input product amount: ");
	scanf("%d",&p_new->data->good_amount);
	printf("Input product remain: ");
	scanf("%d",&p_new->data->good_remain);

	while(p_now != NULL)  //4.ID号在插入的时候需要进行查重，如果已经有该ID号了，提示重复
	{
		if(strcmp(p_new->data->good_id,p_now->data->good_id) == 0)
		{
			printf("ID repeats\n");
			break;
		}
		p_before = p_now;
		p_now = p_now->next;
	}
	//2.分别实现头插法、尾插法，中间位置插入三种，
	printf("Where to insert (0:start   %d:end   other:do not save): ",CurrentCnt);
	scanf("%d",&position);
	if(position < 0 || position > CurrentCnt)  //无效输入，把新节点删了，弹回主菜单
	{
		printf("Invalid input\n");
		free(p_new);
		p_new = NULL;
		return;
	}
	//3.然后根据用户输入的插入方式进行相应的节点位置插入
	if(*L == NULL)  //如果链表为空，特殊处理
	{
		*L = p_new;
	}
	else  //把新节点插入
	{
		if(position == 0)  //插在第一个，要改*L
		{
			p_new->next = *L;
			*L = p_new;
		}
		else  //正常插入
		{
			p_now = *L;
			for(i=0; i<position; i++)
			{
				p_before = p_now;
				p_now = p_now->next;
			}
			p_before->next = p_new;
			p_new->next = p_now;
		}
	}
	CurrentCnt++;
	printf("Insert successfully\n");

}

void info_delete(GoodList **L)  //删除一条商品记录
{
	bool repeat = false;
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	char good_name[MAX_NAME_LEN];
	printf("info_delete\n");

	if(*L == NULL)  //如果是个空链表，直接弹回去，免得崩掉
	{
		printf("NO DATA\n");
		return;
	}
	printf("Input good_name: ");  //1.输入商品的名称，并查找
	read_word(good_name,MAX_NAME_LEN);
	while(p_now != NULL)
	{
		if(strcmp(good_name,p_now->data->good_name) == 0)
		{
			repeat = true;
			break;
		}
		p_before = p_now;
		p_now = p_now->next;
	}

	if(repeat)  //如果名称存在则删除商品信息，即释放对应指针所指向的内存，并且将该指针赋值为空，然后打印出删除成功的提示
	{
		if(p_now == *L)
		{
			*L = p_now->next;
			free(p_now);
			p_now = NULL;
		}
		else
		{
			p_before->next = p_now->next; 
			free(p_now);
			p_now = NULL;
		}
		CurrentCnt--;
		printf("delete succeed");
	}
	else  //2.如果输入的商品名称不存在则出现商品不存在的提示
	{
		printf("Name does not exsist.\n");
	}
}

void info_search(GoodList **L)  //查找一条商品记录
{
	bool repeat = false;
	GoodList *p_now = *L;
	char good_name[MAX_NAME_LEN];
	printf("info_search\n");

	if(*L == NULL)  //如果是个空链表，直接弹回去，免得崩掉
	{
		printf("NO DATA\n");
		return;
	}
	//1.输入商品的名称，如果名称存在则打印商品信息
	printf("Input good_name: ");
	read_word(good_name,MAX_NAME_LEN);
	while(p_now != NULL)  //用于查名称是否存在
	{
		if(strcmp(good_name,p_now->data->good_name) == 0)
		{
			repeat = true;
			break;
		}
		p_now = p_now->next;
	}

	if(repeat)  //如果名称存在则打印商品信息
		Goodprint(p_now);
	else  //2.如果商品不存在则提示商品不存在
		printf("Name does not exsist.\n");
}

void info_flush(GoodList **L)  //将当前商品链表中的内容存入商品文件goodinfo.txt，存盘后销毁链表L
{
	int savecount = CurrentCnt;
	GoodList *p_now = *L;
	FILE *fp = fopen("goodinfo.txt","w");
	printf("info_flush\n");

	while(p_now != NULL)  //1.将链表内容写入到goodinfo.txt
	{
		fprintf(fp,"%s\t",p_now->data->good_id);
		fprintf(fp,"%s\t",p_now->data->good_name);
		fprintf(fp,"%d\t",p_now->data->good_price);
		fprintf(fp,"%s\t",p_now->data->good_discount);
		fprintf(fp,"%d\t",p_now->data->good_amount);
		fprintf(fp,"%d\n",p_now->data->good_remain);
		p_now = p_now->next;
	}
	fclose(fp);
	DelAll(L);  //2.销毁链表
	CurrentCnt = 0;  //3.商品数量置0

	if(savecount != 0)
		printf("提示：%d个商品信息存入Goodinfo.txt文件\n", savecount);
	else
		printf("提示：未写入任何商品信息到Goodinfo.txt文件\n");
}

void bubble_sort(GoodList **L)  //冒泡排序实现对链表节点的排序
{
	bool is_first = true;  //字面意思，判断是否是第一次运行，用于改 *L
	GoodList *p_now = *L;  //p_before  p_now是运行中相邻的2结构的指针
	GoodList *p_before = NULL;
	GoodList *p_end = NULL;  //标记结尾，每次提前一个，bubble_sort特色
	printf("bubble_sort\n");

	if(*L == NULL)  //如果是个空链表，直接弹回去，免得崩掉
	{
		printf("NO DATA\n");
		return;
	}
	//1.采用冒泡排序对商品链表进行排序，按照价格从低到高进行排序
	//2.然后输出排序后的商品链表
	while(p_now->next != p_end)  //bubble sort 从头到尾，结尾依次提前
	{
		while(p_now->next != p_end)  //判断是否到结尾
		{
			if(p_now->data->good_price  >  p_now->next->data->good_price)  //贵的东西丢到链表尾
			{
				if(is_first)  //第一次特殊情况，要改表头
				{
					*L = p_now->next;
					p_before = p_now->next;
					p_now->next = p_now->next->next;
					p_before->next = p_now;
				}
				else  //不是表头就 交换节点顺序
				{
					p_before->next = p_now->next;
					p_before = p_now->next;
					p_now->next = p_now->next->next;
					p_before->next = p_now;
				}
			}
			else  //便宜就继续走，遍历链表
			{
				p_now = p_now->next;
				p_before = p_now;
			}
			is_first = false;  //while走过一次就不是链表头了
		}
		p_end = p_now;  //下一次循环前初始化
		p_now = *L;
		is_first = true;
	}
	printf("sort succeed\n");
}

void DelAll(GoodList **L)  //删除商品文件以及商品链表中的所有信息
{
	printf("DelAll\n");
	DestroyGoods(L);  //1.清空存储商品内容的文件
	*L = NULL;  //2.清空商品链表，销毁已有的节点，并新建一个空链表头
	CurrentCnt = 0;
}

void Goodprint(GoodList *p)  //打印单个商品链表节点的信息
{
	//1.打印单个链表商品结点的信息
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID:%-7s",p->data->good_id);
	printf("名称:%-7s",p->data->good_name);
	printf("价格:%-7d",p->data->good_price);
	printf("折扣:%-7s",p->data->good_discount);
	printf("数量:%-7d",p->data->good_amount);
	printf("剩余:%-7d\n",p->data->good_remain);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void DestroyGoods(GoodList **L)  //释放商品链表
{
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	//1.使用free函数依次free掉L的所有节点
	do{
		p_before = p_now;
		p_now = p_now->next;
		free(p_before->data);
		free(p_before);
		CurrentCnt--;
	}while(p_now != NULL);
}

int show_menu()  //菜单
{
	printf("超市管理系统\n");
	printf("****************************************\n");
	printf("1.显示所有商品的信息:\n");
	printf("2.修改某个商品的信息:\n");
	printf("3.插入某个商品的信息:\n");
	printf("4.删除某个商品的信息:\n");
	printf("5.查找某个商品的信息:\n");
	printf("6.商品存盘并退出系统:\n");
	printf("7.对商品价格进行排序:\n");
	printf("8.(慎用)删除所有类容:\n");
	printf("其他.不存盘并退出退出系统\n");
	printf("****************************************\n");
	printf("请输入你的选择: \n");
	return 0;
}

int getkey()  //扫描选项
{
	int key = 0;
	while(true)
	{
		key = getchar();
		if(key != '\n')
		{
			break;
		}
	}
	system("cls");  //清空屏幕,linux下是system("clear");
	return key;
}

int quite()  //用于不存盘退出
{
	printf("You have quited without saving\n");
	exit(0);  //直接退出
}
