#include <vector>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

class weapon{
protected:
    int m_force;
public:
    weapon(int force=0):m_force(force) { };
    virtual ~weapon( ) { };
    
    virtual int attack( ) {return m_force;};
    int getForce( ) {return m_force;}
};

class sword: public weapon{
public:
    sword(int force):weapon(force) { };
    virtual ~sword( ) { };
    
    virtual int attack( );
};

class bomb: public weapon{
public:
    bomb( ){ };
    virtual ~bomb( ) { };
};

class arrow: public weapon{
public:
    int m_useTimes;
    arrow(int r):m_useTimes(0), weapon(r){ };
    virtual ~arrow( ) { };
};

int sword::attack( )
{
    int ret = m_force;
    m_force *= 0.8;
    return ret;
}

class weaponFactory {
public:
    static weapon* createWeapon(int weaponIndex, int force){
        weapon* w = NULL;
        switch (weaponIndex) {
            case 0:
                w = new sword(force);
                break;
            case 1:
                w = new bomb();
                break;
            case 2:
                w = new arrow(force);
                break;
        }
        return w;
    }
};

class headquater;
class baseCity;
class city;

const char *weapons[3] = {"sword","bomb","arrow"};

class warrior{
protected:
    int m_index;
    int m_life;
    int m_force;
    
    const char *m_headColor;
    headquater *m_hq;
    const char *m_species;
    
    bool m_useBomb(warrior *wa, const char *time);
public:
    weapon   *m_weapons[3];
    baseCity *currentCity;
    
    warrior(int idx, int life, int force, headquater *hq, const char *Species);
    virtual ~warrior( );
    
    void increaseLifeValue(int e){ m_life += e;}
    bool decreaseLifeValue(int e);
    
    int getLifeValue( ){ return m_life;};
    int getForce( ){return m_force;}
    int getIndex( ){return m_index;}
    const char *getSpecies( ){return m_species;}
    const char *getHeadColor( ){return m_headColor;}
    headquater *getHeadquater( ){return m_hq;}
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time);
    
    virtual void moveForward(baseCity *nextCity);
    
    void hurt(int element);
    virtual bool is_dead( );
    
    virtual void runaway(const char *time){ };
    
    void shoot(const char *time, baseCity *nextCity);
    void killedByArrow(warrior *wa, const char *time);
    void useBomb(const char *time);
    
    void sendAwardRequest( );
    void takeCitylife(const char *time);
    
    void report(const char *time);
};

class dragon: public warrior{
private:
    double m_moral;
public:
    dragon(int life, int force, headquater *hq, const char *time);
    virtual ~dragon( ) { };
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time);
    
    void increaseMoral( );
    void decreaseMoral( );
    
    void yell(const char *time);
};

class ninja: public warrior{
public:
    ninja(int life, int force, headquater *hq, const char *time);
    virtual ~ninja( ) { };
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time) { };
};


class iceman: public warrior{
    int mMoveSteps;
public:
    iceman(int life, int force, headquater *hq, const char *time);
    virtual ~iceman( ) { };
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time);
    
    virtual void moveForward(baseCity *nextCity);
};


class lion: public warrior{
public:
    int loyalty;
    lion(int life, int force, headquater *hq, const char *time);
    virtual ~lion( ) { };
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time);
    
    void decreaseLoyalty(int k);
    virtual void runaway(const char *time);
    
    void getKilled(warrior *wa, int force);
    
};


class wolf: public warrior{
public:
    wolf(int life, int force, headquater *hq, const char *time);
    virtual ~wolf( ) { };
    
    virtual void attack(warrior *wa, const char *time);
    virtual void fightBack(warrior *wa, const char *time);
    
    void seizeWeapons(warrior *wa);
};


class baseCity {
public:
    int m_index;
    
        //制造或者走来的武士
    warrior* red;
    warrior* blue;
    
    baseCity(int idx) {
        m_index = idx;
        red=NULL;
        blue=NULL;
    }
    virtual ~baseCity( ) { }
};

class city : public baseCity {
    
public:
    int m_flag;
    int m_life;
    int m_prev;
    int m_pprev;
    
    city(int index):baseCity(index), m_prev(-1), m_pprev(-1), m_flag(-1), m_life(0){ };
    virtual ~city( ) { };
    
    int getFlag( ) {return m_flag;}
    
    void produceLife()
    {
    m_life += 10;
    };
    
    int takeLife()
    {
    int _life = m_life;
    m_life = 0;
    return _life;
    }
    
    void setFlag(const char* time)
    {
        //004:40 blue flag raised in city 4
    if (m_pprev == -1) {
        return;
    }
    if (m_prev == m_pprev){
        if (m_prev == 1) {
            m_flag = 1;
            printf("%s blue flag raised in city %d\n", time, m_index);
        } else {
            m_flag = 0;
            printf("%s red flag raised in city %d\n", time, m_index);
        }
    }
    }
    
    void recordBattleResult(int pprev, int prev)
    {
    m_pprev = pprev;
    m_prev = prev;
    }
    
};



class headquater: public baseCity {
protected:
    const char* headColor;
    int m_dest;
    const char* seq[5];
    
    int warriorLifeValue[5];
    int warriorForceValue[5];
    
    int lastCreateIndex;
    
    int hqLifeValue;
    int warriorCount;
    
    int lionCount;
    int wolfCount;
    int icemanCount;
    int ninjaCount;
    int dragonCount;
    
    int lionLoyaltyDecrease;
    int arrawForce;
    
    std::vector<warrior *> warriors;
    std::vector<warrior *> warriorsToAward;
    
    warrior *_createWarrior(const char* warriorName, int life, int force, const char* time);
public:
    warrior* enemy[2];
    
    headquater(int index, int dest, int m);
    virtual ~headquater();
    
    virtual void setWarriorLifeValue(int dragon, int ninja, int iceman, int lion, int wolf) { }
    virtual void setWarriorForceValue(int dragon, int ninja, int iceman, int lion, int wolf) { }
    void setLionLoyaltyDecrease(int k){ lionLoyaltyDecrease = k;}
    void setArrawForce(int r){ arrawForce = r;}
    
    const char *getHeadColor( ) {return headColor;}
    int getDest( ) {return m_dest;}
    int getHqLifeValue( ) {return hqLifeValue;}
    int getWarriorCount( ) {return warriorCount;}
    int getLionLoyaltyDecrease( ) {return lionLoyaltyDecrease;}
    
    
    int getDragonCount( ) {return dragonCount;}
    int getNinjaCount( ) {return ninjaCount;}
    int getIcemanCount( ) {return icemanCount;}
    int getWolfCount( ) {return wolfCount;}
    int getLionCount( ) {return lionCount;}
    
    void increaseHqLifeValue(int element){hqLifeValue += element;}
    void decreaseHqLifeValue(int element){
        hqLifeValue -= element;
        if (hqLifeValue < 0)
            hqLifeValue = 0;
    }
    
    int createWarrior(const char* time);
    
    void receiveAwardRequest(warrior * wa);
    void awardWarriors( );
    
    void removeWarrior(warrior* wa);
    void report(const char* time);
};


class Red : public headquater {
public:
    Red(int index, int dest, int m);
    virtual ~Red(){};
    
    virtual void setWarriorLifeValue(int dragon, int ninja, int iceman, int lion, int wolf);
    virtual void setWarriorForceValue(int dragon, int ninja, int iceman, int lion, int wolf);
};

class Blue:public headquater{
public:
    Blue(int index, int dest, int m);
    virtual ~Blue() { };
    
    virtual void setWarriorLifeValue(int dragon, int ninja, int iceman, int lion, int wolf);
    virtual void setWarriorForceValue(int dragon, int ninja, int iceman, int lion, int wolf);
};

warrior::warrior(int idx, int life, int force, headquater *hq, const char *species):
m_index(idx), m_life(life), m_force(force), m_hq(hq), m_species(species) {
    m_headColor = hq->getHeadColor();
    for (int i = 0; i < 3; ++i)
        m_weapons[i] = NULL;
}

warrior::~warrior( )
{
    for (int i = 0; i < 3; ++i)
        delete m_weapons[i];
}

bool warrior::is_dead( )
{
    return (m_life <= 0);
}

bool warrior::decreaseLifeValue(int e)
{
    if (m_life <= e) {
        this->~warrior();
        return true;
    }
    m_life -= e;
    return false;
}

void warrior::attack(warrior *wa, const char *time)
{
    int attackForce;
    if (m_weapons[0]){
        attackForce = m_force + m_weapons[0]->attack();
        wa->hurt(attackForce);
        if (m_weapons[0]->getForce() == 0){
            delete m_weapons[0];
            m_weapons[0] = NULL;
        }
    } else {
        attackForce = m_force;
        wa->hurt(attackForce);
    }
        //000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
    printf("%s %s %s %d attacked %s %s %d in city %d with %d and force %d\n",
           time, m_headColor, m_species, m_index, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index, m_life, attackForce);
}

void warrior::fightBack(warrior *wa, const char *time)
{
        //001:40 blue dragon 2 fought back against red lion 2 in city 1
    printf("%s %s %s %d fought back against %s %s %d in city %d",
           time, m_headColor, m_species, m_index, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
    if (m_weapons[0]){
        wa->hurt(m_force / 2 + m_weapons[0]->attack());
        if (m_weapons[0]->getForce() == 0){
            delete m_weapons[0];
            m_weapons[0] = NULL;
        }
    } else {
        wa->hurt(m_force / 2);
    }
}

void warrior:: hurt(int element)
{
    decreaseLifeValue(element);
}

void warrior::sendAwardRequest( )
{
    m_hq->receiveAwardRequest(this);
}

bool warrior::m_useBomb(warrior *wa, const char *time)
{
    bool fightGetKilled = false;
    bool fightBackGetKilled = false;
        //主动攻击会死
    int fightForce = m_force;
    if (m_weapons[0]) {
        fightForce += m_weapons[0]->getForce();
    }
        //杀不死
    if (fightForce < wa->getLifeValue()) {
        int wa_fightBackForce = wa->getForce() / 2;
        if (wa->m_weapons[0]) {
            wa_fightBackForce += wa->m_weapons[0]->getForce();
        }
        if (wa_fightBackForce >= m_life) {
            fightGetKilled = true;
        }
    }
    
        //被敌人攻击会死
    int wa_fightForce = wa->getForce();
    if (wa->m_weapons[0]) {
        wa_fightForce += wa->m_weapons[0]->getForce();
    }
    if (wa_fightForce >= m_life) {
        fightBackGetKilled = true;
    }
    
    if (fightGetKilled && fightBackGetKilled) {
            //000:38 blue dragon 1 used a bomb and killed red lion 7
        printf("%s %s %s %d used a bomb and killed %s %s %d",
               time, m_headColor, m_species, m_index, wa->getHeadColor(), wa->getSpecies(), wa->m_index);
        this->m_hq->removeWarrior(this);
        wa->m_hq->removeWarrior(wa);
        
            //所在城市的红武士和蓝武士指针都置空
        currentCity->red = NULL;
        currentCity->blue = NULL;
        
        this->~warrior();
        wa->~warrior();
        
        return true;
    }
    
    return false;
}

void warrior::shoot(const char *time, baseCity *nextCity)
{
        //没有arrow
    if (!m_weapons[2]) {
        return;
    }
        //对方到达司令部
    int currentCityIndex = currentCity->m_index;
    if (currentCityIndex == m_hq->getDest()) {
        return;
    }
        //下一个城市要是有敌人，调用敌人的killedByArrow
    if (!strcmp(m_headColor, "red")) {
        if (nextCity->blue) {
            printf("%s %s %s %d shot\n", time, m_headColor, m_species, m_index);
            
                //arrow只能用3次
            arrow  *tmp = (arrow *)m_weapons[2];
            ++ tmp->m_useTimes;
            if (tmp->m_useTimes >= 3) {
                delete m_weapons[2];
                m_weapons[2] = NULL;
            }
            
            nextCity->blue->killedByArrow(this, time);
        }
    } else {
        if (nextCity->red != NULL) {
            
            printf("%s %s %s %d shot\n", time, m_headColor, m_species, m_index);
            
                //arrow只能用3次
            arrow  *tmp = (arrow *)m_weapons[2];
            ++ tmp->m_useTimes;
            if (tmp->m_useTimes >= 3) {
                delete m_weapons[2];
                m_weapons[2] = NULL;
            }
            
            nextCity->red->killedByArrow(this, time);
        }
    }
}


void warrior::killedByArrow(warrior *wa, const char *time)
{
        //000:35 blue dragon 1 shot and killed red lion 4
    printf("%s %s %s %d shot and killed %s %s %d\n",
           time, wa->getHeadColor(), wa->getSpecies(),
           wa->m_index, m_headColor, m_species, m_index);
    for (int i = 0; i < 3; ++i) {
        if (m_weapons[i] != NULL) {
            delete m_weapons[i];
        }
    }
    m_hq->removeWarrior(this);
    if (strncmp(m_headColor, "red", 3) == 0) {
        currentCity->red = NULL;
    } else {
        currentCity->blue = NULL;
    }
    this->~warrior();
}

void warrior::takeCitylife(const char *time)
{
    int currentCityIndex = currentCity->m_index;
    if (currentCityIndex == m_hq->getDest()) {
        return;
    }
    city  *tmp = (city *)currentCity;
    int increase = tmp->takeLife();
    m_hq->increaseHqLifeValue(increase);
        //001:40 blue dragon 2 earned 10 elements for his headquarter
    printf("%s %s %s %d earned %d elements for his headquarter\n", time, m_headColor, m_species, m_index, increase);
}

void warrior::moveForward(baseCity *nextCity)
{
    if (!strncmp(m_headColor, "red", 3)) {
        currentCity->red = NULL;
        nextCity->red = this;
        currentCity = nextCity;
    } else {
        currentCity->blue = NULL;
        nextCity->blue = this;
        currentCity = nextCity;
    }
}

void warrior::useBomb(const char *time)
{
    if (m_weapons[1] == NULL) {
        return;
    }
    if (strcmp(m_headColor, "red")) {
        if (currentCity->blue != NULL) {
            m_useBomb(currentCity->blue, time);
        }
    } else {
        if (currentCity->red != NULL) {
            m_useBomb(currentCity->red, time);
        }
    }
}

void warrior::report(const char *time)
{
        //000:55 blue wolf 2 has arrow(2),bomb,sword(23)
        //000:55 blue wolf 4 has no weapon
        // 000:55 blue wolf 5 has sword(20)
    
    
    if (m_weapons[0]) {
        int force = m_weapons[0]->getForce();
        if (m_weapons[1]) {
            if (m_weapons[2]) {
                arrow *tmp = (arrow *)m_weapons[2];
                int left = 3 - tmp->m_useTimes;
                printf("%s %s %s %d has arrow(%d),bomb,sword(%d)\n",
                       time, m_headColor, m_species, m_index, left, force);
            } else {
                printf("%s %s %s %d has bomb,sword(%d)\n",
                       time, m_headColor, m_species, m_index, force);
            }
        } else {
            if (m_weapons[2]) {
                arrow *tmp = (arrow *)m_weapons[2];
                int left = 3 - tmp->m_useTimes;
                printf("%s %s %s %d has arrow(%d),sword(%d)\n",
                       time, m_headColor, m_species, m_index, left, force);
            } else {
                printf("%s %s %s %d has sword(%d)\n",
                       time, m_headColor, m_species, m_index, force);
            }
        }
    } else {
        if (m_weapons[1]) {
            if (m_weapons[2]) {
                arrow *tmp = (arrow *)m_weapons[2];
                int left = 3 - tmp->m_useTimes;
                printf("%s %s %s %d has arrow(%d),bomb\n",
                       time, m_headColor, m_species, m_index, left);
            } else {
                printf("%s %s %s %d has bomb\n",
                       time, m_headColor, m_species, m_index);
            }
        } else {
            if (m_weapons[2]) {
                arrow *tmp = (arrow *)m_weapons[2];
                int left = 3 - tmp->m_useTimes;
                printf("%s %s %s %d has arrow(%d)\n",
                       time, m_headColor, m_species, m_index, left);
            } else {
                printf("%s %s %s %d has no weapon\n",
                       time, m_headColor, m_species, m_index);
            }
        }
    }
    
    
}
    //==============================>dragon<=======================================//
dragon::dragon(int life, int force, headquater *hq, const char *time):warrior(hq->getWarriorCount(), life, force, hq, "dragon")
{
    int m_weaponIndex = hq->getWarriorCount() % 3;
    m_weapons[m_weaponIndex] = weaponFactory::createWeapon(m_weaponIndex, force);
    m_moral = (float)m_hq->getHqLifeValue() / (float)m_life;
    printf("%s %s dragon %d born\n", time, hq->getHeadColor(), hq->getWarriorCount());
    printf("Its morale is %1.2f\n", m_moral);
}

void dragon::attack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    warrior::attack(wa, time);
    if (wa->is_dead()){
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //001:40 red lion 2 was killed in city 1
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
        increaseMoral( );
        sendAwardRequest( );
    } else {
        wa->fightBack(this, time);
        if (not is_dead())
            decreaseMoral();
    }
    if (m_moral > 0.8)
            //003:40 blue dragon 2 yelled in city 4
        yell(time);
}

void dragon::increaseMoral( )
{
    m_moral += 0.2;
}

void dragon::decreaseMoral( )
{
    m_moral -= 0.2;
}

void dragon::yell(const char *time)
{
        //003:40 blue dragon 2 yelled in city 4
    printf("%s %s dragon %d yelled in city %d\n", time, m_headColor, m_index, currentCity->m_index);
}

void dragon::fightBack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::fightBack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        increaseMoral();
        sendAwardRequest( );
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
    } else {
        decreaseMoral();
    }
}


    //==============================>ninja<=======================================//
    // todo: weapon force
ninja::ninja(int life, int force, headquater *hq, const char *time):warrior(hq->getWarriorCount(), life, force, hq, "ninja"){
    int m_weaponIndex1 = hq->getWarriorCount() % 3;
    int m_weaponIndex2 = (hq->getWarriorCount() + 1) % 3;
    m_weapons[m_weaponIndex1] = weaponFactory::createWeapon(m_weaponIndex1, force);
    m_weapons[m_weaponIndex2] = weaponFactory::createWeapon(m_weaponIndex2, force);
    printf("%s %s ninja %d born with strength %d,%d ninja in %s headquarter\n",
           time, hq->getHeadColor(), hq->getWarriorCount(), life, hq->getNinjaCount(), hq->getHeadColor());
    printf("It has a %s and a %s\n", weapons[m_weaponIndex1], weapons[m_weaponIndex2]);
}

void ninja::attack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::attack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        sendAwardRequest( );
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
    }
}


    //==============================>iceman<=======================================//
iceman::iceman(int life, int force, headquater *hq, const char *time):warrior(hq->getWarriorCount(), life, force, hq, "iceman")
{
    mMoveSteps = 0;
    int m_weaponIndex = hq->getWarriorCount() % 3;
    m_weapons[m_weaponIndex] = weaponFactory::createWeapon(m_weaponIndex, force);
    printf("%s %s iceman %d born with strength %d,%d iceman in %s headquarter\n",
           time, hq->getHeadColor(), hq->getWarriorCount(), life, hq->getIcemanCount(), hq->getHeadColor());
    printf("It has a %s\n", weapons[m_weaponIndex]);
}

void iceman::attack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::attack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        sendAwardRequest( );
        
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
        
    } else {
        wa->fightBack(this, time);
    }
}

void iceman::fightBack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::fightBack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        sendAwardRequest( );
        
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
    }
}

void iceman::moveForward(baseCity *nextCity)
{
    ++ mMoveSteps;
    
    if (!(mMoveSteps % 2)){
        if (m_life > 9){
            m_life -= 9;
        } else {
            m_life = 1;
        }
        m_force += 20;
    }
    warrior::moveForward(nextCity);
}

    //==============================>lion<=======================================//
lion::lion(int life, int force, headquater *hq, const char *time):
warrior(hq->getWarriorCount(), life, force, hq, "lion"), loyalty(hq->getHqLifeValue()){
    printf("%s %s lion %d born\n",
           time, hq->getHeadColor(), hq->getWarriorCount());
    printf("Its loyalty is %d\n", loyalty);
};

void lion::attack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::attack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        printf("%s %s %s %d was killed in city %d",
               time, wa->getHeadColor(), wa->getSpecies(), wa->getIndex(), currentCity->m_index);
        sendAwardRequest( );
        
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
    } else {
        wa->fightBack(this, time);
        if (not is_dead()){
            decreaseLoyalty(m_hq->getLionLoyaltyDecrease());
        } else{
            wa->increaseLifeValue(addLife);
        }
    }
}

void lion::fightBack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::fightBack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        sendAwardRequest( );
        
        wa->getHeadquater()->removeWarrior(wa);
        wa->~warrior();
    } else {
        decreaseLoyalty(m_hq->getLionLoyaltyDecrease());
    }
}

void lion::runaway(const char *time)
{
    if (loyalty <= 0){
            //000:05 blue lion 1 ran away
        printf("%s %s lion %d ran way\n", time, m_headColor, m_index);
        m_hq->removeWarrior(this);
        if (strcmp(m_species, "red")) {
            currentCity->red = NULL;
        } else {
            currentCity->blue = NULL;
        }
        this->~lion();
    }
}

void lion::decreaseLoyalty(int k)
{
    loyalty -= k;
}


    //==============================>wolf<=======================================//
wolf::wolf(int life, int force, headquater *hq, const char *time):
warrior(hq->getWarriorCount(), life, force, hq, "wolf") {
    printf("%s %s wolf %d born with strength %d,%d wolf in %s headquarter\n",
           time, hq->getHeadColor(), hq->getWarriorCount(), life, hq->getWolfCount(), hq->getHeadColor());
    for (int i = 0; i < 3; ++i)
        m_weapons[i] = NULL;
};

void wolf::attack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::attack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        sendAwardRequest( );
    } else {
        wa->fightBack(this, time);
    }
}

void wolf::fightBack(warrior *wa, const char *time)
{
    int addLife = 0;
    if (strcmp(wa->getSpecies(), "lion") == 0) {
        addLife += wa->getLifeValue();
    }
    
    warrior::fightBack(wa, time);
    
    if (wa->is_dead()){
        if (strcmp(wa->getSpecies(), "lion") == 0) {
            m_life += addLife;
        }
            //城市记录战果
        city *tmp = (city *)currentCity;
        tmp->m_pprev = tmp->m_prev;
        if (strcmp(m_headColor, "red") == 0) {
            tmp->m_prev = 0;
        } else {
            tmp->m_prev = 1;
        }
        sendAwardRequest( );
    }
    
}

void wolf::seizeWeapons(warrior *wa)
{
    for (int i  = 0; i < 3; ++i) {
        if (not m_weapons[i] && wa->m_weapons[i]){
            m_weapons[i] = wa->m_weapons[i];
            wa->m_weapons[i] = NULL;
        }
    }
}

headquater::headquater(int index,int dest, int m):baseCity(index), m_dest(dest){
    memset(warriorLifeValue, 0, sizeof(warriorLifeValue));
    hqLifeValue = m;
    lastCreateIndex = -1;
    warriorCount = 0;
    lionCount = 0;
    wolfCount = 0;
    icemanCount = 0;
    ninjaCount = 0;
    dragonCount = 0;
    enemy[0] = NULL;
    enemy[1] = NULL;
};

headquater::~headquater( )
{
    int l = (int)warriors.size( );
    for (int i = 0; i < l; ++i)
        delete warriors[i];
}

warrior* headquater::_createWarrior(const char *warriorName, int life, int force, const char *time)
{
    ++ warriorCount;
    warrior* w = NULL;
    
    if (strncmp(warriorName, "dragon", 1) == 0){
        ++ dragonCount;
        w = new dragon(life, force, this, time);
    } else if (strncmp(warriorName, "lion", 1) == 0){
        ++ lionCount;
        w = new lion(life, force, this, time);
    } else if (strncmp(warriorName, "ninja", 1) == 0){
        ++ ninjaCount;
        w = new ninja(life, force, this, time);
    } else if (strncmp(warriorName, "iceman", 1) == 0){
        ++ icemanCount;
        w = new iceman(life, force, this, time);
    } else{
        ++ wolfCount;
        w = new wolf(life, force, this, time);
    }
    return w;
}

int headquater::createWarrior(const char *time)
{
    int currentCreateIndex;
    if (lastCreateIndex == 4){
        currentCreateIndex = 0;
    } else {
        currentCreateIndex = lastCreateIndex + 1;
    }
    const char* warriorName = seq[currentCreateIndex];
    int life = warriorLifeValue[currentCreateIndex];
    int force = warriorForceValue[currentCreateIndex];
    
    if (hqLifeValue < life) {
        return 0;
    } else {
        hqLifeValue -= life;
        warrior* w = _createWarrior(warriorName, life, force, time);
        warriors.push_back(w);
        if (!strncmp(headColor, "red", 3)) red = w;
        else blue = w;
        w->currentCity = this;
        lastCreateIndex = currentCreateIndex;
        return 1;
    }
}

void headquater::receiveAwardRequest(warrior *wa)
{
    warriorsToAward.push_back(wa);
}

void headquater::awardWarriors( )
{
    int num = (int)warriorsToAward.size();
    if (hqLifeValue >= num * 8) {
        for (int i = 0; i < num; ++i)
            warriorsToAward[i]->increaseLifeValue(8);
    } else {
        if (strncmp(headColor, "red", 1)) {
            for (int i = 0; i < num && hqLifeValue >= 8; ++i) {
                warriorsToAward[i]->increaseLifeValue(8);
                hqLifeValue -= 8;
            }
        } else {
            for (int i = num-1; i >= 0 && hqLifeValue >= 8; --i) {
                warriorsToAward[i]->increaseLifeValue(8);
                hqLifeValue -= 8;
            }
        }
    }
}

void headquater::removeWarrior(warrior* wa)
{
    const char* species = wa->getSpecies();
    if (strcmp(species, "dragon") == 0) {
        dragonCount --;
    } else if (strcmp(species, "lion") == 0){
        lionCount --;
    } else if (strcmp(species, "wolf") == 0){
        wolfCount --;
    } else if (strcmp(species, "ninja") == 0){
        ninjaCount --;
    } else {
        icemanCount --;
    }
    warriors[wa->getIndex()-1] = NULL;
}

void headquater::report(const char *time)
{
        //00:50 100 elements in red headquarter
    printf("%s %d elements in %s headquarter\n", time, hqLifeValue, headColor);
}


    //==========================================================================================//
Red::Red(int index, int dest, int m) : headquater(index, dest, m) {
    headquater::headColor = "red";
    headquater::seq[0] = "iceman";
    headquater::seq[1] = "lion";
    headquater::seq[2] = "wolf";
    headquater::seq[3] = "ninja";
    headquater::seq[4] = "dragon";
}

void Red::setWarriorLifeValue(int dragon, int ninja, int iceman, int lion, int wolf){
    warriorLifeValue[0]  = iceman;
    warriorLifeValue[1] = lion;
    warriorLifeValue[2] = wolf;
    warriorLifeValue[3] = ninja;
    warriorLifeValue[4] = dragon;
}

void Red::setWarriorForceValue(int dragon, int ninja, int iceman, int lion, int wolf){
    warriorForceValue[0] = iceman;
    warriorForceValue[1] = lion;
    warriorForceValue[2] = wolf;
    warriorForceValue[3] = ninja;
    warriorForceValue[4] = dragon;
}

Blue::Blue(int index, int dest, int m) : headquater(index, dest, m) {
    headquater::headColor = "blue";
    headquater::seq[0] = "lion";
    headquater::seq[1] = "dragon";
    headquater::seq[2] = "ninja";
    headquater::seq[3] = "iceman";
    headquater::seq[4] = "wolf";
};

void Blue::setWarriorLifeValue(int dragon, int ninja, int iceman, int lion, int wolf) {
    warriorLifeValue[0] = lion;
    warriorLifeValue[1] = dragon;
    warriorLifeValue[2] = ninja;
    warriorLifeValue[3] = iceman;
    warriorLifeValue[4] = wolf;
}

void Blue::setWarriorForceValue(int dragon, int ninja, int iceman, int lion, int wolf){
    warriorForceValue[0] = lion;
    warriorForceValue[1] = dragon;
    warriorForceValue[2] = ninja;
    warriorForceValue[3] = iceman;
    warriorForceValue[4] = wolf;
}

class GameMonitor
{
public:
    int mMaxtime;
    int mCurrentTime;
    int mNbCities;
    
    headquater *red;
    headquater *blue;
    
    baseCity *cities[21];
    
    
    GameMonitor(int M, int N, int R, int K, int T):
    mMaxtime(T), mCurrentTime(0), mNbCities(N)
    {
    red = new Red(0, N+1, M);
    blue = new Blue(N+1, 0, M);
    
    red->setArrawForce(R);
    blue->setArrawForce(R);
    
    red->setLionLoyaltyDecrease(K);
    blue->setLionLoyaltyDecrease(K);
    
        //第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000
    
        //第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000
    int dragon, ninja, iceman, lion, wolf;
    int dragonForce, ninjaForce, icemanForce, lionForce, wolfForce;
    
    std::cin >> dragon >> ninja >> iceman >> lion >> wolf;
    std::cin >> dragonForce >> ninjaForce >> icemanForce >> lionForce >> wolfForce;
    
    red->setWarriorLifeValue(dragon, ninja, iceman, lion, wolf);
    red->setWarriorForceValue(dragonForce, ninjaForce, icemanForce, lionForce, wolfForce);
    
    blue->setWarriorLifeValue(dragon, ninja, iceman, lion, wolf);
    blue->setWarriorForceValue(dragonForce, ninjaForce, icemanForce, lionForce, wolfForce);
    
    for (int i = 1; i < N+1; ++i)
        cities[i] = new city(i);
    for (int i = N+2; i < 21; ++i)
        cities[i] = NULL;
    
    cities[0] = red;
    cities[N+1] = blue;
    };
    
    ~GameMonitor( ){
        for (int i = 0; i < mNbCities+2; ++i)
            delete cities[i];
    }
    
        //2) lion逃跑
    void lionRunAway(const char *time)
    {
    if (cities[0]->red) {
        if (strcmp(cities[0]->red->getSpecies(), "lion") == 0)
            cities[0]->red->runaway(time);
    }
    for (int i = 1; i < mNbCities+1; ++i) {
        if (cities[i]->red)
            if (strcmp(cities[i]->red->getSpecies(), "lion") == 0)
                cities[i]->red->runaway(time);
        
        if (cities[i]->blue)
            if (strcmp(cities[i]->blue->getSpecies(), "lion") == 0)
                cities[i]->blue->runaway(time);
    }
    if (cities[mNbCities+1]->blue) {
        if (strcmp(cities[mNbCities+1]->blue->getSpecies(), "lion") == 0)
            cities[mNbCities+1]->blue->runaway(time);
    }
    }
    
        //3) 武士前进到某一城市
        //12) 武士抵达敌军司令部
        //13) 司令部被占领
    bool warriorsMarch(const char *time)
    {
    for (int i = 0; i < mNbCities+2; ++i) {
        if (cities[i]->red) {
            warrior *_red = cities[i]->red;
                //不是敌军司令部
            if (i != mNbCities+1) {
                    //下一步不是敌军司令部
                if (i+1 != mNbCities+1) {
                    _red->moveForward(cities[i+1]);
                        //000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                    printf("%s red %s %d marched to city %d with %d elements and force %d\n",
                           time, _red->getSpecies(), _red->getIndex(),
                           i+1, _red->getLifeValue(), _red->getForce());
                } else {
                        //敌方司令部有己方武士, 游戏结束，返回true
                    if (cities[i+1]->red){
                            //002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
                        printf("%s red %s %d reached blue headquarter "
                               "with %d elements and force %d\n",
                               time,  _red->getSpecies(), _red->getIndex(),
                               _red->getLifeValue(), _red->getForce());
                            //003:10 blue headquarter was taken
                        printf("%s blue headquarter was taken\n", time);
                        return true;
                    } else{
                        _red->moveForward(cities[i+1]);
                            //001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
                        printf("%s red %s %d reached blue headquarter "
                               "with %d elements and force %d\n",
                               time, _red->getSpecies(), _red->getIndex(),
                               _red->getLifeValue(), _red->getForce());
                    }
                }
            }
        }
        if (cities[i]->blue) {
                //不是敌军司令部
            if (i != 0) {
                warrior *_blue = cities[i]->blue;
                    //下一步不是敌军司令部
                if (i != 1){
                    _blue->moveForward(cities[i-1]);
                        //000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                    printf("%s blue %s %d marched to city %d with %d elements and force %d\n",
                           time, _blue->getSpecies(), _blue->getIndex(),
                           i-1, _blue->getLifeValue(), _blue->getForce());
                } else{
                        //敌方司令部有己方武士, 游戏结束，返回true
                    if (cities[0]->blue){
                        printf("%s blue %s %d reached red headquarter "
                               "with %d elements and force %d\n",
                               time, _blue->getSpecies(), _blue->getIndex(),
                               _blue->getLifeValue(), _blue->getForce());
                            //003:10 blue headquarter was taken
                        printf("%s red headquarter was taken\n", time);
                        return true;
                    } else{
                        _blue->moveForward(cities[i-1]);
                            //001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
                        printf("%s blue %s %d reached red headquarter "
                               "with %d elements and force %d\n",
                               time, _blue->getSpecies(), _blue->getIndex(),
                               _blue->getLifeValue(), _blue->getForce());
                    }
                }
            }
        }
    }
    return false;
    }
    
        //4)武士放箭
    void warriorsShoot(const char *time)
    {
    if (cities[0]->red)
        cities[0]->red->shoot(time, cities[1]);
    for (int i = 1; i < mNbCities + 1; ++i){
        if (cities[i]->red)
            cities[i]->red->shoot(time, cities[i+1]);
        if (cities[i]->blue)
            cities[i]->blue->shoot(time, cities[i-1]);
    }
    if (cities[mNbCities + 1]->blue)
        cities[mNbCities + 1]->blue->shoot(time, cities[mNbCities]);
    }
    
        //5)武士使用bomb
    void warriorsUseBomb(const char *time)
    {
    for (int i = 1; i < mNbCities + 1; ++i){
        if (cities[i]->red == NULL || cities[i]->blue == NULL) {
            continue;
        }
        cities[i]->red->useBomb(time);
        cities[i]->blue->useBomb(time);
    }
    }
    
        //6) 武士主动进攻
    void attack(const char *time)
    {
    for (int i = 1; i < mNbCities + 1; ++i) {
        city *_city = (city *)cities[i];
        if (!_city->red || !_city->blue) {
            continue;
        }
            //插红旗的红武士先攻击， vise visa
        if (!_city->getFlag( )) {
            _city->red->attack(_city->blue, time);
        } else if (_city->getFlag() == 1){
            _city->blue->attack(_city->red, time);
        } else {
            if (i % 2 == 1) {
                    //红旗的红武士先攻击
                _city->red->attack(_city->blue, time);
            } else {
                _city->blue->attack(_city->red, time);
            }
        }
    }
    }
    
    void cityProduceLife(const char *time)
    {
    for (int i = 1; i < mNbCities + 1; ++i) {
        city *tmp = (city *)cities[i];
        tmp->produceLife();
    }
    }
    
        //10) 武士获取生命元( elements )
    void takeCityLife(const char *time)
    {
    for (int i = 1; i < mNbCities + 1; ++i) {
        city *_city = (city *)cities[i];
        if (_city->red && _city->blue) {
            continue;
        }
        if (_city->red) {
            _city->red->takeCitylife(time);
            continue;
        }
        if (_city->blue) {
            _city->blue->takeCitylife(time);
        }
    }
    }
    
        //11) 旗帜升起
    void raiseFlag(const char *time)
    {
    for (int i = 1; i < mNbCities + 1; ++i) {
        city *_city = (city *)cities[i];
        _city->setFlag(time);
        
    }
    }
    
        //14)司令部报告生命元数量
    void headquarterReport(const char *time)
    {
    red->report(time);
    blue->report(time);
    }
    
        //15)武士报告武器情况
    void warriorReport(const char *time)
    {
    for (int i = 0; i < mNbCities + 2; ++i)
        if (cities[i]->red)
            cities[i]->red->report(time);
    
    for (int i = 0; i < mNbCities + 2; ++i)
        if (cities[i]->blue)
            cities[i]->blue->report(time);
    }
    
    void play() {
        bool endOfGame = false;
        for (int t = 0; t <= mMaxtime; ++t) {
            int min = t % 60;
            int h = t / 60;
            char time[6];
            sprintf(time, "%03d:%02d", h, min);
            switch (min) {
                case 0:
                    red->createWarrior(time);
                    blue->createWarrior(time);
                    break;
                case 5:
                    lionRunAway(time);
                    break;
                case 10:
                    endOfGame = warriorsMarch(time);
                    break;
                case 20:
                    cityProduceLife(time);
                    break;
                case 30:
                    takeCityLife(time);
                    break;
                case 35:
                    warriorsShoot(time);
                    break;
                case 38:
                    warriorsUseBomb(time);
                    break;
                case 40:
                    attack(time);
                    raiseFlag(time);
                    break;
                case 50:
                    headquarterReport(time);
                    break;
                case 55:
                    warriorReport(time);
            }
            if (endOfGame)
                return;
        }
    }
};

int main(int argc, const char * argv[]) {
    int caseNumber;
    cin >> caseNumber;
    
    for (int i = 0; i < caseNumber; ++i) {
        printf("Case %d:\n", i+1);
        
        int M,N,R,K, T;
        cin >> M >> N >> R >> K >> T;
        
        GameMonitor monitor(M, N, R, K, T);
        monitor.play( );
    }
    
    return 0;
}






