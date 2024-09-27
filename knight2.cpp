#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag(BaseKnight* knight, int antidote, int phoenixdownI) {
    this->head = NULL;
    this->count = 0;
    this->knight = knight;
    if (knight->getknightType() == DRAGON) {
        this->bagSize = 14;
    }
    else if (knight->getknightType() == LANCELOT) {
        this->bagSize = 16;
    }
    else if (knight->getknightType() == NORMAL) {
        this->bagSize = 19;
    }
    else if (knight->getknightType() == PALADIN) {
        this->bagSize = 1010;
    }
    
    for (int i = 0; i < phoenixdownI; i++) {
        if (this->count == this->bagSize) {
            break;
        }
        PhoenixDownI* pNew = new PhoenixDownI;
        if (head != NULL) {
            pNew->link = this->head;
        }
        this->head = pNew;
        this->count++;
        pNew = NULL;
    }
    if (knight->getknightType() != DRAGON) {
        for (int i = 0; i < antidote; i++) {
            if (this->count == this->bagSize) {
                break;
            }
            AntidoteClass* pNew = new AntidoteClass;
            if (head != NULL) {
                pNew->link = this->head;
            }
            this->head = pNew;
            this->count++;
            pNew = NULL;
        }
    }
    
}
BaseBag::~BaseBag() {}
bool BaseBag::insertFirst(BaseItem* item) {
    if (this->count >= this->bagSize) return false;
    else if (knight->getknightType() == DRAGON && item->itemType == Antidote) return false;
    else {
        if (head != NULL) {
            item->link = this->head;
        }
        this->head = item;
        this->count++;
        return true;
    }
}
BaseItem* BaseBag::get(ItemType itemType) {
    if (this->count==0) return NULL;
    ItemType x = itemType;
    ItemType y = this->head->getitemType();
    if (x != y) {
        BaseItem* prevX = NULL, * currX = this->head;
        while (currX && currX->itemType != x) {
            prevX = currX;
            currX = currX->link;
        }
        BaseItem* prevY = NULL, * currY = this->head;
        while (currY && currY->itemType != y) {
            prevY = currY;
            currY = currY->link;
        }
        if (currX == NULL || currY == NULL) return NULL;
        if (prevX != NULL) prevX->link = currY;
        else this->head = currY;
        if (prevY != NULL) prevY->link = currX;
        else this->head = currX;
        BaseItem* temp = currY->link;
        currY->link = currX->link;
        currX->link = temp;
    }
    BaseItem* res = this->head;
    this->head = this->head->link;
    this->count--;
    return res;
}
string BaseBag::toString() const {
    string str;
    str = "Bag[count=" + to_string(count) + ";";
    BaseItem* wri = this->head;
    for (int i = 1; i <= count; i++) {
        if (wri->itemType == Antidote) {
            str += "Antidote";
        }
        else if (wri->itemType == PhoenixI) {
            str += "PhoenixI";
        }
        else if (wri->itemType == PhoenixII) {
            str += "PhoenixII";
        }
        else if (wri->itemType == PhoenixIII) {
            str += "PhoenixIII";
        }
        else if (wri->itemType == PhoenixIV) {
            str += "PhoenixIV";
        }
        if (i < count) str += ",";
        wri = wri->link;
    }
    str += "]";
    wri =NULL;
    return str;
}

/* * * END implementation of class BaseBag * * */

bool isPaladin(int maxhp) {
    if (maxhp < 2) return 0;
    for (int i = 2; i <= sqrt(maxhp); i++) {
        if (maxhp % i == 0) return 0;
    }
    return 1;
}

bool isLancelot(int maxhp) {
    if (maxhp == 888) return 1;
    return 0;
}

bool isDragon(int maxhp) {
    if (maxhp < 100 || maxhp>999) return 0;
    int a, b, c;
    c = maxhp % 10;
    b = (maxhp % 100 - c) / 10;
    a = (maxhp - b * 10 - c) / 100;
    int max;
    max = a > b ? a : b;
    max = c > max ? c : max;
    if (a * a + b * b + c * c == max * max * 2) return 1;
    return 0;
}

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
PaladinKnight::PaladinKnight() {
    setknightType(PALADIN);
    setknightBaseDamage(0.05);
}
LancelotKnight::LancelotKnight() {
    setknightType(LANCELOT);
    setknightBaseDamage(0.06);
}
DragonKnight::DragonKnight() {
    setknightType(DRAGON);
    setknightBaseDamage(0.075);
}
NormalKnight::NormalKnight() {
    setknightType(NORMAL);
    setknightBaseDamage(0);
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    if (isPaladin(maxhp) == 1) {
        PaladinKnight* knight = new PaladinKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->poisoned = false;
        knight->bag = new BaseBag(knight, antidote, phoenixdownI);
        return knight;
    }
    else if (isLancelot(maxhp) == 1) {
        LancelotKnight*knight = new LancelotKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->poisoned = false;
        knight->bag = new BaseBag(knight, antidote, phoenixdownI);
        return knight;
    }
    else if (isDragon(maxhp) == 1) {
        DragonKnight*knight = new DragonKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->poisoned = false;
        knight->bag = new BaseBag(knight, antidote, phoenixdownI);
        return knight;
    }
    else {
        NormalKnight*knight = new NormalKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->poisoned = false;
        knight->bag = new BaseBag(knight, antidote, phoenixdownI);
        return knight;
    }
}

BaseBag* BaseKnight::getbag() {
    return bag;
}
void BaseKnight::sethp(int i) {
    hp = i;
}
int BaseKnight::gethp() {
    return hp;
}
int BaseKnight::getmaxhp() {
    return maxhp;
}
void BaseKnight::setlevel(int i) {
    level = i;
}
int BaseKnight::getlevel() {
    return level;
}
void BaseKnight::setgil(int i) {
    gil = i;
}
int BaseKnight::getgil() {
    return gil;
}
void BaseKnight::setknightType(KnightType i) {
    knightType = i;
}
int BaseKnight::getknightType() {
    return knightType;
}
void BaseKnight::setpoisoned(bool i) {
    poisoned = i;
}
bool BaseKnight::getpoisoned() {
    return poisoned;
}
void BaseKnight::setknightBaseDamage(int i){
    knightBaseDamage = i;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string& file_armyknights) {
    killOmegaWeapon = 0;
    killHades = 0;
    PaladinShield = 0;
    LancelotSpear = 0;
    GuinevereHair = 0;
    ifstream ifs;
    ifs.open(file_armyknights);
    ifs >> numKnights;
    Army = new BaseKnight * [numKnights];
    int maxhp, level, phoenixdownI, gil, antidote;
    for (int i = 1; i <= numKnights; i++) {
        ifs >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        Army[i - 1] = BaseKnight::create(i, maxhp, level, gil, antidote, phoenixdownI);
    }
    ifs.close();
}

ArmyKnights::~ArmyKnights() {
    for (int i=numKnights-1; i>=0;i--){
        while (Army[i]->getbag()->head != NULL) {
            BaseItem* dele = Army[i]->getbag()->head;
            Army[i]->getbag()->head = Army[i]->getbag()->head->link;
            delete dele;
            dele = NULL;
        }
        Army[i]->getbag()->count = 0;
        delete Army[i];
    }
    delete[]Army;
    Army = NULL;
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
    BaseKnight* lastKnight = this->lastKnight();
    if (opponent->event_id ==1 || opponent->event_id == 2|| opponent->event_id == 3|| opponent->event_id == 4|| opponent->event_id ==5) {
        if (lastKnight->getlevel() < opponent->levelO && lastKnight->getknightType() != PALADIN && lastKnight->getknightType() != LANCELOT) {
            lastKnight->sethp(lastKnight->gethp() - opponent->baseDamage * (opponent->levelO - lastKnight->getlevel()));
            BaseBag* bagofKnight = lastKnight->getbag();
            if (bagofKnight->count > 0) {
                int used = 0;
                BaseItem* find = bagofKnight->head;
                while (find != NULL && used == 0) {
                    if (find->itemType == PhoenixI) {
                        PhoenixDownI* phoenix = new PhoenixDownI;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixI);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 1;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixII) {
                        PhoenixDownII* phoenix = new PhoenixDownII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 2;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIII) {
                        PhoenixDownIII* phoenix = new PhoenixDownIII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 3;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIV) {
                        PhoenixDownIV* phoenix = new PhoenixDownIV;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIV);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 4;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    find = find->link;
                }
            }
            if (lastKnight->gethp() <= 0) {
                if (lastKnight->getgil() >= 100) {
                    lastKnight->setgil(lastKnight->getgil() - 100);
                    lastKnight->sethp(int(lastKnight->getmaxhp()) / 2);
                }
            }
            if (lastKnight->gethp() <= 0) {
                return false;
            }
        }
        else {
            int gilRecieved = opponent->gil;
            for (int i = count() - 1; i >= 0; i--) {
                if (gilRecieved > 0) {
                    if (Army[i]->getgil() + gilRecieved > 999) {
                        gilRecieved = Army[i]->getgil() + gilRecieved - 999;
                        Army[i]->setgil(999);
                    }
                    else {
                        Army[i]->setgil(Army[i]->getgil() + gilRecieved);
                        break;
                    }
                }
            }
        }
        return true;
    }
    else if (opponent->event_id == 6) {
        int levO = opponent->levelO;
        int levKni = lastKnight->getlevel();
        if ( levKni >= levO) {
            if (lastKnight->getlevel() < 10) {
                int temp = lastKnight->getlevel();
                lastKnight->setlevel(temp + 1);
            }
        }
        else {
            if (lastKnight->getknightType() != DRAGON) {
                BaseBag* bagofKnight = lastKnight->getbag();
                if (lastKnight->antidote > 0) {
                    BaseItem* antidote = bagofKnight->get(Antidote);
                    delete antidote;
                    antidote = NULL;
                    (lastKnight->antidote)--;
                }
                else {
                    int temp = lastKnight->gethp();
                    lastKnight->sethp(temp - 10);
                    if (bagofKnight->count > 0) {
                        for (int i = 0; i < 3; i++) {
                            if (bagofKnight->count > 0) {
                                ItemType dropType = (bagofKnight->head)->itemType;
                                BaseItem* drop = bagofKnight->get(dropType);
                                delete drop;
                                drop = NULL;
                            }
                        }
                    }
                    if (bagofKnight->count > 0) {
                        int used = 0;
                        BaseItem* find = bagofKnight->head;
                        while (find != NULL && used == 0) {
                            if (find->itemType == PhoenixI) {
                                PhoenixDownI* phoenix = new PhoenixDownI;
                                if (phoenix->canUse(lastKnight)) {
                                    BaseItem* item = bagofKnight->get(PhoenixI);
                                    delete item;
                                    item = NULL;
                                    phoenix->use(lastKnight);
                                    used = 1;
                                }
                                delete phoenix;
                                phoenix = NULL;
                            }
                            else if (find->itemType == PhoenixII) {
                                PhoenixDownII* phoenix = new PhoenixDownII;
                                if (phoenix->canUse(lastKnight)) {
                                    BaseItem* item = bagofKnight->get(PhoenixII);
                                    delete item;
                                    item = NULL;
                                    phoenix->use(lastKnight);
                                    used = 2;
                                }
                                delete phoenix;
                                phoenix = NULL;
                            }
                            else if (find->itemType == PhoenixIII) {
                                PhoenixDownIII* phoenix = new PhoenixDownIII;
                                if (phoenix->canUse(lastKnight)) {
                                    BaseItem* item = bagofKnight->get(PhoenixIII);
                                    delete item;
                                    item = NULL;
                                    phoenix->use(lastKnight);
                                    used = 3;
                                }
                                delete phoenix;
                                phoenix = NULL;
                            }
                            else if (find->itemType == PhoenixIV) {
                                PhoenixDownIV* phoenix = new PhoenixDownIV;
                                if (phoenix->canUse(lastKnight)) {
                                    BaseItem* item = bagofKnight->get(PhoenixIV);
                                    delete item;
                                    item = NULL;
                                    phoenix->use(lastKnight);
                                    used = 4;
                                }
                                delete phoenix;
                                phoenix = NULL;
                            }
                            find = find->link;
                        }
                    }   
                    if (lastKnight->gethp() <= 0) {
                        if (lastKnight->getgil() >= 100) {
                            lastKnight->setgil(lastKnight->getgil() - 100);
                            lastKnight->sethp(int(lastKnight->getmaxhp()) / 2);
                        }
                    }
                    if (lastKnight->gethp() <= 0) {
                        return false;
                    }
                }
            }
        } 
        return true;
    }
    else if (opponent->event_id == 7) {
        if (lastKnight->getlevel() < opponent->levelO) {
            if (lastKnight->getknightType() != PALADIN) {
                lastKnight->setgil(int(lastKnight->getgil() / 2));
            }
        }
        else {
            int gilRecieved = lastKnight->getgil();
            for (int i = count() - 1; i >= 0; i--) {
                if (gilRecieved > 0) {
                    if (Army[i]->getgil() + gilRecieved > 999) {
                        gilRecieved = Army[i]->getgil() + gilRecieved - 999;
                        Army[i]->setgil(999);
                    }
                    else {
                        Army[i]->setgil(Army[i]->getgil() + gilRecieved);
                        break;
                    }
                }
            }
        }
        return true;
    }
    else if (opponent->event_id == 8) {
        if (lastKnight->getgil() >= 50 || lastKnight->getknightType() == PALADIN) {
            if (lastKnight->gethp() < int(lastKnight->getmaxhp() / 3)) {
                if (lastKnight->getknightType() != PALADIN) {
                    lastKnight->setgil(lastKnight->getgil() - 50);
                }
                lastKnight->sethp(lastKnight->gethp() + int(lastKnight->getmaxhp() / 5));
            }
        }
        return true;
    }
    else if (opponent->event_id == 9) {
        lastKnight->sethp(lastKnight->getmaxhp());
        return true;
    }
    else if (opponent->event_id == 10 && killOmegaWeapon == 0) {
        if (lastKnight->getknightType() == DRAGON || (lastKnight->getlevel() == 10 && lastKnight->gethp() == lastKnight->getmaxhp())) {
            lastKnight->setlevel(10);
            lastKnight->setgil(999);
            killOmegaWeapon == 1;
        }
        else {
            lastKnight->sethp(0);
            BaseBag* bagofKnight = lastKnight->getbag();
            if (bagofKnight->count > 0) {
                int used = 0;
                BaseItem* find = bagofKnight->head;
                while (find != NULL && used == 0) {
                    if (find->itemType == PhoenixI) {
                        PhoenixDownI* phoenix = new PhoenixDownI;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixI);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 1;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixII) {
                        PhoenixDownII* phoenix = new PhoenixDownII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 2;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIII) {
                        PhoenixDownIII* phoenix = new PhoenixDownIII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 3;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIV) {
                        PhoenixDownIV* phoenix = new PhoenixDownIV;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIV);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 4;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    find = find->link;
                }
            }
            if (lastKnight->gethp() <= 0) {
                if (lastKnight->getgil() >= 100) {
                    lastKnight->setgil(lastKnight->getgil() - 100);
                    lastKnight->sethp(int(lastKnight->getmaxhp()) / 2);
                }
            }
            if (lastKnight->gethp() <= 0) {
                return false;
            }
        }
        return true;
    }
    else if (opponent->event_id == 11 && killHades==0) {
        if ((lastKnight->getknightType() == PALADIN && lastKnight->getlevel() >= 8) || lastKnight->getlevel() == 10) {
            killHades = 1;
            PaladinShield = 1;
        }
        else {
            lastKnight->sethp(0);
            BaseBag* bagofKnight = lastKnight->getbag();
            if (bagofKnight->count > 0) {
                int used = 0;
                BaseItem* find = bagofKnight->head;
                while (find != NULL && used == 0) {
                    if (find->itemType == PhoenixI) {
                        PhoenixDownI* phoenix = new PhoenixDownI;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixI);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 1;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixII) {
                        PhoenixDownII* phoenix = new PhoenixDownII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 2;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIII) {
                        PhoenixDownIII* phoenix = new PhoenixDownIII;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIII);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 3;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    else if (find->itemType == PhoenixIV) {
                        PhoenixDownIV* phoenix = new PhoenixDownIV;
                        if (phoenix->canUse(lastKnight)) {
                            BaseItem* item = bagofKnight->get(PhoenixIV);
                            delete item;
                            item = NULL;
                            phoenix->use(lastKnight);
                            used = 4;
                        }
                        delete phoenix;
                        phoenix = NULL;
                    }
                    find = find->link;
                }
            }
            if (lastKnight->gethp() <= 0) {
                if (lastKnight->getgil() >= 100) {
                    lastKnight->setgil(lastKnight->getgil() - 100);
                    lastKnight->sethp(int(lastKnight->getmaxhp()) / 2);
                }

            }
            if (lastKnight->gethp() <= 0) {
                return false;
            }
        }
        return true;
    }
}
bool ArmyKnights::adventure(Events* events) {
    for (int event_i = 0; event_i < events->count(); event_i++) {       
        if (events->get(event_i) == 1) {
            MadBear* opponent = new MadBear;
            opponent->levelO = (event_i + 1) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 2) {
            Bandit* opponent = new Bandit;
            opponent->levelO = (event_i + 2) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 3) {
            LordLupin* opponent = new LordLupin;
            opponent->levelO = (event_i + 3) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 4) {
            Elf* opponent = new Elf;
            opponent->levelO = (event_i + 4) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 5) {
            Troll* opponent = new Troll;
            opponent->levelO = (event_i + 5) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 6) {
            Tornbery* opponent = new Tornbery;
            opponent->levelO = (event_i + 6) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 7) {
            QueenOfCard* opponent = new QueenOfCard;
            opponent->levelO = (event_i + 7) % 10 + 1;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 8) {
            NinaDerings* opponent = new NinaDerings;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 9) {
            DurianGarden* opponent = new DurianGarden;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 10) {
            OmegaWeapon* opponent = new OmegaWeapon;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 11) {
            Hades* opponent = new Hades;
            fight(opponent);
            delete opponent;
            opponent = NULL;
        }
        else if (events->get(event_i) == 95) {
            PaladinShield = 1;
        }
        else if (events->get(event_i) == 96) {
            LancelotSpear = 1;
        }
        else if (events->get(event_i) == 97) {
            GuinevereHair = 1;
        }
        else if (events->get(event_i) == 98) {
            if (hasPaladinShield() == 1 && hasLancelotSpear() == 1 && hasGuinevereHair() == 1) {
                ExcaliburSword = 1;
            }
        }
        else if (events->get(event_i) == 112) {
            bool done = false;
            PhoenixDownII* item = new PhoenixDownII;
            for (int m = count() - 1; m >= 0; m--) {
                if (Army[m]->getbag()->count < Army[m]->getbag()->bagSize) {
                    Army[m]->getbag()->insertFirst(item);
                    done = true;
                    break;
                }
            }
            if (done==false){
                delete item;
                item = NULL;
            }
        }
        else if (events->get(event_i) == 113) {
            bool done = false;
            PhoenixDownIII* item = new PhoenixDownIII;
            for (int m = count() - 1; m >= 0; m--) {
                if (Army[m]->getbag()->count < Army[m]->getbag()->bagSize) {
                    Army[m]->getbag()->insertFirst(item);
                    done = true;
                    break;
                }
            }
            if (done==false){
                delete item;
                item = NULL;
            }
        }
        else if (events->get(event_i) == 114) {
            bool done = false;
            PhoenixDownIV* item = new PhoenixDownIV;
            for (int m = count() - 1; m >= 0; m--) {
                if (Army[m]->getbag()->count < Army[m]->getbag()->bagSize) {
                    Army[m]->getbag()->insertFirst(item);
                    done = true;
                    break;
                }
            }
            if (done==false){
                delete item;
                item = NULL;
            }
        }
        else if (events->get(event_i) == 99) {
            if (hasExcaliburSword() == 1) {
                printInfo();
                return true;
            }
            else if (hasLancelotSpear() == 1 && hasPaladinShield() == 1 && hasGuinevereHair() == 1) {
                int UltmeciaHP = 5000;
                for (int m = count() - 1; m >= 0; m--) {
                    if (Army[m]->getknightType() != NORMAL) {
                        int damage = Army[m]->gethp() * Army[m]->getlevel() * Army[m]->knightBaseDamage;
                        UltmeciaHP -= damage;
                        if (UltmeciaHP <= 0) {
                            printInfo();
                            return true;
                        }
                        else {
                            Army[m]->sethp(0);
                            Army[m]->setgil(0);
                        }
                    }
                }
                if (UltmeciaHP > 0) {
                    for (int m = count() - 1; m >= 0; m--) {
                        Army[m]->sethp(0);
                        Army[m]->setgil(0);
                    }
                }
                printInfo();
                return false;
            }
            else {
                for (int m = count() - 1; m >= 0; m--) {
                    Army[m]->sethp(0);
                    Army[m]->setgil(0);
                }
                printInfo();
                return false;
            }
        }
        printInfo();
        if (count() <= 0) {
            return false;
        }
    }
}

int ArmyKnights::count() const {
    int k=0;
    for (int i = 0; i < numKnights; i++) {
        if (Army[i]->gethp() > 0) {
            k++;
        }
    }
    return k;
}

BaseKnight* ArmyKnights::lastKnight() const {
    for (int i = numKnights - 1; i >= 0; i--) {
        if (Army[i]->gethp() > 0) {
            return Army[i];
        }
    }
    return NULL;
}

bool ArmyKnights::hasPaladinShield() const{
    return PaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const{
    return LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const{
    return GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const{
    return ExcaliburSword;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string& file_armyknights) {
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string& file_events) {
    events = new Events(file_events);
}
void KnightAdventure::run(){
    armyKnights->printResult(armyKnights->adventure(events));
}

/* * * END implementation of class KnightAdventure * * */

Events::Events(const string& file_events) {
    ifstream x;
    x.open(file_events);
    x >> n;
    eve = new int[n];
    for (int i = 0; i < n; i++) {
        x >> eve[i];
    }
    x.close();
}
Events::~Events() {
    delete[]eve;
}
int Events::count() const {
    return n;
}
int Events::get(int i) const {
    return eve[i];
}
BaseItem::BaseItem() {
    this->link = NULL;
}
void BaseItem::setitemType(ItemType i) {
    itemType = i;
}
ItemType BaseItem::getitemType() {
    return itemType;
}
AntidoteClass::AntidoteClass() {
    setitemType(Antidote);
}
bool AntidoteClass::canUse(BaseKnight* knight) {
    if (knight->getknightType() == DRAGON) return false;
    else if (knight->getpoisoned() == 1) {
        return true;
    }
    else return false;
}
void AntidoteClass::use(BaseKnight* knight) {
    if (canUse(knight) == 1) {
        knight->setpoisoned(0);
    }
}

PhoenixDownI::PhoenixDownI() {
    setitemType(PhoenixI);
}
bool PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->gethp() <= 0) {
        return true;
    }
    else return false;
}
void PhoenixDownI::use(BaseKnight* knight) {
    if (knight->gethp() <= 0) {
        knight->sethp(knight->getmaxhp());
    }
}

PhoenixDownII::PhoenixDownII() {
    setitemType(PhoenixII);
}
bool PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 4)) {
        return true;
    }
    else return false;
}
void PhoenixDownII::use(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 4)) {
        knight->sethp(knight->getmaxhp());
    }
}

PhoenixDownIII::PhoenixDownIII() {
    setitemType(PhoenixIII);
}
bool PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 3)) {
        return true;
    }
    else return false;
}
void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 3)) {
        if (knight->gethp() <= 0) {
            knight->sethp(int(knight->getmaxhp() / 3));
        }
        else {
            knight->sethp(knight->gethp() + int(knight->getmaxhp() / 4));
        }
    }
}

PhoenixDownIV::PhoenixDownIV() {
    setitemType(PhoenixIV);
}
bool PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 2)) {
        return true;
    }
    else return false;
}
void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->gethp() < int(knight->getmaxhp() / 2)) {
        if (knight->gethp() <= 0) {
            knight->sethp(int(knight->getmaxhp() / 2));
        }
        else {
            knight->sethp(knight->gethp() + int(knight->getmaxhp() / 5));
        }
    }
}

void BaseOpponent::setevent_id(int i) {
    event_id = i;
}
void BaseOpponent::setOgil(int i) {
    gil = i;
}
void BaseOpponent::setObaseDamage(int i) {
    baseDamage = i;
}
void BaseOpponent::setlevelO(int i) {
    levelO = i;
}

MadBear::MadBear() {
    setevent_id(1);
    setOgil(100);
    setObaseDamage(10);
}
Bandit::Bandit() {
    setevent_id(2);
    setOgil(150);
    setObaseDamage(15);
}
LordLupin::LordLupin() {
    setevent_id(3);
    setOgil(450);
    setObaseDamage(45);
}
Elf::Elf() {
    setevent_id(4);
    setOgil(750);
    setObaseDamage(75);
}
Troll::Troll() {
    setevent_id(5);
    setOgil(800);
    setObaseDamage(95);
}
Tornbery::Tornbery() {
    setevent_id(6);
}
QueenOfCard::QueenOfCard() {
    setevent_id(7);
}
NinaDerings::NinaDerings() {
    setevent_id(8);
}
DurianGarden::DurianGarden() {
    setevent_id(9);
}
OmegaWeapon::OmegaWeapon() {
    setevent_id(10);
}
Hades::Hades() {
    setevent_id(11);
}