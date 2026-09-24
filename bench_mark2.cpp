#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <utility>
#include <ctime>

using namespace std;

using Clock = chrono::high_resolution_clock;

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
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
    }
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

// RANDOMIZED QUICKSORT (трёхпутевая)
mt19937 rnd_qs(time(NULL));
int randInt(int l, int r) { uniform_int_distribution<int> dist(l, r); return dist(rnd_qs); }

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
            if (a[y] < pivot) { swap(a[y], a[x]); x++; }
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

// HEAPSORT
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
        while (j != 0 && a[parent(j)] < a[j]) { swap(a[parent(j)], a[j]); j = parent(j); }
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
            if (largest == x) break;
            swap(a[x], a[largest]);
            x = largest;
        }
    }
}

// Бенчмарк: 5 запусков, среднее
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

int main()
{
    setlocale(LC_ALL, "ru");
    mt19937 rng(2026);
    vector<int> sizes = { 50000, 100000, 500000, 1000000 };
    const int RUNS = 5;

    ofstream csv("results.csv");
    csv << "n,algorithm,avg_time_ms\n";

    cout << "n\t\tMerge sort\tQuicksort(rand)\tHeapsort\n";
    cout << "---------------------------------------------------------------\n";

    for (int n : sizes)
    {
        double sumMerge = 0, sumQuick = 0, sumHeap = 0;
        for (int run = 0; run < RUNS; run++)
        {
            vector<int> base = genRandom(n, rng);
            sumMerge += measure_merge(base);
            sumQuick += measure_quick(base);
            sumHeap += measure_heap(base);
        }
        double avgMerge = sumMerge / RUNS;
        double avgQuick = sumQuick / RUNS;
        double avgHeap = sumHeap / RUNS;

        cout << n << "\t\t" << avgMerge << "\t\t" << avgQuick << "\t\t" << avgHeap << "\n";

        csv << n << ",Merge sort," << avgMerge << "\n";
        csv << n << ",Quicksort," << avgQuick << "\n";
        csv << n << ",Heapsort," << avgHeap << "\n";
    }
    csv.close();
    cout << "\nРезультаты сохранены в results.csv\n";
    return 0;
}