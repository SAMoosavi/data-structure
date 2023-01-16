//IN THE NAME OF ALLAH
//AMIR MOHAMMAD ASKARIEH && SEYED ALI MOOSAVI


#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    int ertefa;
    Node* right;
    Node* left;
};

class Avl_tree{
private:
    int size = 0;
public:
    bool search(Node* node, int data){
        if(node == nullptr)return false;
        if(data < node->data){
            return search(node->left, data);
        }
        else if(data > node->data){
            return search(node->right, data);
        }
        else{ // data == node->data
            return true;
        }
    }
    int ert(Node* node){
        if(node == nullptr)return 0;
        else return node->ertefa;
    }
    Node* small(Node* node){
        if(node == nullptr)return nullptr;
        Node* p = node;
        while(true){
            if(p->left == nullptr)return p;
            p = p->left;
        }
    }
    Node* Right(Node* node){
        Node* left = node->left;
        Node* left_right = left->right;
        left->right = node;
        node->left = left_right;
        node->ertefa = 1 + max(ert(node->left), ert(node->right));
        left->ertefa = 1 + max(ert(left->left), ert(left->right));
        return left;
    }

    Node* Left(Node* node){
        Node* right = node->right;
        Node* right_left = right->left;
        right->left = node;
        node->right = right_left;
        node->ertefa = 1 + max(ert(node->left), ert(node->right));
        right->ertefa = 1 + max(ert(right->left), ert(right->right));
        return right;
    }

    Node* insert(Node* node, int data){
        size ++;
        Node* my_node = new Node;
        my_node->data = data;
        my_node->ertefa = 1;
        if(node == nullptr){
            return my_node;
        }
        if(node->data > data){
            node->left = insert(node->left, data);
        }
        else{
            node->right = insert(node->right , data);
        }

        node->ertefa  = 1 + max(ert(node->left), ert(node->right));
        int diff_right_left = ert(node->left)- ert(node->right);
        if(abs(diff_right_left) <= 1){
            return node;
        }

        if(diff_right_left < -1 && node->left->data < data){
            return Left(node);
        }

        else if(diff_right_left > 1 && node->left->data > data){
            return Right(node);
        }

        else if(diff_right_left < -1 && node->left->data > data){
            node->right = Right(node->right);
            return Left(node);
        }

        else if(diff_right_left > 1 && node->left->data < data){
            node->left = Left(node->left);
            return Right(node);
        }
    }

    Node* erase(Node* node, int data){
        if(node == nullptr) return nullptr;
        if(node->data < data){
            node->right = erase(node->right, data);
        } 
        else if(node->data > data){
            node->left = erase(node->left, data);
        }
        else{
            if(node->left == nullptr || node->right == nullptr){
                if(node->left == nullptr && node->right != nullptr){
                    *node = *node->right;//?
                }
                else if(node->left != nullptr && node->right == nullptr){
                    *node = *node->left;//?
                }
                else{
                    node = nullptr;
                }
            }
            else{
                Node* asd = small(node->right);
                node->data = asd->data;
                node->right = erase(node->right, asd->data);
            }
        }
        size --;
        if(size == 0)return nullptr; // !size -> size == 0
        node->ertefa = max(ert(node->left), ert(node->right)) + 1;
        int diff_right_left = ert(node->left)- ert(node->right);
        if(abs(diff_right_left) <= 1) return node;
        if(diff_right_left > 1 && ert(node->left->left) - ert(node->left->left) >= 0){
            return Right(node);
        }
        if(diff_right_left > 1 && ert(node->left->left) - ert(node->left->left) < 0){
            node->left = Left(node->left);
            return Right(node);
        }
        if(diff_right_left < -1 && ert(node->right->left) - ert(node->right->left) <= 0){
            return Left(node);
        }
        if(diff_right_left < -1 && ert(node->right->left) - ert(node->right->left) > 0){
            node->right = Right(node->right);
            return Left(node);
        }
    }
};
int main(){

}
