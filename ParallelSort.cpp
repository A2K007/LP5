#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubblesort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelbubblesort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = l; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + j + 1];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = arr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = arr[j];
        j++;
        k++;
    }
}

void mergesort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            mergesort(arr, l, m);
#pragma omp section
            mergesort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

void printarr(vector<int> &arr)
{
    for (auto x : arr)
    {
        cout << x << " ";
    }
    cout << endl;
}
int main()
{
    int n = 10000;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int t = rand() % n;
        arr.push_back(t);
    }
    cout << "Original arr : ";
    // printarr(arr);
    auto start = chrono::high_resolution_clock::now();
    mergesort(arr, 0, n - 1);
    // parallelbubblesort(arr);
    auto end = chrono::high_resolution_clock::now();
    cout << "Sorted arr : ";
    // printarr(arr);
    cout << "Time : ";
    auto t = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << t.count() << endl;
    return 0;
}