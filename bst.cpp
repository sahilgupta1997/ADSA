/* Filename:  bst.cpp
 * Author:    Tushar Jain
 * Date:      19/4/2015
 * Purpose:   The implementation file for a BST of student record.
 * Version :  6
 * Version Modifications:
 	3.1) Copy Constructor for Node Class
 	3.2) copyData function for Node Class
 	3.3) delete function of Tree Class overhauled for better efficiency based on Sir's concept

 	4.1) Added Transplant function in Tree Class
 	4.2) delete function of Tree Class changed based on Cormen's concept to utilize transplant()

 	5.1) Class Tree are converted to template form for Generic Use
 	5.2) Key has been converted to string for lexiographical use.
 	5.3) return type of addNode() changed to NodeType.
 	5.4) Main Program to test has been removed. 

 	6.1) Main added for testing
 	6.2) Class Node has been templated.
 	6.3) Class BSTNode made & inherited from Class Node.
 * Bugs:
*/

#include <iostream>
#include <string>
 using namespace std;

// A generic tree node class
template<class NodeType>
 class Node {
 	string key;
 	NodeType* left;
 	NodeType* right;
 	NodeType* parent;
 public:
 	Node() { key="-1"; left=NULL; right=NULL; parent = NULL;};
    Node(NodeType* source) {  //Copy Constructor
    	key=source->Key();left=source->Left();right=source->Right();parent=source->Parent(); 
    };
    void setKey(string aKey) { key = aKey; };
    void setLeft(NodeType* aLeft) { left = aLeft; };
    void setRight(NodeType* aRight) { right = aRight; };
    void setParent(NodeType* aParent) { parent = aParent; };
    string  Key() { return key; };
    NodeType* Left() { return left; };
    NodeType* Right() { return right; };
    NodeType* Parent() { return parent; };
    void copyData(NodeType* source){key=source->key;};
    };

class BSTNode : public Node<BSTNode>
{
};

// Binary Search Tree class
template<class NodeType>
    class Tree {
    	NodeType* root;
    public:
    	Tree();
    	~Tree();
    	NodeType* Root() { return root; };
    	NodeType* addNode(string key);
    	NodeType* findNode(string key, NodeType* parent);
    	void preOrder(NodeType* node);
    	void inOrder(NodeType* node);
    	void postOrder(NodeType* node);
    	void deleteNode(string key);
    	NodeType* min(NodeType* node);
    	NodeType* max(NodeType* node);
    	NodeType* successor(string key, NodeType* parent);
    	NodeType* predecessor(string key, NodeType* parent);
    private:
    	NodeType* addNode(string key, NodeType* leaf);
    	void freeNode(NodeType* leaf);
    	void transplant(NodeType* u,NodeType* v);
    };

/*class BSTree : public Tree<BSTNode>
{
};*/

// Constructor
template<class NodeType>
    Tree<NodeType>::Tree() {
    	root = NULL;
    }

// Destructor
template<class NodeType>
    Tree<NodeType>::~Tree() {
    	freeNode(root);
    }

// Free the node
template<class NodeType>
    void Tree<NodeType>::freeNode(NodeType* leaf)
    {
    	if ( leaf != NULL ) 
    	{
    		freeNode(leaf->Left());
    		freeNode(leaf->Right());
    		delete leaf;
    	}
    }

// Add a node [O(height of tree) on average]
template<class NodeType>
    NodeType* Tree<NodeType>::addNode(string key)
    {
    // No elements. Add the root
    	if ( root == NULL ) {
    		cout << "adding root node ... " << key << endl;
    		NodeType* n = new NodeType();
    		n->setKey(key);
    		root = n;
    		return n;
    	}
    	else {
    		cout << "adding other node ... " << key << endl;
    		return addNode(key, root);
    	}
    }

// Add a node (private function)
template<class NodeType>
    NodeType* Tree<NodeType>::addNode(string key, NodeType* leaf)
     {
    	if ( key < leaf->Key() )
    	{
    		if ( leaf->Left() != NULL )
    			addNode(key, leaf->Left());
    		else {
    			NodeType* n = new NodeType();
    			n->setKey(key);
    			n->setParent(leaf);
    			leaf->setLeft(n);
    			return n;
    		}
    	}
    	else
    	{
    		if ( leaf->Right() != NULL )
    			addNode(key, leaf->Right());
    		else {
    			NodeType* n = new NodeType();
    			n->setKey(key);
    			n->setParent(leaf);
    			leaf->setRight(n);
    			return n;
    		}
    	}
    }

// To move subtrees within BST (private function)
template<class NodeType>
    void Tree<NodeType>::transplant(NodeType* u, NodeType* v)
    {
    	if (u ->Parent() == NULL)
    		root =v;
    	else if(u == u ->Parent() ->Left())
    		u ->Parent() ->setLeft(v);
    	else 
    		u ->Parent() ->setRight(v);
    	if (v)
    		v->setParent(u ->Parent());
    }

// Find a node [O(height of tree) on average]
template<class NodeType>
    NodeType* Tree<NodeType>::findNode(string key, NodeType* node)
    {
    	if ( node == NULL )
    		return NULL;
    	else if ( node->Key() == key )
    		return node;
    	else if ( key < node->Key() )
    		findNode(key, node->Left());
    	else if ( key > node->Key() )
    		findNode(key, node->Right());
    	else
    		return NULL;
    }

// Traverse in pre-order fashion & Print the tree 
template<class NodeType>
    void Tree<NodeType>::preOrder(NodeType* node)
    {
    	if ( node )
    	{
    		cout << node->Key() << " ";
    		preOrder(node->Left());
    		preOrder(node->Right());
    	}
    }

// Traverse in in-order fashion & Print the tree 
template<class NodeType>
    void Tree<NodeType>::inOrder(NodeType* node)
    {
    	if ( node )
    	{
    		inOrder(node->Left());
    		cout << node->Key() << " ";        
    		inOrder(node->Right());
    	}
    }

// Traverse in post-order fashion & Print the tree 
template<class NodeType>
    void Tree<NodeType>::postOrder(NodeType* node)
    {
    	if ( node )
    	{
    		postOrder(node->Left());
    		postOrder(node->Right());
    		cout << node->Key() << " ";
    	}
    }


// Find the node with min key [O(height of tree) on average]
// Traverse the left sub-tree recursively	
// till left sub-tree is empty to get min
template<class NodeType>
    NodeType* Tree<NodeType>::min(NodeType* node)
    {
    	if ( node == NULL )
    		return NULL;

    	if ( node->Left() )
    		min(node->Left());
    	else
    		return node;
    }

// Find the node with max key [O(height of tree) on average]
// Traverse the right sub-tree recursively
// till right sub-tree is empty to get max
template<class NodeType>
    NodeType* Tree<NodeType>::max(NodeType* node)
    {
    	if ( node == NULL )
    		return NULL;

    	if ( node->Right() )
    		max(node->Right());
    	else
    		return node;
    }

// 	Find successor to a node  [O(height of tree) on average]
//	Find the node, 
//	(1) If right-child exists, get the node with min value
// 	for the right sub-tree to get the successor
//	(2) If right-child is NULL, 
//  go up the tree till we encounter a node which is
// 	the left-Child of its parent.
template<class NodeType>
    NodeType* Tree<NodeType>::successor(string key, NodeType *node)
    {
	// Find the Node
    	NodeType* thisKey = findNode(key, node);

    //(1)
    	if ( thisKey && thisKey->Right())
    		return min(thisKey->Right());
    //(2)
    	if ( thisKey && thisKey->Right() == NULL )
    	{
    		NodeType* temp = thisKey->Parent();
    		while(temp && thisKey == temp -> Right())
    		{
    			thisKey = temp;
    			temp = temp -> Parent();
    		}
    		return temp;
    	}

    }

// Find predecessor to a node
// Find the node,
// (1) If left-Child exists, get the node with max value
// for the left sub-tree to get the predecessor
// (2) If left-Child is NULL,
// go up the tree till you encounter a node which is 
// the right-child of its parent.
template<class NodeType>
    NodeType* Tree<NodeType>::predecessor(string key, NodeType *node)
    {

	// Find the Node
    	NodeType* thisKey = findNode(key, node);

    //(1)
    	if ( thisKey && thisKey->Left())
    		return min(thisKey->Left());
    //(2)
    	else if ( thisKey && thisKey->Left() == NULL )
    	{
    		NodeType* temp = thisKey->Parent();
    		while(temp && thisKey == temp -> Left())
    		{
    			thisKey = temp;
    			temp = temp -> Right();
    		}
    		return temp;
    	}

    	else {
    		cout << "Predeccesor exists only for keys from Tree.\n Input a key from tree." ;
    		return NULL;
    	}
    }

// Delete a node
// (1) If leaf just delete
// (2) If only one child delete this node and replace
// with the child
// (3) If 2 children. Find the predecessor (or successor).
// Delete the predecessor (or successor). Replace the
// node to be deleted with the predecessor (or successor).
/* Version 3
template<class NodeType>
void Tree<NodeType>::deleteNode(string key)
{
    // Find the node.
    NodeType* thisKey = findNode(key, root);	//x
    NodeType* y;								//y
    NodeType* z;								//z
    
    if(thisKey->Left() == NULL || thisKey->Right() == NULL )
    	y = thisKey;						//initialized for Case (1) & (2)
    else
    	y = successor(thisKey->Key(),root);	//initialized for Case (3)

    if(y -> Left())							//Case (2)
    	z = y ->Left();
    else
    	z = y ->Right();

    if(z)
    	z ->setParent(y ->Parent());

    NodeType* py = y -> Parent();
    if (y == py ->Left())					//Case (3)
    	py ->setLeft(z);
    else
    	py ->setRight(z);

    if(thisKey != y)
    	thisKey->copyData(y);// Copy Associated data in y to thisKey.

    delete thisKey;
    delete y;
    delete z;
}
*/

template<class NodeType>
void Tree<NodeType>::deleteNode (string key)
{
	NodeType* z= findNode(key, root);

	if(z ->Left() == NULL)
		transplant(z,z->Right());
	else if(z->Right() == NULL)
		transplant(z,z->Left());
	else
	{
		NodeType* y = min(z->Right());
		if (y->Parent() != z)
		{
			transplant(y,y->Right());
			y->setRight(z->Right());
			y->Right()->setParent(y);
		}
		transplant(z,y);
		y->setLeft(z->Left());
		y->Left()->setParent(y);
	}
}

 // Test main program
 int main() 
 {
 	Tree<BSTNode>* tree = new Tree<BSTNode>;

     // Add nodes
 	tree->addNode("300");
 	tree->addNode("100");
 	tree->addNode("200");
 	tree->addNode("400");
 	tree->addNode("500");

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
 	tree->deleteNode("100");

 	cout << "between Delete & Traverse";
     // Traverse the tree
 	tree->preOrder(tree->Root());
 	cout << endl;


 	delete tree;
 	return 0;
 }