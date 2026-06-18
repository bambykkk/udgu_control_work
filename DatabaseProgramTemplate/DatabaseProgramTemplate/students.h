#pragma once

struct Student
{
	char id[11]; //типо номер зачётной книжки
	char fam[15];
	char name[12];
	char otchestvo[13];
	char shifrGrup[15];
	char shifrSpecialnosti[8];
	bool statusStud; // отчислен или нет
	Student* next; //указатель на следующий элемент списка
};