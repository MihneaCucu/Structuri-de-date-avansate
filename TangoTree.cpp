#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;

enum Color { RED, BLACK };

struct Node
{
    int key;
    Node* left, *right, *parent;
    Color color;
    Node(int key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class AuxiliaryTree
{
public:
    Node* root;
    AuxiliaryTree()
    {
        root = nullptr;
    }
    
    void insert (int key)
    {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;
        
        while (x != nullptr)
        {
            y = x;
            if(z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        
        z->parent = y;
        if(y == nullptr)
        {
            root = z;
        }
        else
            if(z->key < y->key)
            {
                y->left = z;
            }
            else
            {
                y->right = z;
            }
        
        z->color = RED;
        insertFixup(z);
    }
    
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
    }
    
    void insertFixup(Node* z) {
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;    }
    
    void remove(Node* z) {
        Node* x, *y;
        if (z->left == nullptr || z->right == nullptr) {
            y = z;
        } else {
            y = successor(z);
        }

        if (y->left != nullptr) {
            x = y->left;
        } else {
            x = y->right;
        }

        if (x != nullptr) {
            x->parent = y->parent;
        }

        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        if (y != z) {
            z->key = y->key;
        }

        if (y->color == BLACK) {
            removeFixup(x);
        }
        
        delete y;
    }

    Node* successor(Node* x) {
        if (x->right != nullptr) {
            return minimum(x->right);
        }

        Node* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node* minimum(Node* x) {
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }

    void removeFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
    Node* search (int key)
    {
        Node* x = root;
        
        while(x != nullptr && key != x->key)
        {
            if(key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        
        return x;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }
};

class TangoTree
{
private:
    vector<AuxiliaryTree*> preferredPaths;

public:
    TangoTree()
    {
        
    }
    
    void updatePaths(Node* node) {
        for (size_t i = 1; i < preferredPaths.size(); ++i) {
            if (node != nullptr) {
                if (node->left != nullptr) {
                    node = node->left;
                } else {
                    node = node->right;
                }
            }
            if (node != nullptr) {
                preferredPaths[i]->insert(node->key);
                node = node->parent;
            }
        }
    }
    
    void insert(int key) {
        Node* newNode = new Node(key);
        if (preferredPaths.empty()) {
            preferredPaths.push_back(new AuxiliaryTree());
            preferredPaths[0]->root = newNode;
        } else {
            Node* currentNode = preferredPaths[0]->root;
            Node* parent = nullptr;
            while (currentNode != nullptr) {
                parent = currentNode;
                if (key < currentNode->key) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }
            newNode->parent = parent;
            if (parent == nullptr) {
                preferredPaths[0]->root = newNode;
            } else if (key < parent->key) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
        updatePaths(newNode);
    }
    
    void remove(int key) {
        for (size_t i = 0; i < preferredPaths.size(); ++i) {
            Node* nodeToRemove = preferredPaths[i]->search(key);
            if (nodeToRemove != nullptr) {
                preferredPaths[i]->remove(nodeToRemove);
                updatePaths(preferredPaths[i]->root);
                return;
            }
        }
    }
    
    int getMinimum() {
        if (preferredPaths.empty()) {
            return INT_MAX;
        }

        int minimum = INT_MAX;
        for (size_t i = 0; i < preferredPaths.size(); ++i) {
            Node* node = preferredPaths[i]->root;
            if (node != nullptr) {
                while (node->left != nullptr) {
                    node = node->left;
                }
                if (node->key < minimum) {
                    minimum = node->key;
                }
            }
        }
        return minimum;
    }

    int getMaximum() {
        if (preferredPaths.empty()) {
            return INT_MIN;
        }

        int maximum = INT_MIN;
        for (size_t i = 0; i < preferredPaths.size(); ++i) {
            Node* node = preferredPaths[i]->root;
            if (node != nullptr) {
                while (node->right != nullptr) {
                    node = node->right;
                }
                if (node->key > maximum) {
                    maximum = node->key;
                }
            }
        }
        return maximum;
    }
    
    Node* search (int key)
    {
        for(auto &tree:preferredPaths)
        {
            Node* result = tree->search(key);
            if(result != nullptr)
                return result;
        }
        
        return nullptr;
    }
    
    vector<AuxiliaryTree*>& getPreferredPaths() 
    {
        return preferredPaths;
    }
};

int main() 
{
    
    
    
    ifstream fin("inserari_crescatoare_1mil.txt");
    
    TangoTree tangoTree;
        int k;
        fin >> k;

        
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; ++i)
        {
            string operation;
            fin >> operation;

            if (operation == "INSERT") 
            {
                int value;
                fin >> value;
                tangoTree.insert(value);
            } 
            
            else if (operation == "SEARCH")
            {
                int value;
                fin >> value;
                Node* result = tangoTree.search(value);
            }

            else if (operation == "DELETE")
            {
                int value;
                fin >> value;
                tangoTree.remove(value);
            } 
            
            else if (operation == "MINIM")
            {
                int minimum = tangoTree.getMinimum();
            } 
            
            else if (operation == "MAXIM")
            {
                int maximum = tangoTree.getMaximum();
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " ms" << std::endl;
    
    vector<AuxiliaryTree*>& paths = tangoTree.getPreferredPaths();
    
    return 0;
}

