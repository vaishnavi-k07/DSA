#include <iostream>
#include <stack>
using namespace std;

// Node structure
class Node {
public:
    int data;
    Node *left, *right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Binary Search Tree class
class BST {
public:
    Node* root;
    BST() { root = NULL; }

    // ---------- Insert Node ----------
    void insert() {
        int value;
        cout << "Enter value to insert: ";
        cin >> value;

        Node* newNode = new Node(value);
        if (root == NULL) {
            root = newNode;
            cout << "Root node inserted.\n";
            return;
        }

        Node* curr = root;
        Node* parent = NULL;

        while (curr != NULL) {
            parent = curr;
            if (value < curr->data)
                curr = curr->left;
            else if (value > curr->data)
                curr = curr->right;
            else {
                cout << "Duplicate value! Skipping insert.\n";
                delete newNode;
                return;
            }
        }

        if (value < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        cout << "Node inserted successfully.\n";
    }

    // ---------- Iterative Traversals ----------
    void inorder() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        stack<Node*> s;
        Node* temp = root;
        cout << "Inorder: ";
        while (temp || !s.empty()) {
            while (temp) {
                s.push(temp);
                temp = temp->left;
            }
            temp = s.top(); s.pop();
            cout << temp->data << " ";
            temp = temp->right;
        }
        cout << endl;
    }

    void preorder() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        stack<Node*> s;
        s.push(root);
        cout << "Preorder: ";
        while (!s.empty()) {
            Node* temp = s.top(); s.pop();
            cout << temp->data << " ";
            if (temp->right) s.push(temp->right);
            if (temp->left) s.push(temp->left);
        }
        cout << endl;
    }

    void postorder() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        stack<Node*> s1, s2;
        s1.push(root);
        cout << "Postorder: ";
        while (!s1.empty()) {
            Node* temp = s1.top(); s1.pop();
            s2.push(temp);
            if (temp->left) s1.push(temp->left);
            if (temp->right) s1.push(temp->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    // ---------- Recursive Traversals ----------
    void inorderRec(Node* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    void preorderRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    void postorderRec(Node* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    // ---------- Search Functions ----------
    void search() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        int num;
        cout << "Enter value to search: ";
        cin >> num;

        Node* temp = root;
        while (temp) {
            if (temp->data == num) {
                cout << num << " is present in the tree.\n";
                return;
            }
            temp = (num < temp->data) ? temp->left : temp->right;
        }
        cout << num << " is not present in the tree.\n";
    }

    void searchRec(Node* node, int num) {
        if (!node) {
            cout << num << " is not present in the tree.\n";
            return;
        }
        if (node->data == num) {
            cout << num << " is present in the tree.\n";
            return;
        }
        if (num < node->data)
            searchRec(node->left, num);
        else
            searchRec(node->right, num);
    }

    // ---------- Ascending & Descending ----------
    void ascending() {
        cout << "Ascending order: ";
        inorderRec(root);
        cout << endl;
    }

    void descending() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        stack<Node*> s;
        Node* temp = root;
        cout << "Descending order: ";
        while (temp || !s.empty()) {
            while (temp) {
                s.push(temp);
                temp = temp->right;
            }
            temp = s.top(); s.pop();
            cout << temp->data << " ";
            temp = temp->left;
        }
        cout << endl;
    }

    // ---------- Single Function for Height ----------
    int height(Node* node) {
        if (node == NULL)
            return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    // ---------- Find Minimum ----------
    void findMin() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        Node* temp = root;
        while (temp->left != NULL)
            temp = temp->left;
        cout << "Minimum value in tree: " << temp->data << endl;
    }

    // ---------- Find Maximum ----------
    void findMax() {
        if (!root) { cout << "Tree is empty!\n"; return; }
        Node* temp = root;
        while (temp->right != NULL)
            temp = temp->right;
        cout << "Maximum value in tree: " << temp->data << endl;
    }
};

// ---------- Main Function ----------
int main() {
    BST B;
    int ch = 1, num;

    while (ch != 0) {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. Insert Node\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n";
        cout << "5. Recursive Inorder\n6. Recursive Preorder\n7. Recursive Postorder\n";
        cout << "8. Search (Iterative)\n9. Search (Recursive)\n10. Ascending Order\n11. Descending Order\n";
        cout << "12. Height of Tree\n13. Find Minimum\n14. Find Maximum\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1: B.insert(); break;
        case 2: B.inorder(); break;
        case 3: B.preorder(); break;
        case 4: B.postorder(); break;
        case 5: cout << "Inorder: "; B.inorderRec(B.root); cout << endl; break;
        case 6: cout << "Preorder: "; B.preorderRec(B.root); cout << endl; break;
        case 7: cout << "Postorder: "; B.postorderRec(B.root); cout << endl; break;
        case 8: B.search(); break;
        case 9: cout << "Enter value to search: "; cin >> num; B.searchRec(B.root, num); break;
        case 10: B.ascending(); break;
        case 11: B.descending(); break;
        case 12: cout << "Height of tree: " << B.height(B.root) << endl; break;
        case 13: B.findMin(); break;
        case 14: B.findMax(); break;
        case 0: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
