#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = right = NULL;
    }
};

class ExpressionTree {
public:
    Node* root;

    ExpressionTree() { root = NULL; }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    // Build tree from prefix
    void build(string pre) {
        stack<Node*> st;
        for (int i = pre.size() - 1; i >= 0; i--) {
            char c = pre[i];
            if (isalnum(c))
                st.push(new Node(c));
            else if (isOperator(c)) {
                Node* node = new Node(c);
                node->left = st.top(); st.pop();
                node->right = st.top(); st.pop();
                st.push(node);
            }
        }
        root = st.top();
        cout << "Tree built successfully!\n";
    }

    // Recursive traversals
    void inorder(Node* r) {
        if (!r) return;
        inorder(r->left);
        cout << r->data;
        inorder(r->right);
    }

    void preorder(Node* r) {
        if (!r) return;
        cout << r->data;
        preorder(r->left);
        preorder(r->right);
    }

    void postorder(Node* r) {
        if (!r) return;
        postorder(r->left);
        postorder(r->right);
        cout << r->data;
    }

    // Non-recursive traversals
    void inorderNR(Node* r) {
        stack<Node*> st;
        Node* temp = r;
        while (temp || !st.empty()) {
            while (temp) {
                 st.push(temp); 
                 temp = temp->left; 
            }
            temp = st.top(); st.pop();
            cout << temp->data;
            temp = temp->right;
        }
    }

    void preorderNR(Node* r) {
        if (!r) return;
        stack<Node*> st;
        st.push(r);
        while (!st.empty()) {
            Node* node = st.top(); st.pop();
            cout << node->data;
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
    }

    void postorderNR(Node* r) {
        if (!r) return;
        stack<Node*> s1, s2;
        s1.push(r);
        while (!s1.empty()) {
            Node* node = s1.top(); s1.pop();
            s2.push(node);
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }
        while (!s2.empty()) { cout << s2.top()->data; s2.pop(); }
    }

    // Count leaf nodes
    int countLeaf(Node* r) {
        if (!r) return 0;
        if (!r->left && !r->right) return 1;
        return countLeaf(r->left) + countLeaf(r->right);
    }

    // Count internal nodes
    int countInternal(Node* r) {
        if (!r || (!r->left && !r->right)) return 0;
        return 1 + countInternal(r->left) + countInternal(r->right);
    }

    // Count operators
    int countOperators(Node* r) {
        if (!r) return 0;
        int c = isOperator(r->data) ? 1 : 0;
        return c + countOperators(r->left) + countOperators(r->right);
    }

    // Height of tree
    int height(Node* r) {
        if (!r) return 0;
        int lh = height(r->left);
        int rh = height(r->right);
        return 1 + max(lh,rh);
    }

    // Mirror tree
    Node* mirror(Node* r) {
        if (!r) return NULL;
        Node* m = new Node(r->data);
        m->left = mirror(r->right);
        m->right = mirror(r->left);
        return m;
    }
};

// ------------------ MAIN FUNCTION ------------------
int main() {
    ExpressionTree t;
    int choice;
    string pre;

    do {
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Build Tree\n";
        cout << "2. Inorder (Rec)\n";
        cout << "3. Preorder (Rec)\n";
        cout << "4. Postorder (Rec)\n";
        cout << "5. Inorder (Non-Rec)\n";
        cout << "6. Preorder (Non-Rec)\n";
        cout << "7. Postorder (Non-Rec)\n";
        cout << "8. Count Leaf Nodes\n";
        cout << "9. Count Internal Nodes\n";
        cout << "10. Count Operators\n";
        cout << "11. Height\n";
        cout << "12. Mirror Tree (Inorder)\n";
        cout << "13. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Prefix Expression: ";
                cin >> pre;
                t.build(pre);
                break;
            case 2:
                if(t.root) { cout << "Inorder: "; t.inorder(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 3:
                if(t.root) { cout << "Preorder: "; t.preorder(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 4:
                if(t.root) { cout << "Postorder: "; t.postorder(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 5:
                if(t.root) { cout << "Inorder (Non-Rec): "; t.inorderNR(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 6:
                if(t.root) { cout << "Preorder (Non-Rec): "; t.preorderNR(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 7:
                if(t.root) { cout << "Postorder (Non-Rec): "; t.postorderNR(t.root); cout << endl; }
                else cout << "Build tree first!\n";
                break;
            case 8:
                if(t.root) cout << "Leaf Nodes: " << t.countLeaf(t.root) << endl;
                else cout << "Build tree first!\n";
                break;
            case 9:
                if(t.root) cout << "Internal Nodes: " << t.countInternal(t.root) << endl;
                else cout << "Build tree first!\n";
                break;
            case 10:
                if(t.root) cout << "Operators: " << t.countOperators(t.root) << endl;
                else cout << "Build tree first!\n";
                break;
            case 11:
                if(t.root) cout << "Height: " << t.height(t.root) << endl;
                else cout << "Build tree first!\n";
                break;
            case 12:
                if(t.root) {
                    cout << "Mirror Tree (Inorder): ";
                    t.inorder(t.mirror(t.root));
                    cout << endl;
                } else cout << "Build tree first!\n";
                break;
            case 13:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while(choice != 13);

    return 0;
}
