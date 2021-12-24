//����� ����� ������
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
        cout << "\n�������������� [X][Y]: [" << x << "][" << y << "]" << endl;
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
    virtual void ability(UnitList*& list) { cout << "� ����� ����� ��� �����������." << endl; }
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

// == ����� ==
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
        cout << "��������: " << hp << endl;
        cout << "����: " << dmg << endl;
        cout << "��������: " << speed << endl;
        cout << "����: " << mana << endl;
        cout << "\n�������������� [X][Y]: [" << x << "][" << y << "]" << endl;
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
        if (!mute) cout << "��-������� ����� ������ �� ����\n";
    }
    virtual void die()
    {
        if (!mute) cout << "��-������� ����\n";
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
        if (!mute) cout << "��-����������� ����� ������ �� ����\n";
    }
    virtual void die()
    {
        if (!mute) cout << "��-����������� ����\n";
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
        if (!mute) cout << "��-��������� ����� ������ �� ����\n";
    }
    virtual void die()
    {
        if (!mute) cout << "��-��������� ����\n";
    }
    virtual ~Mage() {}
};

// ������ ���� ������
class WarriorShield : public Warrior
{
    static int roleId;
public:
    void info() {
        cout << "�������" << endl;
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
        cout << "�������" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int WarriorAssasin::roleId = 2;

// ������ ���� ��������
class ShooterHunter : public Shooter
{
    static int roleId;
public:
    void info() {
        cout << "�������" << endl;
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
        cout << "�������" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int ShooterSniper::roleId = 4;

// ������ ���� �����
Unit* createIdUnit(int sw);
Unit* createIdUnit(int sw, int x, int y);
class MageSummoner : public Mage
{
    static int roleId;
public:
    void info() {
        cout << "�����������" << endl;
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
        cout << "������" << endl;
    }
    int getRoleId() {
        return roleId;
    }
};
int MageWizard::roleId = 6;


//== ������ �������� ==
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
            cout << "��������������: [" << unitList[i]->getX() << "][" << unitList[i]->getY() << "]" << endl;
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

// == ���� ==
Unit* menuCreateUnit(UnitList*& army, int x, int y);

//����� ����
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
        cout << "��������: " << hp << endl;
        if (baseArmy) cout << "������� ���������� ������: " << baseArmy->getSize() << "/" << maxUnit << endl;
        else cout << "������� ���������� ������: 0/" << maxUnit << endl;
    }
    void addUnit(UnitList*& list) {
        bool check1 = false; //����� �� �������
        do {
            char sw1 = ' ';
            sw1 = ' ';
            check1 = false;
            cout << "\n�������� ���� ��������� �����:\n";
            cout << "1 2 3\n";
            cout << "4 ";
            draw();
            cout << " 5\n";;
            cout << "6 7 8\n";
            cout << "[9] �������� ������ ����\n";
            cout << "����������, ������� �����, ����� ��������� ������ ��������: ";

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
            case '9': //[9] ������ ����
                if (!baseArmy || baseArmy->getSize() < maxUnit) menuCreateUnit(baseArmy, 0, 0);
                else {
                    cout << "���������� ������ � ���� �������� ������������� ����������.\n";
                    check1 = true;
                }
                break;
            default:
                cout << "������! ����������, ���������� �����\n";
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

//== ���� ==
int idField = 0;
//����� ����
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
    //���� ���������
    void recordObj(int**& Arr, UnitList*& list)
    {
        if (list)
        {
            for (size_t i = 0; i < list->getSize(); i++)
            {
                int tempX = list->getUnit(i + 1)->getX();
                int tempY = list->getUnit(i + 1)->getY();
                if ((tempY > 0) && (tempY <= maxY) && (tempX > 0) && (tempX <= maxX)) { //���� ������ ����
                    Arr[tempY - 1][tempX - 1] = list->getUnit(i + 1)->getRoleId();
                }
            }
        }
    }
    void show() {
        if ((unitList || baseList || neutralList) && (unitList->getSize() + baseList->getSize() + neutralList->getSize() < maxObj))
        {
            cout << "���������� ������ ��������� ���������� ��������!" << endl;
            return;
        }
        int** Arr = new int* [maxY];
        for (int i = 0; i < maxY; ++i)
        {
            Arr[i] = new int[maxX]();
        } //������ ��������� ������

        //����������, ��� ����� �����
        if (landList) recordObj(Arr, landList);
        if (neutralList) recordObj(Arr, neutralList);
        if (unitList) recordObj(Arr, unitList);
        if (baseList) recordObj(Arr, baseList);

        //�����
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
        delete[] Arr; //������� ��������� ������
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
    bool canMove(int newX, int newY, Unit*& obj) { //������ ���� �������� �� ����� �� ������� ��
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
    bool move(int x1, int y1, Unit*& obj) { //������ ���� �������� �� ����� �� ������� ��
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
        bool check1 = false; //����� �� �������
        Unit* temp = 0;
        do {
            char sw1 = ' ';
            sw1 = ' ';
            check1 = false;
            cout << "\n��������, � ��� ������ �����������������:\n";
            cout << "1 2 3\n";
            cout << "4 X 5\n";;
            cout << "6 7 8\n";
            cout << "����������, ������� �����, ����� ��������� ������ ��������: ";

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
                cout << "������! ����������, ���������� �����\n";
                check1 = true;
                break;
            }
        } while (check1);
        if (temp) act(Unit1, temp);
        else
        {
            cout << "����� �� � ��� �����������������" << endl;
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

// == �������� ==
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
            cout << "[1] ���������� ������ ��� ����" << endl;
            cout << "[2] ���������� ������ �� ���� (�� ������ ���� ������)" << endl; //!!������ ��� �������� �� ������
            cout << "[0] ��������� �����" << endl;
            cout << "������� �����, ����� ��������� ������ ��������: " << endl;
            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[1] ���������� ������ ��� ����
                field.setBiome(createIdUnit(getRoleId()));
                break;
            case '2': //[2] ���������� ������ �� ���� (�� ������ ���� ������)
                cout << "������� ���������� �������: ";
                cin >> x >> y;
                field.landList->addUnit(createIdUnit(getRoleId(), x, y));
                break;
            case '0': //[0] �����
                break;
            default:
                cout << "������! ����������, ���������� �����\n";
                check1 = true; //���� ����� ������
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

//== ����������� ������� ==
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
            cout << "[1] ���������� ������ �� ����" << endl;
            cout << "[2] ������������ ������" << endl; //�� �� ���
            cout << "[0] ��������� �����" << endl;
            cout << "������� �����, ����� ��������� ������ ��������: " << endl;
            cin >> sw1;
            while (cin.get() != '\n') { sw1 = ' '; };

            switch (sw1)
            {
            case '1': //[2] ���������� ������ �� ���� (�� ������ ���� ������)
                cout << "������� ���������� �������: ";
                cin >> x >> y;
                field.landList->addUnit(createIdUnit(getRoleId(), x, y));
                break;
            case '0': //[0] �����
                break;
            default:
                cout << "������! ����������, ���������� �����\n";
                check1 = true; //���� ����� ������
                break;
            }
        } while (check1);
    }
};

//��������� ����� ������ ���������
class Dog : public Neutral
{
    static int roleId;
public:
    int hp = 10,
        dmg = 5;
    void info() {
        cout << "ϸ�" << endl;
    }
    bool interact(Unit*& Unit1) {
        if (Unit1->getRoleId() == 5)
        {
            cout << "���" << endl;
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
    bool check1 = false; //����� �� �������
    do {
        char sw1 = ' ';
        sw1 = ' ';
        check1 = false;
        cout << "\n�������� ���� ��������� �����:\n";
        cout << "1 2 3\n";
        cout << "4 ";
        draw();
        cout << " 5\n";;
        cout << "6 7 8\n";
        cout << "����������, ������� �����, ����� ��������� ������ ��������: ";

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
            cout << "������! ����������, ���������� �����\n";
            check1 = true;
            break;
        }
    } while (check1);
}

//���������� - ��������� ����, � ������� ��������
class Trap : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void info() {
        cout << "�������" << endl;
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
    bool check1 = false; //����� �� �������
    do {
        char sw1 = ' ';
        sw1 = ' ';
        check1 = false;
        cout << "\n�������� ���� ���������� �������:\n";
        cout << "1 2 3\n";
        cout << "4 ";
        draw();
        cout << " 5\n";;
        cout << "6 7 8\n";
        cout << "����������, ������� �����, ����� ��������� ������ ��������: ";

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
            cout << "������! ����������, ���������� �����\n";
            check1 = true;
            break;
        }
    } while (check1);
}

//����� ��������� �����
class Note : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void outputText() {
        cout << "�� ������� ���������� �������.";
    }
    void info() {
        cout << "�������" << endl;
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

//����� �� ����� ����� � ������ (���� ���������� ����� ���� �����������������)
class Teleport : public Neutral
{
    static int roleId;
public:
    bool canPass() { return true; }
    void info() {
        cout << "��������" << endl;
    }
    bool interact(Unit*& Unit1) {
        cout << "������� ����������, ���� ���������� �������������: ";
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