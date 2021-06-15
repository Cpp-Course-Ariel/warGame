#include "Soldier.hpp"
#include <math.h>

//FootSoldier: initial health points=100, damage per activity=10
namespace WarGame{

    class SniperCommander : public Soldier{
        private:

        public:
        SniperCommander(uint player):Soldier(120,100,player){}

        // need to change attack function
        void Attacking(std::vector<std::vector<Soldier*>>& board,uint Player, std::pair<int,int> placeOfSoldier){
            std::pair <int,int> placeToattack = {0,0};
            int maxHealth = 0;
                for (int i = 0; i < board.size(); i++){
                    for (int j = 0; j < board[0].size(); j++){
                        if(board[i][j] !=nullptr){
                           if (board[i][j]->getPlayer() != Player){//checks if the solfier that found is the other player soldier
                                if( board[i][j]->getLife() >= maxHealth ){
                                     maxHealth = board[i][j]->getLife();
                                     placeToattack = {i,j};//enter the place of the closest soldier
                                }
                            }
                        }
                    }
                    
                }

                 if (maxHealth != 0){
                     board[placeToattack.first][placeToattack.second]->decreaseHealth(board[placeOfSoldier.first][placeOfSoldier.second]->getDamage());
                     if(board[placeToattack.first][placeToattack.second]->getLife() <=0){
                         board[placeToattack.first][placeToattack.second] = nullptr;
                     }
                 }
                 
                 for (int i = 0; i < board.size(); i++){
                     for (int j = 0; j < board[0].size(); j++){
                         if(board[i][j] != nullptr){
                            if(board[i][j]->getPlayer() == Player  && dynamic_cast<Sniper*>(board[i][j]) ){
                                 board[i][j]->Attacking(board,Player,std::pair<int,int> {i,j} );
                            }
                         }
                     }
                 }
            }
    };
}