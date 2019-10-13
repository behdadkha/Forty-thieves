//Collaborator: Behzad Khamneli

#include "CardTypes.h"
#include "CardStack.h"
#include "GameBoard.h"

#include <iostream>
#include <stdexcept>
#include <functional>

#include <vector>

using std::vector;


BoardT::BoardT(vector<CardT> deck):D(CardStackT({})), W(CardStackT({}))
{
	if(!two_decks(init_seq(10), init_seq(8), CardStackT(deck), CardStackT({})))
		throw std::invalid_argument("bad deck");
	vector<CardT> first(deck.cbegin(), deck.cbegin()+40);
	vector<CardT> second(deck.cbegin()+40, deck.cbegin()+104);
	
	//initializes the instance variables
	this->T = tab_deck(first);
	this->D = CardStackT(second);
	this->F = init_seq(8);
	this->W = CardStackT({});
	
}

bool BoardT::is_valid_tab_mv(CategoryT c, nat n0, nat n1) const{
	//exceptions for when invalid position
	if(c == Tableau && !(is_valid_pos(Tableau,n0) && is_valid_pos(Tableau,n1)))
		throw std::out_of_range("not valid tab_tab move");
	if(c == Foundation && !(is_valid_pos(Tableau, n0) && is_valid_pos(Foundation, n1)))
		throw std::out_of_range("not valid tab_foundation move");
	switch(c){
		case Tableau:
			return valid_tab_tab(n0, n1);
		case Foundation:
                     	return valid_tab_foundation(n0, n1);
		case Deck:	//tab deck and tab waste moves are not valid 
			return false;
		case Waste:
			return false;
	}
	return false;
}
bool BoardT::is_valid_waste_mv(CategoryT c, nat n) const{
	//empty waste cant have any move
	if(W.size() == 0)
		throw std::invalid_argument("W.size is 0");
	if(c == Tableau && !is_valid_pos(Tableau,n))
		throw std::out_of_range("not valid pos");
	if(c == Foundation && !is_valid_pos(Foundation, n))
		throw std::out_of_range("not valid pos");
	switch(c){
		case Tableau:
			return valid_waste_tab(n);
		case Foundation:
			return valid_waste_foundation(n);
		case Deck:
			return false;
		case Waste:
			return false;
	}
	return false;
}
bool BoardT::is_valid_deck_mv() const{
	return D.size() > 0;
}
void BoardT::tab_mv(CategoryT c, nat n0, nat n1){
	if(!is_valid_tab_mv(c,n0,n1))
		throw std::invalid_argument("not valid move");
	if(c == Tableau){
		//moves card from T[n0] to T[n1]
		T[n1] = T[n1].push(T[n0].top());
		T[n0] = T[n0].pop();
	}
	if(c == Foundation){
		//moves card from T[n0] to F[n1]
		F[n1] = F[n1].push(T[n0].top());
		T[n0] = T[n0].pop();
	}
}
void BoardT::waste_mv(CategoryT c, nat n){	
	if(!is_valid_waste_mv(c,n))
		throw std::invalid_argument("not valid move");
	if(c == Tableau){
		//moves the card from waste to T[n]
		T[n] = T[n].push(W.top());
		W = W.pop();
	}
	if(c == Foundation){
		//mvoes the card from waste to F[n]
		F[n] = F[n].push(W.top());
		W = W.pop();
	}
}
void BoardT::deck_mv(){
	if(!is_valid_deck_mv())
		throw std::invalid_argument("not valid deck move");
	//moves a card from deck to waste
	W = W.push(D.top());
	D = D.pop();
}
CardStackT BoardT::get_tab(nat i) const{
	if(!is_valid_pos(Tableau,i))
		throw std::out_of_range("tab does not exist");
	return T[i];
}
CardStackT BoardT::get_foundation(nat i) const{
	if(!is_valid_pos(Foundation,i))
		throw std::out_of_range("foundation does not exist");
	return F[i];
}
CardStackT BoardT::get_deck() const{
	return D;
}
CardStackT BoardT::get_waste() const{
	return W;
}
bool BoardT::valid_mv_exists() const{
	
	for(auto c : {Tableau, Foundation}){
		for(int n0 = 0, n1 = 0; is_valid_pos(Tableau, n0) && is_valid_pos(c,n1); n0++,n1++){
			if(is_valid_tab_mv(c, n0, n1))
				return true;//existential quantification
		}
	}
	for(auto c : {Tableau, Foundation}){
		for(int n = 0; is_valid_pos(c,n) && W.size() != 0; n++){
			if(is_valid_waste_mv(c,n))
				return true;
		}
	}
        if(is_valid_deck_mv())
                return true;

	return false;//if no valid move exists
}
bool BoardT::is_win_state() const{
		
	for(int i = 0; i < 8; i++){
		if(F[i].size() == 0)//not a win state if any foundation stack is empty
			return false;
		if(!(F.at(i).top().r == KING))
			return false;
		
	}
	return true;
}

// private methods

bool BoardT::two_decks(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W) const{
	for(int st = Heart; st != Spade; st++){
		for(int rk = 1; rk <= 13; rk++ ){//using lambda function
			if(!(cnt_cards(T,F,D,W, [st,rk](CardT c) {return (c.s == st && c.r == rk);}) == 2))
				return false;
		}
	}
	return true;
}
unsigned int BoardT::cnt_cards_seq(vector<CardStackT> S, std::function<bool(CardT)> f) const{
	int num = 0;
	for(auto s : S){
		num += cnt_cards_stack(s, f);	
	}
	return num;
}
nat BoardT::cnt_cards_stack(CardStackT s, std::function<bool(CardT)> f) const{
	int num = 0;
	for(auto c : s.toSeq()){
		if(f(c))
			num++;
	}
	return num;
}
nat BoardT::cnt_cards(vector<CardStackT> T, vector<CardStackT> F, CardStackT D, CardStackT W, std::function<bool(CardT)> f) const{
	return cnt_cards_seq(T,f)+cnt_cards_seq(F,f)+cnt_cards_stack(D,f)+cnt_cards_stack(W,f);	
}
vector<CardStackT> BoardT::init_seq(nat n){
	vector<CardStackT> s;
	vector<CardT> emp = {}; 
	for(nat i = 0; i < n; i++){
		s.push_back(CardStackT(emp));//creates empty stacks
	}
	return s;
}
vector<CardStackT> BoardT::tab_deck(vector<CardT> deck){
	vector<CardStackT> T;
	for(int i = 0; i < 10; i++){
		
		vector<CardT> sT(deck.cbegin()+(4*i), deck.cbegin()+(4*(i+1)));
		
		T.push_back(CardStackT(sT));//pushs stacks with cards
	}
	return T;
}
bool BoardT::is_valid_pos(CategoryT c, nat n)const{
	//only tableau and foundation have restircted pos
	if(c == Tableau){
		return 0 <= n && n <= 9; 
	}else if(c == Foundation){
		return 0 <= n && n <= 7;  
	}else
		return true;
}
bool BoardT::valid_tab_tab(nat n0, nat n1) const{
	if(T[n0].size() > 0){
		if(T[n1].size() > 0)
			return tab_placeable(T[n0].top(), T[n1].top());
		if(T[n1].size() == 0)
			return true;//without checking we know its placeable
	}
	if(T[n0].size() == 0){//if there is no card in Tableau[n0] 
		if(T[n1].size() > 0)
			return false;//not possible to move when stack is empty
		if(T[n1].size() == 0)
			return false;
	}
	return false;
}
bool BoardT::valid_tab_foundation(nat n0, nat n1) const{
	if(T[n0].size() > 0){
		if(F[n1].size() > 0)
			return foundation_placeable(T[n0].top(), F[n1].top());
		if(F[n1].size() == 0)
			return T[n0].top().r == ACE;//Aces can only initialize the foundation stacks
	}
	if(T[n0].size() == 0){//not possible to move a card when there is no cards
		if(F[n1].size() > 0)
			return false;
		if(F[n1].size() == 0)
			return false;
	}
	return false;
}
bool BoardT::valid_waste_tab(nat n) const{
	if(T[n].size() > 0)//there already exists a card
		return tab_placeable(W.top(), T[n].top());
	if(T[n].size() == 0)//if its the first card going to the tableau[n]
		return true;
	return false;
}
bool BoardT::valid_waste_foundation(nat n) const{
	if(F[n].size() > 0)
		return foundation_placeable(W.top(), F[n].top());
	if(F[n].size() == 0)
		return W.top().r == ACE;//Aces can only initialize the foundation stacks
	return false;
}
bool BoardT::tab_placeable(CardT c, CardT d) const{
	return c.s == d.s && c.r == d.r - 1;//game rules
}
bool BoardT::foundation_placeable(CardT c, CardT d) const{
	return c.s == d.s && c.r == d.r + 1;//game rules
}
