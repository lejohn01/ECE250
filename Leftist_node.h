/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y64zou@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}
/** Note: You must use the style above here and in Leftist_heap.h **/
template <typename Type>
Type Leftist_node<Type>::retrieve() const
{
	return element;
}
template <typename Type>
int Leftist_node<Type>::count(Type const &obj) const
{
	if(this == nullptr)
	{
		return 0;
	}
	int sum_left = 0;
	int sum_right = 0;
	if(this->retrieve() > obj)
	{
		return 0;
	}
	if(this->retrieve() == obj)
	{
		sum_left = this->left()->count(obj);
		sum_right = this->right()->count(obj);
		return 1 + (sum_left + sum_right);
	}
	if(this->retrieve() < obj)
	{//go down its subtrees
		sum_left = this->left()->count(obj);
		sum_right = this->right()->count(obj);
	}
	return (sum_left + sum_right);
	//count(5) returns how many times 5 appears in the subtree with this object as the root
}
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const
{
	return left_tree;
}
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const
{
	return right_tree;
}
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
	if(this == nullptr)
	{
		return -1;
	}
	else
	{
		return heap_null_path_length;
	}
}
template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&pointer_to_this)
{
	if (new_heap == nullptr)
	{
		heap_null_path_length =-1;
		return;
	}
	if(pointer_to_this == nullptr)
	{
		pointer_to_this = new_heap;
		pointer_to_this->heap_null_path_length = 0;//update the null path length here
		return;
	}
	if((*pointer_to_this).retrieve() <= (*new_heap).retrieve())
	{
		this->right()->push(new_heap,right_tree);
		//swap if the right tree's npl is larger than the left tree's npl
		if(this->left()->null_path_length() < this->right()->null_path_length())
		{
			Leftist_node* temp = left_tree;
			left_tree = right_tree;
			right_tree = temp;
			delete temp;
		}
		heap_null_path_length = 1 + this->right()->null_path_length();
		return;
	}
	else
	{
		Leftist_node* temp = pointer_to_this;
		pointer_to_this = new_heap; //use a temp to hold the pointer_to_this as we need to add it back in
		pointer_to_this->push(temp,new_heap);
		//delete temp;
		return;
	}
}
template <typename Type>
void Leftist_node<Type>::clear()
{

	if(this == nullptr)
	{
		return;
	}
		left()->clear();
		right()->clear();
		delete this;

	return;
	//if this is null do nothing; otherwise call clear on this left subtree, right subtree, and this itself
}
// You must implement everything

#endif
