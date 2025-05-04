#include <iostream>
#include <vector>
using namespace std;

bool found = false;

void SumOfSubset(const vector<int>& arr, int size, int index, vector<int>& subset, int currentSum, int target) {
    if (currentSum == target) {
        cout << "{ ";
        for (int i = 0; i < size; i++) {
            if (subset[i] != 0) {
                cout << subset[i] << " ";
            }
        }
        cout << "}" << endl;
        found = true;
        return;
    }

    if (currentSum > target || index >= size) {
        return;
    }

    subset[index] = arr[index];
    SumOfSubset(arr, size, index + 1, subset, currentSum + arr[index], target);

    subset[index] = 0;
    SumOfSubset(arr, size, index + 1, subset, currentSum, target);
}

int main() {
    int size, target;
    cout << "Enter Target Sum: ";
    cin >> target;
    cout << "Enter Size of array: ";
    cin >> size;

    vector<int> arr(size);
    vector<int> subset(size, 0);

    cout << "Enter elements:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Subsets with sum " << target << ":" << endl;
    SumOfSubset(arr, size, 0, subset, 0, target);

    if (!found) {
        cout << "No subsets found." << endl;
    }

    return 0;
}
