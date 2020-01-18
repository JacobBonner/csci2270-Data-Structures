#include <iostream>
using namespace std;


class TreeTraversal
{
    private:
        Node* root;

    public:
        TreeTraversal();
        void inOrderTreeTraversal();
        void insertNodeBST(int key);
        void printTree();
};