#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <utility>

using namespace std;

mt19937 rnd(time(NULL));
int randInt(int l, int r)
{
    uniform_int_distribution<int>dist(l, r);
    return dist(rnd);
}

pair<int, int>partition_random(vector<int>& a, int l, int r)
{
    int pos = randInt(l, r - 1);
    int pivot = a[pos];
    int x = l, y = l;
    for (int i = l; i < r; i++)
    {
        if (a[i] <= pivot)
        {
            swap(a[i], a[y]);
            if (a[y] < pivot)
            {
                swap(a[y], a[x]);
                x++;
            }
            y++;
        }
    }
    return make_pair(x, y);
}

void quickSort_random(vector<int> &a, int l, int r)
{
    if ((r - l) < 2)
        return;
    pair<int, int> p = partition_random(a, l, r);
    quickSort_random(a, l, p.first);
    quickSort_random(a, p.second, r);
}


int partition_Lomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort_Lomuto(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_Lomuto(arr, low, high);
        quickSort_Lomuto(arr, low, pi - 1);
        quickSort_Lomuto(arr, pi + 1, high);
    }
}

int main() {
    vector<int> arr = { 5, 2, 9, 1, 5, 6 };
    quickSort_Lomuto(arr, 0, arr.size() - 1);

    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}