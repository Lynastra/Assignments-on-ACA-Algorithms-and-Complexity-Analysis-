#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> a, vector<int> b)
{
	int n = a.size();
	int m = b.size();
	vector<int>c(n + m);
	int i = 0;
	int j = 0;
	int k = 0;
	while (i != n && j != m)
	{
		if (a[i] <= b[j])
		{
			c[k] = a[i];
			k++;
			i++;
		}
		else
		{
			c[k] = b[j];
			k++;
			j++;
		}
	}
	while (i != n)
	{
		c[k] = a[i];
		k++;
		i++;
	}
	while (j != m)
	{
		c[k] = b[j];
		k++;
		j++;
	}
	return c;
}

vector<int> merge_sort(vector<int>& a)
{
	int n = a.size();
	if (n <= 1)
		return a;
	else
	{
		int m = n / 2;
		vector <int> b(a.begin(), a.begin() + m);
		vector<int> c(a.begin() + m, a.end());
		return merge(merge_sort(b), merge_sort(c));
	}
}