#include <iostream>
#include <locale.h>

// ассемблерная вставка
short int as(char x, short int y, char z)

{
	short int v_as = 0;
	__asm 
	{

		// x = -0x7E; y = 0x4FBA; z = 0x7F, v = 0x8D
		//Вычисление знаменателя (пояснения на основе 2 теста)
		mov al, z; // z в Al, AL=7F
		cbw; //Расширение AL до AX, AX=007F
		add ax, 4; // AX=0083
		mov cx, ax; // Сохраним знаменатель в CX


		//Вычисление числителя
		mov al, x;  // x в AL, AL=-7E=82
		sub al, 2;  // x-2 в AL, AL=80
		mov bl, 7;  // 7 в BL, BL=07
		imul bl;    // AX=FC80  
		mov bx, y;  // y в  BX, BX=4FBA
		add ax, bx; // Сложение AX и BX, AX=4C3A
		cwd; // Расширение AX до двойного слова DX:AX, AX=4C3A, DX=0000
		idiv cx; // DX:AX разделим на CX, AX=0094 - частное, DX=007E - остаток
		sub ax, 7; // AX=8D
		mov v_as, ax;// Результат запишем в v_as (008D)

	}

	return v_as;

}

// ассемблерная вставка



int main() 
{

	setlocale(LC_ALL, "Russian");

	short int x1, y, z1, v, v_c, v_as; // слова
	char x,z;  // байты
	short int as(char x, short int y, char z);
	short int i = 0;

	while (i != 2)
	{
		if (i == 0)
		{
			x = -0x1; y = 0x13; z = -0x2, v = -0x8;
		}
		if (i == 1)
		{
			x = -0x7E; y = 0x4FBA; z = 0x7F, v = 0x8D;
		}
		std::cout << '\n' << '\n';
		v_c = (7 * (x - 2) + y) / (z + 4) - 7; // Вычисление выражения средствами Си
		v_as = as(x, y, z);
		std::cout << "Полученный с помощью ассемблера результат: \n" << std::dec << v_as << " (в 10-ой)  |  " << std::hex << v_as << " (в 16-ой)\n";
		std::cout << "Полученный с помощью Си результат: \n" << std::dec << v_c << " (в 10-ой)  |  " << std::hex << v_c << " (в 16-ой)\n";
		std::cout << "Теоретические значения:" << '\n' << std::dec << v << " (в 10-ой)  |  " << std::hex << v << " (в 16-ой)\n";
		std::cout << '\n' << '\n';
		i += 1;
	}

	i = 0;
	char sure;
	while (i == 0)
	{
		std::cout << "Ввести свои данные? (y/n)";
		std::cin >> sure;
		if (sure == 'y')
		{
			 std::cout << "Введите значения переменных x,y,z:";
	         std::cin >> std::hex >> x1;
	         std::cin >> std::hex >> y;
	         std::cin >> std::hex >> z1;
			 x = char(x1);
	         z = char(z1);
			 v_c = (7 * (x - 2) + y) / (z + 4) - 7; // Вычисление выражения средствами Си
			 v_as = as(x, y, z);
			 std::cout << "Полученный с помощью ассемблера результат: \n" << std::dec << v_as << " (в 10-ой)  |  " << std::hex << v_as << " (в 16-ой)\n";
			 std::cout << "Полученный с помощью Си результат: \n" << std::dec << v_c << " (в 10-ой)  |  " << std::hex << v_c << " (в 16-ой)\n";
		}
		else
		{
			i += 1;
		}

	}		



}
