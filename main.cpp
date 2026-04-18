#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==============================
// 工具函式
// ==============================
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

void printTitle(const string& title) {
    cout << "\n==============================\n";
    cout << title << "\n";
    cout << "==============================\n";
}

// ==============================
// 1. Selection Sort
// ==============================
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// ==============================
// 2. Insertion Sort
// ==============================
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ==============================
// 3. Bubble Sort
// ==============================
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

// ==============================
// 4. Shell Sort
// ==============================
void shellSort(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

// ==============================
// 5. Merge Sort
// ==============================
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ==============================
// 6. Quick Sort
// ==============================
int partitionArray(vector<int>& arr, int low, int high) {
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

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionArray(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==============================
// 7. Radix Sort
// ==============================
void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

// ==============================
// 8. Heap Sort
// ==============================
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ==============================
// 執行單一排序並輸出
// ==============================
void runSingleTest(const string& sortName, void (*sortFunc)(vector<int>&), const vector<int>& data) {
    vector<int> arr = data;
    cout << sortName << "\n";
    cout << "Before: ";
    printArray(arr);
    sortFunc(arr);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runMergeSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Merge Sort\n";
    cout << "Before: ";
    printArray(arr);
    mergeSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runQuickSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Quick Sort\n";
    cout << "Before: ";
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

// ==============================
// 主程式
// ==============================
int main() {
    vector<int> bestCase1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> bestCase2 = {1, 2, 3, 4, 6, 5, 7, 8, 9, 10};
    vector<int> worstCase1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> worstCase2 = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    vector<int> radixCase  = {329, 457, 657, 839, 436, 720, 355};
    vector<int> mixedCase  = {42, 17, 93, 8, 23, 55, 4, 16, 77, 61};

    printTitle("Test Data 1: Best Case - Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase1);
    runSingleTest("Insertion Sort", insertionSort, bestCase1);
    runSingleTest("Bubble Sort", bubbleSort, bestCase1);
    runSingleTest("Shell Sort", shellSort, bestCase1);
    runMergeSortTest(bestCase1);
    runQuickSortTest(bestCase1);
    runSingleTest("Radix Sort", radixSort, bestCase1);
    runSingleTest("Heap Sort", heapSort, bestCase1);

    printTitle("Test Data 2: Near Best Case - Almost Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase2);
    runSingleTest("Insertion Sort", insertionSort, bestCase2);
    runSingleTest("Bubble Sort", bubbleSort, bestCase2);
    runSingleTest("Shell Sort", shellSort, bestCase2);
    runMergeSortTest(bestCase2);
    runQuickSortTest(bestCase2);
    runSingleTest("Radix Sort", radixSort, bestCase2);
    runSingleTest("Heap Sort", heapSort, bestCase2);

    printTitle("Test Data 3: Worst Case - Reverse Sorted");
    runSingleTest("Selection Sort", selectionSort, worstCase1);
    runSingleTest("Insertion Sort", insertionSort, worstCase1);
    runSingleTest("Bubble Sort", bubbleSort, worstCase1);
    runSingleTest("Shell Sort", shellSort, worstCase1);
    runMergeSortTest(worstCase1);
    runQuickSortTest(worstCase1);
    runSingleTest("Radix Sort", radixSort, worstCase1);
    runSingleTest("Heap Sort", heapSort, worstCase1);

    printTitle("Test Data 4: Another Reverse Large Values");
    runSingleTest("Selection Sort", selectionSort, worstCase2);
    runSingleTest("Insertion Sort", insertionSort, worstCase2);
    runSingleTest("Bubble Sort", bubbleSort, worstCase2);
    runSingleTest("Shell Sort", shellSort, worstCase2);
    runMergeSortTest(worstCase2);
    runQuickSortTest(worstCase2);
    runSingleTest("Radix Sort", radixSort, worstCase2);
    runSingleTest("Heap Sort", heapSort, worstCase2);

    printTitle("Test Data 5: Radix Test");
    runSingleTest("Selection Sort", selectionSort, radixCase);
    runSingleTest("Insertion Sort", insertionSort, radixCase);
    runSingleTest("Bubble Sort", bubbleSort, radixCase);
    runSingleTest("Shell Sort", shellSort, radixCase);
    runMergeSortTest(radixCase);
    runQuickSortTest(radixCase);
    runSingleTest("Radix Sort", radixSort, radixCase);
    runSingleTest("Heap Sort", heapSort, radixCase);

    printTitle("Test Data 6: Random Mixed");
    runSingleTest("Selection Sort", selectionSort, mixedCase);
    runSingleTest("Insertion Sort", insertionSort, mixedCase);
    runSingleTest("Bubble Sort", bubbleSort, mixedCase);
    runSingleTest("Shell Sort", shellSort, mixedCase);
    runMergeSortTest(mixedCase);
    runQuickSortTest(mixedCase);
    runSingleTest("Radix Sort", radixSort, mixedCase);
    runSingleTest("Heap Sort", heapSort, mixedCase);

    return 0;
}
