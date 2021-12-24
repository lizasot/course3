#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

//отрисовка объекта по айди
void drawUnit(int id)
{
	switch (id)
	{
	case 0:
		cout << " ";
		break;
	case 1:
		cout << "\x1b[32mW\x1b[37m";
		break;
	case 2:
		cout << "\x1b[33mW\x1b[37m";
		break;
	case 3:
		cout << "\x1b[32mS\x1b[37m";
		break;
	case 4:
		cout << "\x1b[33mS\x1b[37m";
		break;
	case 5:
		cout << "\x1b[32mM\x1b[37m";
		break;
	case 6:
		cout << "\x1b[33mM\x1b[37m";
		break;
	case 7:
		cout << "B";
		break;
	case 8:
		cout << "\x1b[32m*\x1b[37m";
		break;
	case 9:
		cout << "\x1b[36m~\x1b[37m";
		break;
	case 10:
		cout << "\x1b[31m*\x1b[37m";
		break;
	case 11:
		cout << "@";
		break;
	case 12:
		cout << "*";
		break;
	case 13:
		cout << "=";
		break;
	case 14:
		cout << "\x1b[36mT\x1b[37m";
		break;
	default:
		cout << "?";
		break;
	}
}
bool mute = false;

#include "composite.h"
#include "unitFactory.h"

//== Список команд == 
void moveUnit(Field& field, int id)
{
	Unit* hero = field.unitList->getUnit(id);
	bool check1 = false; //выход из подменю
	bool change = true; //выход из подменю
	do {
		char sw1 = ' ';
		check1 = true;
		sw1 = ' ';
		if (change)
		{
			system("cls");
			field.show();
			cout << "\nВыберите куда шагнуть юниту:\n";
			cout << "1 2 3\n";
			cout << "4 Х 5\n";
			cout << "6 7 8\n";
			cout << "[0] Вернуться назад\n";
		}
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw1;
		while (cin.get() != '\n') { sw1 = ' '; };

		switch (sw1)
		{
		case '1': //[1] -1 -1
			field.move(-1, -1, hero);
			break;
		case '2': //[2] 0 -1
			field.move(0, -1, hero);
			break;
		case '3': //[3] 1 -1
			field.move(1, -1, hero);
			break;
		case '4': //[1] -1 0
			field.move(-1, 0, hero);
			break;
		case '5': //[2] 1 0
			field.move(1, 0, hero);
			break;
		case '6': //[3] -1 1
			field.move(-1, 1, hero);
			break;
		case '7': //[7] 0 1
			field.move(0, 1, hero);
			break;
		case '8': //[7] 1 1
			field.move(1, 1, hero);
			break;
		case '0': //[0] Назад
			check1 = false;
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			break;
		}
	} while (check1);
}

void newField(Field& field)
{
	int x, y;
	cout << "Создайте поле размера X и Y (два целых числа):" << endl;
	cin >> x >> y;
	field.setXY(x, y);
}

Unit* createIdUnit(int sw)
{
	RoleUnitFactory newUnit;

	WShieldFactory shield;
	WAssasinFactory assasin;
	SHunterFactory hunter;
	SSnipernFactory sniper;
	MSummonerFactory summoner;
	MWizardFactory wizard;
	Unit* p = 0;
	switch (sw)
	{
	case 1: //[1] Щитовик
		p = newUnit.createUnits(shield);
		break;
	case 2: //[2] Ассасин
		p = (newUnit.createUnits(assasin));
		break;
	case 3: //[3] Охотник
		p = (newUnit.createUnits(hunter));
		break;
	case 4: //[4] Снайпер
		p = (newUnit.createUnits(sniper));
		break;
	case 5: //[5] Призыватель
		p = (newUnit.createUnits(summoner));
		break;
	case 6: //[6] Колдун
		p = (newUnit.createUnits(wizard));
		break;
	case 7: //[7] База
		p = (newUnit.createUnits(7));
		break;
	case 8: //[8] Травка
		p = (newUnit.createUnits(8));
		break;
	case 9: //[9] Водичка
		p = (newUnit.createUnits(9));
		break;
	case 10: //[10] Огонь
		p = (newUnit.createUnits(10));
		break;
	case 11: //[11] Пёс
		p = (newUnit.createUnits(11));
		break;
	case 12: //[12] Ловушка
		p = (newUnit.createUnits(12));
		break;
	case 13: //[13] Записка
		p = (newUnit.createUnits(13));
		break;
	case 14: //[14] Телепорт
		p = (newUnit.createUnits(14));
		break;
	case 0: //[0] Назад
		break;
	default:
		break;
	}
	return p;
}

Unit* createIdUnit(int sw, int x, int y)
{
	Unit* p = createIdUnit(sw);
	p->setXY(x, y);
	return p;
}

void menuCreateUnit(UnitList*& army)
{
	bool check1 = false;
	char sw1 = ' ';
	do {
		check1 = false;
		sw1 = ' ';
		cout << "\nВыберите класс юнита:\n";
		cout << "\x1b[32m[1]\x1b[0m Щитовик\n";
		cout << "\x1b[32m[2]\x1b[0m Ассасин\n";
		cout << "\x1b[32m[3]\x1b[0m Охотник\n";
		cout << "\x1b[32m[4]\x1b[0m Снайпер\n";
		cout << "\x1b[32m[5]\x1b[0m Призыватель\n";
		cout << "\x1b[32m[6]\x1b[0m Колдун\n";
		cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw1;
		while (cin.get() != '\n') { sw1 = ' '; };

		switch (sw1)
		{
		case '1': //[1] Щитовик
			army->addUnit(createIdUnit(1));
			break;
		case '2': //[2] Ассасин
			army->addUnit(createIdUnit(2));
			break;
		case '3': //[3] Охотник
			army->addUnit(createIdUnit(3));
			break;
		case '4': //[4] Снайпер
			army->addUnit(createIdUnit(4));
			break;
		case '5': //[5] Призыватель
			army->addUnit(createIdUnit(5));
			break;
		case '6': //[6] Колдун
			army->addUnit(createIdUnit(6));
			break;
		case '0': //[0] Назад
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			check1 = true; //цикл пойдёт заново
			break;
		}
	} while (check1);
}

Unit* menuCreateUnit(UnitList*& army, int x, int y)
{
	RoleUnitFactory newUnit;

	WShieldFactory shield;
	WAssasinFactory assasin;
	SHunterFactory hunter;
	SSnipernFactory sniper;
	MSummonerFactory summoner;
	MWizardFactory wizard;
	Unit* p = 0;
	bool check1 = false;
	char sw1 = ' ';
	do {
		check1 = false;
		sw1 = ' ';
		cout << "\nВыберите класс юнита:\n";
		cout << "\x1b[32m[1]\x1b[0m Щитовик\n";
		cout << "\x1b[32m[2]\x1b[0m Ассасин\n";
		cout << "\x1b[32m[3]\x1b[0m Охотник\n";
		cout << "\x1b[32m[4]\x1b[0m Снайпер\n";
		cout << "\x1b[32m[5]\x1b[0m Призыватель\n";
		cout << "\x1b[32m[6]\x1b[0m Колдун\n";
		cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw1;
		while (cin.get() != '\n') { sw1 = ' '; };

		switch (sw1)
		{
		case '1': //[1] Щитовик
			p = newUnit.createUnits(shield);
			army->addUnit(p);
			break;
		case '2': //[2] Ассасин
			p = newUnit.createUnits(assasin);
			army->addUnit(p);
			break;
		case '3': //[3] Охотник
			p = newUnit.createUnits(hunter);
			army->addUnit(p);
			break;
		case '4': //[4] Снайпер
			p = newUnit.createUnits(sniper);
			army->addUnit(p);
			break;
		case '5': //[5] Призыватель
			p = newUnit.createUnits(summoner);
			army->addUnit(p);
			break;
		case '6': //[6] Колдун
			p = newUnit.createUnits(wizard);
			army->addUnit(p);
			break;
		case '0': //[0] Назад
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			check1 = true; //цикл пойдёт заново
			break;
		}
		(army->getUnit(army->getSize()))->setXY(x, y);
	} while (check1);
	return p;
}

void menuLandscape(Field& field)
{
	bool check1 = false;
	char sw1 = ' ';
	Grass grass;
	Water water;
	Fire fire;
	do {
		cout << endl;
		cout << "[1] Открыть интерфейс травки" << endl;
		cout << "[2] Открыть интерфейс водички" << endl;
		cout << "[3] Открыть интерфейс огонь" << endl;
		cout << "[4] Удалить объект с поля (не должно быть биомом)" << endl;
		cout << "[0] Вернуться назад" << endl;
		cout << "Введите число, чтобы выполнить нужное действие: " << endl;
		cin >> sw1;
		while (cin.get() != '\n') { sw1 = ' '; };

		switch (sw1)
		{
		case '1': //[1] Интерфейс травки
			grass.interface(field);
			break;
		case '2': //[1] Интерфейс водички
			water.interface(field);
			break;
		case '3': //[1] Интерфейс лавы
			fire.interface(field);
			break;
		case '0': //[0] Назад
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			check1 = true; //цикл пойдёт заново
			break;
		}
	} while (check1);
}

void menuCreateObj(UnitList*& list)
{
	bool check1 = false;
	char sw1 = ' ';
	int x, y;
	do {
		check1 = false;
		sw1 = ' ';
		cout << "\nВыберите объект:\n";
		cout << "\x1b[32m[1]\x1b[0m Телепорт\n";
		cout << "\x1b[32m[2]\x1b[0m Записка\n";
		cout << "\x1b[32m[3]\x1b[0m Собакен\n";
		cout << "\x1b[32m[4]\x1b[0m Ловушка\n";
		cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw1;
		while (cin.get() != '\n') { sw1 = ' '; };

		switch (sw1)
		{
		case '1': //[1] Телепорт
			cout << "Введите координаты: " << endl;
			cin >> x >> y;
			list->addUnit(createIdUnit(14, x, y));
			break;
		case '2': //[2] Записка
			cout << "Введите координаты: " << endl;
			cin >> x >> y;
			list->addUnit(createIdUnit(13, x, y));
			break;
		case '3': //[3] Собакен
			cout << "Введите координаты: " << endl;
			cin >> x >> y;
			list->addUnit(createIdUnit(11, x, y));
			break;
		case '4': //[4] Ловушка
			cout << "Введите координаты: " << endl;
			cin >> x >> y;
			list->addUnit(createIdUnit(12, x, y));
			break;
		case '0': //[0] Назад
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			check1 = true; //цикл пойдёт заново
			break;
		}
	} while (check1);
}

int main()
{
	setlocale(0, "");

	Field f1;
	newField(f1);
	bool check = true; //выход из меню
	bool check1 = false; //выход из подменю
	Field f2 = f1;
	UnitList* army = f1.unitList;
	UnitList* base = f1.baseList;


	//false - заканчивает цикл, приводя непосредственно к выходу
	do {
		f1.show();
		char sw = ' '; //переключатель главного меню
		char sw1 = ' '; //переключатель саб-меню
		int id = 0;
		cout << "\nВыберите нужный раздел: \n";
		cout << "\x1b[32m[1]\x1b[0m Добавить юнита\n";
		cout << "\x1b[32m[2]\x1b[0m Удалить юнита\n";
		cout << "\x1b[32m[3]\x1b[0m Выбрать юнита\n";
		cout << "\x1b[32m[4]\x1b[0m Сохранить текущее поле\n";
		cout << "\x1b[32m[5]\x1b[0m Вывести сохранённое поле\n";
		cout << "\x1b[32m[6]\x1b[0m Установить базу\n";
		cout << "\x1b[32m[7]\x1b[0m Создать юнита на базе\n";
		cout << "\x1b[32m[8]\x1b[0m Редактировать ландшафт\n";
		cout << "\x1b[32m[9]\x1b[0m Установить нейтральный объект\n";
		cout << "\x1b[32m[0]\x1b[0m Закрыть программу\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw;
		while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, возвращается ошибка

		switch (sw)
		{
		case '1': //[1] Добавить юнита
			system("cls");
			menuCreateUnit(army);
			break;

		case '2': //[2] Удалить юнита
			if (!army) break;
			army->info();
			cout << "\n[0] Назад" << endl;
			cout << "Выберите номер юнита, которого необходимо удалить:";
			cin >> id;
			if (!id) break;
			system("cls");
			army->deleteUnit(id);
			break;

		case '3': //[3] Выбрать юнита
			if (!army) break;
			do {
				check1 = false;
				sw1 = ' ';
				cout << endl;
				army->info();
				cout << "\n[0] Вернуться назад" << endl;
				cout << "Выберите номер юнита, которого хотите рассмотреть:" << endl;
				int id;
				cin >> id;
				if (id && army->getUnit(id))
				{
					army->getUnit(id)->outputStats();
					cout << "\x1b[32m[1]\x1b[0m Передвижение по карте\n";
					cout << "\x1b[32m[2]\x1b[0m Применить способность\n";
					cout << "\x1b[32m[3]\x1b[0m Открыть доступные взаимодействия\n";
					cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
					cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

					cin >> sw1;
					while (cin.get() != '\n') { sw1 = ' '; };

					switch (sw1)
					{
					case '1': //[1] Передвижение по карте
						moveUnit(f1, id);
						system("cls");
						break;
					case '2':
						army->getUnit(id)->ability(f1.neutralList);
						break;
					case '3':
						f1.actList(army->getUnit(id));
						break;
					case '0': //[0] Назад
						break;
					default:
						cout << "Ошибка! Пожалуйста, попробуйте снова\n";
						check1 = true; //цикл пойдёт заново
						break;
					}
				}
			} while (check1);
			break;

		case '4': //[4] Сохранить текущее поле
			mute = true;
			system("cls");
			f2.setUnitList((f1.unitList)->getClone());
			f2.setBaseList((f1.baseList)->getClone());
			f2.setLandList((f1.landList)->getClone());
			f2.setBiome(createIdUnit((f1.biome)->getRoleId()));
			cout << "Поле было сохранено!" << endl;
			mute = false;
			break;

		case '5': //[5] Вывод сохранённого поля
			system("cls");
			cout << "Ранее сохранённое поле: " << endl;
			f2.show();
			break;

		case '6': //[6] Установить базу
			cout << "Введите координаты: " << endl;
			int x, y;
			cin >> x >> y;
			base->addUnit(createIdUnit(7, x, y));
			system("cls");
			break;

		case '7': //[7] Создание юнитов (через базу)
			base->info();
			cout << "\n[0] Назад" << endl;
			cout << "Выберите базу, которая создаст юнита: ";
			cin >> id;
			if (!id) break;
			(base->getUnit(id))->addUnit(army);
			system("cls");
			break;

		case '8': //[8] Редактирование ландшафта
			menuLandscape(f1);
			system("cls");
			break;

		case '9': //[9] Установить нейтральный объект
			menuCreateObj(f1.neutralList);
			system("cls");
			break;

		case '0': //[0] Закрыть программу
			cout << "Выход из программы...\n";
			check = false; //выход из цикла
			break;
		default: //в случае, если введено что-то иное
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			break;
		}
	} while (check);
	return 0;
}