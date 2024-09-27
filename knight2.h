#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

class BaseBag;
class BaseOpponent;
class BaseKnight;
class ArmyKnights;
class BaseItem;
class Events;

// #define DEBUG
bool isPaladin(int maxhp);
bool isLancelot(int maxhp);
bool isDragon(int maxhp);
enum ItemType {/* TODO: */Antidote, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV };
class BaseBag {
public:
    BaseItem* head;
    int count;
    int bagSize;
    BaseKnight* knight;
    BaseBag(BaseKnight* knight, int antidote, int phoenixdownI);
    ~BaseBag();
    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
};
class BaseOpponent {
public:
    int event_id;
    int levelO;
    int gil;
    int baseDamage;
    void setlevelO(int i);
    void setevent_id(int i);
    void setOgil(int i);
    void setObaseDamage(int i);
};

class MadBear : public BaseOpponent {
public:
    MadBear();
};
class Bandit : public BaseOpponent {
public:
    Bandit();
};
class LordLupin : public BaseOpponent {
public:
    LordLupin();
};
class Elf : public BaseOpponent {
public:
    Elf();
};
class Troll : public BaseOpponent {
public:
    Troll();
};
class Tornbery : public BaseOpponent {
public:
    Tornbery();
};
class QueenOfCard : public BaseOpponent {
public:
    QueenOfCard();
};
class NinaDerings : public BaseOpponent {
public:
    NinaDerings();
};
class DurianGarden : public BaseOpponent {
public:
    DurianGarden();
};
class OmegaWeapon : public BaseOpponent{
public:
    OmegaWeapon();
};
class Hades : public BaseOpponent {
public:
    Hades();
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    BaseBag* bag;
    KnightType knightType;
public:
    bool poisoned;
    int antidote;
    int knightBaseDamage;
    void sethp(int i);
    int gethp();
    int getmaxhp();
    void setlevel(int i);
    int getlevel();
    void setgil(int i);
    int getgil();
    BaseBag* getbag();
    void setknightType(KnightType i);
    int getknightType();
    void setpoisoned(bool i);
    bool getpoisoned();
    
    void setknightBaseDamage(int i);
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight();
};

class LancelotKnight : public BaseKnight {
public:
    LancelotKnight();
};

class DragonKnight : public BaseKnight {
public:
    DragonKnight();
};

class NormalKnight : public BaseKnight {
public:
    NormalKnight();
};

class ArmyKnights {
public:
    BaseKnight** Army;
    int numKnights;
    bool killOmegaWeapon;
    bool killHades;
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    BaseItem();
    ItemType itemType;
    BaseItem* link;
    void setitemType(ItemType i);
    ItemType getitemType();
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};
class AntidoteClass : public BaseItem {
public:
    AntidoteClass();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownI : public BaseItem {
public:
    PhoenixDownI();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownII : public BaseItem {
public:
    PhoenixDownII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIII : public BaseItem {
public:
    PhoenixDownIII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIV : public BaseItem {
public:
    PhoenixDownIV();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class Events {
public:
    int n;
    int* eve;
    Events(const string& file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string& );
    void loadEvents(const string& );
    void run();
};

#endif // __KNIGHT2_H__