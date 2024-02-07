#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

class BST {

private:
    struct TreeNode { //construct the tree
        int ufID;
        int height;
        int leftHeight;
        int rightHeight;
        TreeNode* left;
        TreeNode* right;
        string name;
        TreeNode() {};
        TreeNode(int _ufID, string _name) : ufID(_ufID), name(_name), left(nullptr), right(nullptr), height(1) {};
        ~TreeNode() {};
    };

    TreeNode* RotateLeft(TreeNode* node); //private functions
    TreeNode* RotateRight(TreeNode* node);
    TreeNode* RotateRightLeft(TreeNode* node);
    TreeNode* RotateLeftRight(TreeNode* node);
    int printLevelCount(TreeNode* root);
    void removeInorder(TreeNode* root, int x, bool& verify);
    void printPostorder(TreeNode* root, vector<string>& name);
    void printPreorder(TreeNode* root, vector<string>& name);
    void AddZero(TreeNode* root);
    void printInorder(TreeNode* node, vector<string>& name);
    void searchID(TreeNode* node, int ufID, bool& verify);
    void searchName(TreeNode* node, string name, bool& verify);
    int getOffset(TreeNode* node);
    void getHeight(TreeNode* node);
    TreeNode* insert(TreeNode* root, int ufID, string name);
    TreeNode* removeID(TreeNode* node, int ufID);
    TreeNode* findInorderSuccessor(TreeNode* node);
    TreeNode* root;

public:
    void searchNamePub(string name); //public helper functions
    void printLevelCountPub();
    void searchIDPub(int ufID);
    void insertPub(int ufID, string name);
    void printInorderPub();
    void printPreorderPub();
    void printPostorderPub();
    void removeInorderPub(int x);
    int InorderCounter = 0;
    void removeIDPub(int ufID);
    BST() : root(nullptr) {};
    ~BST() { delete root; }
};

void BST::getHeight(TreeNode* root){
    //No children
    if(root-> right == nullptr && root->left == nullptr){
        root->height = 1;
    }else if(root -> left == nullptr && root->right != nullptr){ //No left but right +1 
        root->height = 1 + root->right->height;
    }else if(root->right == nullptr && root->left != nullptr){ //No right but left +1
        root->height = 1 + root->left->height;
    }else if(root->left != nullptr && root-> right != nullptr){ // Left or right highest +1
        root->height = 1+ max(root->left->height, root->right->height);
    }

}

int BST::getOffset(TreeNode* root){
    if(root-> right == nullptr && root->left == nullptr || root == nullptr){ //no children balance 0
        return 0;
    }else if(root->left == nullptr && root->right != nullptr){ //right node get its height 
        return root->right->height * -1;
    }else if(root->right == nullptr && root->left != nullptr){ //left node height
        return root->left->height;
    }else {
        return (root->left->height - root->right->height); //left node minus right node
    }
}

BST::TreeNode* BST::RotateLeft(BST::TreeNode* node){ //rotate the tree left
    TreeNode* grandchild = node->right->left;
    TreeNode* ParentUpdate = node->right;
    ParentUpdate->left = node;
    node->right = grandchild;

    getHeight(node);

    return ParentUpdate;
}

BST::TreeNode* BST::RotateRight(BST::TreeNode* node){ //rotate the tree right
    TreeNode* grandchild = node->left->right;
    TreeNode* ParentUpdate = node->left;
    ParentUpdate->right = node;
    node->left = grandchild;

    getHeight(node);

    return ParentUpdate;
}

BST::TreeNode* BST::RotateLeftRight(BST::TreeNode* node){ //rotate left then right
    TreeNode* ParentUpdate = RotateRight(node->right);
    node->right = ParentUpdate;
    ParentUpdate = RotateLeft(node);

    return ParentUpdate;
}

BST::TreeNode* BST::RotateRightLeft(BST::TreeNode* node){ //rotate right then left
    TreeNode* ParentUpdate = RotateLeft(node->left);
    node->left = ParentUpdate;
    ParentUpdate = RotateRight(node);

    return ParentUpdate;
}

BST::TreeNode* BST::findInorderSuccessor(TreeNode* node){ //takes node and finds the smallest value from that branch
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}

void BST::insertPub(int ufID, string name){
    root = insert(root, ufID, name);
}

BST::TreeNode* BST::insert(TreeNode* root, int ufID, string name){

    if(root == nullptr){
        cout << "successful" <<endl;
        return new TreeNode(ufID, name);
    }else if(ufID == root->ufID){
        cout << "unsuccessful" <<endl;
        return root;
    }else if(ufID < root->ufID){
        root->left = insert(root->left, ufID, name); //finds where to place then node
    }else if(ufID > root->ufID){
        root->right = insert(root->right, ufID, name);
    }else {
        cout <<"unsuccessful" <<endl;
        return root;
    }

    getHeight(root); //get the hieght of new node
    int balance = getOffset(root); //calculate the balance of the new node

    if(balance == -2){

        if(int x = getOffset(root->right) == -1){ //if parent = -2 and child = -1 rotate left
            root = RotateLeft(root);
            getHeight(root);
        }else if(int x = getOffset(root->right) == 1){ //parent = -2 child = 1 right left rotate
            root = RotateRightLeft(root);
            getHeight(root);
        }

        /*
        if(ufID < root->right->ufID){
            root->right = RotateRight(root->right);
            root = RotateLeft(root);
            getHeight(root);
        }else{
            root = RotateLeft(root);
            getHeight(root);
        }
        */
    }
    
    if(balance == 2){

        if(int x = getOffset(root->left) == 1){ //parent = 2 child = 1 right rotate
            root = RotateRight(root);
            getHeight(root);
        }else if(int x = getOffset(root->left) == -1){ //parent = 2 child = -1 left right rotate
            root = RotateLeftRight(root);
            getHeight(root);
        }

    /*
        if(ufID > root->left->ufID){
            root->left = RotateLeft(root->left);
            root = RotateRight(root);
            getHeight(root);
        }else{
            root = RotateRight(root);
            getHeight(root);
        }
    */
    }
    return root;


} 

void BST::removeIDPub(int ufID){
    removeID(root, ufID);
}

BST::TreeNode* BST::removeID(BST::TreeNode* node, int ufID){
    if(ufID < node->ufID){
        node->left = removeID(node->left, ufID); //search for the node to remove
    }else if(ufID > node->ufID){
        node->right = removeID(node->right, ufID);
    }else{

        if(node->left == nullptr && node->right == nullptr){ //children of the node to fix | no children
            node = nullptr;
        }else if(node->left == nullptr && node->right != nullptr){ //right child
            TreeNode* temp = node->right;
            node = node->right;
        }else if(node->right == nullptr && node->left != nullptr){ //left child
            TreeNode* temp = node->left;
            node = node->left;
        }else if(node-> left != nullptr && node->right != nullptr){ //2 children
            TreeNode* temp = findInorderSuccessor(node->right);
            node->ufID = temp->ufID;
            node->name = temp->name;
            node->right = removeID(node->right, temp->ufID);
        }


    }
    return node;

}

void BST::AddZero(TreeNode* root){ //append zeroes if they are lost when stored as an integer
    string ufID = string(8 - to_string(root->ufID).size(), '0').append(to_string(root->ufID));
    cout << ufID <<endl;
}

void BST::searchName(BST::TreeNode* root, string name, bool& verify){
    bool Printed = false;
    if(root == nullptr){
        return;
    }
    if(root->name == name){
        if(to_string(root->ufID).size() != 8){ //If the zeroes are leading add them back on
            Printed = true;
            verify = true;
            AddZero(root);
        }
        if(!Printed){ //if zeroes are not leading
            cout <<root->ufID <<endl;
            verify = true;
        }
    }

    if(root->left != nullptr){ //this is where is searches for the name
        searchName(root->left, name, verify);
    }
    if(root->right != nullptr){
        searchName(root->right, name, verify);
    }
    return;

}

void BST::searchNamePub(string name){
    bool verify = false;
    searchName(root, name, verify);

    if(verify == false){
        cout <<"unsuccessful" <<endl;
    }
    
}

void BST::searchID(BST::TreeNode* root, int ufID, bool& verify){ //Search based on ID
    if(root == nullptr){
        return;
    }
    if(root->ufID == ufID){
        cout << root->name <<endl;
        verify = true;
    }
    if(root->ufID > ufID){ //If root ID value is greater than ID to search, recall moving left
        searchID(root->left, ufID, verify);
    }
    if(root->ufID < ufID){ //If root ID value is less than ID to search, recall moving right
        searchID(root->right, ufID, verify);
    }
    return;

}

void BST::searchIDPub(int ufID){
    bool verify = false;
    searchID(root, ufID, verify);
    if(verify == false){
        cout <<"unsuccessful" <<endl;
    }
}

void BST::printInorder(BST::TreeNode* root, vector<string>& name){ //prints from the left to the right of the tree in value order
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr){
        printInorder(root->left, name);
    }
    name.push_back(root->name);
    if(root->right != nullptr){
        printInorder(root->right, name);
    }
}

void BST::printInorderPub(){
    vector<string> name;
    printInorder(root, name);
    for(unsigned int i = 0; i <name.size(); i++){
        if(i != 0){
            cout <<", ";
        }
        cout << name[i];
    }
}

void BST::printPreorder(TreeNode* root, vector<string>& name){ //prints from the left, root then left then right
    if(root == nullptr){
        return;
    }
    name.push_back(root->name);

    if(root->left != nullptr){
        printPreorder(root->left, name);
    }
    if(root->right != nullptr){
        printPreorder(root->right, name);
    }

}

void BST::printPreorderPub(){
    vector<string> name;
    printPreorder(root, name);
    for(unsigned int i = 0; i < name.size(); i++){
        if(i != 0){
            cout << ", ";
        }
        cout << name[i];
    }
}

void BST::printPostorderPub(){
    vector<string> name;
    printPostorder(root, name);
    for(unsigned int i = 0; i < name.size(); i++){
        if(i != 0){
            cout << ", ";
        }
        cout << name[i];
    }
}

void BST::printPostorder(TreeNode* root, vector<string>& name){ //prints the left then the root then the right
    if(root == nullptr){
        return;
    }
    if(root->left != nullptr){
        printPostorder(root->left, name);
    }
    if(root->right != nullptr){
        printPostorder(root->right, name);
    }
    name.push_back(root->name);


}

void BST::removeInorder(BST::TreeNode* node, int x, bool& verify){ //uses the print in order except only goes for input x count, then deletes
    if(InorderCounter < x){
        if(node->left != nullptr){
            removeInorder(node->left, x, verify);
        }
        InorderCounter++;

        if(InorderCounter == x){
            verify = true;
            removeID(root, node->ufID);
        }
        if(node->right != nullptr){
            removeInorder(node->right, x, verify);
        }
    }
}

void BST::removeInorderPub(int x){
    bool verify = false;
    removeInorder(root, x + 1, verify);
    if(verify){
        cout << "successful" <<endl;
    }else {
        cout <<"unsuccessful" <<endl;
    }
    InorderCounter = 0;
}

int BST::printLevelCount(TreeNode* root){ //gets the height of input and prints
    if(root == nullptr){
        return 0;
    }
    return root ->height;
}

void BST::printLevelCountPub(){
    int levelCount = printLevelCount(root);
    cout << levelCount <<endl;
}
