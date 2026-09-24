#include <iostream>
#include <vector>
using namespace std;

// heapsort - сортировка, основанная на применении 
// структуры данных пирамида
/*
* 1) Сначала строится невозрастающая пирамида,
* в корне кот. находится максимум
* 2) Каждый раз извлекается максимальный элемент
* и отправляется в конец. Операция происходит внутри
* самого массива, т.е. сортировка происходит in-place
* (не требует дополнительной памяти)
*/

// Свободные функции вместо методов struct heap в классической
// реализации для очереди с приоритетом
// куча (пирамида) работает напрямую на векторе, без обёртки в структуру

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

    // стадия построения max-кучи: вставка по одному
    for (int i = 0; i < n; i++)
    {
        // нужно добавить i-й элемент в пирамиду
        // изначально i-й элемент на i-й позиции
        // необходимо его "просеять" вверх
        int j = i;
        while (j != 0 && a[parent(j)] < a[j])
        {
            swap(a[parent(j)], a[j]);
            j = parent(j);
        }
        // извлекли из пирамиды максимум 
    // теперь она размера i, но в корне может быть
    // элемент, который нарушает условие сохранения 
    // (поддержки) пирамиды
    }
    
    // стадия извлечения максимумов
    for (int i = n - 1; i > 0; i--)
    {
        swap(a[i], a[0]);   // максимум (корень) уезжает в конец
        int x = 0;
        while (true)
        {
            int left = leftChild(x);
            int right = rightChild(x);
            int largest = x;
            if (left < i && a[left] > a[largest]) largest = left;
            if (right < i && a[right] > a[largest]) largest = right;
            if (largest == x) break;
            swap(a[x], a[largest]);
            x = largest;
        }
    }
}