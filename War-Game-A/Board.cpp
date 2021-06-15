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
        if(board[location.first][location.second] != nullptr){
             throw out_of_range ("There is already player there");
         }
        if(location.first < board.size() && location.second < board.size()){
            return board[location.first][location.second];
        }
        else {
            throw out_of_range ("The place is incorrect");
         }
    }
    
    // operator for reading which soldiers are on the game-board.
    Soldier* Board::operator[](std::pair<int,int> location) const{
        return this->board[location.first][location.second];
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
        if(this->board[source.first][source.second] != nullptr){
            if(this->board[source.first][source.second]->getPlayer() == player_number){
                //move the soldier UP || DOWN || RIGHT || LEFT
                switch (direction)
                {
                case MoveDIR::Down:
                    if(source.first - 1 >= 0 ){
                    this->board[source.first-1][source.second] = this->board[source.first][source.second];
                    this->board[source.first][source.second] = nullptr; 
                    //this->board[source.first-1][source.second]->Attacking(*this, player_number, {source.first-1,source.second});
                    }else throw out_of_range ("Cant move the player Up to there");
                    break;
                case MoveDIR::Up:
                    if(source.first + 1 < this->board.size() ){
                    this->board[source.first+1][source.second] = this->board[source.first][source.second];
                    this->board[source.first][source.second] = nullptr; 
                    //this->board[source.first+1][source.second]->Attack();
                    }else throw out_of_range ("Cant move the player Down to there");
                    break;
                case MoveDIR::Right:
                    if(source.second + 1 < this->board.size() ){
                    this->board[source.first][source.second+1] = this->board[source.first][source.second];
                    this->board[source.first][source.second] = nullptr; 
                    //this->board[source.first+1][source.second]->Attack();
                    }else throw out_of_range ("Cant move the player Down to there");
                    
                    break;

                case MoveDIR::Left:
                    if(source.second - 1 >= 0 ){
                    this->board[source.first][source.second-1] = this->board[source.first][source.second];
                    this->board[source.first][source.second] = nullptr; 
                    //this->board[source.first+1][source.second]->Attack();
                    }else throw out_of_range ("Cant move the player Down to there");

                    break;

                default:
                    break;
                

                }
            }
        }else throw out_of_range ("There is no soldier in this place");
    }

    // returns true iff the board contains one or more soldiers of the given player.
    bool Board::has_soldiers(uint player_number) const{
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(this->board[i][j] != nullptr && this->board[i][j]->getPlayer() == player_number){
                    return true;
                }
            }
        }
        return false;
    }

};
