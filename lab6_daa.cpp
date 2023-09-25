#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;

    Item(int id, double profit, double weight) : item_id(id), item_profit(profit), item_weight(weight) {
        profit_weight_ratio = profit / weight;
    }
};

bool compare(Item item1, Item item2) {
    return item1.profit_weight_ratio > item2.profit_weight_ratio;
}

double fractionalKnapsack(vector<Item>& items, double capacity) {
    sort(items.begin(), items.end(), compare);

    double maxProfit = 0.0;

    for (int i = 0; i < items.size(); i++) {
        if (capacity == 0) {
            break;
        }

        if (items[i].item_weight <= capacity) {
            maxProfit += items[i].item_profit;
            capacity -= items[i].item_weight;
        } else {
            double fraction = capacity / items[i].item_weight;
            maxProfit += items[i].item_profit * fraction;
            capacity = 0;
        }
    }

    return maxProfit;
}

int main() {
    vector<Item> items = {
        {1, 120, 30},
        {2, 100, 20},
        {3, 60, 10}
    };
    double knapsackCapacity = 50.0;

    double maxProfit = fractionalKnapsack(items, knapsackCapacity);

    cout << "Maximum profit: " << maxProfit << endl;

    return 0;
}
