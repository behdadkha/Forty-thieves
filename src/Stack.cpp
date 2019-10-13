//Collaborator: Behzad Khamneli

// Implementation here
#include <vector>
#include "Stack.h"
#include "CardTypes.h"
#include <stdexcept>

using std::vector;

template <class T>
Stack<T>::Stack(vector<T> s){
	this->S = s;//instance initializer
}

template <class T>
Stack<T> Stack<T>::push(T e){
	S.push_back(e);
	return Stack(S);//following functional programing
}

template <class T>
Stack<T> Stack<T>::pop(){
	if(S.size() == 0)
		throw std::out_of_range("no element to pop!!");
	S.pop_back();
	return Stack(S);
}

template <class T>
T Stack<T>::top() const{
	if(S.size() == 0)
		throw std::out_of_range("no element in the stack!!");
	return S.back(); //the last pushed element
}

template <class T>
unsigned int Stack<T>::size() const{
	return S.size();
}

template <class T>
vector<T> Stack<T>::toSeq() const{
	return S;
}

// Keep this at bottom
template class Stack<CardT>;
