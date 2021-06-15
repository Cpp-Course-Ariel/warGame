#pragma once
#include <stdio.h>
#include <iostream>

namespace WarGame{
class Soldier{
    private:
    uint Life;
    uint Damage;
    uint Player;
    uint maxHealth;
    
    public:
    Soldier(uint life, uint damage,uint player):Life(life),Damage(damage),Player(player),maxHealth(life){};
    Soldier():Life(0),Damage(0),Player(0){};

    uint getPlayer(){
        return this->Player;
    }
    uint getLife(){
        return this->Life;
    }
    uint getDamage(){
        return this->Damage;
    }

    void decreaseHealth(uint num){
        this->Life = this->Life - num;
        if(this->Life <=0){
            this->Life =0;
        }
    }
    void addLife(uint addlife){
        this->Life = this->Life + addlife;
    }
    void heal(){
        this->Life = this->maxHealth;
    }

    virtual void Attacking(std::vector<std::vector<Soldier*>>&,uint,std::pair<int,int>) =0;
    
    virtual ~Soldier(){}
    };
};
