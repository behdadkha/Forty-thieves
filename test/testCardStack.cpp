#include "catch.h"
#include "CardTypes.h"
#include "CardStack.h"
#include "GameBoard.h"

TEST_CASE("tests for CardStack", "[CardStack]"){
	//folowing the last year's assignment testDEM.cpp
	std::vector<CardT> cards;
	cards.push_back({Heart, 1});
	cards.push_back({Spade, 3});
        cards.push_back({Diamond, 2});
        cards.push_back({Heart, 13});
        cards.push_back({Club, 1});
        cards.push_back({Spade, 6});
        cards.push_back({Diamond, 9});

	CardStackT testStack(cards);

	SECTION("check if Constructor creats a new stack"){
		REQUIRE(testStack.top().r == 9);
	}
	SECTION("push general case"){
		
		testStack.push({Heart,13});
		CardT after = testStack.top();
		REQUIRE((after.r == 13 & after.s == Heart));
	}
	SECTION("push an empty cardT"){
		testStack.push({});
		REQUIRE((
			testStack.top().s == 0
		    &	testStack.top().r == 0
		));
		//pushing empty card{} creates a card Heart, 0 
	}
	SECTION("pop general case"){
		testStack.pop();
		REQUIRE((
			testStack.top().s == Spade 
		    &   testStack.top().r == 6
		));
	}
	SECTION("pop exception out of range empty stack"){
            	
                //pops all the cards in stack
		for(int i = 0; i < 7; i++){
			testStack.pop();
		}
	
		REQUIRE_THROWS_AS( testStack.pop(), ::out_of_range );
	}
	SECTION("top general case"){
		REQUIRE((
			testStack.top().r == 9 
		&	testStack.top().s == Diamond
		));  
	}
	SECTION("top Exception when the stack is empty"){
		for(int i = 0; i < 7; i++)
			testStack.pop();  //emptying the stack	
		REQUIRE_THROWS_AS(testStack.top().r == 2, ::out_of_range);
	}
	SECTION("size general case"){
		REQUIRE(testStack.size() == 7);
	}
	SECTION("size for empty stack"){
		CardStackT empty({});
		REQUIRE(empty.size() == 0);
	}
	SECTION("toSeq general case"){
		std::vector<CardT> te = testStack.toSeq();
		CardStackT newS(te);
		REQUIRE((
			newS.top().s == testStack.top().s
		&	newS.top().r == testStack.top().r
		));
	}
	
}
