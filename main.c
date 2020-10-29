#include "header.h"
int main()
{
	manage L;
	FILE *in;
	int i;
	L.head = NULL;
	L.tail = NULL;
	L.count = 0;
	tables arr[15];
	int flag = 0;
	Manot* mana = NULL;
	Manot* new_mana = NULL;
	char input, buffer[100], func;
	int order_count, new_quant, table_order, quantity;
	in = fopen("Instructions.txt", "rt");//opent the file that we want to get data.
	if (in == NULL)
		Error_Msg("eror open the file");
	printf("welcome to the resturant\n------------------------\n");
	tafrit();//function that show what each function should done.
	input = getch();//get from the zero for the kelet.
	putch(input);
	fseek(in, 0L, SEEK_SET);//initialization the pointer of the file to the start.
	for (i = 0; i < table; i++)
	{
		arr[i].head = NULL;
		arr[i].bill = 0;
	}
	while (fscanf(in, "%c", &func) != EOF)//get the function that we eant to use from the file.
	{
		zero_input(input);
		if (func != '1')
		{
			fscanf(in, "%c", &func);
		}
		if (func <'1' || func > '5')//if thr kelet is error 
		{
			printf("\n\neror kelet bye bye\n");
			break;
		}

		switch (func)
		{
		case '1':printf("\t one");
			CreateProducts_1(&L, new_mana);
			printf("\nplease enter 0 again:");
			input = getch();
			putch(input);
			break;
		case '2':printf("\t two");
			fscanf(in, " %s%d", buffer, &new_quant);
			AddItem_2(&L, new_quant, buffer);
			printf("\nplease enter 0 again:");
			flag = 0;
			input = getch();
			putch(input);
			break;
		case '3':printf("\t three");
			fscanf(in, " %d%s%d", &table_order, buffer, &order_count);
			OrderItem_3(table_order, buffer, order_count, &L, arr, mana);
			printf("\nplease enter 0 again:");
			flag = 0;
			input = getch();
			putch(input);
			break;
		case '4':printf("\t four");
			fscanf(in, " %d%s%d", &table_order, buffer, &quantity);
			Remove_Item_4(table_order, buffer, quantity, arr, &L);
			printf("\nplease enter 0 again:");
			flag = 0;
			input = getch();
			putch(input);
			break;
		case '5': printf("\t five");
			fscanf(in, " %d", &table_order);
			remove_table_5(arr, table_order);
			flag = 0;
			printf("\nplease enter 0 again:");
			input = getch();
			putch(input);
			break;
		default:
			printf("not in the list from 1-5");
			flag = 0;
			input = getch();
			putch(input);
			break;
		}
	}
	fclose(in);
	//free all dynamic allocation.
	free(&new_mana->ProductName);
	free(new_mana);
	free(&mana->ProductName);
	free(mana);
	//initialization data.
	input = NULL;
	new_quant = 0;
	order_count = 0;
	quantity = 0;
	table_order = 0;
	input = '\0';
	func = '\0';
	Delete_kitchen(&L);//function that delete all the manot in the kitchen.
	Delete_tables(arr);//delete all the tables.
	return 0;
}






