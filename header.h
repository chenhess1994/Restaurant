#ifndef header
#define header
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>

#define table 15//number of tables in the resturant
typedef struct Manot {//struct of the data of mana.
	char *ProductName;
	float price;
	int Quantity;
	char premium;
	struct Manot *next;
}Manot, *PManot;
typedef struct tables//struct of the data of tables.
{
	Manot* head;
	float bill;
}tables;
typedef struct manage {
	Manot* head;
	Manot* tail;
	int count;
}manage;
void Error_Msg(char*msg);//func that print eror message.
void tafrit();//function that show what each function should done.
char zero_input(char zero);//function that get the data from the user and check if it was 0.
void CreateProducts_1(manage* l, Manot* new_mana);//function that create linkes list from the file manot.txt .
void AddItem_2(manage* l, int quantity, char* name_mana);//function that add inventory to exist mana.
void OrderItem_3(int table_number, char* order_mana, int quantity, manage* l, tables* arr, Manot* mana);//function that order mana to the table.
void Remove_Item_4(int table_num, char*productName, int quantity, tables* arr, manage* l);//function that delte specific mana from the table.
void remove_table_5(tables* arr, int table_num);//function that give the table the final bill and free this table.
int check_name(char* name, manage* l);//function that check if the mana exsist in the kitchen
int check_table_if_free(manage* l, int table_number, tables* arr);//function that chcheck if the table is free.
Manot* check_address(manage* l, char* name_mana);//function that check the adress of the pointer on the mana in the kitchen
void Delete_tables(tables* arr);//delete all the tables.
void Delete_kitchen(manage *l);//function that delete all the manot in the kitchen.
#endif





