/**
 * \file Stack.h
 * \author Behdad Khamneli
 * \brief Generic template module stack<T>
 */

//collaborator: Behzad Khamneli

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

/**
 * \brief Class representing stack
 */
template <class T>
class Stack
{
    private:
	// sequence of T
        std::vector<T> S; 

    public:
	/**
 	 * \brief Constructs a new stack
 	 * \param p A seq of T(The elements of the stack)
 	 */
        Stack(std::vector<T> s);

	/**
 	 * \brief Pushes a new element into the stack
 	 * \param e A element of type T
 	 * \return A new stack with element e at the back
 	 */
        Stack<T> push(T e);

	/**
 	 * \brief Removes the last element from the stack
 	 * \throws out_of_range if the stack vector is empty(S)
 	 * \return A new stack with the last element removed
 	 */
        Stack<T> pop();

	/**
 	 * \brief returns the top element in the stack
 	 * \throws out_of_range if the stack vector is empty(S)
 	 * \return The top element: T in the stack
 	 */
        T top() const;

	/**
 	 * \return The size of the stack
 	 */
        unsigned int size() const;

	/**
 	 * \brief Returns a seq of T representing the stack
 	 * \return seq of T
 	 */
        std::vector<T> toSeq() const;
};

#endif
