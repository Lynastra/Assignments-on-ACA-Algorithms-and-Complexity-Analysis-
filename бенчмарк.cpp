#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <utility>
#include <ctime>
#include <iomanip>
using namespace std;
using Clock = chrono::high_resolution_clock;

// MergeSort (кормановская версия)
void merge(vector<int>& a, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 1), R(n2 + 1);
    for (int i = 0; i < n1; i++) 
        L[i] = a[p + i];
    for (int j = 0; j < n2; j++) 
        R[j] = a[q + 1 + j];
    L[n1] = INT_MAX; R[n2] = INT_MAX;
    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
        a[k] = (L[i] <= R[j]) ? L[i++] : R[j++];
}
void mergeSortCLRS(vector<int>& a, int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        mergeSortCLRS(a, p, q);
        mergeSortCLRS(a, q + 1, r);
        merge(a, p, q, r);
    }
}

// Randomized QuickSort 
mt19937 rnd_qs(time(NULL));
int randInt(int l, int r) 
{ 
    uniform_int_distribution<int> dist(l, r); 
    return dist(rnd_qs); 
}

pair<int, int> partition_random(vector<int>& a, int l, int r)
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
void quickSort_random(vector<int>& a, int l, int r)
{
    if ((r - l) < 2) return;
    pair<int, int> p = partition_random(a, l, r);
    quickSort_random(a, l, p.first);
    quickSort_random(a, p.second, r);
}

// HeapSort
int parent(int x) 
{ 
    return (x - 1) / 2; 
}
int leftChild(int x) 
{ 
    return 2 * x + 1; 
}
int rightChild(int x) 
{ 
    return 2 * x + 2; 
}
void heapsort(vector<int>& a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j != 0 && a[parent(j)] < a[j]) 
        { 
            swap(a[parent(j)], a[j]); 
            j = parent(j); 
        }
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[i], a[0]);
        int x = 0;
        while (true)
        {
            int left = leftChild(x), right = rightChild(x), largest = x;
            if (left < i && a[left] > a[largest]) 
                largest = left;
            if (right < i && a[right] > a[largest]) 
                largest = right;
            if (largest == x) 
                break;
            swap(a[x], a[largest]);
            x = largest;
        }
    }
}

// Бенчмарк
double measure_merge(vector<int> a) {
    auto t1 = Clock::now();
    mergeSortCLRS(a, 0, (int)a.size() - 1);
    auto t2 = Clock::now();
    return chrono::duration<double, milli>(t2 - t1).count();
}
double measure_quick(vector<int> a) {
    auto t1 = Clock::now();
    quickSort_random(a, 0, (int)a.size());
    auto t2 = Clock::now();
    return chrono::duration<double, milli>(t2 - t1).count();
}
double measure_heap(vector<int> a) {
    auto t1 = Clock::now();
    heapsort(a);
    auto t2 = Clock::now();
    return chrono::duration<double, milli>(t2 - t1).count();
}

vector<int> genRandom(int n, mt19937& rng) {
    vector<int> a(n);
    for (auto& x : a) x = rng() % 1000000;
    return a;
}
vector<int> genSorted(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = i;
    return a;
}
vector<int> genReverse(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = n - i;
    return a;
}

int main()
{
    setlocale(LC_ALL, "ru");
    mt19937 rng(777);
    vector<int> sizes = { 1000, 10000, 100000, 1000000 };

    cout << left << setw(10) << "n" << setw(14) << "тип данных"
        << setw(14) << "Merge sort" << setw(18) << "Quicksort(rand)" << setw(12) << "Heapsort" << "\n";
    cout << string(68, '-') << "\n";

    for (int n : sizes)
    {
        vector<int> r = genRandom(n, rng);
        vector<int> s = genSorted(n);
        vector<int> rv = genReverse(n);

        cout << left << setw(10) << n << setw(14) << "случайный"
            << setw(14) << fixed << setprecision(2) << measure_merge(r)
            << setw(18) << measure_quick(r)
            << setw(12) << measure_heap(r) << "\n";

        cout << left << setw(10) << n << setw(14) << "отсортир."
            << setw(14) << measure_merge(s)
            << setw(18) << measure_quick(s)
            << setw(12) << measure_heap(s) << "\n";

        cout << left << setw(10) << n << setw(14) << "обратный"
            << setw(14) << measure_merge(rv)
            << setw(18) << measure_quick(rv)
            << setw(12) << measure_heap(rv) << "\n";
    }
    return 0;
}