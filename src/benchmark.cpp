// benchmark.cpp
// Do thoi gian sap xep (chi tinh thoi gian SORT, khong tinh thoi gian doc file)
// cho 1 thuat toan tren 1 file du lieu.
//
// Cach dung: ./benchmark <quicksort|heapsort|mergesort|stdsort> <file_du_lieu>
// In ra: <thoi_gian_ms>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "sort_algorithms.h"
using namespace std;
using namespace std::chrono;

// Doc file du lieu vao a. Tra ve false neu mo file that bai hoac noi dung sai dinh dang.
static bool readArray(const string& path, vector<double>& a) {
    ifstream fin(path);
    if (!fin) return false;
    int n = 0;
    if (!(fin >> n) || n < 0) return false;
    a.resize(n);
    for (int i = 0; i < n; i++)
        if (!(fin >> a[i])) return false;
    return true;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Dung: " << argv[0] << " <quicksort|heapsort|mergesort|stdsort> <file>\n";
        return 1;
    }
    string algo = argv[1];
    string path = argv[2];

    vector<double> a;
    if (!readArray(path, a)) {            // doc file TRUOC, khong tinh vao thoi gian do
        cerr << "Khong doc duoc file du lieu hop le: " << path << "\n";
        return 3;
    }

    auto t0 = high_resolution_clock::now();

    if (algo == "quicksort")      QuickSort(a);
    else if (algo == "heapsort")  HeapSort(a);
    else if (algo == "mergesort") MergeSort(a);
    else if (algo == "stdsort")   sort(a.begin(), a.end());
    else { cerr << "Thuat toan khong hop le: " << algo << "\n"; return 1; }

    auto t1 = high_resolution_clock::now();
    double ms = duration<double, std::milli>(t1 - t0).count();

    // Kiem tra ket qua da sap xep dung chua (an toan / phat hien bug)
    bool ok = is_sorted(a.begin(), a.end());
    if (!ok) {
        cerr << "LOI: ket qua KHONG duoc sap xep dung cho thuat toan " << algo
             << " tren file " << path << "\n";
        return 2;
    }

    // In: ten_thuat_toan,ten_file,n,thoi_gian_ms
    cout << fixed << setprecision(3);
    cout << algo << "," << path << "," << a.size() << "," << ms << "\n";
    return 0;
}
