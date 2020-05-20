#include "doctest.h"
#include <iostream>
#include "Board.hpp"
#include "Soldier.hpp"
#include "FootCommander.hpp"
#include "FootSoldier.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"
#include <cassert>

using namespace std;
using namespace WarGame;



    TEST_CASE("Create board and Enter players") {
        CHECK_NOTHROW(FootSoldier s = FootSoldier(1));
        CHECK_NOTHROW( FootCommander s = FootCommander(1));
        CHECK_NOTHROW( Sniper s = Sniper(1));
        CHECK_NOTHROW( SniperCommander s = SniperCommander(1));
        CHECK_NOTHROW( Paramedic s = Paramedic(1));
        CHECK_NOTHROW( ParamedicCommander s = ParamedicCommander(1));
        CHECK_NOTHROW( Board board(8,8));
        
        Board board(8,8);
        CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
        CHECK_NOTHROW((board[{0,1}] = new FootCommander(1)));
        CHECK_NOTHROW((board[{0,2}] = new Paramedic(1)));
        CHECK_NOTHROW((board[{0,3}] = new ParamedicCommander(1)));
        CHECK_NOTHROW((board[{0,4}] = new Sniper(1)));
        CHECK_NOTHROW((board[{0,5}] = new SniperCommander(1)));

        CHECK_THROWS((board[{0,3}] = new SniperCommander(1))); // throws exeption there is allready soldier there
        CHECK_THROWS((board[{0,5}] = new SniperCommander(1)));
        
        CHECK_NOTHROW((board[{7,0}] = new FootSoldier(2)));
        CHECK_NOTHROW((board[{7,1}] = new FootCommander(2)));
        CHECK_NOTHROW((board[{7,2}] = new Paramedic(2)));
        CHECK_NOTHROW((board[{7,3}] = new ParamedicCommander(2)));
        CHECK_NOTHROW((board[{7,4}] = new Sniper(2)));
        CHECK_NOTHROW((board[{7,5}] = new SniperCommander(2)));

};

    TEST_CASE("Create board and Enter players") {
        Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
            CHECK_NOTHROW(board.move(1, {0,0}, Board::MoveDIR::Up));
			CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
			CHECK_NOTHROW((board[{0,3}] = new FootSoldier(1)));
            CHECK_NOTHROW(board.move(1, {0,3}, Board::MoveDIR::Up));     
			CHECK_NOTHROW((board[{7,3}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(2, {7,3}, Board::MoveDIR::Left)); 

};
    TEST_CASE("Checks soldier ability") {
            Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
            CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(1, {0,0}, Board::MoveDIR::Up));
            CHECK(board[{7,1}]->getLife() == 90);
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK(board[{1,0}]->getLife() == 90);
};
    TEST_CASE("Checks paramedic ability") {
            Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
            CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
            CHECK_NOTHROW((board[{6,2}] = new Paramedic(2)));
            CHECK_NOTHROW(board.move(1, {0,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK_NOTHROW(board.move(2, {7,2}, Board::MoveDIR::Down));
            CHECK(board[{6,1}]->getLife() == 100);
};

    TEST_CASE("Checks Sniper ability") {
            Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new Sniper(1)));
            CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(1, {0,0}, Board::MoveDIR::Up));
            CHECK(board[{7,1}]->getLife() == 50);
};
    TEST_CASE("Checks FootSoldier commander ability") {
            //Both soldier and commander shoots the opponent soldier and reduce his life by 30
            Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
            CHECK_NOTHROW((board[{7,1}] = new FootCommander(2)));
            CHECK_NOTHROW((board[{6,2}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK(board[{0,0}]->getLife() == 70);
};

   TEST_CASE("Checks Paramedic commander ability") {
            //Both soldier and commander shoots the opponent soldier and reduce his life by 30
            Board board (8,8);
            CHECK_NOTHROW((board[{0,3}] = new FootSoldier(1)));
            CHECK_NOTHROW((board[{7,1}] = new FootCommander(2)));
            CHECK_NOTHROW((board[{6,2}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK(board[{0,3}]->getLife() == 70);
            CHECK_NOTHROW((board[{0,2}] = new Paramedic(1)));
            CHECK_NOTHROW((board[{0,4}] = new ParamedicCommander(1)));
            CHECK_NOTHROW(board.move(1, {0,4}, Board::MoveDIR::Up));
            CHECK(board[{0,3}]->getLife() == 100);
};

   TEST_CASE("Checks Sniper commander ability") {
            Board board (8,8);
            CHECK_NOTHROW((board[{0,3}] = new FootSoldier(1)));
            CHECK_NOTHROW((board[{7,1}] = new SniperCommander(2)));
            CHECK_NOTHROW((board[{6,2}] = new Sniper(2)));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK(board[{0,3}]->getLife() == 0);
    
};


    TEST_CASE("player one wins") {
            Board board (8,8);
            CHECK_NOTHROW((board[{0,0}] = new FootSoldier(1)));
			CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
            CHECK_NOTHROW(board.move(1, {0,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(2, {7,1}, Board::MoveDIR::Down));
            CHECK((board[{6,1}]->getLife()) == 90);
            CHECK((board[{1,0}]->getLife()) == 90);
            CHECK_NOTHROW(board.move(1, {1,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(1, {2,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(1, {3,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(1, {4,0}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(1, {5,0}, Board::MoveDIR::Right));
            CHECK_NOTHROW(board.move(1, {5,1}, Board::MoveDIR::Left));
            CHECK_NOTHROW(board.move(1, {5,0}, Board::MoveDIR::Right));
            CHECK_NOTHROW(board.move(1, {5,1}, Board::MoveDIR::Up));
            CHECK_NOTHROW(board.move(1, {6,1}, Board::MoveDIR::Right));
            CHECK(board.has_soldiers(2) == false);
};


    TEST_CASE("player Two wins") {
            Board board (8,8);
            assert((!board.has_soldiers(1)));
			CHECK_NOTHROW((board[{0,1}] = new FootSoldier(1)));
			CHECK_NOTHROW((board[{0,3}] = new FootCommander(1)));
			CHECK_NOTHROW((board[{0,5}] = new FootSoldier(1)));
			assert(board.has_soldiers(1));

			// Add soldiers for player 2:
			assert(!board.has_soldiers(2));
			CHECK_NOTHROW((board[{7,1}] = new FootSoldier(2)));
			CHECK_NOTHROW((board[{7,3}] = new FootCommander(2)));
			CHECK_NOTHROW((board[{7,5}] = new FootSoldier(2)));
            CHECK_NOTHROW((board[{7,6}] = new FootCommander(2)));
			assert(board.has_soldiers(2));

            CHECK_NOTHROW ((board.move(1, {0,1}, Board::MoveDIR::Up))); 
			CHECK(!board.has_soldiers(2) == false);
			CHECK_NOTHROW ((board.move(2, {7,1}, Board::MoveDIR::Down))); 
			CHECK((!board.has_soldiers(1)) == false);
			CHECK_NOTHROW((board.move(1, {0,3}, Board::MoveDIR::Up)));   
			CHECK((!board.has_soldiers(2) == false));
			CHECK_NOTHROW((board.move(2, {7,3}, Board::MoveDIR::Left)));
			CHECK(!board.has_soldiers(1) == false);
            CHECK_NOTHROW ((board.move(1, {1,1}, Board::MoveDIR::Up))); 
			CHECK(!board.has_soldiers(2) == false);
            CHECK_NOTHROW ((board.move(2, {7,6}, Board::MoveDIR::Down))); 
			CHECK(!board.has_soldiers(1) == false);
            CHECK_NOTHROW ((board.move(1, {1,3}, Board::MoveDIR::Up))); 
			CHECK(!board.has_soldiers(2) == false);
            CHECK_NOTHROW ((board.move(2, {6,6}, Board::MoveDIR::Down))); 
			CHECK(!board.has_soldiers(1) == true);

		
};


