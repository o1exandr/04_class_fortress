/*
Додаткове завдання(за бажанням)
*Завдання 4.
Описати клас Fortress (Фортеця).
Для початку, напишіть клас Shooter (Стрілець), який буде містити два поля:
o	назва амуніції
o	кількість амуніції.
Стрілець  може
o	виконати дію "постріл" і витратити для цього одиницю амуніції, повідомляючи в консоль, як вона називалась;
o	здійснити дію "дати амуніцію", яка встановлюватиме назву і кількість амуніції,  отримуючи ці дані через параметри.
Стрілець має три дочірні класи: Archer (Лучник), Range (Рейнджер) та Catapult (Катапульта), які заміщають дію "постріл", доповнюючи повідомлення в консоль інформацією про те, хто саме з них вистрілив.
Перші два повинні стріляти стрілами, а катапульта - каменями.

Від перших двох породжується клас ArcherTower(Cтрілецька вежа), у якої запас амуніції має бути один (спільний) для обох: лучника і рейнджера (подумайте, який механізм множинного успадкування тут варто застосувати).

Від класів  Стрілкова Вежа і Катапульта має походити клас Fortress.
Лише в її конструкторі мають поставлятись стріли для стрілкової вежі і камені для катапульти.
Додайте до фортеці ще кілька полів - товщина стін, стан воріт у відсотках, і т. д. - на Ваше бажання та фантазію.

В кожного з полів чи методів у цій ієрархії має бути встановлений максимальний рівень захисту, і успадкування має відбуватись по найвище допустимому по захисту специфікаторові доступу.
Але таким, щоб в main() можна було виконати наступне:
створити об'єкт фортеці
вистрілити лучником(н-д 3 рази),  рейнджером(н-д, 2 рази) і  з катапульти

Отже, всього має бути 6 класів,  фінальним класом серед них є клас "Фортеця", лише один об'єкт якої буде створено.
Зверніть на це увагу - 6 класів описано, всі використовуються. Але об'єкт у всій програмі один(фортеця)
ПРИМІТКИ! Коли створюватиметься фортеця, доставте в стрілкову вежу лише 4 стріли, тоді буде явно видно, що на другий постріл рейнджеру стріл не вистачить, оскільки лучник перед тим витратив 3 із 4-х стріл.

*/

#include "stdafx.h"
#include <iostream> 
#include <string>


using namespace std;

/*
Для початку, напишіть клас Shooter (Стрілець), який буде містити два поля:
o	назва амуніції
o	кількість амуніції.
*/
class Shooter
{
protected:

	string nameAmmunition;
	int qtyAmmunition;

public:

	Shooter(string nameAmmunition = "weapon", int qtyAmmunition = 1):nameAmmunition(nameAmmunition), qtyAmmunition(qtyAmmunition)
	{}

	void shoot()
	{
		if (qtyAmmunition < 1)
			cout << "not have ammunition\n";
		else
		{
			--qtyAmmunition;
			cout << "shoot by " << nameAmmunition << ", remains: " << qtyAmmunition << endl;
		}
	}

	void setAmmunition(string name, int qty)
	{
		nameAmmunition = name;
		qtyAmmunition = qty;
	}
};

/*
Стрілець має три дочірні класи: 
 - Archer (Лучник), 
 - Range (Рейнджер), 
 - Catapult (Катапульта), 
які заміщають дію "постріл", доповнюючи повідомлення в консоль інформацією про те, хто саме з них вистрілив.
Перші два повинні стріляти стрілами, а катапульта - каменями.
*/

//Archer (Лучник)
class Archer: virtual public Shooter
{

public:

	Archer(string nameAmmunition = "arrow", int qtyAmmunition = 1)
	{
		Archer::setAmmunition(nameAmmunition, qtyAmmunition);
	}

	void shoot()
	{
		cout << "Archer: ";
		Shooter::shoot();
	}
};

//Range (Рейнджер)
class Range : virtual public Shooter
{

public:

	Range(string nameAmmunition = "arrow", int qtyAmmunition = 1)
	{
		Range::setAmmunition(nameAmmunition, qtyAmmunition);
	}

	void shoot()
	{
		cout << "Range: ";
		Shooter::shoot();
	}
};

//Catapult(Катапульта)
class Catapult : public Shooter
{

public:

	Catapult(string nameAmmunition = "stone", int qtyAmmunition = 1)
	{
		Catapult::setAmmunition(nameAmmunition, qtyAmmunition);
	}

	void shoot()
	{
		cout << "Catapult: ";
		Shooter::shoot();
	}
};

/*
Від перших двох породжується клас ArcherTower(Cтрілецька вежа), 
у якої запас амуніції має бути один (спільний) для обох: лучника і рейнджера 
(подумайте, який механізм множинного успадкування тут варто застосувати).
*/
class ArcherTower : public Archer, public Range
{

public:

	ArcherTower(string nameAmmunition = "arrow", int qtyAmmunition = 1)
	{
	}

	void shoot()
	{
		cout << "ArcherTower: ";
		Shooter::shoot();
	}

};

/*
Від класів  Стрілкова Вежа і Катапульта має походити клас Fortress.
Лише в її конструкторі мають поставлятись стріли для стрілкової вежі і камені для катапульти.
Додайте до фортеці ще кілька полів - товщина стін, стан воріт у відсотках, і т. д. - на Ваше бажання та фантазію.
*/
class Fortress : public ArcherTower, public Catapult
{
protected:

	int wall_thickness = 10;
	int health_gate = 100;

public:

	Fortress(int qtyAmmunArrow = 1, int qtyAmmunStone = 1)
	{
		ArcherTower::qtyAmmunition = qtyAmmunArrow;
		Catapult::qtyAmmunition = qtyAmmunStone;
	}

};



int main()
{
	Fortress f(4, 6); //4 стріли і 6 каменів

	f.Archer::shoot();
	f.Archer::shoot();
	f.Archer::shoot();

	f.Range::shoot();
	f.Range::shoot(); //на цьому пострілі стріл вже немає

	f.Catapult::shoot();
	f.Catapult::shoot();


	cout << endl;
	system("pause");
	return 0;
}

