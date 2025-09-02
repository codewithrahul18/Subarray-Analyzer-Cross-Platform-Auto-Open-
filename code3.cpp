// Subarray Analyzer (Cross-Platform Auto Open)
#include <iostream>
#include <fstream>
#include <cstdlib> // for system()
using namespace std;

// ===== Utility to auto-open files cross-platform =====
void openFile(const string &filename) {
    #ifdef _WIN32
        system(("start " + filename).c_str()); // Windows
    #elif __APPLE__
        system(("open " + filename).c_str());  // MacOS
    #else
        system(("xdg-open " + filename).c_str()); // Linux
    #endif
}

// ===== Function to print all subarrays =====
void printSubarrays(int arr[], int n, ofstream &txt, ofstream &csv) {
    txt << "\n🔹 All Subarrays:\n";
    cout << "\n🔹 All Subarrays:\n";

    for (int st = 0; st < n; st++) {
        for (int end = st; end < n; end++) {
            txt << "[ ";
            cout << "[ ";
            for (int i = st; i <= end; i++) {
                txt << arr[i] << " ";
                cout << arr[i] << " ";
            }
            txt << "]\n";
            cout << "]\n";

            // Save in CSV
            for (int i = st; i <= end; i++) {
                csv << arr[i];
                if (i < end) csv << ",";
            }
            csv << "\n";
        }
    }
}

// ===== Function to print subarrays with sum =====
void printSubarraysWithSum(int arr[], int n, ofstream &txt, ofstream &csv) {
    txt << "\n🔹 All Subarrays with Current Sum:\n";
    cout << "\n🔹 All Subarrays with Current Sum:\n";

    for (int st = 0; st < n; st++) {
        int currSum = 0;
        for (int end = st; end < n; end++) {
            currSum += arr[end];

            txt << "[ ";
            cout << "[ ";
            for (int i = st; i <= end; i++) {
                txt << arr[i] << " ";
                cout << arr[i] << " ";
            }
            txt << "]  → Sum = " << currSum << "\n";
            cout << "]  → Sum = " << currSum << "\n";

            // Save subarray + sum in CSV
            for (int i = st; i <= end; i++) {
                csv << arr[i];
                if (i < end) csv << ",";
            }
            csv << "," << currSum << "\n";
        }
    }
}

// ===== Kadane’s Algorithm =====
int maxSubarraySum(int arr[], int n, ofstream &txt, ofstream &csv) {
    int maxSum = arr[0];
    int currSum = arr[0];

    for (int i = 1; i < n; i++) {
        currSum = max(arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
    }

    txt << "\n✅ Maximum Subarray Sum = " << maxSum << "\n";
    cout << "\n✅ Maximum Subarray Sum = " << maxSum << "\n";

    csv << "MAX_SUBARRAY_SUM," << maxSum << "\n";

    return maxSum;
}

// ===== Main Program =====
int main() {
    int n;
    cout << "📊 Subarray Analyzer Project\n";
    cout << "👨‍💻 Programmer: THE RAHUL CHAUHAN\n";
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Open files
    ofstream txt("subarray_report.txt");
    ofstream csv("subarray_report.csv");

    if (!txt || !csv) {
        cout << "⚠️ Error: Could not create output files!\n";
        return 1;
    }

    // Add header / credit
    txt << "📊 Subarray Analyzer Report\n";
    txt << "👨‍💻 Programmer: THE RAHUL CHAUHAN\n\n";
    csv << "Subarray Elements,Sum\n";

    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Print All Subarrays\n";
        cout << "2. Print Subarrays with Current Sum\n";
        cout << "3. Find Maximum Subarray Sum (Kadane)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: printSubarrays(arr, n, txt, csv); break;
            case 2: printSubarraysWithSum(arr, n, txt, csv); break;
            case 3: maxSubarraySum(arr, n, txt, csv); break;
            case 4: 
                cout << "Results saved in 'subarray_report.txt' and 'subarray_report.csv' 👌\n";
                txt << "\nReport Generated Successfully ✅\n";
                txt << "👨‍💻 Programmer: THE RAHUL CHAUHAN\n";
                csv << "REPORT_GENERATED_BY,THE RAHUL CHAUHAN\n";

                // Auto open reports (cross-platform)
                openFile("subarray_report.txt");
                openFile("subarray_report.csv");

                cout << "Opening reports... 📂\nExiting... 👋\n";
                break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    txt.close();
    csv.close();
    return 0;
}
