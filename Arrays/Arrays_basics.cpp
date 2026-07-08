// Author: Aashir Khan
// Array Operations Toolkit - Complete Edition
// Demonstrates clean coding and strong programming fundamentals

#include <iostream>
#include <iomanip>
#include <limits>

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

// ==================== CORE INPUT/OUTPUT ====================

void input(int array[], int &size) {
    cout << "\nEnter Array Size (1-100): ";
    cin >> size;

    // Input validation
    while (size < 1 || size > 100) {
        cout << "Invalid! Size must be between 1 and 100: ";
        cin >> size;
    }

    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}

void display(const int array[], int size) {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// ==================== UTILITY OPERATIONS ====================

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void sortDescending(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                swap(array[i], array[j]);
            }
        }
    }
}

// ==================== SEARCH OPERATIONS ====================

int linearSearch(const int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) return i;
    }
    return -1;
}

int binarySearch(const int array[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == target) return mid;
        else if (array[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ==================== MENU 1: BASIC OPERATIONS ====================

void sumOfValues() {
    displayHeader("SUM OF ARRAY VALUES");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
    display(array, size);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    cout << "\n✓ Sum of all values: " << sum << endl;
    pauseScreen();
}

void countEvenNumbers() {
    displayHeader("COUNT EVEN NUMBERS");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
    display(array, size);

    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) evenCount++;
        else oddCount++;
    }

    cout << "\n✓ Even numbers: " << evenCount << endl;
    cout << "  Odd numbers:  " << oddCount << endl;
    pauseScreen();
}

void findLargest() {
    displayHeader("LARGEST NUMBER");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
    display(array, size);

    int maxVal = array[0];
    int maxIndex = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > maxVal) {
            maxVal = array[i];
            maxIndex = i;
        }
    }

    cout << "\n✓ Largest number: " << maxVal << " at index " << maxIndex << endl;
    pauseScreen();
}

void reverseArray() {
    displayHeader("REVERSE ARRAY");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    int left = 0, right = size - 1;
    while (left < right) {
        swap(array[left], array[right]);
        left++;
        right--;
    }

    cout << "Reversed: ";
    display(array, size);

    pauseScreen();
}

void findSecondLargest() {
    displayHeader("SECOND LARGEST NUMBER");

    int array[100], size = 0;
    input(array, size);

    if (size < 2) {
        cout << "\n✗ Need at least 2 elements!" << endl;
        pauseScreen();
        return;
    }

    cout << "\nArray: ";
    display(array, size);

    // Sort in descending order
    sortDescending(array, size);

    // Find first element different from largest
    int i = 0;
    while (i < size && array[i] == array[0]) {
        i++;
    }

    if (i < size) {
        cout << "\n✓ Second largest: " << array[i] << endl;
    } else {
        cout << "\n✗ All elements are identical!" << endl;
    }

    pauseScreen();
}

// ==================== MENU 2: SHIFT OPERATIONS ====================

void rightShift(int array[], int size, int positions) {
    positions = positions % size; // Handle shifts larger than array size

    for (int shift = 0; shift < positions; shift++) {
        int last = array[size - 1];
        for (int j = size - 1; j > 0; j--) {
            array[j] = array[j - 1];
        }
        array[0] = last;
    }
}

void leftShift(int array[], int size, int positions) {
    positions = positions % size; // Handle shifts larger than array size

    for (int shift = 0; shift < positions; shift++) {
        int first = array[0];
        for (int j = 0; j < size - 1; j++) {
            array[j] = array[j + 1];
        }
        array[size - 1] = first;
    }
}

void shiftArray() {
    displayHeader("SHIFT ARRAY");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    int positions;
    cout << "\nEnter shift positions: ";
    cin >> positions;

    cout << "\nShift Direction:" << endl;
    cout << "1. Right Shift (→)" << endl;
    cout << "2. Left Shift (←)" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        rightShift(array, size, positions);
        cout << "\nRight shifted by " << positions << ": ";
    } else if (choice == 2) {
        leftShift(array, size, positions);
        cout << "\nLeft shifted by " << positions << ": ";
    } else {
        cout << "\n✗ Invalid choice!" << endl;
        pauseScreen();
        return;
    }

    display(array, size);
    pauseScreen();
}

// ==================== MENU 3: SEGREGATION ====================

void segregateZeros() {
    displayHeader("SEGREGATE ZEROS");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    // Move all zeros to the left
    int left = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == 0) {
            swap(array[left], array[i]);
            left++;
        }
    }

    cout << "\nSegregated (zeros first): ";
    display(array, size);

    pauseScreen();
}

void segregateEvens() {
    displayHeader("SEGREGATE EVEN NUMBERS");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    // Move all even numbers to the left
    int left = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            swap(array[left], array[i]);
            left++;
        }
    }

    cout << "\nSegregated (evens first): ";
    display(array, size);

    pauseScreen();
}

void segregateEvensStable() {
    displayHeader("SEGREGATE EVENS (STABLE)");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    // Stable segregation using insertion sort technique
    for (int i = 1; i < size; i++) {
        if (array[i] % 2 == 0) {
            int key = array[i];
            int j = i - 1;

            // Shift odd numbers to the right
            while (j >= 0 && array[j] % 2 != 0) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    cout << "\nStable Segregation (maintains relative order): ";
    display(array, size);

    cout << "\nℹ️  Note: Elements maintain their original order within" << endl;
    cout << "   even and odd groups (stable algorithm)" << endl;

    pauseScreen();
}

// ==================== MENU 4: ADVANCED OPERATIONS ====================

void targetSum() {
    displayHeader("TARGET SUM");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
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
        cout << "\n✗ No pair sums to " << target << endl;
    }

    pauseScreen();
}

void productExceptSelf() {
    displayHeader("PRODUCT EXCEPT SELF");

    int array[100], size = 0;
    input(array, size);

    cout << "\nOriginal: ";
    display(array, size);

    int result[100];

    // Calculate product of all elements except self
    for (int i = 0; i < size; i++) {
        result[i] = 1;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                result[i] *= array[j];
            }
        }
    }

    cout << "Result:   ";
    display(result, size);

    cout << "\nℹ️  Each position contains product of all OTHER elements" << endl;

    pauseScreen();
}

void searchOperations() {
    displayHeader("SEARCH OPERATIONS");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
    display(array, size);

    int target;
    cout << "\nEnter target to search: ";
    cin >> target;

    cout << "\nSearch Method:" << endl;
    cout << "1. Linear Search (works on any array)" << endl;
    cout << "2. Binary Search (requires sorted array)" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;

    int index = -1;

    if (choice == 1) {
        index = linearSearch(array, size, target);
    } else if (choice == 2) {
        // Sort first for binary search
        bubbleSort(array, size);
        cout << "\nSorted: ";
        display(array, size);
        index = binarySearch(array, size, target);
    } else {
        cout << "\n✗ Invalid choice!" << endl;
        pauseScreen();
        return;
    }

    if (index != -1) {
        cout << "\n✓ Found " << target << " at index " << index << endl;
    } else {
        cout << "\n✗ " << target << " not found" << endl;
    }

    pauseScreen();
}

void findOccurrences() {
    displayHeader("FIND OCCURRENCES");

    int array[100], size = 0;
    input(array, size);

    cout << "\nArray: ";
    display(array, size);

    int target;
    cout << "\nEnter target: ";
    cin >> target;

    int first = -1, last = -1, count = 0;

    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            if (first == -1) first = i;
            last = i;
            count++;
        }
    }

    if (count > 0) {
        cout << "\n✓ Found " << target << "!" << endl;
        cout << "  First occurrence: index " << first << endl;
        cout << "  Last occurrence:  index " << last << endl;
        cout << "  Total count:      " << count << endl;
    } else {
        cout << "\n✗ " << target << " not found" << endl;
    }

    pauseScreen();
}

void mergeSortedArrays() {
    displayHeader("MERGE TWO SORTED ARRAYS");

    int arr1[100], arr2[100], merged[200];
    int size1 = 0, size2 = 0;

    cout << "\nFirst Array:" << endl;
    input(arr1, size1);
    bubbleSort(arr1, size1);
    cout << "Sorted: ";
    display(arr1, size1);

    cout << "\nSecond Array:" << endl;
    input(arr2, size2);
    bubbleSort(arr2, size2);
    cout << "Sorted: ";
    display(arr2, size2);

    int i = 0, j = 0, k = 0;

    // Merge
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }

    while (i < size1) merged[k++] = arr1[i++];
    while (j < size2) merged[k++] = arr2[j++];

    cout << "\nMerged: ";
    display(merged, k);

    pauseScreen();
}

// ==================== MAIN MENU ====================

void displayMainMenu() {
    clearScreen();
    displayHeader("ARRAY OPERATIONS TOOLKIT");

    cout << "\n┌─────────────────────────────────────────────────┐" << endl;
    cout << "│  BASIC OPERATIONS                               │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  1. Sum of Values                               │" << endl;
    cout << "│  2. Count Even Numbers                          │" << endl;
    cout << "│  3. Find Largest Number                         │" << endl;
    cout << "│  4. Reverse Array                               │" << endl;
    cout << "│  5. Find Second Largest                         │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  SHIFT & SEGREGATION                            │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  6. Shift Array (Left/Right)                    │" << endl;
    cout << "│  7. Segregate Zeros                             │" << endl;
    cout << "│  8. Segregate Even Numbers                      │" << endl;
    cout << "│  9. Segregate Evens (Stable)                    │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  ADVANCED OPERATIONS                            │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  10. Target Sum (Two Numbers)                   │" << endl;
    cout << "│  11. Product Except Self                        │" << endl;
    cout << "│  12. Search Operations                          │" << endl;
    cout << "│  13. Find All Occurrences                       │" << endl;
    cout << "│  14. Merge Two Sorted Arrays                    │" << endl;
    cout << "├─────────────────────────────────────────────────┤" << endl;
    cout << "│  0.  Exit Program                               │" << endl;
    cout << "└─────────────────────────────────────────────────┘" << endl;

    cout << "\nEnter your choice: ";
}

// ==================== MAIN FUNCTION ====================

int main() {
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:  sumOfValues(); break;
            case 2:  countEvenNumbers(); break;
            case 3:  findLargest(); break;
            case 4:  reverseArray(); break;
            case 5:  findSecondLargest(); break;
            case 6:  shiftArray(); break;
            case 7:  segregateZeros(); break;
            case 8:  segregateEvens(); break;
            case 9:  segregateEvensStable(); break;
            case 10: targetSum(); break;
            case 11: productExceptSelf(); break;
            case 12: searchOperations(); break;
            case 13: findOccurrences(); break;
            case 14: mergeSortedArrays(); break;
            case 0:
                cout << "\n✓ Thank you for using the Array Toolkit!" << endl;
                cout << "  Happy Coding! 🚀\n" << endl;
                break;
            default:
                cout << "\n✗ Invalid choice! Please try again." << endl;
                pauseScreen();
        }

    } while (choice != 0);

    return 0;
}