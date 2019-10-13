/**
 * \file CardTypes.h
 * \author Behdad Khamneli
 * \brief record type module that stores constants and card types
 */
#ifndef A3_CARD_TYPES_H_
#define A3_CARD_TYPES_H_

/**
 * \brief Describes the rank of a card.
 */
typedef unsigned short int RankT;

/**
 * \brief Total number of cards
 */
#define TOTAL_CARDS 104

/**
 * \brief RankT for an Ace.
 */
#define ACE    1

/**
 * \brief RankT for an Jack.
 */
#define JACK   11

/**
 * \brief RankT for a Queen.
 */
#define QUEEN  12

/**
 * \brief RankT for a King.
 */
#define KING   13

/**
 * \brief Defines different suits
 */
enum SuitT {Heart, Diamond, Club, Spade};

/**
 * \brief Defines different Catagories
 */
enum CategoryT {Tableau, Foundation, Deck, Waste};

/**
 * \brief tuple of CardT
 */
struct CardT{
    SuitT s;
    unsigned short int r; 
};

/**
 * \brief natural number
 */
typedef unsigned int nat;
#endif
