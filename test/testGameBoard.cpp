//Author: Behdad Khamneli
//Collaborator: Behzad Khamneli
#include "catch.h"
#include "CardTypes.h"
#include "CardStack.h"
#include "GameBoard.h"
#include <iostream>

std::vector<CardT> deckGen(){
	std::vector<CardT> d;
  	for (RankT rank = ACE; rank <= KING; rank++) {
    		for (unsigned int suit = 0; suit < 4; suit++) {
      			CardT n = { static_cast<SuitT>(suit), rank };
      			d.push_back(n);
      			d.push_back(n);
    		}
  	}
	return d;
}



TEST_CASE( "tests for BoardT" , "[BoardT]" ){

		
	std::vector<CardT> d = deckGen();

	BoardT b1(d);
	std::random_shuffle(d.begin(), d.end());
	BoardT b2(d);//randomized deck

	SECTION( "check if constructor correctly initializes T,F,D,W" ){
		b1.tab_mv(Foundation, 0,0);
		REQUIRE
		((
			b1.is_valid_tab_mv(Foundation, 0,1) == true
		     &	b1.get_waste().size() == 0
		     &	b1.get_foundation(0).size() == 1
		));
	}
	SECTION("Constructor throw invalid argument"){
		std::vector<CardT> dec = {{Spade,2},{Heart,1}};
		REQUIRE_THROWS_AS( BoardT(dec), ::invalid_argument);
	}

	SECTION( "is_valid_tab_mv normal and edge cases" ){
		REQUIRE
		((
			b1.is_valid_tab_mv(Tableau, 0,0) == false
		    &   b1.is_valid_tab_mv(Foundation, 0, 0) == true //Ace can initialize Foundation
		    &   b1.is_valid_tab_mv(Deck,0,0) == false
		    &   b1.is_valid_tab_mv(Waste,0,1) == false
		));
		b1.tab_mv(Foundation,0,2);
		REQUIRE( b1.is_valid_tab_mv(Foundation, 0,3) == true );
	}

	SECTION( "is_valid_tab_mv out of range exception"){
                REQUIRE_THROWS_AS( b1.is_valid_tab_mv(Tableau, 0,10), ::out_of_range);
		REQUIRE_THROWS_AS(b1.is_valid_tab_mv(Foundation, 0,100), ::out_of_range);
                REQUIRE_THROWS_AS( b1.is_valid_tab_mv(Tableau, 11,2), ::out_of_range);
                REQUIRE_THROWS_AS(b1.is_valid_tab_mv(Foundation, -1,0), ::out_of_range);
	}
	
	SECTION("is_valid_waste_mv normal and edge cases"){
		b1.deck_mv();
		b1.tab_mv(Foundation, 0,0);
		//Waste has 13 of Spade on top
		//Tableau has:
		//Diamond, 1 | Spade, 1 | Diamond, 2 | Spade, 2 | Diamond, 3 | Spade, 3 | Diamond , 4
		// Spade, 4 | Diamond, 5| Spade, 5  
	
		
		REQUIRE
                ((
                        b1.is_valid_waste_mv(Tableau, 0) == false //not same suits
		     &	b1.is_valid_waste_mv(Foundation, 0) == false // foundation[0] has ace wants 2 not king
		     &	b1.is_valid_waste_mv(Deck, 0) == false // not valid move 
                ));
	}
	SECTION("is_valid_waste_mv throws invalid argument"){
		
		REQUIRE_THROWS_AS(b2.is_valid_waste_mv(Tableau,0), :: invalid_argument);//waste is initially empty
	}
	SECTION("is_valid_waste_mv throws out of range"){
		b1.deck_mv();
		REQUIRE_THROWS_AS(b1.is_valid_waste_mv(Tableau, 11) , ::out_of_range);
		REQUIRE_THROWS_AS(b1.is_valid_waste_mv(Foundation, 9), ::out_of_range);
	}
	SECTION("is_valid_deck_mv normal and when deck is empty"){
		REQUIRE(b1.is_valid_deck_mv());
		for(int i = 0; i < 64; i++){
			b1.deck_mv();
		}
		REQUIRE(b1.is_valid_deck_mv() == false);
	}
	SECTION("tab_mv normal and edge cases"){
		b2.deck_mv();
	
                //deck has Diamond, 3 on top
                //waste has Club, 7 on top
                //Tableau has
                //Heart, 13 | Club, 4 | Club, 11 | Heart, 1 | Heart, 2 | Spade, 9 | Diamond, 7 | Heart, 6
                //Diamond, 5 | Diamond, 8

                b2.tab_mv(Tableau, 6,9);//tab_tab move
		b2.tab_mv(Foundation,3,0);//tab_foundation move
                REQUIRE
		((
			b2.get_tab(9).top().s == Diamond
		     &  b2.get_tab(9).top().r == 7
		     &  b2.get_tab(6).top().r != 7
		     &  b2.get_foundation(0).top().s == Heart
		     &  b2.get_foundation(0).top().r == 1
		     
		));
	}
	
	//Another test for tab_mv is in line 222 tab_mv removes last card
	
	
	SECTION("tab_mv throws invalid argument"){
		REQUIRE_THROWS_AS(b2.tab_mv(Tableau,0,1), ::invalid_argument);
		REQUIRE_THROWS_AS(b2.tab_mv(Foundation,0,0), ::invalid_argument);//moving non-Ace to empty foundation
	}
	SECTION("waste_mv normal and edge cases for mov to Tableau"){
                b2.deck_mv();
		b2.deck_mv();
      
                //deck has Diamond, 7 on top
                //waste has Spade, 11 on top
                //Tableau has
                //Club, 12 | Diamond, 10 | Diamond, 3 | Heart, 12 | Spade, 12 | Heart, 9 | Spade, 8 | Spade, 13 | Spade, 5
                //Club, 6

		b2.waste_mv(Tableau, 4);
		REQUIRE
		((
			b2.get_tab(4).top().s == Spade
		    &   b2.get_tab(4).top().r == 11
		));
		
	}
	SECTION("Waste_mv throws invalic argument"){
		b2.deck_mv();
		REQUIRE_THROWS_AS(b2.waste_mv(Tableau,2), ::invalid_argument);
		REQUIRE_THROWS_AS(b2.waste_mv(Foundation,0), ::invalid_argument);
		
	}
	SECTION("deck_mv moves a card from deck into waste"){
		CardStackT before = b2.get_deck();
		b2.deck_mv();
		REQUIRE((before.top().r == b2.get_waste().top().r & before.top().s == b2.get_waste().top().s));
		
	}
	SECTION("deck_mv removes the moved card from the deck"){
		int sizeBefore = b2.get_deck().size();
		b2.deck_mv();
		REQUIRE(sizeBefore - 1 == b2.get_deck().size());
	}
	SECTION("deck_mv throws invalid argument"){
		
		//to empty the deck
		for(int i = 0; i < 64; i++){
			b2.deck_mv();
		}
		REQUIRE_THROWS_AS(b2.deck_mv(), ::invalid_argument);
	}
	SECTION("get_tab normal case(cards before and after a tab mov)"){
	
		//Tableau has
		//Heart, 8 | Diamond, 6 | Club, 2 | Diamond, 5 | Diamond, 6 | Diamond, 1 | 
		//Diamond, 3 | Diamond, 2 | Diamond, 10 | Diamond, 5
		
		CardStackT before = b2.get_tab(7);
		b2.tab_mv(Tableau,7,6);
		REQUIRE((b2.get_tab(6).top().r == before.top().r 
			& b2.get_tab(6).top().s == before.top().s));	
	}
	SECTION("get_tab throws out of range"){
		REQUIRE_THROWS_AS(b2.get_tab(-1), ::out_of_range);
		REQUIRE_THROWS_AS(b2.get_tab(11), ::out_of_range);
	}
	SECTION("get_foundation normal cases"){
		
		//foundation is initialy empty
		b1.tab_mv(Foundation, 1,0); //moves an ACE to Foundaiton[0]
		REQUIRE((
			b1.get_foundation(0).top().s == Spade
		    &	b1.get_foundation(0).top().r == ACE
		));
	}
	SECTION("get_foundation when foundaiton is empty"){
		REQUIRE(b2.get_foundation(1).size() == 0);
	}
	SECTION("get_foundation Exception for invalid position"){
		REQUIRE_THROWS_AS(b2.get_foundation(9), ::out_of_range);
	}
	SECTION("get_deck normal cases"){
		
		//deck has Spade , 13
		REQUIRE((b1.get_deck().top().r == 13 & b1.get_deck().top().s == Spade));	
	}
	SECTION("get_deck when deck is empty"){
		for(int i = 0; i < 64; i++){
			b1.deck_mv();
		}
		REQUIRE(b1.get_deck().size() == 0);
	}
	SECTION("get_waste normal case"){
		//initializing waste
		//deck has Heart, 8 on top
		b2.deck_mv();
		REQUIRE((b2.get_waste().top().s == Heart & b2.get_waste().top().r == 8));
	}
	SECTION("get_waste with empty waste"){
		REQUIRE_THROWS_AS(b2.get_waste().top(), ::out_of_range);
	}
	SECTION("size of get_waste when waste is empty"){
		REQUIRE(b2.get_waste().size() == 0);
	}
	SECTION("valid_mv_exists normal case"){
		REQUIRE(b2.valid_mv_exists());
	}
	SECTION("is win state with empty foundation"){
		REQUIRE(!b2.is_win_state());
	}
	SECTION("tab_mv moves the last card in Tableau[0]"){
		
		b1.tab_mv(Foundation,0,0);
                b1.tab_mv(Foundation,0,1);
                b1.tab_mv(Foundation,0,2);
                b1.tab_mv(Foundation,0,3);
		
		REQUIRE(b1.get_tab(0).size() == 0);
	}
	SECTION("is_win state with random cards in foundation "){
		
		b1.tab_mv(Foundation, 0,0);
		b1.tab_mv(Foundation, 1,1);
		b1.tab_mv(Foundation, 0,2);
		b1.tab_mv(Foundation, 1,3);
		b1.tab_mv(Foundation, 0,4);
		b1.tab_mv(Foundation, 1,5);
		b1.tab_mv(Foundation, 0,6);
		b1.tab_mv(Foundation, 1,7);//foundation is full of ACEs
		
		REQUIRE(!b1.is_win_state());
	}
}
