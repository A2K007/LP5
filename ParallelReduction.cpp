#include <bits/stdc++.h>
#include <omp.h>

using namespace std; 

template <typename T>
T parallelMin(const vector<T> &arr)
{
    T ans = arr[0];
#pragma omp parallel for
    for (int i = 0; i < arr.size(); i++)
    {
        ans = min(ans, arr[i]);
    }
    return ans;
}

template <typename T>
T parallelMax(const vector<T> &arr)
{
    T ans = arr[0];
#pragma omp parallel for
    for (int i = 0; i < arr.size(); i++)
    {
        ans = max(ans, arr[i]);
    }
    return ans;
}

template <typename T>
T parallelSum(const vector<T> &arr)
{
    T ans = 0;
#pragma omp parallel for
    for (int i = 0; i < arr.size(); i++)
    {
        ans = ans + arr[i];
    }
    return ans;
}

template <typename T>
T parallelAverage(const vector<T> &arr)
{
    T sum = parallelSum(arr);
    return static_cast<double>(sum)/arr.size();
}

int main()
{
    const int size = 10;
    vector<int> arr(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;
    // Compute min, max, sum, and average using parallel reduction
    int minVal = parallelMin(arr);
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double average = parallelAverage(arr);

    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}