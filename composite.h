//общий класс юнитов
class UnitList;
class Unit
{
public:
    string name;
    int x = 1, y = 1;
    virtual int getRoleId() { return 0; };
    virtual void info() {
        cout << "Unit" << endl;
    }
    virtual void outputStats() {
        cout << "\nМестоположение [X][Y]: [" << x << "][" << y << "]" << endl;
    }
    virtual void draw() {
        drawUnit(getRoleId());
    }
    void sayName() {
        cout << name << endl;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    virtual void setXY(int newX, int newY) {
        x = newX;
        y = newY;
    }
    virtual bool interact(Unit*& Unit1) { return false; }
    virtual void ability(UnitList*& list) { cout << "У этого юнита нет способности." << endl; }
    virtual bool canPass() { return true; }
    virtual bool move(int x1, int y1) {
        x += x1;
        y += y1;
        return true;
    }
    virtual void changeHp(int heal) { return; }
    virtual void die() { return; }
    virtual void effect(Unit*& obj) { return; }
    virtual void addUnit(UnitList*& list) { return; }
    virtual ~Unit() {}
};

// == Юниты ==
class Army : public Unit
{
public:
    int hp = 10,
        dmg = 5,
        speed = 1,
        mana = 1;
    int range = 1;
    virtual bool canPass() { return false; }
    virtual void changeHp(int heal)
    {
        hp += heal;
    }
    virtual void outputStats() {
        if (name != "") cout << name << endl;
        cout << "Здоровье: " << hp << endl;
        cout << "Урон: " << dmg << endl;
        cout << "Ловкость: " << speed << endl;
        cout << "Мана: " << mana << endl;
        cout << "\nМестоположение [X][Y]: [" << x << "][" << y << "]" << endl;
    }
};

class Warrior : public Army
{
public:
    virtual void info() {
        cout << "Warrior" << endl;
    }
    Warrior()
    {
        if (!mute) cout << "По-воински готов бегать по полю\n";
    }
    virtual void die()
    {
        if (!mute) cout << "По-воински умер\n";
    }
    virtual ~Warrior() {}
};

class Shooter : public Army
{
public:
    virtual void info() {
        cout << "Shooter" << endl;
    }
    Shooter()
    {
        if (!mute) cout << "По-стрелковски готов бегать по полю\n";
    }
    virtual void die()
    {
        if (!mute) cout << "По-стрелковски умер\n";
    }
    virtual ~Shooter() {}
};

class Mage : public Army
{
public:
    virtual void info() {
        cout << "Mage" << endl;
    }
    Mage()
    {
        if (!mute) cout << "По-магически готов бегать по полю\n";
    }
    virtual void die()
    {
        if (!mute) cout << "По-магически умер\n";
    }
    virtual ~Mage() {}
};

// Классы всех Воинов
class WarriorShield : public Warrior
{
    static int roleId;
public:
    void info() {
        cout << "Щитовик" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int WarriorShield::roleId = 1;

class WarriorAssasin : public Warrior
{
    static int roleId;
public:
    void info() {
        cout << "Ассасин" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int WarriorAssasin::roleId = 2;

// Классы всех Стрелков
class ShooterHunter : public Shooter
{
    static int roleId;
public:
    void info() {
        cout << "Охотник" << endl;
    }
    void setTrap(UnitList*& list);
    void ability(UnitList*& list) { setTrap(list); }
    int getRoleId() {
        return roleId;
    }
};
int ShooterHunter::roleId = 3;

class ShooterSniper : public Shooter
{
    static int roleId;
public:
    void info() {
        cout << "Снайпер" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int ShooterSniper::roleId = 4;

// Классы всех Магов
Unit* createIdUnit(int sw);
Unit* createIdUnit(int sw, int x, int y);
class MageSummoner : public Mage
{
    static int roleId;
public:
    void info() {
        cout << "Призыватель" << endl;
    }
    void summonDog(UnitList*& list);
    void ability(UnitList*& list) { summonDog(list); }
    int getRoleId() {
        return roleId;
    }
};
int MageSummoner::roleId = 5;

class MageWizard : public Mage
{
    static int roleId;
public:
    void info() {
        cout << "Колдун" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int MageWizard::roleId = 6;


//== Списки объектов ==
class UnitList
{
public:
    vector<Unit*> unitList;
    UnitList* fuse(UnitList* list) {
        UnitList* newList = list;
        size_t i;
        for (i = 0; i < unitList.size(); i++) newList->unitList.push_back(unitList[i]);
        return newList;
    }
    void info() {
        size_t i;
        for (i = 0; i < unitList.size(); ++i)
        {
            cout << i + 1 << ". ";
            unitList[i]->info();
            cout << "Местоположение: [" << unitList[i]->getX() << "][" << unitList[i]->getY() << "]" << endl;
        }
    }
    void draw() {
        size_t i;
        for (i = 0; i < unitList.size(); ++i)  unitList[i]->draw();
    }
    void sayName() {
        size_t i;
        for (i = 0; i < unitList.size(); ++i)  unitList[i]->sayName();
    }
    Unit* getUnit(int id) {
        return unitList[id - 1];
    }
    size_t getSize() {
        return unitList.size();
    }
    void addUnit(Unit* p) {
        unitList.push_back(p);
    }
    void deleteUnit(int id) {
        auto iter = unitList.cbegin();
        unitList[id - 1]->die();
        unitList.erase(iter + (id - 1));
    }
    Unit* searchXY(int x, int y)
    {
        size_t i;
        for (i = 0; i < unitList.size(); i++)
        {
            if (unitList[i]->getX() == x && unitList[i]->getY() == y)
            {
                return unitList[i];
            }
        }
        return 0;
    }
    UnitList* getClone() {
        UnitList* p = new UnitList;
        size_t i;
        for (i = 0; i < unitList.size(); i++)
        {
            Unit* temp = createIdUnit(unitList[i]->getRoleId());
            *temp = (*unitList[i]);
            p->unitList.push_back(temp);
        }
        return p;
    }
    ~UnitList() {
        size_t i;
        for (i = 0; i < unitList.size(); ++i)  delete unitList[i];
    }
};

// == База ==
Unit* menuCreateUnit(UnitList*& army, int x, int y);

//класс базы
class Base : public Unit
{
    static int roleId;
public:
    float hp;
    size_t maxUnit;
    UnitList* baseArmy;
    bool canPass() { return false; }
    void info() {
        if (name != "") cout << name << endl;
        cout << "Здоровье: " << hp << endl;
        if (baseArmy) cout << "Текущее количество юнитов: " << baseArmy->getSize() << "/" << maxUnit << endl;
        else cout << "Текущее количество юнитов: 0/" << maxUnit << endl;
    }
    void addUnit(UnitList*& list) {
        bool check1 = false; //выход из подменю
        do {
            char sw1 = ' ';
            sw1 = ' ';
            check1 = false;
            cout << "\nВыберите куда поставить юнита:\n";
            cout << "1 2 3\n";
            cout << "4 ";
            draw();
            cout << " 5\n";;
            cout << "6 7 8\n";
            cout << "[9] Оставить внутри базы\n";
            cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[1] -1 -1
                menuCreateUnit(list, x - 1, y - 1);
                break;
            case '2': //[2] 0 -1
                menuCreateUnit(list, x, y - 1);
                break;
            case '3': //[3] 1 -1
                menuCreateUnit(list, x + 1, y - 1);
                break;
            case '4': //[1] -1 0
                menuCreateUnit(list, x - 1, y);
                break;
            case '5': //[2] 1 0
                menuCreateUnit(list, x + 1, y);
                break;
            case '6': //[3] -1 1
                menuCreateUnit(list, x - 1, y + 1);
                break;
            case '7': //[7] 0 1
                menuCreateUnit(list, x, y + 1);
                break;
            case '8': //[7] 1 1
                menuCreateUnit(list, x + 1, y + 1);
                break;
            case '9': //[9] Внутри базы
                if (!baseArmy || baseArmy->getSize() < maxUnit) menuCreateUnit(baseArmy, 0, 0);
                else {
                    cout << "Количество юнитов в базе достигло максимального количества.\n";
                    check1 = true;
                }
                break;
            default:
                cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                check1 = true;
                break;
            }
        } while (check1);
    }
    int getRoleId() {
        return roleId;
    }
    Base();
};
Base::Base() {
    name = "";
    hp = 10;
    maxUnit = 10;
    x = 1;
    y = 1;
    baseArmy = new UnitList;
}
int Base::roleId = 7;

//== Поле ==
int idField = 0;
//класс поля
class Field
{
public:
    string name;
    int id;
    int maxX;
    int maxY;
    int maxObj = (maxX * maxY) / 2;
    UnitList* unitList;
    UnitList* baseList;
    UnitList* landList;
    UnitList* neutralList;
    Unit* biome;
    //надо пофиксить
    void recordObj(int**& Arr, UnitList*& list)
    {
        if (list)
        {
            for (size_t i = 0; i < list->getSize(); i++)
            {
                int tempX = list->getUnit(i + 1)->getX();
                int tempY = list->getUnit(i + 1)->getY();
                if ((tempY > 0) && (tempY <= maxY) && (tempX > 0) && (tempX <= maxX)) { //если внутри поля
                    Arr[tempY - 1][tempX - 1] = list->getUnit(i + 1)->getRoleId();
                }
            }
        }
    }
    void show() {
        if ((unitList || baseList || neutralList) && (unitList->getSize() + baseList->getSize() + neutralList->getSize() < maxObj))
        {
            cout << "Количество юнитов превышает допустимое значение!" << endl;
            return;
        }
        int** Arr = new int* [maxY];
        for (int i = 0; i < maxY; ++i)
        {
            Arr[i] = new int[maxX]();
        } //создаём двумерный массив

        //запоминаем, где стоят юниты
        if (landList) recordObj(Arr, landList);
        if (neutralList) recordObj(Arr, neutralList);
        if (unitList) recordObj(Arr, unitList);
        if (baseList) recordObj(Arr, baseList);

        //вывод
        for (int i = 0; i < maxX + 2; i++) cout << 'X';
        cout << '\n';
        for (int j = 0; j < maxY; j++)
        {
            for (int i = 0; i < maxX; i++)
            {
                if (i == 0) cout << 'X';
                if (Arr[j][i]) drawUnit(Arr[j][i]);
                else if (biome) biome->draw();
                else cout << ' ';
                if (i == maxX - 1) cout << 'X' << endl;
            }
        }
        for (int i = 0; i < maxX + 2; i++) cout << 'X';
        cout << '\n';

        for (int i = 0; i < maxY; ++i)
        {
            delete[] Arr[i];
        }
        delete[] Arr; //удаляем двумерный массив
    }
    void setXY(int x, int y) {
        maxX = x;
        maxY = y;
    }
    void setUnitList(UnitList* listObj) {
        unitList = listObj;
    }
    void setBaseList(UnitList* listObj) {
        baseList = listObj;
    }
    void setLandList(UnitList* listObj) {
        landList = listObj;
    }
    void setBiome(Unit* obj) {
        biome = obj;
    }
    int getId()
    {
        return id;
    }
    bool canMove(int newX, int newY, Unit*& obj) { //добавь сюда проверку на выход за границы пж
        Unit* temp = unitList->searchXY(newX, newY);
        if (temp) if (!temp->canPass()) return false;

        if (!temp) temp = baseList->searchXY(newX, newY);
        if (temp) if (!temp->canPass()) return false;

        if (!temp) temp = neutralList->searchXY(newX, newY);
        if (temp) if (!temp->canPass()) return false;
        else temp->effect(obj);

        temp = landList->searchXY(newX, newY);
        if (!temp) temp = biome;
        if (!temp->canPass()) return false;
        else temp->effect(obj);

        return true;
    }
    bool move(int x1, int y1, Unit*& obj) { //добавь сюда проверку на выход за границы пж
        int newX = obj->getX() + x1;
        int newY = obj->getY() + y1;
        if (canMove(newX, newY, obj)) return obj->move(x1, y1);
        else return false;
    }
    void act(Unit* Unit1, Unit* Unit2)
    {
        Unit2->interact(Unit1);
    }
    void actList(Unit* Unit1)
    {
        bool check1 = false; //выход из подменю
        Unit* temp = 0;
        do {
            char sw1 = ' ';
            sw1 = ' ';
            check1 = false;
            cout << "\nВыберите, с чем хотите взаимодействовать:\n";
            cout << "1 2 3\n";
            cout << "4 X 5\n";;
            cout << "6 7 8\n";
            cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[1] -1 -1
                temp = neutralList->searchXY(Unit1->getX() - 1, Unit1->getY() - 1);
                break;
            case '2': //[2] 0 -1
                temp = neutralList->searchXY(Unit1->getX(), Unit1->getY() - 1);
                break;
            case '3': //[3] 1 -1
                temp = neutralList->searchXY(Unit1->getX() + 1, Unit1->getY() - 1);
                break;
            case '4': //[1] -1 0
                temp = neutralList->searchXY(Unit1->getX() - 1, Unit1->getY());
                break;
            case '5': //[2] 1 0
                temp = neutralList->searchXY(Unit1->getX() + 1, Unit1->getY());
                break;
            case '6': //[3] -1 1
                temp = neutralList->searchXY(Unit1->getX() - 1, Unit1->getY() + 1);
                break;
            case '7': //[7] 0 1
                temp = neutralList->searchXY(Unit1->getX(), Unit1->getY() + 1);
                break;
            case '8': //[7] 1 1
                temp = neutralList->searchXY(Unit1->getX() + 1, Unit1->getY() + 1);
                break;
            default:
                cout << "Ошибка! Пожалуйста, попробуйте снова\n";
                check1 = true;
                break;
            }
        } while (check1);
        if (temp) act(Unit1, temp);
        else
        {
            cout << "Здесь не с чем взаимодействовать" << endl;
        }
    }
    Field(const Field& F)
    {
        if (F.name != "") name = F.name + "1";
        else name = "";
        id = ++idField;
        maxX = F.maxX;
        maxY = F.maxY;
        if (F.unitList) unitList = (F.unitList)->getClone();
        if (F.baseList) baseList = (F.baseList)->getClone();
        if (F.landList) landList = (F.landList)->getClone();
        if (F.neutralList) neutralList = (F.neutralList)->getClone();
        if (F.biome) biome = createIdUnit(F.biome->getRoleId());
    }
    Field();
};

Field::Field() {
    name = "";
    id = ++idField;
    maxX = 10;
    maxY = 6;
    unitList = new UnitList;
    baseList = new UnitList;
    landList = new UnitList;
    neutralList = new UnitList;
    biome = new Unit;
}

// == Ландшафт ==
class Landscape : public Unit
{
public:
    void interface(Field& field)
    {
        bool check1 = false;
        char sw1 = ' ';
        int x, y;
        do {
            cout << endl;
            cout << "[1] Установить объект как биом" << endl;
            cout << "[2] Установить объект на поле (не должно быть биомом)" << endl; //!!сделай чек является ли биомом
            cout << "[0] Вернуться назад" << endl;
            cout << "Введите число, чтобы выполнить нужное действие: " << endl;
            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[1] Установить объект как биом
                field.setBiome(createIdUnit(getRoleId()));
                break;
            case '2': //[2] Установить объект на поле (не должно быть биомом)
                cout << "Введите координаты объекта: ";
                cin >> x >> y;
                field.landList->addUnit(createIdUnit(getRoleId(), x, y));
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
};

class Grass : public Landscape
{
    static int roleId;
public:
    int getRoleId() {
        return roleId;
    }
};
int Grass::roleId = 8;

class Water : public Landscape
{
    static int roleId;
public:
    bool canPass() { return false; }
    int getRoleId() {
        return roleId;
    }
};
int Water::roleId = 9;

class Fire : public Landscape
{
    static int roleId;
public:
    void effect(Unit*& obj)
    {
        obj->changeHp(-1);
    }
    int getRoleId() {
        return roleId;
    }
};
int Fire::roleId = 10;

//== Нейтральные объекты ==
class Neutral : public Unit
{
public:
    virtual bool canPass() { return false; }
    void interface(Field& field)
    {
        bool check1 = false;
        char sw1 = ' ';
        int x, y;
        do {
            cout << endl;
            cout << "[1] Установить объект на поле" << endl;
            cout << "[2] Активировать умение" << endl; //хз чё ещё
            cout << "[0] Вернуться назад" << endl;
            cout << "Введите число, чтобы выполнить нужное действие: " << endl;
            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[2] Установить объект на поле (не должно быть биомом)
                cout << "Введите координаты объекта: ";
                cin >> x >> y;
                field.landList->addUnit(createIdUnit(getRoleId(), x, y));
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
};

//управлять могут только Саммонеры
class Dog : public Neutral
{
    static int roleId;
public:
    int hp = 10,
        dmg = 5;
    void info() {
        cout << "Пёс" << endl;
    }
    bool interact(Unit*& Unit1) {
        if (Unit1->getRoleId() == 5)
        {
            cout << "гав" << endl;
            return true;
        }
        return false;
    }
    void tryToGetCommand() {}
    int getRoleId() {
        return roleId;
    }
};
int Dog::roleId = 11;
void MageSummoner::summonDog(UnitList*& list) {
    bool check1 = false; //выход из подменю
    do {
        char sw1 = ' ';
        sw1 = ' ';
        check1 = false;
        cout << "\nВыберите куда поставить пёселя:\n";
        cout << "1 2 3\n";
        cout << "4 ";
        draw();
        cout << " 5\n";;
        cout << "6 7 8\n";
        cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

        cin >> sw1;
        while (cin.get() != '\n') { sw1 = ' '; };

        switch (sw1)
        {
        case '1': //[1] -1 -1
            list->addUnit(createIdUnit(11, x - 1, y - 1));
            break;
        case '2': //[2] 0 -1
            list->addUnit(createIdUnit(11, x, y - 1));
            break;
        case '3': //[3] 1 -1
            list->addUnit(createIdUnit(11, x + 1, y - 1));
            break;
        case '4': //[1] -1 0
            list->addUnit(createIdUnit(11, x - 1, y));
            break;
        case '5': //[2] 1 0
            list->addUnit(createIdUnit(11, x + 1, y));
            break;
        case '6': //[3] -1 1
            list->addUnit(createIdUnit(11, x - 1, y + 1));
            break;
        case '7': //[7] 0 1
            list->addUnit(createIdUnit(11, x, y + 1));
            break;
        case '8': //[7] 1 1
            list->addUnit(createIdUnit(11, x + 1, y + 1));
            break;
        default:
            cout << "Ошибка! Пожалуйста, попробуйте снова\n";
            check1 = true;
            break;
        }
    } while (check1);
}

//наступаешь - получаешь урон, а ловушка исчезает
class Trap : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void info() {
        cout << "Ловушка" << endl;
    }
    void effect(Unit*& obj)
    {
        obj->changeHp(-5);
    }
    int getRoleId() {
        return roleId;
    }
};
int Trap::roleId = 12;
void ShooterHunter::setTrap(UnitList*& list) {
    bool check1 = false; //выход из подменю
    do {
        char sw1 = ' ';
        sw1 = ' ';
        check1 = false;
        cout << "\nВыберите куда установить ловушку:\n";
        cout << "1 2 3\n";
        cout << "4 ";
        draw();
        cout << " 5\n";;
        cout << "6 7 8\n";
        cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

        cin >> sw1;
        while (cin.get() != '\n') { sw1 = ' '; };

        switch (sw1)
        {
        case '1': //[1] -1 -1
            list->addUnit(createIdUnit(12, x - 1, y - 1));
            break;
        case '2': //[2] 0 -1
            list->addUnit(createIdUnit(12, x, y - 1));
            break;
        case '3': //[3] 1 -1
            list->addUnit(createIdUnit(12, x + 1, y - 1));
            break;
        case '4': //[1] -1 0
            list->addUnit(createIdUnit(12, x - 1, y));
            break;
        case '5': //[2] 1 0
            list->addUnit(createIdUnit(12, x + 1, y));
            break;
        case '6': //[3] -1 1
            list->addUnit(createIdUnit(12, x - 1, y + 1));
            break;
        case '7': //[7] 0 1
            list->addUnit(createIdUnit(12, x, y + 1));
            break;
        case '8': //[7] 1 1
            list->addUnit(createIdUnit(12, x + 1, y + 1));
            break;
        default:
            cout << "Ошибка! Пожалуйста, попробуйте снова\n";
            check1 = true;
            break;
        }
    } while (check1);
}

//можно прочитать текст
class Note : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void outputText() {
        cout << "Вы увидели содержание записки.";
    }
    void info() {
        cout << "Записка" << endl;
    }
    bool interact(Unit*& Unit1) {
        outputText();
        return true;
    }
    int getRoleId() {
        return roleId;
    }
};
int Note::roleId = 13;

//тпшит из одной точки в другую (надо находиться рядом чтоб взаимодействовать)
class Teleport : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void info() {
        cout << "Телепорт" << endl;
    }
    bool interact(Unit*& Unit1) {
        cout << "Введите координаты, куда необходимо переместиться: ";
        int x, y;
        cin >> x >> y;
        Unit1->setXY(x, y);
        return true;
    }
    int getRoleId() {
        return roleId;
    }
};
int Teleport::roleId = 14;