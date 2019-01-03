#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"
#include "function.h"

void info_init(GoodList **L)  //��ȡ��Ʒ�ļ�goodinfo.txt������,����������L
{
	bool res = check_nullfile();  //1.�ж�goodinfo.txt�Ƿ���ڣ����������½�һ��goodinfo.txt
	FILE *fp = fopen("goodinfo.txt","r");
	GoodList *p_now = NULL;
	GoodList *p_before = NULL;
	*L = NULL;

	while( res && !feof(fp) )  //3.Ȼ���½�����
	{
		assign_memory(&p_now);
		if(*L == NULL)  //��*Lָ���һ���ڵ�
		{
			*L = p_now;
			p_before = p_now;
		}
		else  //��������
		{
			p_before->next = p_now;  //��һ���ڵ�p->next = �½ڵ�p
			p_before = p_now;
		}
		CurrentCnt++;
		read_data(fp,p_now);  //2.��δ�ﵽ�ļ�β������£����ļ��ж�ȡ��Ʒ��Ϣ
	}
	fclose(fp);
	printf("��Ʒ�������ļ��ѽ�������%d����Ʒ��¼\n", CurrentCnt);
}

void OutputAll(GoodList **L)  //����Ļ�����������Ʒ��Ϣ
{
	GoodList *p_now = *L;

	printf("OutputAll\n");
	if(*L == NULL)  //���������⴦��
	{
		printf("NO DATA\n");
	}
	while(p_now != NULL)  //1.���������ݽ��ж�ȡ��Ȼ�������Ʒ��Ϣ
	{
		Goodprint(p_now);
		p_now = p_now->next;
	}
}

void info_change(GoodList **L)  //�޸�һ����Ʒ��¼
{
	bool repeat = false;
	GoodList *p_now = *L;
	char good_name[MAX_NAME_LEN];
	printf("info_change\n");

	if(*L == NULL)  //����Ǹ�������ֱ�ӵ���ȥ����ñ���
	{
		printf("NO DATA\n");
		return;
	}
	printf("Input good_name: ");  //1.������Ʒ�����ƣ�������ƴ������ӡ��Ʒ��Ϣ
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
	if(repeat)  //2.Ȼ���û������µ���Ʒ��Ϣ
	{
		Goodprint(p_now);
		input_data(p_now);
		printf("Change successfully");  //3.���Ҫ�޸ĵ���Ʒ���ڲ�����Ϣ���������������޸ĳɹ��������´�ӡ�����ѡ�����
	}
	else
	{
		printf("Name does not exsist.\n");
	}
}

void info_insert(GoodList **L)  //���һ����Ʒ��¼
{
	int position = 0, i=0;
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	GoodList *p_new = NULL;  //�½��ڵ������

	printf("info_insert\n");
	assign_memory(&p_new);
	input_data(p_new);  //1.���������ĳһ����Ʒ����Ϣ������ID�����ơ��۸��ۿۡ�������ʣ��
	while(p_now != NULL)  //4.ID���ڲ����ʱ����Ҫ���в��أ�����Ѿ��и�ID���ˣ���ʾ�ظ�
	{
		if(strcmp(p_new->data->good_id,p_now->data->good_id) == 0)
		{
			printf("ID repeats\n");
			break;
		}
		p_before = p_now;
		p_now = p_now->next;
	}
	//2.�ֱ�ʵ��ͷ�巨��β�巨���м�λ�ò������֣�
	printf("Where to insert (0:start   %d:end   other:do not save): ",CurrentCnt);
	scanf("%d",&position);
	if(position < 0 || position > CurrentCnt)  //��Ч���룬���½ڵ�ɾ�ˣ��������˵�
	{
		printf("Invalid input\n");
		free(p_new);
		p_new = NULL;
		return;
	}
	//3.Ȼ������û�����Ĳ��뷽ʽ������Ӧ�Ľڵ�λ�ò���
	if(*L == NULL)  //�������Ϊ�գ����⴦��
	{
		*L = p_new;
	}
	else  //���½ڵ����
	{
		if(position == 0)  //���ڵ�һ����Ҫ��*L
		{
			p_new->next = *L;
			*L = p_new;
		}
		else  //��������
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

void info_delete(GoodList **L)  //ɾ��һ����Ʒ��¼
{
	bool repeat = false;
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	char good_name[MAX_NAME_LEN];

	printf("info_delete\n");
	if(*L == NULL)  //����Ǹ�������ֱ�ӵ���ȥ����ñ���
	{
		printf("NO DATA\n");
		return;
	}
	printf("Input good_name: ");  //1.������Ʒ�����ƣ�������
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
	if(repeat)  //������ƴ�����ɾ����Ʒ��Ϣ�����ͷŶ�Ӧָ����ָ����ڴ棬���ҽ���ָ�븳ֵΪ�գ�Ȼ���ӡ��ɾ���ɹ�����ʾ
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
	else  //2.����������Ʒ���Ʋ������������Ʒ�����ڵ���ʾ
	{
		printf("Name does not exsist.\n");
	}
}

void info_search(GoodList **L)  //����һ����Ʒ��¼
{
	bool repeat = false;
	GoodList *p_now = *L;
	char good_name[MAX_NAME_LEN];
	printf("info_search\n");

	if(*L == NULL)  //����Ǹ�������ֱ�ӵ���ȥ����ñ���
	{
		printf("NO DATA\n");
		return;
	}
	//1.������Ʒ�����ƣ�������ƴ������ӡ��Ʒ��Ϣ
	printf("Input good_name: ");
	read_word(good_name,MAX_NAME_LEN);
	while(p_now != NULL)  //���ڲ������Ƿ����
	{
		if(strcmp(good_name,p_now->data->good_name) == 0)
		{
			repeat = true;
			break;
		}
		p_now = p_now->next;
	}
	if(repeat)  //������ƴ������ӡ��Ʒ��Ϣ
		Goodprint(p_now);
	else  //2.�����Ʒ����������ʾ��Ʒ������
		printf("Name does not exsist.\n");
}

void info_flush(GoodList **L)  //����ǰ��Ʒ�����е����ݴ�����Ʒ�ļ�goodinfo.txt�����̺���������L
{
	int savecount = CurrentCnt;
	GoodList *p_now = *L;
	FILE *fp = fopen("goodinfo.txt","w");

	printf("info_flush\n");
	while(p_now != NULL)  //1.����������д�뵽goodinfo.txt
	{
		write_data(fp,p_now);
		p_now = p_now->next;
	}
	fclose(fp);
	DestroyGoods(L);  //2.��������3.��Ʒ������0
	printf("��ʾ��%d����Ʒ��Ϣ����Goodinfo.txt�ļ�\n", savecount);
}

void bubble_sort(GoodList **L)  //ð������ʵ�ֶ�����ڵ������
{
	GoodList *p_now = *L;  //p_before  p_now�����������ڵ�2�ṹ��ָ��
	GoodList *p_before = NULL;
	GoodList *p_end = NULL;  //��ǽ�β��ÿ����ǰһ����bubble_sort��ɫ
	printf("bubble_sort\n");

	if(*L == NULL)  //����Ǹ�������ֱ�ӵ���ȥ����ñ���
	{
		printf("NO DATA\n");
		return;
	}
	//1.����ð���������Ʒ����������򣬰��ռ۸�ӵ͵��߽�������
	//2.Ȼ�������������Ʒ����
	while(p_now->next != p_end)  //bubble sort ��ͷ��β����β������ǰ
	{
		while(p_now->next != p_end)  //�ж��Ƿ񵽽�β
		{
			if(p_now->data->good_price  >  p_now->next->data->good_price)  //��Ķ�����������β
			{
				if(*L == p_now)  //��һ�����������Ҫ�ı�ͷ
				{
					*L = p_now->next;
					p_before = p_now->next;
					p_now->next = p_now->next->next;
					p_before->next = p_now;
				}
				else  //���Ǳ�ͷ�� �����ڵ�˳��
				{
					p_before->next = p_now->next;
					p_before = p_now->next;
					p_now->next = p_now->next->next;
					p_before->next = p_now;
				}
			}
			else  //���˾ͼ����ߣ���������
			{
				p_before = p_now;
				p_now = p_now->next;
			}
		}
		p_end = p_now;  //��һ��ѭ��ǰ��ʼ��
		p_now = *L;
	}
	printf("sort succeed\n");
}

void DelAll(GoodList **L)  //ɾ����Ʒ�ļ��Լ���Ʒ�����е�������Ϣ
{
	printf("DelAll\n");
	DestroyGoods(L);  //1.��մ洢��Ʒ���ݵ��ļ�
	*L = NULL;  //2.�����Ʒ�����������еĽڵ㣬���½�һ��������ͷ
	CurrentCnt = 0;
	printf("Delete succeed");
}

void Goodprint(GoodList *p)  //��ӡ������Ʒ����ڵ����Ϣ
{
	//1.��ӡ����������Ʒ������Ϣ
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID:%-7s",p->data->good_id);
	printf("����:%-7s",p->data->good_name);
	printf("�۸�:%-7d",p->data->good_price);
	printf("�ۿ�:%-7s",p->data->good_discount);
	printf("����:%-7d",p->data->good_amount);
	printf("ʣ��:%-7d\n",p->data->good_remain);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void DestroyGoods(GoodList **L)  //�ͷ���Ʒ����
{
	GoodList *p_now = *L;
	GoodList *p_before = NULL;
	//1.ʹ��free��������free��L�����нڵ�
	do{
		p_before = p_now;
		p_now = p_now->next;
		free(p_before->data);
		free(p_before);
		CurrentCnt--;
	}while(p_now != NULL);
}

int show_menu()  //�˵�
{
	printf("���й���ϵͳ\n");
	printf("****************************************\n");
	printf("1.��ʾ������Ʒ����Ϣ:\n");
	printf("2.�޸�ĳ����Ʒ����Ϣ:\n");
	printf("3.����ĳ����Ʒ����Ϣ:\n");
	printf("4.ɾ��ĳ����Ʒ����Ϣ:\n");
	printf("5.����ĳ����Ʒ����Ϣ:\n");
	printf("6.��Ʒ���̲��˳�ϵͳ:\n");
	printf("7.����Ʒ�۸��������:\n");
	printf("8.(����)ɾ����������:\n");
	printf("����.�����̲��˳��˳�ϵͳ\n");
	printf("****************************************\n");
	printf("���������ѡ��: \n");
	return 0;
}

int getkey()  //ɨ��ѡ��
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
	system("cls");  //�����Ļ,linux����system("clear");
	return key;
}

int quite()  //���ڲ������˳�
{
	printf("You have quited without saving\n");
	exit(0);  //ֱ���˳�
}
