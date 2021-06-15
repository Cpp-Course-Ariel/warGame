#include "Board.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "Soldier.hpp"
using namespace std;

namespace WarGame{

    // operator for putting soldiers on the game-board during initialization.
    Soldier*& Board::operator[](std::pair<int,int> location){
       /** if(board[location.first][location.second] != nullptr){
             throw out_of_range ("There is already player there");
         }**/
        if(location.first < board.size() && location.second < board[0].size()){
            return board[location.first][location.second];
        }
        else {
            throw out_of_range ("The place is incorrect");
         }
    }
    
    // operator for reading which soldiers are on the game-board.
    Soldier* Board::operator[](std::pair<int,int> location) const{
        if(location.first < board.size() && location.second < board[0].size()){
            return board[location.first][location.second];
        }else{
            throw out_of_range ("The place is incorrect");
        }
    }
    
    // The function "move" tries to move the soldier of player "player"
    //     from the "source" location to the "target" location,
    //     and activates the special ability of the soldier.
    // If the move is illegal, it throws "std::invalid_argument". 
    // Illegal moves include:
    //  * There is no soldier in the source location (i.e., the soldier pointer is null);
    //  * The soldier in the source location belongs to the other player.
    //  * There is already another soldier (of this or the other player) in the target location.
    // IMPLEMENTATION HINT: Do not write "if" conditions that depend on the type of soldier!
    // Your code should be generic. All handling of different types of soldiers 
    //      must be handled by polymorphism.
    void Board::move(uint player_number, std::pair<int,int> source, MoveDIR direction){
        if(source.first >= this->board.size() || source.first < 0 || source.second >= this->board[0].size() || source.second < 0){
            throw out_of_range ("Out of bounds");
        }

        if(this->board[source.first][source.second] != nullptr){
            if(this->board[source.first][source.second]->getPlayer() == player_number){
                //move the soldier UP || DOWN || RIGHT || LEFT
                std::pair<int,int> dest = source;
                switch (direction)
                {
                case MoveDIR::Down: dest.first = dest.first - 1;
                    break;
                
                case MoveDIR::Up: dest.first = dest.first + 1;
                    break;
                    
                case MoveDIR::Right: dest.second = dest.second + 1;
                    break;

                case MoveDIR::Left: dest.second = dest.second -1;
                    break;
                
                default:
                    break;
                }

                 if(dest.first<0 || dest.second<0 || dest.first>=board.size() || dest.second>=board[0].size()){
                    throw out_of_range ("reaching over the limit.");
                 }
                if(board[dest.first][dest.second]!=nullptr ){
                    throw out_of_range ("There is another soldier there!");
                }
                    board[dest.first][dest.second]=board[source.first][source.second];
                    board[source.first][source.second]=nullptr;
                    board[dest.first][dest.second]->Attacking(this->board,player_number,dest);
            }else throw out_of_range ("this is not your soldier");
        }else throw out_of_range ("There is no soldier in this place");
    }

    // returns true iff the board contains one or more soldiers of the given player.
    bool Board::has_soldiers(uint player_number) const{
        for (int i = 0; i < this->board.size(); i++){
            for (int j = 0; j < this->board[0].size(); j++){
                if(this->board[i][j] != nullptr && this->board[i][j]->getPlayer() == player_number){
                    return true;
                }
            }
        }
        return false;
    }

};
