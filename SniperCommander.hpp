#include "Soldier.hpp"
#include <math.h>

//FootSoldier: initial health points=100, damage per activity=10
namespace WarGame{

    class SniperCommander : public Soldier{
        private:

        public:
        SniperCommander(uint player):Soldier(100,10,player){}

        // need to change attack function
        void Attacking(WarGame::Board& board,int PlayerToAttack, std::pair<int,int> placeOfSoldier){
            std::pair <int,int> placeToattack = {0,0};
            int minDistance = INT16_MAX;
            if(board.has_soldiers(PlayerToAttack)){//checks if there is soldiers to other player
                for (size_t i = 0; i < 8; i++){
                    for (size_t j = 0; j < 8; j++){
                        if (board[{i,j}]->getPlayer() == PlayerToAttack){//checks if the solfier that found is the other player soldier
                            if( pow(placeOfSoldier.first - i,2) + pow(placeOfSoldier.second - j,2) < minDistance )
                                placeToattack = {i,j};//enter the place of the closest soldier
                        }
                    }
                    
                }
                 if (minDistance < INT16_MAX){
                     board[{placeToattack}]->decreaseHealth(10);
                 }
            }
            else std::cout << ("No soldier left") << std::endl;
        }

 
    };
}