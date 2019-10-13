/**
 * \file GameBoard.h
 * \author Behdad Khamneli
 * \brief Template module to create the Game board
 */

//Collaborator: Behzad Khamneli

#ifndef A3_GAME_BOARD_H_
#define A3_GAME_BOARD_H_

#include <vector>
#include <functional>
#include "CardTypes.h"
#include "CardStack.h"

using namespace std;

/**
 * \brief Class representing a (forty thieves) game board
 * \details Creates a game board having Tableau, Foundation, Deck and Waste
 */
class BoardT{
	private:
		// A seq of CardStackT --> Tableau 
		vector<CardStackT> T;
		// A seq of CardStackT --> Foundation
		vector<CardStackT> F;
		// CardStackT --> Deck
		CardStackT D;
		// CardStackT --> Waste
		CardStackT W;

		//local functions
		/**
 		 * \brief checks if there is two of each card in the board
 		 * \param T The Tableau
 		 * \param F The Foundation
 		 * \param D The Deck stack
 		 * \param W The Waste stack
 		 * \return True if there is two of each card in the board, False otherwise
 		 */
		bool two_decks(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W) const;
		
		/**
 		 * \brief Counts the cards in seq of CardStackT
 		 * \param S A sequence of Stacks of cards 
 		 * \param f Function that takes a CardT and returns a bool
 		 * \return A natural number representing the number of cards in S
 		 */
		nat cnt_cards_seq(vector<CardStackT> S, std::function<bool(CardT)> f) const;

		/**
		 * \brief Counts the number of cards in a Stack
		 * \param s A stack(CardStackT) of cards
		 * \param f A function that takes a CardT and returns a bool
		 * \return A natural number representing the number of cards in s
		 */
		nat cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f) const;

		/**
 		 * \brief Counts the number of cards in the board
 		 * \details adds up all the cards in Tableau, Foundation, Deck and Waste
 		 * \param T The Tableau
 		 * \param F The Foundation
 		 * \param D The Deck
 		 * \param W The Waste
 		 * \return A natural number representing the total number of cards in the board
 		 */
		nat cnt_cards(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W, std::function<bool(CardT)>f) const;

		/**
 		 * \brief creates a empty seq of CardStackT
 		 * \details Can be used to initialize the Foundation 
 		 * \param n A natural number representing the number of empty stacks
 		 * \return A seq of CardStackT with n number of empty stacks
 		 */
		vector<CardStackT> init_seq(nat n);

		/**
 		 * \brief Creates a sequence of CardStackT from a part of the given deck of cards
 		 * \details Can be used to initialize the Tableau
 		 * \param deck A seq of CardT 
 		 * \return A seq of CardStackT that is a part of the deck
 		 */
		vector<CardStackT> tab_deck(vector<CardT> deck);
		
		/**
 		 * \breif Checks if n is a valid position in Category c
 		 * \param c One of the elements of CategoryT
 		 * \param n (natural number)The position that needs to be checked
 		 * \return True if the position is valid, False otherwise
 		 */
		bool is_valid_pos(CategoryT c, nat n) const;

		/**
 		 * \brief Checks if the tab tab move is valid
 		 * \details move is from n0 to n1 is tableau
 		 * \param n0 (natural number)The first position to move from
 		 * \param n1 (natural number)The destination in tableau
 		 * \return True if the move is valid, False otherwise
 		 */
		bool valid_tab_tab(nat n0, nat n1) const;

		/**
 		 * \brief Checks if the Tableau to Foundation move is valid
 		 * \param n0 (natural number)The position to move from in Tableau
 		 * \param n1 (natural number)The position to move to in Foundation
 		 * \return True if the move from Tableau to Foundation is valid, False otherwise
 		 */
		bool valid_tab_foundation(nat n0, nat n1) const;

		/**
 		 * \brief Checks if the Waste to Tableau move is valid
 		 * \param n (natural number)The position in Tableau
 		 * \return True if the move from Waste to Tableau is valid, False otherwise
 		 */
		bool valid_waste_tab(nat n) const;

		/**
 		 * \brief Checks if the move from Waste to Foundation is valid
 		 * \param n (natural number)The position in Foundation
 		 * \return True if the move from Waste to Foundation is valid, False otherwise
 		 */
		bool valid_waste_foundation(nat n) const;

		/**
		 * \brief Checks if it is valid to place a card on top of another card in Tableau
		 * \param c The card that needs to be placed in Tablea
		 * \param d The top card of the Tableau's stacks
		 * \return True if its possible to place c on d in Tableau, False otherwise
		 */
		bool tab_placeable(CardT c, CardT d) const;

		/**
 		 * \brief Checks if it is valid to put a card on top of other card in foundation
 		 * \param c The card that needs to be placed in Foundation
 		 * \param d The top card of the Foundation stacks
 		 * \return True if its possible to place c on top of d in Foundation, False otherwise
 		 */
		bool foundation_placeable(CardT c, CardT d) const;

		
	public:
		/**
   		 * \brief Constructs a new board
   		 * \details Initializes the Tableau, Foundation, Deck and Waste
   		 * \param deck A seq of cards(two decks of cards)
   		 * \throws invalid_argument if there is not two of each card in the board
   		 */
		BoardT(vector<CardT> deck);
		/**
 		 * \brief Checks if its valid to move a card from Tableau
 		 * \param c The destination category
 		 * \param n0 The position of the Card in Tableau
 		 * \param n1 The destination position in c
 		 * \throws out_of_range if the given positions are invalid in category 
 		 * \return True if the move is valid, False otherwise 
 		 */
		bool is_valid_tab_mv(CategoryT c, nat n0, nat n1) const;

		/**
 		 * \brief Checks if it is valid to move a card from waste
 		 * \param c The destination category
 		 * \param n The destination position in c
 		 * \throws invalid_argument if there is no card in Waste
 		 * \throws out_of_range if the given position is not valid in Tableau
 		 * \throws out_of_range if the given position is not valid in Foundation
 		 * \return True if the move is valid, False otherwise
 		 */
		bool is_valid_waste_mv(CategoryT c, nat n) const;

		/**
 		 * \brief Checks if it is valid to move a card from Deck
 		 * \return True if Deck is not empty, False if the Deck is empty
 		 */
		bool is_valid_deck_mv() const;
		
		/**
 		 * \brief Moves a card from Tableau
 		 * \details destination catagories can only be Tableau or Foundation
 		 * because it is not possible to move from Tableau to deck or waste
 		 * \param c The destination Cate1gory(Tableau or Foundation)
 		 * \param n0 (natural number)The card's position in Tableau
 		 * \param n1 (natural number)The card's position in c
 		 * \throws invalid_argument if the tab move is not valid
 		 */
		void tab_mv(CategoryT c, nat n0, nat n1);

		/**
 		 * \brief Moves a card from Waste
 		 * \param c The destination category(Tableau or Foundation)
 		 * \param n (natural number)The position in c
 		 * \throws invalid_argument if the waste mov is not valid
 		 */
		void waste_mv(CategoryT c, nat n);

		/**
 		 * \brief Move a card from deck to waste
 		 * \throws invalid_argument if it is not a valid deck move
 		 */
		void deck_mv();
		
		/**
 		 * \brief Returns the stack of cards in Tableau
 		 * \param i (natural number)A position in Tableau
 		 * \throws out_of_range if i is not a valid Tableau position
 		 * \return CardStackT at position i in Tableau
 		 */
		CardStackT get_tab(nat i) const;

		/**
 		 * \brief Returns the stack of cards in Foundation
 		 * \param i A position in Foundation
 		 * \throws out_of_range if i is not a valid position in Foundation
 		 * \return CardStackT at position i in Foundation
 		 */
		CardStackT get_foundation(nat i) const;

		/**
 		 * \return The Deck:CardStackT
 		 */
		CardStackT get_deck() const;

		/**
  		 * \return The Waste:CardStackT
  		 */
		CardStackT get_waste() const;

		/**
 		 * \brief Checks if a valid move exists
 		 * \details checks if it is possible to do a tab move, waste move or deck move
 		 * \return True if a valid move exists, False otherwise
 		 */
		bool valid_mv_exists() const;

		/**
 	  	 * \brief Checks if all the Foundation stacks have king as the top card
 	  	 * \return True if Foundation stacks are not empty and they all have
 	  	 * king at the top, False otherwise
 	  	 */
		bool is_win_state() const;
};
#endif
