#include <iostream>
using namespace std;

class KnapsackDP {
private:
    int profit[20], weight[20];
    int dp[20][50];
    int n, W;

public:
    void input() {
        cout << "Enter number of items: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "Enter weight of item "<< i + 1 << " : ";
            cin >> weight[i];
            cout<<"Enter profit of item " << i + 1 << " : ";
            cin >> profit[i];   
        }
        cout << "Enter capacity of knapsack: ";
        cin >> W;
    }

    void solve() {
        // Build DP table
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                if (i == 0 || w == 0)
                    dp[i][w] = 0;
                else if (weight[i - 1] <= w)
                    dp[i][w] = max(profit[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
                else
                    dp[i][w] = dp[i - 1][w];
            }
        }

        cout << "\n[Dynamic Programming] Maximum value = " << dp[n][W] << endl;

        // Backtrack to find items included
        int res = dp[n][W];
        int w = W;
        int totalWeight = 0;

        cout << "\nItems included in the optimal solution:\n";
        cout << "-----------------------------------------\n";
        cout << "Item\tWeight\tProfit\n";

        for (int i = n; i > 0 && res > 0; i--) {
            if (res == dp[i - 1][w])
                continue;
            else {
                cout << i << "\t" << weight[i - 1] << "\t" << profit[i - 1] << endl;
                totalWeight += weight[i - 1];
                res -= profit[i - 1];
                w -= weight[i - 1];
            }
        }

        cout << "-----------------------------------------\n";
        cout << "Total weight used = " << totalWeight << " / " << W << endl;
    }

    void displayTable() {
        cout << "\nDP Table:\n";
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= W; w++)
                cout << dp[i][w] << "\t";
            cout << endl;
        }
    }
};

int main() {
    KnapsackDP K;
    int choice;

    do {
        cout << "\n========= 0-1 Knapsack (Dynamic Programming) =========";
        cout << "\n1. Input Items";
        cout << "\n2. Solve using Dynamic Programming";
        cout << "\n3. Display DP Table";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                K.input();
                break;
            case 2:
                K.solve();
                break;
            case 3:
                K.displayTable();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
