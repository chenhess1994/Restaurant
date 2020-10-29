#include "header.h"

void Error_Msg(char*msg)//func that print eror message.
{
	printf("\n%s", msg);
	exit(1);
}
void tafrit()//function that show what each function should done.
{
	printf("\n1->CreateProducts\n2->AddItems\n3->OrderItem\n4->RemoveItem\n5->RemoveTable\nplease enter nubmer 0 first: ");
}
char zero_input(char input)//function that get the data from the user and check if it was 0.
{
	while (input != '0')
	{
		input = getch();
		putch(input);
		printf("\n");
	}
	return input;
}
void CreateProducts_1(manage* l, Manot* new_mana)//function that create linkes list from the file manot.txt .
{
	l->head = NULL;
	char buffer[100];
	FILE* ma;
	l->count = 0;
	int temp_quantty;
	float temp_price;
	char prim;
	ma = fopen("Manot.txt", "rt");
	if (ma == NULL)
	{
		Delete_kitchen(l);
		fclose(ma);
		Error_Msg("Memmory error!");
	}
	fseek(ma, 0L, SEEK_SET);//initialized to start of the file
	while (fscanf(ma, "%s%d%f", buffer, &temp_quantty, &temp_price) != EOF)
	{
		fscanf(ma, "%c%c", &prim, &prim);
		if (check_name(buffer, l) == 1)//check the name of mana
		{
			printf("\nerror:more than one mana in the same name please check");
			return;
		}
		else
		{
			if (temp_quantty <= 0)//check if quantity is good
			{
				printf("\nerror:not right qantity");
				return;
			}
			else
			{
				if (temp_price <= 0)//check the  price if good
				{
					printf("\nerror:not right price");
					return;
				}
				else
				{
					if (prim != 'Y' && prim != 'N')//check the primum if its Y or N
					{
						printf("\nerror:not Y or N ");
						return;
					}
					else//if we got here all good
					{
						new_mana = (Manot*)malloc(sizeof(Manot));// malloc for mana
						if (new_mana == NULL)
						{
							Delete_kitchen(l);
							fclose(ma);
							Error_Msg("Memmory error!");
						}
						new_mana->Quantity = temp_quantty;
						new_mana->price = temp_price;
						new_mana->premium = prim;
						new_mana->ProductName = (char*)malloc((strlen(buffer) + 1));//malloc for the name of mana
						if (new_mana->ProductName == NULL)
						{
							Delete_kitchen(l);
							fclose(ma);
							Error_Msg("eror open the file");
						}
						strcpy(new_mana->ProductName, buffer);
						if (l->head == NULL)
						{
							l->head = l->tail = new_mana;
							l->tail->next = NULL;
						}
						else
						{
							new_mana->next = l->head;
							l->head = new_mana;
						}
						l->count++;
					}
				}
			}
		}
	}
	printf("\ncount of manot: %d\n", l->count);
	printf("the manot was input sucssecly :) \n");
	fclose(ma);
}
void AddItem_2(manage* l, int new_quantity, char* name_mana)//function that add inventory to exist mana.
{
	FILE* ma;
	int old_q = 0;
	PManot temp_head = l->head;
	ma = fopen("Manot.txt", "rt");
	if (ma == NULL)
	{
		Delete_kitchen(l);
		fclose(ma);
		Error_Msg("eror open the file");
	}
	fseek(ma, 0L, SEEK_SET);
	while (l->head != NULL)
	{
		if (check_name(name_mana, l) == 0)//check if mana exsist
		{
			printf("\nerror:not found this name");
			return;
		}
		else
		{
			if (new_quantity <= 0)//check if quantity is good
			{
				printf("\nerror:not right qantity");
				return;
			}
			else
			{	
				if (strcmp(temp_head->ProductName, name_mana) == 0)//check if the name mana is the same string to temp_head->ProductName
				{
					old_q = temp_head->Quantity;//old quantity
					temp_head->Quantity = old_q + new_quantity;//the new quantity
					break;
				}
				temp_head = temp_head->next;// go to the next list
			}
		}
	}
	printf("\nname:%s\nold count:%d\nadd to count:%d\nnew quantity:%d", name_mana, old_q, new_quantity, temp_head->Quantity);
	fclose(ma);
}
void OrderItem_3(int table_number, char* order_mana, int quantity, manage* l, tables* arr, Manot* mana)//function that order mana to the table.
{
	Manot* temp_head = l->head;
	Manot* adress, *mana_ord;
	adress = check_address(l, order_mana);//function that check the adress of the pointer on the mana in the kitchen
	if (check_name(order_mana, l) == 0)//check if the name is exist in the manot list.
	{
		printf("\nerror:the mana is not exsist");
		return;
	}
	else
	{
		if (table_number <= 0 || table_number > table)//if there are not right number of table from 1-15
		{
			printf("\nerror:the number of table is not exsist\n");
			return;
		}
		else
		{
			if (quantity > adress->Quantity || quantity < 0)//if the quantity is positive and smaller than what the kitchen have.
			{
				printf("\nerror:the quantity is bigger than what we have");
				return;
			}
			else//if we got here all good
			{
				if (arr[table_number - 1].bill == 0)//if there are not bill in the table
				{
					mana = (Manot*)malloc(sizeof(Manot));
					if (mana == NULL)
					{
						Delete_tables(arr);
						Delete_kitchen(l);
						Error_Msg("eror open the file");
					}
					mana->ProductName = (char*)malloc(strlen(order_mana) + 1);
					if (mana->ProductName == NULL)
					{
						Delete_tables(arr);
						Delete_kitchen(l);
						Error_Msg("eror open the file");
					}
					strcpy(mana->ProductName, order_mana);
					mana->Quantity = 0;//intilized the quantity
					mana->price = 0;//initlized the price
					mana->premium = adress->premium;//gice the adress to mana->premium 
					mana->Quantity += quantity;//up the quantity in the table
					adress->Quantity -= quantity;//remove quantity from the kitchen
					mana->price += (adress->price)*quantity;//up the price for mana
					mana->next = NULL;
					arr[table_number - 1].bill += (adress->price)*quantity;//calculate the bill
					arr[table_number - 1].head = mana;//pass the mana to head of the table
				}
				else
				{
					if (strcmp(order_mana, arr[table_number - 1].head->ProductName) != 0 )//if the name of mana is not in the list
					{
						mana = (Manot*)malloc(sizeof(Manot));
						if (mana == NULL)
						{
							Delete_tables(arr);
							Delete_kitchen(l);
							Error_Msg("eror open the file");
						}
						mana->ProductName = (char*)malloc(strlen(order_mana) + 1);
						if (mana->ProductName == NULL)
						{
							Delete_tables(arr);
							Delete_kitchen(l);
							Error_Msg("eror open the file");
						}
						strcpy(mana->ProductName, order_mana);
						mana->Quantity = 0;//intilized the quantity
						mana->price = 0;//initlized the price
						mana->premium = adress->premium;//gice the adress to mana->premium
						mana->Quantity += quantity;//up the quantity in the table
						adress->Quantity -= quantity;//remove quantity from the kitchen
						mana->price += (adress->price)*quantity;//up the price for mana
						mana->next = NULL;
						arr[table_number - 1].bill += (adress->price)*quantity;
						mana->next = arr[table_number - 1].head; //connect
						arr[table_number - 1].head = mana;
					}
					else//update the data in the spasific position of the array
					{
						while (arr[table_number - 1].head != NULL)
						{
							if (strcmp(order_mana, arr[table_number - 1].head->ProductName) == 0)
							{
								mana_ord = arr[table_number - 1].head;
								break;
							}
							arr[table_number - 1].head = arr[table_number - 1].head->next;
						}
						mana_ord->Quantity = mana_ord->Quantity + quantity; //add countity for table
						temp_head->Quantity = temp_head->Quantity - quantity;//remove from kitchen
						mana_ord->price = (adress->price)*quantity;//up the price for mana
						arr[table_number - 1].bill = arr[table_number - 1].bill + mana_ord->price; //calculate the bill
					}
				}
				printf("\ntable %d: %d manot %s in price per one:%.2f and until now:%.2f", table_number, quantity, order_mana, adress->price, arr[table_number - 1].bill);
			}
		}
	}
}
void Remove_Item_4(int table_num, char*productName, int quantity, tables* arr, manage* l)//function that delte specific mana from the table.
{
	Manot* count = check_address(l, productName);
	Manot* EZER = l->head;
	tables t = arr[table_num - 1];
	Manot* temp;
	Manot* temp1 ;//1 after
	int flag = 0;
	if (arr[table_num - 1].head == NULL)//check the tabke if not NULL
	{
		printf("\nerror:the table is empty");
		return;
	}
	else {
	   	 temp = arr[table_num - 1].head;//current
		 temp1 = arr[table_num - 1].head->next;//1 after
		 while (temp1!=NULL)
		 {
			 if ((strcmp(temp1->ProductName, productName) == 0))
			 {
				 break;
			 }
			 temp1 = temp1->next;
			 temp = temp->next;
		 }
		while (t.head != NULL)
		{
			if (strcmp(t.head->ProductName, productName) == 0)//serch the mana in the table
			{
				flag = 1;
				break;
			}
			t.head = t.head->next;
		}

		if (flag == 0)//if the table dosent order this mana.
		{
			printf("\nerror:there are no name of mana in this order of table %d", table_num);
			return;
		}
		else
		{
			while (EZER != NULL)//serch where the adress of the mana in the kitchen
			{
				if (strcmp(EZER->ProductName, productName) == 0)
					break;
				EZER = EZER->next;
			}
			if (strcmp(EZER->ProductName, productName) != 0)//if this pruduct dosent exist in the system.
			{
				printf("\nerror:this prouduct dosent exsist in the system");
				return;
			}
			else
			{
				if (quantity <= 0 || quantity > arr[table_num - 1].head->Quantity)//check quantity if good
				{
					printf("\nerror:there is a problem with the quantity please check");
					return;
				}
				else
				{
					if (quantity == t.head->Quantity)//if the manot that return equal to manot in the table.
					{
						printf("\nthe mana %s was deleted", t.head->ProductName);
						arr[table_num - 1].bill = arr[table_num - 1].bill - t.head->price;
						if (temp->next == NULL)//if the next is null mean the only mana in the table.
						{
							if (strcmp(temp->ProductName, productName) == 0)//check if the name is the same
							{
								free(arr[table_num-1].head->ProductName);
								free(arr[table_num-1].head);
								arr[table_num - 1].bill = 0;
								arr[table_num - 1].head = NULL;
							}
						}
						else//if there are more then one mana
						{
							temp->next = temp1->next;
							free(temp1->ProductName);
							free(temp1);
						}

					}
					else//if there are some of the manot 
					{
						temp->Quantity -= quantity;
						temp->price = temp->price - quantity*(count->price);
						arr[table_num - 1].bill = arr[table_num - 1].bill - (count->price)*quantity;
						printf("\nthe quantity of mana %s is:%d", temp->ProductName, temp->Quantity);
					}
				}
			}
		}
	}
}
void remove_table_5(tables* arr, int table_num)//function that give the table the final bill and free this table.
{
	int flag = 0;
	int i = 1;
	Manot* temp;
	if (arr[table_num - 1].bill==0)//check the tabke if free or not
	{
		printf("\nthere is no manot in the table");
		return;
	}
	else
	{
		printf("\nthe bill for table %d:\n", table_num);
		while (arr[table_num - 1].head != NULL)
		{
			printf("the mana %d:%s\n", i, arr[table_num - 1].head->ProductName);
			temp = arr[table_num - 1].head;
			arr[table_num - 1].head = arr[table_num - 1].head->next;
			if (temp->premium == 'Y')
			{
				flag = 1;
			}
			i++;
			free(temp->ProductName);
			temp->ProductName = NULL;
			free(temp);
			temp = NULL;
		}
		if (flag == 1)//if primum
		{
			printf("this table is pryimum");
			printf("\nthe payment for table %d: %.2f\n", table_num, arr[table_num - 1].bill + arr[table_num - 1].bill*0.2);
			arr[table_num - 1].bill = 0;
			printf("bye bye ;)");
		}
		else//if not primum
		{
			printf("\nthis table is  not pryimum");
			printf("\nthe payment for table %d: %.2f\n", table_num, arr[table_num - 1].bill);
			arr[table_num - 1].bill = 0;
			printf("bye bye ;)");
		}

	}
}
Manot* check_address(manage* l, char* name_mana)//check the adress of the pointer on the mana in the kitchen.
{
	Manot* head = l->head;
	if (head == NULL)
		return NULL;
	else
	{
		while (head != NULL)
		{
			if (strcmp(head->ProductName, name_mana) == 0)
				return head;

			head = head->next;
		}
	}
	return NULL;
}
int check_name(char* name, manage* l)//check if the mana exsist in the kitchen
{
	FILE* ma;
	PManot temp_head = l->head;
	ma = fopen("Manot.txt", "rt");
	if (ma == NULL)
	{
		Delete_kitchen(l);
		fclose(ma);
		Error_Msg("Memmory error!");
	}
	fseek(ma, 0L, SEEK_SET);
	if (temp_head == NULL)
	{
		return 0;
	}
	while (temp_head != NULL && ma != NULL)
	{
		if (strcmp(name, temp_head->ProductName) == 0)
			return 1;

		temp_head = temp_head->next;
	}
	return 0;
}
int check_table_if_free(manage* l, int table_number, tables* arr)//check if the table is free 
{
	int i;
	for (i = 0; i < table; i++)
	{
		if (i == table_number)
		{
			if (arr[i - 1].head != NULL)
				return 1;
		}
	}
	return 0;
}
void Delete_tables(tables* arr)//delete all the tables 
{
	char *temp;
	Manot* temp1;
	int i;

	for (i = 0; i < table; i++)//delete all the bill
	{
		arr[i].bill = 0;
	}
	for (i = 0; i < table; i++)//delete all the  table head
	{
		while (arr[i].head != NULL)
		{
			temp = arr[i].head->ProductName;
			temp1 = arr[i].head;
			arr[i].head = arr[i].head->next;
			free(temp);//FOR NAME
			free(temp1);//FOR HEAD
		}
		if (arr[i].head == NULL)
		{
			break;
		}
	}
}
void Delete_kitchen(manage *l)//function that delete all the manot in the kitchen.
{
	Manot* temp,*temp1;
	while (l->head != NULL)
	{
		free(l->head->ProductName);
		temp = l->head->next;
		free(l->head);
		l->head = temp;
	}
	if (l->head == NULL)
		return;

	temp = NULL;
	l->tail = NULL;
	l->count = 0;
}





