/* Filename:  avl.cpp
 * Author:    Tushar Jain
 * Date:      19/4/2015
 * Purpose:   The implementation file for a BST of student record.
 * Version :  2
 * Version Modifications:
 * 	 1.1) Class AVLTree inherits class Tree
 * 	 1.2) Main added for testing
 * 	 1.3) Constructors added.
 * 	 1.4) Utility functions max(), getBalance() & height() added
 * 	 
 * 	 2.1) Class Avlnode inherited from Class Node
 * 	 2.2) InsertNode() added
 * 	 2.3) UpdateHeight(),BalanceTree() & right,left rotation functions added
 * 
 * Bugs:
 * 1.1) No delete function
 *->Done->  1.2) AVLNode doesn't inherit Node
 * 1.3) Node isn't templated
 * 1.4) File I/O not implemented
 * 1.5) Student record class not managed
*/

#include <iostream>
#include <string>
#include "bst.cpp"
 using namespace std;

//same error with & without inheritance 
//=> template not required for Node
//=> insert function is not working


class AvlNode : public Node<AvlNode>
 {
	int height;
 public:
//
	AvlNode(){height =1;};
	//~AvlNode();
	int Height() { return height; };
	int BalanceFactor(){
		return this->Left()->Height() - this->Right()->Height();
	};
	int setHeight(int aHeight){height=aHeight;};
 };

//
 class AvlTree : public Tree<AvlNode>
 {
 public:
	//AvlTree();
	//~AvlTree();
	void insertNode(string key);
	void deleteNode(string key);
	using Tree::max;

private:
	int height(AvlNode* N)
	{
		if(N == NULL)
			return 0;
		return N->Height();
	};
	int getBalance(AvlNode* N)
	{
		if(N == NULL)
			return 0;
		return height(N->Left()) - height(N->Right());
	}
	int max(int a, int b){ return (a > b)? a : b;} 	// A utility function to get maximum of two integers
	void heightUpdate(AvlNode* z);
	void balanceTree(AvlNode* z);
	void rightRotate(AvlNode* z);
	void leftRotate(AvlNode* z);
	
 };


// Insert a node in AVL Tree
// 1. Perform the normal BST rotation
// 2. Update height of this ancestor node
// 3. Get the balance factor of this ancestor node to check whether
// this node became unbalanced 
// 4. If this node becomes unbalanced, apply appropriate 
// rotation case out of the 4
/*AvlNode* AvlTree::insertNode(AvlNode* node, string key)
{
	// (1)
	if(node == NULL)
	{
		AvlNode* node = new AvlNode;
		node->setKey(key);
		return node;
	}

	if(key < node->Key())
		node->setLeft(insertNode(node->Left(),key));
	else
		node->setRight(insertNode(node->Right(),key));

	// (2)
	node->setHeight(max(height(node->Left()),height(node->Right())));

	// (3)
	int balance = getBalance(node);

	// (4)
	
	// Left Left Case
	if (balance > 1 && key < node->Left()->Key())
	    return rightRotate(node);
	 
	// Right Right Case
	if (balance < -1 && key > node->Right()->Key())
	    return leftRotate(node);
	 
	// Left Right Case
	if (balance > 1 && key > node->Left()->Key())
	{
	    node->setLeft(leftRotate(node->Left()));
	    return rightRotate(node);
	}
	 
	// Right Left Case
	if (balance < -1 && key < node->Right()->Key())
	{
	    node->setRight(rightRotate(node->Right()));
	    return leftRotate(node);
	}
	// return the (unchanged) node pointer 
	return node;

}*/
void AvlTree::insertNode(string key)
{
	AvlNode* n = addNode(key);
	heightUpdate(n);
}

void AvlTree::heightUpdate(AvlNode* node)
{
	int oldheight = height(node);
	//Update height
	node->setHeight(max(height(node->Left()),height(node->Right()))+1);
	
	int balance = getBalance(node);
	if(oldheight != height(node))
		if(balance<=2 && balance>= -2 )
			heightUpdate(node->Parent());
		else
			balanceTree(node);
	else
		return;
}

void AvlTree::deleteNode(string key)
{

}
//can be improved page 33 Lecture
void AvlTree::balanceTree(AvlNode* z)
{
	int bf= getBalance(z);
	if(bf ==2)
		if(getBalance(z->Left()) == 1)       //Case 1:Single Rotation
			rightRotate(z);		
		else if (getBalance(z->Left()) == -1)//Case 3:Double Rotation
			{
				leftRotate(z->Left());
				rightRotate(z);
			}

	if(bf ==-2)
		if(getBalance(z->Right()) == -1)     //Case 2:Single Rotation
			leftRotate(z);		
		else if (getBalance(z->Right()) == 1)//Case 4:Double Rotation
			{
				rightRotate(z->Right());
				leftRotate(z);
			}
}

void AvlTree::rightRotate(AvlNode *z)
{
	AvlNode *y = z->Left();

	//Take care of parent of y, z
	y->setParent(z->Parent());
	if(z->Parent()->Right() == z)
	   z->Parent()->setRight(y);
	else
		z->Parent()->setLeft(y);

	AvlNode* yr = y->Right();
	// Perform rotation
	z->setParent(y);
	y->setRight(z);
	z->setLeft(yr);

	// Update heights
	y->setHeight(max(height(y->Left()),height(y->Right()))+1);
	z->setHeight(max(height(z->Left()),height(z->Right()))+1);
}
 
void AvlTree::leftRotate(AvlNode *z)
{
	AvlNode *y = z->Right();

	//Take care of parent of y, z
	y->setParent(z->Parent());
	if(z->Parent()->Right() == z)
	   z->Parent()->setRight(y);
	else
		z->Parent()->setLeft(y);

	AvlNode* yl = y->Left();
	// Perform rotation
	z->setParent(y);
	y->setLeft(z);
	z->setRight(yl);

	// Update heights
	y->setHeight(max(height(y->Left()),height(y->Right()))+1);
	z->setHeight(max(height(z->Left()),height(z->Right()))+1);
}

 // Test main program
int main() 
 {
 	AvlTree* tree = new AvlTree;

     // Add nodes
 	tree->insertNode("300");
 	tree->insertNode("100");
 	tree->insertNode("200");
 	tree->insertNode("400");
 	tree->insertNode("500");

     // Traverse the tree
 	cout << "Pre-Order" << endl;
 	tree->preOrder(tree->Root());
 	cout << endl;

     // Find nodes
 	if ( tree->findNode("500", tree->Root()) )
 		cout << "Node 500 found" << endl;
 	else
 		cout << "Node 500 not found" << endl;

 	if ( tree->findNode("600", tree->Root()) )
 		cout << "Node 600 found" << endl;
 	else
 		cout << "Node 600 not found" << endl;

     // Min & Max
 	cout << "Min=" << tree->min(tree->Root())->Key() << endl;
 	cout << "Max=" << tree->max(tree->Root())->Key() << endl;

     // Successor and Predecessor
 	cout << "Successor to 200=" <<
 	tree->successor("200", tree->Root())->Key() << endl;
 	cout << "Predecessor to 300=" <<
 	tree->predecessor("300", tree->Root())->Key() << endl;

     // Delete a node
     // 
 //	tree->deleteNode("100");

 	cout << "between Delete & Traverse";
     // Traverse the tree
 	tree->preOrder(tree->Root());
 	cout << endl;


 	delete tree;
 	return 0;
 }
