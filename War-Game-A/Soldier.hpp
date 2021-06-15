#pragma once
#include <stdio.h>
#include <iostream>

namespace WarGame{
class Soldier{
    private:
    uint Life;
    uint Damage;
    uint Player;
    
    public:
    Soldier(uint life, uint damage,uint player):Life(life),Damage(damage),Player(player){};
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
    }
    void addLife(uint addlife){
        this->Life = this->Life + addlife;
    }

    //virtual void Attacking(WarGame::Board&,int,std::pair<int,int>);


    };
};
