#include <iostream>
using namespace std;

class FractionalKnapsack {
    int n, capacity;
    int weight[20], profit[20];
    float ratio[20];

public:
    void input() {
        cout << "Enter number of items: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter weight of item " << i + 1 << ": ";
            cin >> weight[i];
            cout << "Enter profit of item " << i + 1 << ": ";
            cin >> profit[i];
            ratio[i] = (float)profit[i] / weight[i];
        }
        cout << "Enter knapsack capacity: ";
        cin >> capacity;
    }

    void display() {
        cout << "\nItem\tWeight\tProfit\tRatio\n";
        for (int i = 0; i < n; i++)
            cout << i + 1 << "\t" << weight[i] << "\t" << profit[i] << "\t" << ratio[i] << endl;
    }

    void sortItems() {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (ratio[i] < ratio[j]) {
                    swap(ratio[i], ratio[j]);
                    swap(weight[i], weight[j]);
                    swap(profit[i], profit[j]);
                }
            }
        }
        cout << "\nItems sorted by profit/weight ratio.\n";
    }

    void compute() {
        float totalProfit = 0;
        int currWeight = 0;
        cout << "\nItem\tWeightTaken\tProfitTaken\n";
        for (int i = 0; i < n; i++) {
            if (currWeight >= capacity) break;
            if (currWeight + weight[i] <= capacity) {
                currWeight += weight[i];
                totalProfit += profit[i];
                cout << i + 1 << "\t" << weight[i] << "\t\t" << profit[i] << endl;
            } else {
                int remain = capacity - currWeight;
                if (remain > 0) {
                    float profitTaken = ratio[i] * remain;
                    totalProfit += profitTaken;
                    currWeight += remain;              
                    cout << i + 1 << "\t" << remain << "\t\t" << profitTaken << " (fraction)" << endl;
                }
                break; // knapsack full (or no remaining capacity)
            }
        }
        cout << "\nTotal Weight Used = " << currWeight << " / " << capacity << endl;
        cout << "Maximum Profit (Total) = " << totalProfit << endl;
    }
};

int main() {
    FractionalKnapsack fk;
    int ch;
    do {
        cout << "\n--- Fractional Knapsack Menu ---";
        cout << "\n1. Input Items";
        cout << "\n2. Display Items";
        cout << "\n3. Sort Items";
        cout << "\n4. Compute Maximum Profit";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1: fk.input(); break;
        case 2: fk.display(); break;
        case 3: fk.sortItems(); break;
        case 4: fk.compute(); break;
        case 5: cout << "\nExiting..."; break;
        default: cout << "\nInvalid choice!";
        }
    } while (ch != 5);
    return 0;
}
