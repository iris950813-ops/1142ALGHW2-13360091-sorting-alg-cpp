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

    // TODO:
    // 使用挑選排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 外圈從 i = 0 到 n-2
    // 2. 在未排序區間中找最小值的位置 minIndex
    // 3. 將 arr[i] 與 arr[minIndex] 交換

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

    // TODO:
    // 使用插入排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 外圈從 i = 1 到 n-1
    // 2. 設 key = arr[i]
    // 3. 將比 key 大的元素往右移
    // 4. 把 key 插入正確位置

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

    // TODO:
    // 使用氣泡排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 每一輪把最大值往右推
    // 2. 可使用 swapped 變數判斷是否提早結束

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

    // TODO:
    // 使用 Shell 排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. gap 先設為 n/2
    // 2. 每次 gap /= 2
    // 3. 對每個 gap 做類似 insertion sort

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
    // TODO:
    // 合併 arr[left..mid] 與 arr[mid+1..right]
    //
    // 提示：
    // 1. 先建立 leftArr 與 rightArr
    // 2. 比較兩邊元素，小的先放回 arr
    // 3. 最後把剩餘元素補回 arr

    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }

    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    // TODO:
    // 使用遞迴完成 merge sort
    //
    // 提示：
    // 1. 終止條件：left >= right
    // 2. 找中間 mid
    // 3. 遞迴排序左半部
    // 4. 遞迴排序右半部
    // 5. 呼叫 merge()

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
    // TODO:
    // 以 arr[high] 作為 pivot，完成 partition
    //
    // 提示：
    // 1. pivot = arr[high]
    // 2. i = low - 1
    // 3. 掃描 j = low 到 high - 1
    // 4. 若 arr[j] < pivot，則交換到左側
    // 5. 最後將 pivot 放到正確位置
    // 6. 回傳 pivot 的索引

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
    // TODO:
    // 使用遞迴完成 quick sort
    //
    // 提示：
    // 1. 若 low < high
    // 2. 呼叫 partitionArray()
    // 3. 遞迴排序左半部與右半部

    if (low < high) {
        int pi = partitionArray(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ==============================
// 7. Radix Sort
// 僅處理非負整數
// ==============================
void countingSortByDigit(vector<int>& arr, int exp) {
    // TODO:
    // 依照指定位數 exp 進行 counting sort
    //
    // 提示：
    // 1. digit = (arr[i] / exp) % 10
    // 2. count[10] 紀錄各數字出現次數
    // 3. 轉成累計次數
    // 4. 由右往左放入 output，保持穩定性
    // 5. 將 output 複製回 arr

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
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void radixSort(vector<int>& arr) {
    // TODO:
    // 使用 radix sort 將 arr 由小到大排序
    //
    // 提示：
    // 1. 找出最大值 maxVal
    // 2. 從個位數開始 exp = 1
    // 3. 每次乘以 10，直到 maxVal / exp == 0
    // 4. 每次呼叫 countingSortByDigit(arr, exp)

    int maxVal = *max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, exp);
    }
}

// ==============================
// 8. Heap Sort
// ==============================
void heapify(vector<int>& arr, int n, int i) {
    // TODO:
    // 維護以 i 為根的 max-heap
    //
    // 提示：
    // 1. largest = i
    // 2. left = 2*i + 1, right = 2*i + 2
    // 3. 找出三者中最大者
    // 4. 若最大者不是 i，交換後遞迴 heapify

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用 heap sort 將 arr 由小到大排序
    //
    // 提示：
    // 1. 先建立 max heap
    // 2. 再把堆頂元素和最後元素交換
    // 3. 縮小 heap 範圍後重新 heapify

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
