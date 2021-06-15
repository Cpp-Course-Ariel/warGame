/**#include "doctest.h"
#include <iostream>
#include "Board.hpp"
#include "Soldier.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
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
**/

#include "doctest.h"
#include <iostream>
#include <stdexcept>

#include "DemoGame.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"
#include <cassert>
using namespace WarGame;
//check exceptions in diff cases

TEST_CASE("Sniper VS Sniper") { //good
    WarGame::Board board(8,8);
    CHECK(!board.has_soldiers(1));
    board[{0,1}] = new Sniper(1);
    CHECK(board.has_soldiers(1));

    CHECK(!board.has_soldiers(2));
	board[{7,1}] = new Sniper(2);
    CHECK(board.has_soldiers(2));

    board.move(1,{0,1},WarGame::Board::MoveDIR::Up);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    CHECK_THROWS(board.move(1,{0,1},WarGame::Board::MoveDIR::Up));
    board.move(1,{1,1},WarGame::Board::MoveDIR::Up);
    CHECK(!board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
}

TEST_CASE("Foot vs Foot") {
    WarGame::Board board(8,8);
    CHECK(!board.has_soldiers(1));
    board[{0,1}] = new FootSoldier(1); //soldier 1 - 100
    CHECK(board.has_soldiers(1));

    CHECK(!board.has_soldiers(2));
	board[{7,1}] = new FootSoldier(2); //soldier 2 - 100
    CHECK(board.has_soldiers(2));

    board.move(1,{0,1},WarGame::Board::MoveDIR::Up); //soldier 2 - 90
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    CHECK_THROWS(board.move(1,{0,1},WarGame::Board::MoveDIR::Up)); //no soldier thehre
    board.move(1,{1,1},WarGame::Board::MoveDIR::Up); //soldier 2 - 80
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    CHECK_THROWS(board.move(1,{7,1},WarGame::Board::MoveDIR::Up));
    CHECK_THROWS(board.move(2,{7,1},WarGame::Board::MoveDIR::Up));
    board.move(2,{7,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 90
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{6,1},WarGame::Board::MoveDIR::Down); //sodier 1 - 80
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{5,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 70
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{2,1},WarGame::Board::MoveDIR::Up); //soldier 2 - 70
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    CHECK_THROWS(board.move(1,{3,1},WarGame::Board::MoveDIR::Up));//there is another soldier in the destenation
    CHECK_THROWS(board.move(2,{4,1},WarGame::Board::MoveDIR::Down)); //gam ze
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{3,1},WarGame::Board::MoveDIR::Down); //soldier 2 - 60
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{4,1},WarGame::Board::MoveDIR::Up); //soldier 1 - 60
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{5,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 50
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
	board.move(2,{4,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 40
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{3,1},WarGame::Board::MoveDIR::Up); //soldier 1 - 30
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{4,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 20
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{3,1},WarGame::Board::MoveDIR::Up); //soldier 1 - 10
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(2,{4,1},WarGame::Board::MoveDIR::Down); //soldier 1 - 0
    CHECK(board.has_soldiers(2));
    CHECK(!board.has_soldiers(1));

}
TEST_CASE("3 VS 3") {
    WarGame::Board board(8,8);
    CHECK(!board.has_soldiers(1));
    board[{0,1}] = new FootSoldier(1);//player 1 footSoldier1 {0,1}
    //CHECK_THROWS((board[{0,1}] = new FootSoldier(1))); //there is already soldier there
    board[{0,0}] = new FootCommander(1); //player 1 commanderSoldier {0,0}
    board[{0,2}] = new FootSoldier(1);//player 1 footSoldier2 {0,2}
    CHECK(board.has_soldiers(1)); //there is no need to write this any time

    CHECK(!board.has_soldiers(2));
    board[{7,0}] = new FootCommander(2);//player 2 commanderSoldier {7,0}
	board[{7,1}] = new FootSoldier(2);//player 2 footSoldier1 {7,1}
    board[{7,2}] = new FootSoldier(2);//player 2 footSoldier2 {7,2}

    CHECK(board.has_soldiers(2));

    board.move(1,{0,1},WarGame::Board::MoveDIR::Up); //player 2 footsoldier1 - 90
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    CHECK_THROWS(board.move(1,{0,1},WarGame::Board::MoveDIR::Up)); //no soldier there
    board.move(1,{1,1},WarGame::Board::MoveDIR::Up); //player 2 footsoldier1 - 80 
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    CHECK_THROWS(board.move(2,{7,0},WarGame::Board::MoveDIR::Left)); // cant move left
    board.move(2,{7,0},WarGame::Board::MoveDIR::Down); //player 1 commanderSoldier - 130, player 1 footsoldier1 - 70,   player 1 footsoldier2 - 90, 
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{0,0},WarGame::Board::MoveDIR::Up);//player 2 commanderSoldier - 130, player 2 footsoldier1 - 70,   player 2 footsoldier2 - 90, 
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{1,0},WarGame::Board::MoveDIR::Down);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{0,0},WarGame::Board::MoveDIR::Up);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{1,0},WarGame::Board::MoveDIR::Down);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

     board.move(1,{0,0},WarGame::Board::MoveDIR::Up);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{1,0},WarGame::Board::MoveDIR::Down);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{0,0},WarGame::Board::MoveDIR::Up);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{1,0},WarGame::Board::MoveDIR::Down);
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{0,2},WarGame::Board::MoveDIR::Up);
    board.move(1,{1,2},WarGame::Board::MoveDIR::Up);
   
    CHECK(!board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
	
	// the winner is team 1
}
TEST_CASE("One soldier of this type"){
    WarGame::Board board(8,8);
    CHECK(!board.has_soldiers(1));
    board[{0,0}] = new FootSoldier(1);//player 1 soldier1
	CHECK(board.has_soldiers(1));
    board[{0,1}] = new FootCommander(1);//player 1 soldier2
	CHECK(board.has_soldiers(1));
    board[{0,2}] = new Sniper(1);//player 1 soldier3
	CHECK(board.has_soldiers(1));
    board[{0,3}] = new SniperCommander(1);//player 1 soldier4
	CHECK(board.has_soldiers(1));
    board[{0,4}] = new Paramedic(1);//player 1 soldier5
    board[{0,5}] = new ParamedicCommander(1);//player 1 soldier6
    CHECK(board.has_soldiers(1));
    CHECK(!board.has_soldiers(2));
    board[{7,0}] = new FootSoldier(2);//player 2 soldier1
    board[{7,1}] = new FootCommander(2);//player 2 soldier2
    board[{7,2}] = new Sniper(2);//player 2 soldier3
    board[{7,3}] = new SniperCommander(2);//player 2 soldier4
    board[{7,4}] = new Paramedic(2);//player 2 soldier5
    board[{7,5}] = new ParamedicCommander(2);//player 2 soldier6


	//consider using for.....
    CHECK(board.has_soldiers(2));
    board.move(1,{0,0},WarGame::Board::MoveDIR::Up); //player2 soldier1 - 90
    CHECK(board.has_soldiers(2));
    board.move(1,{0,1},WarGame::Board::MoveDIR::Up);//player2 soldier2 - 130, player 2 soldier1 - 80
    CHECK(board.has_soldiers(2));
    board.move(1,{0,2},WarGame::Board::MoveDIR::Up);//player2 soldier6 - 150
    CHECK(board.has_soldiers(2));
    board.move(1,{0,3},WarGame::Board::MoveDIR::Up);//player2 soldier6 - 50, player 2 soldier2 80 //need to define that commander shoots first
    CHECK(board.has_soldiers(2));
    board.move(1,{0,4},WarGame::Board::MoveDIR::Up);//player1 soldier4 - 120 //need to define that curing id done after the step/move
    CHECK(board.has_soldiers(2));
    board.move(1,{0,5},WarGame::Board::MoveDIR::Up); //player1 soldier5 - 100, player 1 soldier4 - 120, player 1 soldier6 - 200
    CHECK(board.has_soldiers(2));
	
	
    //sniper 1 will kill them all
    board.move(1,{1,3},WarGame::Board::MoveDIR::Down); //player2 soldier6 - 100, player 2 soldier2 80
	CHECK(board.has_soldiers(2));
    board.move(1,{0,3},WarGame::Board::MoveDIR::Up); //player2 soldier4 - 20, player2 soldier3 - 50 //need to define to check the closes when there are equalh healh points
	CHECK(board.has_soldiers(2));
    board.move(1,{1,3},WarGame::Board::MoveDIR::Down); //player2 soldier5 - 0, player2 soldier6 - 50
    CHECK(board.has_soldiers(2));
    board.move(1,{0,3},WarGame::Board::MoveDIR::Up); //player2 soldier1 - 0, player2 soldier2 - 30
        //just to be Sure all is dead

        board.move(1,{1,2},WarGame::Board::MoveDIR::Down); //player2 soldier3 - 0, player2 soldier 6 - 20/10
        board.move(1,{0,2},WarGame::Board::MoveDIR::Up); //player2 soldier3 - 0, player2 soldier 6 - 0
        board.move(1,{1,2},WarGame::Board::MoveDIR::Down); //player2 soldier3 - 0, player2 soldier 6 - 0

for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if(board[{i,j}]!= nullptr)
            if(board.getmat()[i][j]->getPlayer() == 2){
                printf("%d %d %d \n", board.getmat()[i][j]->getLife() ,i ,j);
            }
        }
    }
     for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if(board[{i,j}]!= nullptr)
            if(board.getmat()[i][j]->getPlayer() == 1){
                printf("%d \n", board.getmat()[i][j]->getLife());
            }
        }   
    }
    
    //just to be Sure all is dead
    CHECK(!board.has_soldiers(2));
	
	//good test
}
TEST_CASE("2 VS 2"){
    WarGame::Board board(8,8);
    CHECK(!board.has_soldiers(1));
    board[{0,1}] = new FootSoldier(1); //player1 soldier1 - 100
    board[{0,0}] = new FootCommander(1); //player1 soldier2 - 150
    CHECK(board.has_soldiers(1));

    CHECK(!board.has_soldiers(2));
    board[{7,0}] = new FootCommander(2); //player2 soldier1 - 150
    board[{7,1}] = new FootSoldier(2); //player2 soldier2 - 100

    CHECK(board.has_soldiers(2));

    board.move(1,{0,1},WarGame::Board::MoveDIR::Up); // player2 soldier2 - 90
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    CHECK_THROWS(board.move(1,{0,1},WarGame::Board::MoveDIR::Up));
    board.move(1,{1,1},WarGame::Board::MoveDIR::Up); // player2 soldier2 - 80

    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    CHECK_THROWS(board.move(2,{7,0},WarGame::Board::MoveDIR::Left));
    board.move(2,{7,0},WarGame::Board::MoveDIR::Down); //player1 soldier1 - 90
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{0,0},WarGame::Board::MoveDIR::Up); // player2 soldier1 - 130, player2 soldier2 - 70
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{1,0},WarGame::Board::MoveDIR::Up); // player2 soldier1 - 110, player2 soldier2 - 60
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{2,0},WarGame::Board::MoveDIR::Down); // player2 soldier1 - 90, player2 soldier2 - 50
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{1,0},WarGame::Board::MoveDIR::Up); // player2 soldier1 - 70, player2 soldier2 - 40
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{2,0},WarGame::Board::MoveDIR::Down); // player2 soldier1 - 50, player2 soldier2 - 30
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

    board.move(1,{1,0},WarGame::Board::MoveDIR::Up);// player2 soldier1 - 30, player2 soldier2 - 20
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));
    board.move(1,{2,0},WarGame::Board::MoveDIR::Down); // player2 soldier1 - 10, player2 soldier2 - 10
    CHECK(board.has_soldiers(2));
    CHECK(board.has_soldiers(1));

        board.move(1,{1,0},WarGame::Board::MoveDIR::Up);// player2 soldier1 - 0, player2 soldier2 - 0
    
    CHECK(board.has_soldiers(1));
        board.move(1,{2,0},WarGame::Board::MoveDIR::Down); // i think youve done


    CHECK(board.has_soldiers(1)); 
    CHECK(!board.has_soldiers(2)); 
	//the winner is team 1
}

WarGame::Board fillBoard(){
    WarGame::Board p(6,6);
    p[{0,0}]= new FootSoldier(1);
    p[{3,3}]= new FootSoldier(2);
    p[{5,0}]= new FootCommander(1);
    p[{3,5}]= new FootCommander(2);
    p[{0,1}]= new Sniper(1);
    p[{3,0}]= new Sniper(2);
    p[{2,1}]= new SniperCommander(1);
    p[{0,3}]= new SniperCommander(2);
    p[{5,1}]= new Paramedic(1);
    p[{1,3}]= new Paramedic(2);
    p[{4,5}]= new ParamedicCommander(1);
    p[{4,0}]= new ParamedicCommander(2);
    return p;
}
WarGame::Board fillCommBoard(){
    WarGame::Board p (5,5);
    p[{0,0}] = new FootSoldier(1);
    p[{0,1}] = new FootSoldier(2);
    p[{0,3}] = new SniperCommander(2);
    p[{0,4}] = new FootCommander(2);
    p[{2,0}] = new Paramedic(2);
    p[{2,1}] = new Paramedic(1);
    p[{2,2}] = new FootCommander(1);
    p[{2,3}] = new SniperCommander(1);
    p[{4,0}] = new Sniper(1);
    p[{4,1}] = new Sniper(2);
    p[{4,3}] = new ParamedicCommander(1);
    p[{4,4}] = new ParamedicCommander(2);
    return p;
}



TEST_CASE("Check Adding player to board"){
    
    WarGame::Board q(1,1);
            CHECK_FALSE(q.has_soldiers(1));
            CHECK_FALSE(q.has_soldiers(2));
    WarGame::Board p = fillBoard();
            CHECK(p.has_soldiers(1));
            CHECK(p.has_soldiers(2));
            CHECK(typeid(*p[{0,0}]) == typeid(FootSoldier));
            CHECK(typeid(*p[{3,3}]) == typeid(FootSoldier));
            CHECK(typeid(*p[{5,0}]) == typeid(FootCommander));
            CHECK(typeid(*p[{3,5}]) == typeid(FootCommander));
            CHECK(typeid(*p[{0,1}]) == typeid(Sniper));
            CHECK(typeid(*p[{3,0}]) == typeid(Sniper));
            CHECK(typeid(*p[{2,1}]) == typeid(SniperCommander));
            CHECK(typeid(*p[{0,3}]) == typeid(SniperCommander));
            CHECK(typeid(*p[{5,1}]) == typeid(Paramedic));
            CHECK(typeid(*p[{1,3}]) == typeid(Paramedic));
            CHECK(typeid(*p[{4,5}]) == typeid(ParamedicCommander));
            CHECK(typeid(*p[{4,0}]) == typeid(ParamedicCommander));
}

TEST_CASE("Check Adding player to board 2"){
    WarGame::Board q(1,1);
            CHECK_FALSE(q.has_soldiers(1));
            CHECK_FALSE(q.has_soldiers(2));
    WarGame::Board p = fillCommBoard();
            CHECK(p.has_soldiers(1));
            CHECK(p.has_soldiers(2));
            CHECK(typeid(*p[{0,0}]) == typeid(FootSoldier));
            CHECK(typeid(*p[{0,1}]) == typeid(FootSoldier));
            CHECK(typeid(*p[{0,3}]) == typeid(SniperCommander));
            CHECK(typeid(*p[{0,4}]) == typeid(FootCommander));
            CHECK(typeid(*p[{2,3}]) == typeid(SniperCommander));
            CHECK(typeid(*p[{4,1}]) == typeid(Sniper));
            CHECK(typeid(*p[{2,2}]) == typeid(FootCommander));
            CHECK(typeid(*p[{2,3}]) == typeid(SniperCommander));
            CHECK(typeid(*p[{2,0}]) == typeid(Paramedic));
            CHECK(typeid(*p[{2,1}]) == typeid(Paramedic));
            CHECK(typeid(*p[{4,3}]) == typeid(ParamedicCommander));
            CHECK(typeid(*p[{4,4}]) == typeid(ParamedicCommander));
            CHECK(typeid(*p[{4,0}]) == typeid(Sniper));
}

TEST_CASE("Move function - no Commander"){
    WarGame::Board p = fillBoard();
    p.move(1,{0,0},WarGame::Board::Up);
            CHECK(p[{0,0}]== nullptr);
            CHECK(typeid(*p[{1,0}])==typeid(FootSoldier));

    p.move(1,{0,1},WarGame::Board::Right);
            CHECK(p[{0,1}]==nullptr);
            CHECK(typeid(*p[{0,2}])== typeid(Sniper));

    p.move(1,{5,1},WarGame::Board::Down);
            CHECK(p[{5,1}]==nullptr);
            CHECK(typeid(*p[{4,1}])== typeid(Paramedic));


    p.move(2,{3,0},WarGame::Board::Right);
            CHECK(p[{3,0}]== nullptr);
            CHECK(typeid(*p[{3,1}])==typeid(Sniper));

    p.move(2,{3,3},WarGame::Board::Up);
            CHECK(p[{3,3}]== nullptr);
            CHECK(typeid(*p[{4,3}])==typeid(FootSoldier));

    p.move(2,{1,3},WarGame::Board::Right);
            CHECK(p[{1,3}]== nullptr);
            CHECK(typeid(*p[{1,4}])==typeid(Paramedic));

}

TEST_CASE("Move Function - Commander"){
    WarGame::Board p = fillCommBoard();
    p.move(1,{2,2},WarGame::Board::Up);
            CHECK(p[{2,2}]==nullptr);
            CHECK(typeid(*p[{3,2}])== typeid(FootCommander));

    p.move(1,{2,3},WarGame::Board::Down);
            CHECK(p[{2,3}]==nullptr);
            CHECK(typeid(*p[{1,3}])==typeid(SniperCommander));


    p.move(1,{4,3},WarGame::Board::Down);
            CHECK(p[{4,3}]==nullptr);
            CHECK(typeid(*p[{3,3}])==typeid(ParamedicCommander));


    p.move(2,{0,4},WarGame::Board::Up);
            CHECK(p[{0,4}]==nullptr);
            CHECK(typeid(*p[{1,4}])== typeid(FootCommander));

    p.move(2,{0,3},WarGame::Board::Left);
            CHECK(p[{0,3}]==nullptr);
            CHECK(typeid(*p[{0,2}])==typeid(SniperCommander));


    p.move(2,{4,4},WarGame::Board::Down);
            CHECK(p[{4,4}]==nullptr);
            CHECK(typeid(*p[{3,4}])==typeid(ParamedicCommander));

}

TEST_CASE("Exceptions") {
    WarGame::Board p = fillBoard();
    //Out of board
            CHECK_THROWS(p.move(1, {5, 1}, WarGame::Board::Up));
            CHECK_THROWS(p.move(1, {0, 0}, WarGame::Board::Down));
            CHECK_THROWS(p.move(2, {3, 5}, WarGame::Board::Right));
            CHECK_THROWS(p.move(1, {4, 5}, WarGame::Board::Right));
            CHECK_THROWS(p.move(1, {5, 0}, WarGame::Board::Left));
    //Busy place
            CHECK_THROWS(p.move(2, {4, 0}, WarGame::Board::Up));
            CHECK_THROWS(p.move(2, {3, 0}, WarGame::Board::Up));
            CHECK_THROWS(p.move(2, {0, 3}, WarGame::Board::Up));
            CHECK_THROWS(p.move(2, {1, 3}, WarGame::Board::Down));
            CHECK_THROWS(p.move(1, {0, 1}, WarGame::Board::Left));
    //Null Place
            CHECK_THROWS(p.move(1, {2, 0}, WarGame::Board::Up));
            CHECK_THROWS(p.move(1, {4, 3}, WarGame::Board::Up));
            CHECK_THROWS(p.move(1, {2, 2}, WarGame::Board::Down));
            CHECK_THROWS(p.move(2, {1, 0}, WarGame::Board::Right));
            CHECK_THROWS(p.move(2, {5, 4}, WarGame::Board::Left));
    //Source out of bound
            CHECK_THROWS(p.move(1, {6, 0}, WarGame::Board::Up));
            CHECK_THROWS(p.move(1, {7, 3}, WarGame::Board::Up));
            CHECK_THROWS(p.move(1, {8, 2}, WarGame::Board::Down));
            CHECK_THROWS(p.move(2, {9, 0}, WarGame::Board::Right));
            CHECK_THROWS(p.move(2, {10, 4}, WarGame::Board::Left));
            
}

TEST_CASE("Check Moves"){
    WarGame::Board p = fillBoard();
            CHECK_NOTHROW(p.move(1,{0,0},WarGame::Board::Up));
            CHECK_NOTHROW(p.move(1,{0,1},WarGame::Board::Left));
            CHECK_NOTHROW(p.move(1,{2,1},WarGame::Board::Down));
            CHECK_NOTHROW(p.move(2,{3,0},WarGame::Board::Down));
            CHECK_NOTHROW(p.move(2,{3,3},WarGame::Board::Right));
            CHECK_NOTHROW(p.move(2,{3,5},WarGame::Board::Down));
            CHECK_NOTHROW(p.move(2,{4,0},WarGame::Board::Down));
            CHECK_NOTHROW(p.move(1,{4,5},WarGame::Board::Up));
            CHECK_NOTHROW(p.move(1,{5,0},WarGame::Board::Down));
            CHECK_NOTHROW(p.move(1,{5,1},WarGame::Board::Right));
            CHECK_NOTHROW(p.move(1,{5,2},WarGame::Board::Right));
            CHECK_NOTHROW(p.move(1,{5,5},WarGame::Board::Left));
            CHECK_NOTHROW(p.move(1,{4,0},WarGame::Board::Right));
}

TEST_CASE("Extra"){
    WarGame::Board b (4,4);
            CHECK(!b.has_soldiers(1));
            CHECK(!b.has_soldiers(2));
    b[{0,0}]= new FootSoldier(1);
            CHECK(!b.has_soldiers(2));
            CHECK(b.has_soldiers(1));
    b[{3,3}] = new Sniper(2);
            CHECK(b.has_soldiers(1));
            CHECK(b.has_soldiers(2));
    b.move(1,{0,0},WarGame::Board::Up);
            CHECK(b.has_soldiers(1));
            CHECK(b.has_soldiers(2));
    b.move(2,{3,3},WarGame::Board::Down);
            CHECK(b.has_soldiers(1));
            CHECK(b.has_soldiers(2));
    b.move(2,{2,3},WarGame::Board::Down);
            CHECK(b.has_soldiers(2));
            CHECK(!b.has_soldiers(1));

}

