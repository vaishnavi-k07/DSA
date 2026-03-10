#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

struct Node {
    int dest, length;
    Node* next;
};

class RoadMap {
    string inter[MAX];
    int n;
    int matrix[MAX][MAX];
    Node* list[MAX];

public:

    RoadMap() {
        n = 0;
        for (int i = 0; i < MAX; i++) {
            list[i] = NULL;
            for (int j = 0; j < MAX; j++)
                matrix[i][j] = 0;
        }
    }

    void addIntersections() {
        cout << "Enter number of intersections: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Intersection " << i << ": ";
            cin >> inter[i];
        }
    }

    int findInter(string name) {
        for (int i = 0; i < n; i++)
            if (inter[i] == name) return i;
        return -1;
    }

    void addRoad(bool useMatrix) {
        string A, B;
        int len;
        cout << "From intersection: ";  cin >> A;
        cout << "To intersection: ";    cin >> B;
        cout << "Length (km/min): ";    cin >> len;

        int u = findInter(A);
        int v = findInter(B);

        if (u == -1 || v == -1) {
            cout << "Intersection not found!\n";
            return;
        }

        if (useMatrix)
            matrix[u][v] = len;
        else {
            Node* newNode = new Node;
            newNode->dest = v;
            newNode->length = len;
            newNode->next = list[u];
            list[u] = newNode;
        }

        cout << "Road added.\n";
    }

    void showMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    void showList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < n; i++) {
            cout << inter[i] << " -> ";
            Node* temp = list[i];
            while (temp) {
                cout << inter[temp->dest] << "(" << temp->length << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void checkRoad(bool useMatrix) {
        string A, B;
        cout << "Enter starting intersection: ";
        cin >> A;
        cout << "Enter ending intersection: ";
        cin >> B;

        int u = findInter(A);
        int v = findInter(B);

        if (u == -1 || v == -1) {
            cout << "Intersection not found.\n";
            return;
        }

        // MATRIX MODE
        if (useMatrix) {
            if (matrix[u][v] != 0) {
                cout << "Direct road found: " << inter[u] << " -> "
                     << inter[v] << " | Length: " << matrix[u][v] << endl;
                return;
            }
            cout << "No direct road found.\n";
        }

        // LIST MODE
        else {
            Node* temp = list[u];
            while (temp) {
                if (temp->dest == v) {
                    cout << "Direct road found: " << inter[u] << " -> "
                         << inter[v] << " | Length: " << temp->length << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "No direct road found.\n";
        }
    }
};

// ---------------- MAIN ----------------

int main() {
    RoadMap r;
    int mode, ch;

    cout << "1. Adjacency Matrix\n2. Adjacency List\nEnter mode: ";
    cin >> mode;
    bool useMatrix = (mode == 1);

    do {
        cout << "\n1. Add Intersections\n2. Add Road\n3. Display Map\n4. Check Road\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: r.addIntersections(); break;
            case 2: r.addRoad(useMatrix); break;
            case 3: useMatrix ? r.showMatrix() : r.showList(); break;
            case 4: r.checkRoad(useMatrix); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (ch != 5);

    return 0;
}
