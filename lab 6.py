class Item:
    def __init__(self, item_id, item_profit, item_weight):
        self.item_id = item_id
        self.item_profit = item_profit
        self.item_weight = item_weight
        self.profit_weight_ratio = item_profit / item_weight

def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio:
        largest = left

    if right < n and arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def build_max_heap(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

def fractional_knapsack(items, capacity):
    n = len(items)
    build_max_heap(items)
    max_profit = 0

    for i in range(n):
        if capacity == 0:
            break

        if items[i].item_weight <= capacity:
            max_profit += items[i].item_profit
            capacity -= items[i].item_weight
        else:
            fraction = capacity / items[i].item_weight
            max_profit += items[i].item_profit * fraction
            capacity = 0

    return max_profit

# Example usage:
if __name__ == "__main__":
    items = [
        Item(1, 120, 30),
        Item(2, 100, 20),
        Item(3, 60, 10),
    ]
    knapsack_capacity = 50
    max_profit = fractional_knapsack(items, knapsack_capacity)
    print("Maximum profit:", max_profit)
