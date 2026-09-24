#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <algorithm>
#include <random>
using namespace std;

// MERGE(A, p, q, r) - по псевдокоду Кормена, переведено в 0-индексацию.
// A[p..r] включительно (здесь НЕ полуинтервал, а отрезок!)
// L[1..n1] и R[1..n2] в книге -> L[0..n1-1] и R[0..n2-1] здесь.
void merge(vector<int>& a, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (int i = 0; i < n1; i++)
        L[i] = a[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[q + 1 + j];

    L[n1] = INT_MAX; // сигнальное значение вместо бесконечности 
    R[n2] = INT_MAX;

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

// MERGE-SORT(A, p, r) - по псевдокоду, A[p..r] включительно
void mergeSortCLRS(vector<int>& a, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSortCLRS(a, p, q);
        mergeSortCLRS(a, q + 1, r);
        merge(a, p, q, r);
    }
}

void printVec(const string& label, const vector<int>& v)
{
    cout << label << ": ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

void test_basic()
{
    // пример, который разбирает Корман
    vector<int> a = { 5, 2, 4, 6, 1, 3 };
    mergeSortCLRS(a, 0, (int)a.size() - 1);
    assert((a == vector<int>{1, 2, 3, 4, 5, 6}));
    cout << "[OK] test_basic\n";
}

void test_single()
{
    vector<int> a = { 9 };
    mergeSortCLRS(a, 0, 0);
    assert((a == vector<int>{9}));
    cout << "[OK] test_single\n";
}

void test_already_sorted()
{
    vector<int> a = { 1,2,3,4,5,6,7 };
    mergeSortCLRS(a, 0, (int)a.size() - 1);
    assert((a == vector<int>{1, 2, 3, 4, 5, 6, 7}));
    cout << "[OK] test_already_sorted\n";
}

void test_reverse_sorted()
{
    vector<int> a = { 7,6,5,4,3,2,1 };
    mergeSortCLRS(a, 0, (int)a.size() - 1);
    assert((a == vector<int>{1, 2, 3, 4, 5, 6, 7}));
    cout << "[OK] test_reverse_sorted\n";
}

void test_duplicates()
{
    vector<int> a = { 4,2,4,2,4,1,1 };
    mergeSortCLRS(a, 0, (int)a.size() - 1);
    assert((a == vector<int>{1, 1, 2, 2, 4, 4, 4}));
    cout << "[OK] test_duplicates\n";
}

void test_stability()
{
    // <= в строке 13 псевдокода - признак устойчивости, проверим на структуре
    struct P { int key, idx; };
    // закодируем след. образом: key*10000+idx
    // т.е. так, чтобы сравнение по числу совпадало 
    // со сравнением по idx при равных key
    vector<int> keys = { 3,1,3,2,1,3 };
    vector<int> encoded;
    for (int i = 0; i < (int)keys.size(); i++)
        encoded.push_back(keys[i] * 10000 + i);
    mergeSortCLRS(encoded, 0, (int)encoded.size() - 1);

    vector<int> idxForKey3;
    for (int v : encoded) if (v / 10000 == 3) idxForKey3.push_back(v % 10000);
    assert((idxForKey3 == vector<int>{0, 2, 5})); // исходный порядок для ключа 3: индексы 0,2,5
    cout << "[OK] test_stability\n";
}

void test_random_stress(int iterations = 500)
{
    mt19937 rng(42);
    for (int it = 0; it < iterations; it++)
    {
        int n = rng() % 300;
        if (n == 0) continue;
        vector<int> a(n);
        for (auto& x : a) x = (int)(rng() % 2000) - 1000;
        auto expected = a;
        sort(expected.begin(), expected.end());
        mergeSortCLRS(a, 0, n - 1);
        assert(a == expected);
    }
    cout << "[OK] test_random_stress (" << iterations << " iterations)\n";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    test_basic();
    test_single();
    test_already_sorted();
    test_reverse_sorted();
    test_duplicates();
    test_stability();
    test_random_stress();
    cout << "\nВсе тесты пройдены успешно.\n";
}