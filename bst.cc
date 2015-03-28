#include <iostream>
#include <vector>
#include <cstdlib>	// provides atoi()
#include <iomanip>	// provides std::setw()
#include <cstdio>	// provides sprintf()


/**
 * Defines the tree in a type agnostic way. Usually this would be done with
 * templates, but let's ignore those for today.
 */
typedef int KType;

/**
 * A tree node.
 */
struct Node {
	KType key;
	Node * left;
	Node * right;
};

/**
 * A visitor that can be used to traverse the tree. This is an abstract class;
 * you can't instantiate it directly.
 */
class Visitor {
public:
	virtual ~Visitor() { }
	virtual void visit(Node* node, int level) = 0;
};

/**
 * Creates a new Node with key=key, left=l, and right=r.
 */
Node* createNode( KType key, Node* l = NULL, Node* r = NULL ) {
	Node* result = new Node;
	result->key = key;
	result->left = l;
	result->right = r;
	return result;
}

/**
 * Deletes all nodes in the tree rooted at root and sets root to NULL.
 */
void deleteTree( Node*& root ) {
	if ( root != NULL ) {
		deleteTree( root->left );
		deleteTree( root->right );
		delete root;
		root = NULL;
	}
}

/**
 * Recursively find a node with key 'key'.
 */
Node *& find(KType key, Node *& r) {
	if (r == NULL) return r;
	if (key < r->key)
		return find(key, r->left);
	if (key > r->key)
		return find(key, r->right);
	return r;
}

/**
 * Finds the parent of node in the tree rooted at rootNode
 */
Node* find_parent(Node* rootNode, Node* node) {
  if ( rootNode == NULL || rootNode == node ) {
    return NULL;
  }
  else if ( rootNode->left == node || rootNode->right == node ) {
    return rootNode;
  }
  else if (node->key < rootNode->key) {
    return find_parent(rootNode->left, node);
  }
  else {
    return find_parent(rootNode->right, node);
  }
}

/**
 * Deletes a node containing 'key' in the tree rooted at 'root'.
 */
bool delete_node(Node*& root, KType key) {

	// find target node to delete
	Node* target = find(key, root);
	if (!target) return false;

	// find parent of target
	Node* parent = find_parent(root, target);

	// case 1: target is a leaf
	if (target->left == NULL && target->right == NULL) {
		if (parent != NULL) {
			if ( parent->left == target )
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			root = NULL;

		// free target
		delete target;
		return true;
	}

	// case 2: target has two children
	else if (target->left != NULL && target->right != NULL) {
        Node* pred = target->left;
        while (pred->right)
            pred = pred->right;
        KType val = pred->key;
        delete_node(root, pred->key);
        pred = new Node;
        pred->key = val;
        if (parent) {
            if (parent->left == target)
                parent->left = pred;
            else
                parent->right = pred;
        }
        else
            root = pred;
        pred->left = target->left;
        pred->right = target->right;
        delete target;
		return true;
	}

	// case 3: target has only left child
	else if (target->left != NULL) {
		// set parent's child pointer
		if (parent != NULL) {
			if ( parent->left == target )
				parent->left = target->left;
			else
				parent->right = target->left;
		}
		else
			root = target->left;

		// free target
		delete target;
		return true;
	}

	// case 4: target has only right child
	else {
		// set parent's child pointer
		if (parent != NULL) {
			if (parent->left == target)
				parent->left = target->right;
			else
				parent->right = target->right;
		}
		else
			root = target->right;

		// free target
		delete target;
		return true;
	}
}

/**
 * Inserts key 'key' into the tree rooted at 'root'.
 */
void insert(KType key, Node *& root) {
	Node *& target = find(key, root);
	if( target != NULL ) {
		std::cerr << "Duplicate key \"" << key << "\" not inserted." << std::endl;
	} else {
		target = createNode(key);
	}
}

/**
 * Prints out the tree sideways.
 */
void printTree( Node * r, int d = 0 ) {
	if( r == NULL ) return;
	printTree( r->right, d+1 );
	std::cout << std::setw( 3 * d ) << ""; // output 3 * d spaces
	std::cout << r->key << std::endl;
	printTree( r->left, d+1 );
}

/**
 * Returns the number of nodes in the tree rooted at root.
 */
int numNodes( Node* root ) {
	if (!root) return 0;
    return 1 + numNodes(root->left) + numNodes(root->right);
}

/**
 * Returns the number of leaves in the tree rooted at root.
 */
int numLeaves( Node* root ) {
    if (!root) return 0;
	if (!root->left & !root->right) return 1;
    return numLeaves(root->left) + numLeaves(root->right);
}

/**
 * Returns the height of node x.
 */
int height( Node* x ) {
	if (!x) return -1;  // minus the root
    int r = 1 + height (x->right);
    int l = 1 + height (x->left);
    if (r > l) return r;
    else return l;
    
}

/**
 * Returns the depth of node x in the tree rooted at root.
 */
int depth( Node* x , Node* root ) {
    if (!root) return 0;
    if (root->key == x->key) return 0;
    if (root->key > x->key)
        return 1 + depth(x, root->left);
    else return 1 + depth(x, root->right);
}

/**
 * Traverse a tree rooted at rootNode in-order and use 'v' to visit each node.
 */
void in_order( Node*& rootNode, int level, Visitor& v ) {
    if (!rootNode) return;
    in_order(rootNode->left, level+1, v);
    v.visit(rootNode, level);
    in_order(rootNode->right, level+1, v);
    
}

/**
 * Traverse a tree rooted at rootNode pre-order and use 'v' to visit each node.
 */
void pre_order( Node*& rootNode, int level, Visitor& v ) {
    if (!rootNode) return;
    v.visit(rootNode, level);
    pre_order(rootNode->left, level+1, v);
    pre_order(rootNode->right, level+1, v);
}

/**
 * Traverse a tree rooted at rootNode post-order and use 'v' to visit each node.
 */
void post_order( Node*& rootNode, int level, Visitor& v ) {
    if (!rootNode) return;
    post_order(rootNode->left, level+1, v);
    post_order(rootNode->right, level+1, v);
    v.visit(rootNode, level);
}

