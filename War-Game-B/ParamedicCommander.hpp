#include "Soldier.hpp"
#include <math.h>

//FootSoldier: initial health points=100, damage per activity=10
namespace WarGame
{

    class ParamedicCommander : public Soldier
    {
    private:
    public:
        ParamedicCommander(uint player) : Soldier(200, 0, player) {}

    
        void Attacking(std::vector<std::vector<Soldier *>> &board, uint Player, std::pair<int, int> placeOfSoldier)
        {
            std::pair<int, int> placeToattack = {0, 0};
            double minDistance = INT16_MAX;
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (board[i][j] != nullptr)
                    {
                        if (board[i][j]->getPlayer() == Player)
                        { //checks if the solfier that found is the other player soldier
                            if (sqrt(pow(placeOfSoldier.first - i, 2) + pow(placeOfSoldier.second - j, 2) <= minDistance))
                            {
                                minDistance = pow(placeOfSoldier.first - i, 2) + pow(placeOfSoldier.second - j, 2);
                                placeToattack = {i, j}; //enter the place of the closest soldier
                            }
                        }
                    }
                }
            }

            if (minDistance < INT16_MAX)
            {
                board[placeToattack.first][placeToattack.second]->heal();
            }
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (board[i][j] != nullptr)
                    {
                        if (board[i][j]->getPlayer() == Player && dynamic_cast<Paramedic *>(board[i][j]))
                        {
                            board[i][j]->Attacking(board, Player, std::pair<int, int>{i, j});
                        }
                    }
                }
            }
        }
    };
} // namespace WarGame