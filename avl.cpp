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
} // DONE
// Set height to 1 + max(child heights). Node is non-null; child heights are correct.

int balanceFactor(const Node* node) {
    (void)node;
    if (node==nullptr){
        return 0;
    }
    //printf("oh no");
    return nodeHeight(node->left)-nodeHeight(node->right);
} // DONE// Return left height minus right height, or 0 for nullptr.


Node* rotateLeft(Node* root) {
    Node* temp = root;
    Node* temp2 = root->right->left;
    root = root->right;
    root->left = temp;
    temp->right = temp2;
    updateHeight(temp);
    updateHeight(temp2);
    updateHeight(root);
    return root;
} // DONE

Node* rotateRight(Node* root) {
    Node* temp = root;
    Node* temp2 = root->left->right;
    root = root->left;
    root->right = temp;
    temp->left = temp2;
    updateHeight(temp);
    updateHeight(temp2);
    updateHeight(root);
    return root;
}
//DONE

Node* rebalance(Node* root) { //has issues
    //printf("rebalancing");
    updateHeight(root);
    //does balanceFactor have issues????
    if (balanceFactor(root) > 1){
        //printf("balance factor too big"); 
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
} // DONE

Node* insertNode(Node* root, Node* newNode) {
    (void)newNode;
    //printf("inserting");
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
        updateHeight(root);
        return rebalance(root);
    // printf("done "); test 3 don't worry bout this insert runs fine
    }
     // DONE
}

Node* deleteNode(Node* root, int departure) {
    (void)departure;
    if (root == nullptr){
        return nullptr;
    }
    //find node now
    if (root->data.departure == departure){
        //delete now
        if ((root->left==nullptr) || (root->right==nullptr)){
            Node* successor = nullptr; //1 or 0 children
            if (root->left){
                successor = root->left;
            } else if (root->right){
            successor = root->right;
            }
        delete root;
        return successor;
        }// 2 children
        Node* min = root->right; //find the min to replace the key
        while(min->left != nullptr){
            min = min->left;
        }
        root->data = min->data;
        root->right = deleteNode(root->right, min->data.departure);

    } else if (root->data.departure < departure){
        root->right = deleteNode(root->right, departure); //it's bigger
    } else if (root->data.departure > departure) {
        root->left = deleteNode(root->left, departure); //it's smaller
    }
    return rebalance(root);
// TODO
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
     // DONE
}

const Node* earliestNode(const Node* root, int departure) {
    (void)root;
    (void)departure; //at or after...
    if (departure == root->data.departure){ //this is AT (base case)
        return root; 
    } 
    std::queue<Node*> paragon;
    if (departure > root->data.departure) { //queue time?/???
        //look thru root->right
        Node* earliest = nullptr; //nothing is closest and after the time so far
        paragon.push(root->right); 
        while (paragon.size() > 0){ //this loop looks thru all nodes for a time closest
            Node* current = paragon.front();
            paragon.pop();
            if (current->left){
                paragon.push(current->left);
            }
            if (current->right){
                paragon.push(current->right);
            } //added its children to the queue here
            //now comparison time.
            if (current->data.departure >= departure){ //if we find a value AFTER departure:
                if(earliest==nullptr){
                    earliest = current;
                }else if (earliest->data.departure > current->data.departure){ 
                    earliest = current; //if current is smaller than current earliest
                }// then it's closer to departure so. earlier.
            } 
        }// loop done when there are no more values to check thru.
        return earliest;
        
    } else if (departure < root->data.departure){ //if departure is earlier than the root...
//look thru root->right
        Node* earliest = nullptr; //should be root if empyt at end
        paragon.push(root->left); 
        while (paragon.size() > 0){ //this loop looks thru all nodes for a time closest
            Node* current = paragon.front();
            paragon.pop();
            if (current->left){
                paragon.push(current->left);
            }
            if (current->right){
                paragon.push(current->right);
            } //added its children to the queue here
            //now comparison time.
            if (current->data.departure >= departure){ //if we find a value AFTER departure:
                if(earliest==nullptr){
                    earliest = current;
                }else if (earliest->data.departure > current->data.departure){ 
                    earliest = current; //if current is smaller than current earliest
                }// then it's closer to departure so. earlier.
            } 
        }// loop done when there are no more values to check thru.     
        if (earliest == nullptr){
            return root;
        }   else {
            return earliest;
        }
    }
    return nullptr; // DONE
}

void findRange(const Node* root, int start, int end,
               const Node* results[], int& count) {
    (void)root;
    (void)start;
    (void)end;
    (void)results;
    (void)count; //use an in-order search, l, node, r
    if (root == nullptr){
        return;
    }
    findRange(root->left, start, end, results, count);
    if ((root->data.departure >= start) && (root->data.departure <= end)){
        results[count] = root;
        count++;
    }
    findRange(root->right, start, end, results, count);
}
    

    //left tree call
    //center node call
    //right tree call mabye append is PART of the call? and counter at the end

    //root = earliestNode(root, start);
    // TODO
// Collect node pointers with departure in [start, end], in time order, and update count.
// If start > end, add nothing; if start == end, collect only an exact match.
