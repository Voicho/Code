#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"
#include "function.h"

//Auther: Jim Heisenberg

//没啥好注释的，函数与变量名字说明了一切

int main()
{
	GoodList *p_head;
	info_init(&p_head);
	while(true)
	{
		show_menu();
		switch(getkey())
		{
			case '1': OutputAll(&p_head); break;
			case '2': info_change(&p_head); break;
			case '3': info_insert(&p_head); break;
			case '4': info_delete(&p_head); break;
			case '5': info_search(&p_head); break;
			case '6': info_flush(&p_head); exit(0);
			case '7': bubble_sort(&p_head); break;
			case '8': DelAll(&p_head); break;
			default: quite();
		}
	}
}
