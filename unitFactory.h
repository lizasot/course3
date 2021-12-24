// == ����������� ������� ��� �������� ������ ==

// ����������� ������� ��� ������������ ������
class WarriorFactory
{
public:
    virtual Warrior* createWarrior() = 0;
    virtual ~WarriorFactory() {}
};

// ����������� ������� ��� ������������ ��������
class ShooterFactory
{
public:
    virtual Shooter* createShooter() = 0;
    virtual ~ShooterFactory() {}
};

// ����������� ������� ��� ������������ �����
class MageFactory
{
public:
    virtual Mage* createMage() = 0;
    virtual ~MageFactory() {}
};

// ������� ��� �������� ��������-�����
class WShieldFactory : public WarriorFactory
{
public:
    Warrior* createWarrior() {
        return new WarriorShield;
    }
};

// ������� ��� �������� ��������-�������
class SHunterFactory : public ShooterFactory
{
public:
    Shooter* createShooter() {
        return new ShooterHunter;
    }
};

// ������� ��� �������� ��������-����
class MSummonerFactory : public MageFactory
{
public:
    Mage* createMage() {
        return new MageSummoner;
    }
};

// ������� ��� �������� �����-��������
class WAssasinFactory : public WarriorFactory
{
public:
    Warrior* createWarrior() {
        return new WarriorAssasin;
    }
};

// ������� ��� �������� �������-��������
class SSnipernFactory : public ShooterFactory
{
public:
    Shooter* createShooter() {
        return new ShooterSniper;
    }
};

// ������� ��� �������� ����-��������
class MWizardFactory : public MageFactory
{
public:
    Mage* createMage() {
        return new MageWizard;
    }
};

// �������� ���������� �����
class RoleUnitFactory
{
public:
    Unit* createUnits(WarriorFactory& factory) {
        return factory.createWarrior();
    }
    Unit* createUnits(ShooterFactory& factory) {
        return factory.createShooter();
    }
    Unit* createUnits(MageFactory& factory) {
        return factory.createMage();
    }
    Unit* createUnits(int roleId) {
        switch (roleId)
        {
        case 7:
            return new Base;
        case 8:
            return new Grass;
        case 9:
            return new Water;
        case 10:
            return new Fire;
        case 11:
            return new Dog;
        case 12:
            return new Trap;
        case 13:
            return new Note;
        case 14:
            return new Teleport;
        default:
            return new Unit;
            break;
        }
    }
};