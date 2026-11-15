// Implement only this file. See avl.h and the assignment for contracts.
#include "avl.h"
#include <queue>



int nodeHeight(const Node* node) {
    (void)node; //head down the 'root' to the value
    if (!node){
        return 0;
    }
    if (!(node->left) && !(node->right)){
        return 1;
    } //no node left or right. return 1 for height
    //traverse down tree. assuming there are nodes... (which there should be)
    std::queue<Node*> cyclonus;
    if (node->left){
            cyclonus.push(node->left);
    }
    if (node->right){
        cyclonus.push(node->right); //add the existing nodes to the queue first
    }
    int size = 1;
    while (cyclonus.size() !=0){ //while the queue ain't empty...
        size++;
        int len = cyclonus.size(); //how many nodes are in this current layer
        for (int i=0; i<len; i++){ //start looking at all nodes in next layer!
            Node* current = cyclonus.front();
            cyclonus.pop(); // set the current and then BOOT the front
            if (current->left){
            cyclonus.push(current->left);
            }
            if (current->right){
                cyclonus.push(current->right); 
            } //assuming this node has children, add to queue
        }
    }
    return size;
} 

void updateHeight(Node* node) {
    (void)node;
    if (node){
        node->height = 1 + std::max(nodeHeight(node->left), nodeHeight(node->right));
    }
} // TODO
// Set height to 1 + max(child heights). Node is non-null; child heights are correct.

int balanceFactor(const Node* node) {
    (void)node;
    if (!node){
        return 0;
    }
    //printf("oh no");
    return nodeHeight(node->left)-nodeHeight(node->right);
} // TODO// Return left height minus right height, or 0 for nullptr.


Node* rotateLeft(Node* root) {
    printf("rotating left");
    if (!(root->right->right)){ //if there is no right root but still unbalanced...
        //swap root left and root.
        Node* temp = root->right;
        root->right = root->right->left;
        root->right->right = temp;
        temp->left = nullptr;
    }
    if (root->right){// accounting for a case where there is already a right side
        Node* temp = root; //save a pointer to the current root
        root=root->right; //now change that root, shift to right
        root->left = temp; //make the left pointer of new root the old temp
        temp->right = nullptr; // now cut off the old's link to the new parent root
    }
    rebalance(root); //rebalance everything
    return root;
} // TODO
/*
    1
      \                 2
        3    ->        / \
       /              1   3
      2        
*/

Node* rotateRight(Node* root) {
    //printf("rotating right");
    if (!(root->left->left)){ //if there is no left root but still unbalanced...
        //swap root left and root.
        Node* temp = root->left;
        root = root->left->right;
        root->left->left = temp;
        temp->right = nullptr;
    }
    if (root->left->left){// accounting for a case where there is already a right side
        Node* temp = root; //save a pointer to the current root
        root=root->left; //now change that root, shift to right
        root->right = temp; //make the left pointer of new root the old temp
        temp->left = nullptr; // now cut off the old's link to the new parent root
    }
    rebalance(root); //rebalance everything
    return root;
} // TODO

Node* rebalance(Node* root) { //has issues
    //printf("rebalancing");
    //updateHeight(root);
    //does balanceFactor have issues????
    if (balanceFactor(root) > 1){
        //printf("balance factor too big"); //test 3 bfactor too big
        if (balanceFactor(root->left) < 0){
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }
    if (balanceFactor(root) < -1){
        //printf("balance factor too small");
        if (balanceFactor(root->right) > 0){
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }

    return root;
} // TODO

Node* insertNode(Node* root, Node* newNode) {
    (void)newNode;
    if (root==nullptr){
        //printf("no root");
        root=newNode;
        return root;
    }else{ //root exists. figure out if your new node is bigger or smaller
        if (newNode->data.departure > root->data.departure){
            //printf("bigger");
            if (root->right ==nullptr){ //if it's bigger, see if right is empty to insert
                root->right=newNode;
            } else { //otherwise try again at the right root
                root->right = insertNode(root->right, newNode);
            }
        }
        else if (newNode->data.departure < root->data.departure){
            //printf("smaller");
            if (root->left ==nullptr){ //ditto on left
                root->left=newNode;
            } else { 
                root->left = insertNode(root->left, newNode);
            }
        }
        return rebalance(root);
    // printf("done "); test 3 don't worry bout this insert runs fine
    }
    return root; // TODO
}

Node* deleteNode(Node* root, int departure) {
    (void)departure;
    return root; // TODO
}

const Node* findNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    if (root==nullptr){
        return nullptr;
    }
    if (departure == root->data.departure){
        return root;
    } else if (departure > root->data.departure){
        return findNode(root->right, departure);
    } else if (departure < root->data.departure){
        return findNode(root->left, departure);
    }
    return nullptr;
     // TODO
}

const Node* earliestNode(const Node* root, int departure) {
    (void)root;
    (void)departure;
    return nullptr; // TODO
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    (void)root;
    (void)start;
    (void)end;
    (void)results;
    (void)count; // TODO
}
