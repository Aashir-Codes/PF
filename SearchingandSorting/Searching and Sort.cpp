#include <iostream>
#include <iomanip>
using namespace std;

// ==================== UTILITY FUNCTIONS ====================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void displayHeader(const string& title) {
    cout << "\n" << string(50, '=') << endl;
    cout << setw(30) << title << endl;
    cout << string(50, '=') << endl;
}

// ==================== INPUT/OUTPUT FUNCTIONS ====================
void input(int array[], int &size) {
    cout << "\nEnter Array Size (max 100): ";
    cin >> size;

    if (size <= 0 || size > 100) {
        cout << "Invalid size! Setting to 10." << endl;
        size = 10;
    }

    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}

void display(int array[], int size) {
    cout << "Array: [ ";
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// ==================== SEARCH FUNCTIONS ====================
int linearSearch(int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int array[], int size, int target) {
    int start = 0;
    int end = size - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (array[mid] == target) {
            return mid;
        }
        else if (array[mid] < target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return -1;
}

int binarySearchRange(int array[], int target, int start, int end) {
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (array[mid] == target) {
            return mid;
        }
        else if (array[mid] < target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    return -1;
}

// ==================== SORTING FUNCTIONS ====================
void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void selectionSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(array[i], array[minIndex]);
        }
    }
}

// ==================== MENU OPERATIONS ====================

// 1. Target Sum
void targetSum() {
    displayHeader("TARGET SUM");

    int array[100];
    int size = 0;
    input(array, size);
    display(array, size);

    int target;
    cout << "\nEnter target sum: ";
    cin >> target;

    bool found = false;

    for (int i = 0; i < size && !found; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] + array[j] == target) {
                cout << "\n✓ Found: " << array[i] << " + " << array[j]
                     << " = " << target << endl;
                cout << "  Indices: [" << i << "] + [" << j << "]" << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "\n✗ No pair found that sums to " << target << endl;
    }

    pauseScreen();
}

// 2. Product of Array Except Self
void productExceptSelf() {
    displayHeader("PRODUCT EXCEPT SELF");

    int array[100];
    int size = 0;
    input(array, size);

    cout << "\nOriginal ";
    display(array, size);

    int result[100];
    for (int i = 0; i < size; i++) {
        result[i] = 1;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                result[i] *= array[j];
            }
        }
    }

    cout << "Result   ";
    display(result, size);

    pauseScreen();
}

// 3. Find Largest Number
void findLargest() {
    displayHeader("LARGEST NUMBER");

    int array[100];
    int size = 0;
    input(array, size);
    display(array, size);

    int largest = array[0];
    int index = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > largest) {
            largest = array[i];
            index = i;
        }
    }

    cout << "\n✓ Largest number: " << largest << " at index " << index << endl;

    pauseScreen();
}

// 4. Reverse Array
void reverseArray() {
    displayHeader("REVERSE ARRAY");

    int array[100];
    int size = 0;
    input(array, size);

    cout << "\nOriginal ";
    display(array, size);

    for (int i = 0; i < size / 2; i++) {
        swap(array[i], array[size - 1 - i]);
    }

    cout << "Reversed ";
    display(array, size);

    pauseScreen();
}

// 5. Second Largest
void findSecondLargest() {
    displayHeader("SECOND LARGEST");

    int array[100];
    int size = 0;
    input(array, size);
    display(array, size);

    if (size < 2) {
        cout << "\n✗ Need at least 2 elements!" << endl;
        pauseScreen();
        return;
    }

    int largest = array[0];
    int secondLargest = -1;

    for (int i = 1; i < size; i++) {
        if (array[i] > largest) {
            secondLargest = largest;
            largest = array[i];
        }
        else if (array[i] > secondLargest && array[i] != largest) {
            secondLargest = array[i];
        }
    }

    if (secondLargest == -1) {
        cout << "\n✗ No second largest found (all elements might be same)" << endl;
    } else {
        cout << "\n✓ Second largest: " << secondLargest << endl;
    }

    pauseScreen();
}

// 6. Search Operations
void searchMenu() {
    displayHeader("SEARCH OPERATIONS");

    int array[100];
    int size = 0;
    input(array, size);
    display(array, size);

    int target;
    cout << "\nEnter target to search: ";
    cin >> target;

    cout << "\nChoose Search Method:" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search (array must be sorted)" << endl;
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    int index = -1;

    if (choice == 1) {
        index = linearSearch(array, size, target);
    }
    else if (choice == 2) {
        bubbleSort(array, size);
        cout << "\nSorted ";
        display(array, size);
        index = binarySearch(array, size, target);
    }

    if (index != -1) {
        cout << "\n✓ Found " << target << " at index " << index << endl;
    } else {
        cout << "\n✗ " << target << " not found" << endl;
    }

    pauseScreen();
}

// 7. Sorting Operations
void sortingMenu() {
    displayHeader("SORTING");

    int array[100];
    int size = 0;
    input(array, size);

    cout << "\nOriginal ";
    display(array, size);

    cout << "\nChoose Sorting Algorithm:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        bubbleSort(array, size);
        cout << "\n✓ Sorted using Bubble Sort" << endl;
    }
    else if (choice == 2) {
        selectionSort(array, size);
        cout << "\n✓ Sorted using Selection Sort" << endl;
    }
    else {
        cout << "\n✗ Invalid choice!" << endl;
        pauseScreen();
        return;
    }

    cout << "Sorted   ";
    display(array, size);

    pauseScreen();
}

// 8. Merge Two Sorted Arrays
void mergeSortedArrays() {
    displayHeader("MERGE SORTED ARRAYS");

    int array1[100], array2[100], merged[200];
    int size1 = 0, size2 = 0;

    cout << "\nFirst Array:" << endl;
    input(array1, size1);
    bubbleSort(array1, size1);
    cout << "Sorted ";
    display(array1, size1);

    cout << "\nSecond Array:" << endl;
    input(array2, size2);
    bubbleSort(array2, size2);
    cout << "Sorted ";
    display(array2, size2);

    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (array1[i] <= array2[j]) {
            merged[k++] = array1[i++];
        } else {
            merged[k++] = array2[j++];
        }
    }

    while (i < size1) {
        merged[k++] = array1[i++];
    }

    while (j < size2) {
        merged[k++] = array2[j++];
    }

    cout << "\nMerged  ";
    display(merged, k);

    pauseScreen();
}

// 9. First/Last Occurrence
void occurrenceMenu() {
    displayHeader("OCCURRENCE FINDER");

    int array[100];
    int size = 0;
    input(array, size);
    display(array, size);

    int target;
    cout << "\nEnter target: ";
    cin >> target;

    int firstOccur = -1, lastOccur = -1, count = 0;

    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            if (firstOccur == -1) {
                firstOccur = i;
            }
            lastOccur = i;
            count++;
        }
    }

    if (count > 0) {
        cout << "\n✓ Target " << target << " found!" << endl;
        cout << "  First occurrence: index " << firstOccur << endl;
        cout << "  Last occurrence:  index " << lastOccur << endl;
        cout << "  Total occurrences: " << count << endl;
    } else {
        cout << "\n✗ Target " << target << " not found" << endl;
    }

    pauseScreen();
}

// ==================== MAIN MENU ====================
void displayMainMenu() {
    clearScreen();
    displayHeader("ARRAY OPERATIONS TOOLKIT");

    cout << "\n1.  Target Sum (Find two numbers that sum to target)" << endl;
    cout << "2.  Product Except Self" << endl;
    cout << "3.  Find Largest Number" << endl;
    cout << "4.  Reverse Array" << endl;
    cout << "5.  Find Second Largest" << endl;
    cout << "6.  Search Operations (Linear/Binary)" << endl;
    cout << "7.  Sorting (Bubble/Selection)" << endl;
    cout << "8.  Merge Two Sorted Arrays" << endl;
    cout << "9.  Find Occurrences (First/Last/Count)" << endl;
    cout << "0.  Exit Program" << endl;

    cout << "\n" << string(50, '-') << endl;
    cout << "Enter your choice: ";
}

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                targetSum();
                break;
            case 2:
                productExceptSelf();
                break;
            case 3:
                findLargest();
                break;
            case 4:
                reverseArray();
                break;
            case 5:
                findSecondLargest();
                break;
            case 6:
                searchMenu();
                break;
            case 7:
                sortingMenu();
                break;
            case 8:
                mergeSortedArrays();
                break;
            case 9:
                occurrenceMenu();
                break;
            case 0:
                cout << "\n✓ Thank you for using the Array Toolkit!" << endl;
                cout << "  Goodbye! 👋\n" << endl;
                break;
            default:
                cout << "\n✗ Invalid choice! Please try again." << endl;
                pauseScreen();
        }

    } while (choice != 0);

    return 0;
}