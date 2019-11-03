/**********************************************************************************************************************************************************************************************************************
* Author:		Brett Sprague
* Filename:		avl.h
* Date:			2/20/2019
* Class: AVL
*
* Purpose: Creates a doubly linked list
*
* Manager functions:
*	AVL()
*		Sets m_root to nullptr
*	~AVL()
*	AVL(const AVL & copy)
*	AVL & operator= (const AVL & rhs)
* Methods:
*	void Insert(const T & data)
*		Calls the recursive insert method to insert from m_root
*	void Delete(T data)
*		Calls the recursive delete method to delete from m_root
*	int Height()
*		Calls the recursive height function
*	void BreadthFirst(void(*Visit)(AVLNode<T>*))
*		Traverses the tree breadthfirst calling Visit on each node
*	void InOrderTrav(void(*Visit)(AVLNode<T>*))
*		Calls the recursive InOrderTrav function with m_root
*	void PreOrderTrav(void(*Visit)(AVLNode<T>*))
*		Calls the recursive PreOrderTrav function with m_root
*	void PostOrderTrav(void(*Visit)(AVLNode<T>*))
*		Calls the recursive PostOrderTrav function with m_root
*	void Purge(AVLNode<T> * root)
*		Recursively purges the list through a postorder traversal
*	void CopyTree(AVLNode<T> * mainRoot)
*		Copies the tree through a breadth first traversal
*	int Height(AVLNode<T> * root)
*		Recursively checks for the height of the tree and returns it
*	void FixBalance(AVLNode<T> * root)
*		Fixes the given node's balance factor based on its left and right children subtrees
*	void Insert(AVLNode<T> *& root, T data, bool & taller)
*		Recursively goes through the tree to insert data and fixes the balance of the tree
*	AVLNode<T> * Delete(AVLNode<T> * root, T data, bool & shorter)
*		Recursively goes through the tree to delete the given data and fixes the balance of the tree
*	void RightRotation(AVLNode<T> *& root, bool & taller)
*		Causes a right rotation to fix the balance of the tree (RR or RL)
*	void RightBalance(AVLNode<T> *& root)
*		Balances the roots right side. 
*	void LeftRotation(AVLNode<T> *& root, bool & taller)
*		Causes a left rotation to fix the balance of the tree (LL or LR)
*	void LeftBalance(AVLNode<T> *& root)
*		Balances the roots left side
*	void InOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root)
*		Traverses the tree calling the Visit function on each node InOrder
*	void PreOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root)
*		Traverses the tree calling the Visit function on each node PreOrder
*	void PostOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root)
*		Traverses the tree calling the Visit function on each node PostOrder
***********************************************************************************************************************************************************************************************************************/
#pragma once
#include "avlnode.h"
#include "listqueue.h"
template <typename T> class AVL
{
public:
	AVL();
	~AVL();
	AVL(const AVL & copy);
	AVL & operator= (const AVL & rhs);
	inline void Insert(const T & data) { bool taller = false; Insert(m_root, data, taller); }
	void Delete(T data);
	inline int Height() { return Height(m_root) - 1; }
	void BreadthFirst(void(*Visit)(AVLNode<T>*));
	void InOrderTrav(void(*Visit)(AVLNode<T>*));
	void PreOrderTrav(void(*Visit)(AVLNode<T>*));
	void PostOrderTrav(void(*Visit)(AVLNode<T>*));
private:
	void Purge(AVLNode<T> * root);
	void CopyTree(AVLNode<T> * mainRoot);
	int Height(AVLNode<T> * root);
	void FixBalance(AVLNode<T> * root);
	void Insert(AVLNode<T> *& root, T data, bool & taller);
	AVLNode<T> * Delete(AVLNode<T> * root, T data, bool & shorter);
	void RightRotation(AVLNode<T> *& root, bool & taller);
	void RightBalance(AVLNode<T> *& root);
	void LeftRotation(AVLNode<T> *& root, bool & taller);
	void LeftBalance(AVLNode<T> *& root);

	void InOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root);
	void PreOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root);
	void PostOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T> * root);
	AVLNode<T> * m_root;
};

template<typename T>
inline AVL<T>::AVL() : m_root(nullptr)
{}

template<typename T>
inline AVL<T>::~AVL()
{
	Purge(m_root);
	m_root = nullptr;
}

template<typename T>
inline AVL<T>::AVL(const AVL & copy) : m_root(nullptr)
{
	Purge(m_root);
	CopyTree(copy.m_root);
}

template<typename T>
inline AVL<T> & AVL<T>::operator=(const AVL & rhs)
{
	if (&rhs != this)
	{
		Purge(m_root);
		CopyTree(rhs.m_root);
	}
	return *this;
}

/********************************************************************************************************************************************************************
* Purpose: Deletes all nodes in the tree
*
* Precondition:
*	None
*
* Postcondition:
*	Frees up all memory taken by the nodes in the tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::Purge(AVLNode<T> * root)
{
	if (root != nullptr)
	{
		Purge(root->m_left);
		Purge(root->m_right);
		delete root;
	}
}

/********************************************************************************************************************************************************************
* Purpose: Inserts the tree to a copy, breadth first so that the tree stays in the same orientation
*
* Precondition:
*	None
*
* Postcondition:
*	Creates a copy of the tree from the root passed through
*********************************************************************************************************************************************************************/
template<typename T>
void AVL<T>::CopyTree(AVLNode<T> * mainRoot) //Performs a breadth-first to copy the AVL tree (breadth-first prevents rebalancing)
{
	AVLNode<T> * root = mainRoot;
	ListQueue<AVLNode<T>*> queue;
	if (root != nullptr)
	{
		queue.Enqueue(root);
		while (!queue.isEmpty()) //Continues until the entire tree has been visited and each has been queued once
		{
			root = queue.Dequeue();
			Insert(root->m_data);
			if (root->m_left != 0)
				queue.Enqueue(root->m_left);
			if (root->m_right != 0)
				queue.Enqueue(root->m_right);
		}
	}
}

/********************************************************************************************************************************************************************
* Purpose: Finds the height of the AVL tree ( +1 )
*
* Precondition:
*	None
*
* Postcondition:
*	Returns the height of the tree + 1
*********************************************************************************************************************************************************************/
template<typename T>
inline int AVL<T>::Height(AVLNode<T> * root)
{
	if (!root)
		return 0;
	return 1 + (Height(root->m_left) < Height(root->m_right) ? Height(root->m_right) : Height(root->m_left));
}

/********************************************************************************************************************************************************************
* Purpose: Uses the height of either of the node's subtrees to find the correct balance factor for the given node
*
* Precondition:
*	None
*
* Postcondition:
*	Sets the given nodes balance factor to be correct based on the AVL tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::FixBalance(AVLNode<T> * root)
{
	if (Height(root->m_left) > Height(root->m_right))	//If the height of the left is greater than that of the right it is left heavy
		root->m_balance = LEFT_HEAVY;

	else if (Height(root->m_right) > Height(root->m_left)) //If the height of the right is greater than that of the left it is right heavy
		root->m_balance = RIGHT_HEAVY;

	else													//If the height of either side is equal it is even heighted
		root->m_balance = EVEN_HEIGHT;

}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to Insert given data
*
* Precondition:
*	None
*
* Postcondition:
*	Adds the data to the tree and rotates if necassary in addition to fixing balance factors of every node
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::Insert(AVLNode<T> *& root, T data, bool & taller)
{
	if (!root)
	{
		root = new AVLNode<T>(data);
		taller = true;
	}
	else if (data < root->m_data) //Left Subtree
	{
		Insert(root->m_left, data, taller);
		if (taller)
		{
			switch (root->m_balance)
			{
			case LEFT_HEAVY:
				LeftRotation(root, taller); //LL
				break;
			case EVEN_HEIGHT:
				root->m_balance = LEFT_HEAVY;
				break;
			case RIGHT_HEAVY:
				root->m_balance = EVEN_HEIGHT;
				taller = false;
				break;
			}
		}
	}
	else if (data >= root->m_data) //Right Subtree
	{
		Insert(root->m_right, data, taller);
		if (taller)
		{
			switch (root->m_balance)
			{
			case LEFT_HEAVY:
				root->m_balance = EVEN_HEIGHT;
				taller = false;
				break;
			case EVEN_HEIGHT:
				root->m_balance = RIGHT_HEAVY;
				break;
			case RIGHT_HEAVY:
				RightRotation(root, taller); //RR
				break;
			}
		}
	}
	FixBalance(root);
}

/********************************************************************************************************************************************************************
* Purpose: Calls the recursive delete function from the start of m_root
*
* Precondition:
*	The tree must exist
*
* Postcondition:
*	Deletes data from the tree
*********************************************************************************************************************************************************************/
template <typename T>
void AVL<T>::Delete(T data)
{
	if (!m_root)
		throw Exception("Cannot delete from an empty tree.");
	bool shorter = false;
	Delete(m_root, data, shorter);
}

/********************************************************************************************************************************************************************
* Purpose: Deletes the given data from the tree
*
* Precondition:
*	The tree must exist
*
* Postcondition:
*	Deletes the data from the tree and rotates if necassary in addition to fixing balance factors of every node
*********************************************************************************************************************************************************************/
template<typename T>
inline AVLNode<T> * AVL<T>::Delete(AVLNode<T> * root, T data, bool & shorter)
{
	if (!root)
	{
		throw Exception("Cannot delete data from list");
	}
	else if (data < root->m_data) //Left Subtree
	{
		root->m_left = Delete(root->m_right, data, shorter);
		if (shorter)
		{
			switch (root->m_balance)
			{
			case LEFT_HEAVY:
				root->m_balance = EVEN_HEIGHT;
				shorter = false;
				break;
			case EVEN_HEIGHT:
				root->m_balance = RIGHT_HEAVY;
				break;
			case RIGHT_HEAVY:
				RightRotation(root, shorter); //RR
				break;
			}
		}
	}
	else if (data > root->m_data) //Right Subtree
	{
		root->m_right = Delete(root->m_right, data, shorter);
		if (shorter)
		{
			switch (root->m_balance)
			{
			case LEFT_HEAVY:
				LeftRotation(root, shorter);
				break;
			case EVEN_HEIGHT:
				root->m_balance = LEFT_HEAVY;
				break;
			case RIGHT_HEAVY:
				root->m_balance = EVEN_HEIGHT;
				shorter = false;
			}
		}
	}
	FixBalance(root); //Maybe works! Might have to cut this line of code

	if (data == root->m_data)
	{
		shorter = true;
		AVLNode<T> * temp = root;

		if (!root->m_left) //If no left child
			root = root->m_right;

		else if (!root->m_right)
			root = root->m_left;

		else	//Two children
		{
			temp = root->m_right;
			AVLNode<T> * trail = nullptr;
			while (temp->m_left) //Travel to the left-most data from the right subtree
			{
				trail = temp;
				temp = temp->m_left;
			}
			root->m_data = temp->m_data; //Copy the data over
			if (trail == nullptr)
				root->m_right = temp->m_right;
			else
				trail->m_left = temp->m_right;
		}
		delete temp;
	}
	return root;
}

/********************************************************************************************************************************************************************
* Purpose: Causes a rotation to correct the right balance of the root's subtree
*
* Precondition:
*	The AVL tree must have been out of balance
*
* Postcondition:
*	Rotates the AVL tree so that is again a valid AVL tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::RightRotation(AVLNode<T> *& root, bool & taller) //Look at this, pure RR and pure LL don't function
{
	if (root->m_balance != root->m_right->m_balance)
	{
		LeftBalance(root->m_right);
		RightBalance(root);
		FixBalance(root->m_right);
	}
	else
		RightBalance(root);
	FixBalance(root->m_left);
	taller = false; //Prevent further changes as the program goes further up the call-stack
}

/********************************************************************************************************************************************************************
* Purpose: Configures the passed through node and its right child to help balance the tree
*
* Precondition:
*	The AVL tree must have been out of balance
*
* Postcondition:
*	Balances the given section of the AVL tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::RightBalance(AVLNode<T> *& root)
{
	AVLNode<T> * oldParent = root;
	AVLNode<T> * newParent = root->m_right;
	oldParent->m_right = newParent->m_left;
	newParent->m_left = oldParent;
	root = newParent;
}

/********************************************************************************************************************************************************************
* Purpose: Causes a rotation to correct the left balance of the root's subtree
*
* Precondition:
*	The AVL tree must have been out of balance
*
* Postcondition:
*	Rotates the AVL tree so that is again a valid AVL tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::LeftRotation(AVLNode<T> *& root, bool & taller)
{
	if (root->m_balance != root->m_left->m_balance)
	{
		RightBalance(root->m_left);
		LeftBalance(root);
		FixBalance(root->m_left);
	}
	else
		LeftBalance(root);
	FixBalance(root->m_right);
	taller = false; //Prevent further changes as the program goes further up the call-stack
}

/********************************************************************************************************************************************************************
* Purpose: Configures the passed through node and its left child to help balance the tree
*
* Precondition:
*	The AVL tree must have been out of balance
*
* Postcondition:
*	Balances the given section of the AVL tree
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::LeftBalance(AVLNode<T> *& root)
{
	AVLNode<T> * oldParent = root;
	AVLNode<T> * newParent = root->m_left;
	oldParent->m_left = newParent->m_right;
	newParent->m_right = oldParent;
	root = newParent;
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to call a given "Visit" function on every node in a breadth first order
*
* Precondition:
	None
*
* Postcondition:
*	Calls the "Visit" function on each node
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::BreadthFirst(void(*Visit)(AVLNode<T>*))
{
	if (!m_root)
		throw Exception("Cannot Traverse Empty Tree");
	AVLNode<T> * root = m_root;
	ListQueue<AVLNode<T>*> queue;
	if (root != nullptr)
	{
		queue.Enqueue(root);
		while (!queue.isEmpty()) //Continues until the entire tree has been visited and each has been queued once
		{
			root = queue.Dequeue();
			Visit(root);
			if (root->m_left != 0)
				queue.Enqueue(root->m_left);
			if (root->m_right != 0)
				queue.Enqueue(root->m_right);
		}
	}
}

/********************************************************************************************************************************************************************
* Purpose: Calls the recursive InOrder function from m_root and checks for an empty tree
*
* Precondition:
*	The tree cannot be empty
*
* Postcondition:
*	Calls InOrderTrav with m_root
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::InOrderTrav(void(*Visit)(AVLNode<T>*))
{
	if (!m_root)
		throw Exception("Cannot Traverse Empty Tree");
	InOrderTrav(Visit, m_root);
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to call a given "Visit" function on every node in a breadth first order
*
* Precondition:
*	The tree must not be empty
*
* Postcondition:
*	Calls the "Visit" function on each node
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::InOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T>* root)
{
	if (root != nullptr)
	{
		InOrderTrav(Visit, root->m_left);
		Visit(root);
		InOrderTrav(Visit, root->m_right);
	}
}

/********************************************************************************************************************************************************************
* Purpose: Calls the recursive PreOrder function from m_root and checks for an empty tree
*
* Precondition:
*	The tree cannot be empty
*
* Postcondition:
*	Calls PreOrderTrav with m_root
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::PreOrderTrav(void(*Visit)(AVLNode<T>*))
{
	if (!m_root)
		throw Exception("Cannot Traverse Empty Tree");
	PreOrderTrav(Visit, m_root);
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to call a given "Visit" function on every node in a PreOrder order
*
* Precondition:
*	The tree must not be empty
*
* Postcondition:
*	Calls the "Visit" function on each node
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::PreOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T>* root)
{
	if (root != nullptr)
	{
		Visit(root);
		PreOrderTrav(Visit, root->m_left);
		PreOrderTrav(Visit, root->m_right);
	}
}

/********************************************************************************************************************************************************************
* Purpose: Calls the recursive InOrder function from m_root and checks for an empty tree
*
* Precondition:
*	The tree cannot be empty
*
* Postcondition:
*	Calls PostOrderTrav with m_root
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::PostOrderTrav(void(*Visit)(AVLNode<T>*))
{
	if (!m_root)
		throw Exception("Cannot Traverse Empty Tree");
	PostOrderTrav(Visit, m_root);
}

/********************************************************************************************************************************************************************
* Purpose: Allows the user to call a given "Visit" function on every node in a PreOrder order
*
* Precondition:
*	The tree must not be empty
*
* Postcondition:
*	Calls the "Visit" function on each node
*********************************************************************************************************************************************************************/
template<typename T>
inline void AVL<T>::PostOrderTrav(void(*Visit)(AVLNode<T>*), AVLNode<T>* root)
{
	if (root != nullptr)
	{
		PostOrderTrav(Visit, root->m_left);
		PostOrderTrav(Visit, root->m_right);
		Visit(root);
	}
}