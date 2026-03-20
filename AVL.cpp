#include <iostream>
#include <string>
#include<stack>
using namespace std;

struct Node {
    int id;
    string name;
    Node *left, *right;
    int height;
    Node(int i, string n) {
        id = i;
        name = n;
        left = right = NULL;
        height = 1;
    }
};

int height(Node *n) {
    return (n == NULL) ? 0 : n->height;
}

int getBalance(Node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *t = x->right;
    x->right = y;
    y->left = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *t = y->left;
    y->left = x;
    x->right = t;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node *root, int id, string name) {
    if (root == NULL)
        return new Node(id, name);

    if (id < root->id)
        root->left = insert(root->left, id, name);
    else if (id > root->id)
        root->right = insert(root->right, id, name);
    else {
        cout << "ID already exists\n";
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);

    if (bal > 1 && id < root->left->id)
        return rotateRight(root);
    if (bal < -1 && id > root->right->id)
        return rotateLeft(root);
    if (bal > 1 && id > root->left->id) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bal < -1 && id < root->right->id) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* minValue(Node *p) {
    while (p->left != NULL)
        p = p->left;
    return p;
}

Node* deleteNode(Node *root, int id) {
    if (root == NULL)
        return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                delete root;
                root = NULL;
            } else {
                *root = *temp;
                delete temp;
            }
        } else {
            Node *temp = minValue(root->right);
            root->id = temp->id;
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int bal = getBalance(root);

    if (bal > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (bal > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bal < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (bal < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Non-recursive search
void search(Node *root, int id) {
    int cmp = 0;
    while (root != NULL) {
        cmp++;
        if (id == root->id) {
            cout << "Found: " << root->name << endl;
            cout << "Comparisons: " << cmp << endl;
            return;
        }
        if (id < root->id)
            root = root->left;
        else
            root = root->right;
    }
    cout << "Employee not found\n";
    cout << "Comparisons: " << cmp << endl;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->id << " - " << root->name << endl;
        inorder(root->right);
    }
}
void inorderNR(Node *root){
    if(!root){
        cout<<"Tree is empty";
        return;
    }
    stack<Node*> s;
    Node *temp=root;
    cout<<"Inorder:\n";
    while(temp || !s.empty()){
        while(temp){
            s.push(temp);
            temp=temp->left;
        }
        temp=s.top(); s.pop();
        cout<<temp->id<<" - "<<temp->name<<endl;
        temp=temp->right;
    }
}
void reverseOrder(Node *root) {
    if (root != NULL) {
        reverseOrder(root->right);
        cout << root->id << " - " << root->name << endl;
        reverseOrder(root->left);
    }
}

int main() {
    Node *root = NULL;
    int ch, id;
    string name;

    while (true) {
        cout << "\n--- Employee Directory (AVL Tree) ---\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display Ascending Order\n";
        cout << "5. Display Descending Order\n";
        cout << "6. Display Height\n";
        cout << "7. Maximum Comparisons\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter ID and Name: ";
                cin >> id >> name;
                root = insert(root, id, name);
                break;

            case 2:
                cout << "Enter ID: ";
                cin >> id;
                search(root, id);
                break;

            case 3:
                cout << "Enter ID to Delete: ";
                cin >> id;
                root = deleteNode(root, id);
                cout << "Deleted if exists\n";
                break;

            case 4:
                cout << "\nAscending Order:\n";
                inorder(root);
                cout<<endl;
                inorderNR(root);
                break;

            case 5:
                cout << "\nDescending Order:\n";
                reverseOrder(root);
                break;

            case 6:
                cout << "Height of Tree: " << height(root) << endl;
                break;

            case 7:
                cout << "Maximum Comparisons: " << height(root) << endl;
                break;

            case 8:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }
}
