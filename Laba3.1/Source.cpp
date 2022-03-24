#include"Autorization.h"
#include<Windows.h>


//Арутюнян Артур Артуровияч
//1
//Счет в банке представляет собой структуру с полями:
//номер счета, код счета, фамилия владельца, сумма на счете, дата открытия счета, вид вклада, годовой процент начисления.



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Autorization acc;

	int command = 0;

	while (!acc.Exit())
	{
		acc.Menu();
		std::cin.ignore();
		std::cin.get();
		system("cls");
	}
	return 0;
}

