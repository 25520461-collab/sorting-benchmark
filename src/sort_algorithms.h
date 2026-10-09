// sort_algorithms.h
// Cai dat 3 thuat toan sap xep kinh dien de doi chung voi std::sort cua C++.
//
// LUU Y QUAN TRONG VE PIVOT CUA QUICKSORT:
// Ban "giao khoa" nguyen thuy (chon phan tu CUOI lam pivot, khong ngau nhien
// hoa) se SUY BIEN VE O(n^2) va GAY TRAN NGAN XEP (stack overflow) khi chay
// tren du lieu da sap xep san (dataset_01_asc, dataset_02_desc) voi n ~ 1
// trieu phan tu, vi do sau de quy se dat toi ~1 trieu. Day chinh la han che
// ly thuyet ma bo du lieu 1 va 2 duoc thiet ke de boc lo.
//
// De benchmark co the chay het tren ca 10 bo du lieu ma khong crash/treo may
// (va vi vay thu thap duoc so lieu thuc te de so sanh), cai dat duoi day
// dung PIVOT TRUNG VI CUA 3 (median-of-three: dau - giua - cuoi). Day la mot
// ky thuat chong suy bien TIEU CHUAN, van la "Quicksort" dung nghia, chi
// khac cach CHON pivot. Phan "Ly thuyet" trong tai lieu huong dan di kem co
// giai thich day du va mot thi nghiem rieng chung minh ban pivot-cuoi ngay
// tho bi suy bien nhu the nao.

#pragma once
#include <vector>
#include <algorithm>
#include <cstddef>
#include <utility>
using namespace std;

// ============================== QUICK SORT ==============================
namespace QS_detail {
    // Sap xep a[lo], a[mid], a[hi] sao cho a[lo] <= a[mid] <= a[hi], roi dua
    // gia tri TRUNG VI (median) do ve dung vi tri a[hi] de lam pivot theo
    // dung so do Lomuto chuan (pivot luon nam o CUOI doan dang xet).
    inline void medianOfThree(vector<double>& a, int lo, int hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < a[lo]) swap(a[lo], a[mid]);
        if (a[hi]  < a[lo]) swap(a[lo], a[hi]);
        if (a[hi]  < a[mid]) swap(a[mid], a[hi]);
        swap(a[mid], a[hi]);   // dua trung vi ve vi tri hi -> dung lam pivot
    }

    inline int partitionLomuto(vector<double>& a, int lo, int hi) {
        medianOfThree(a, lo, hi);
        double pivot = a[hi];
        int i = lo - 1;
        for (int j = lo; j < hi; j++) {
            if (a[j] < pivot) {
                i++;
                swap(a[i], a[j]);
            }
        }
        swap(a[i + 1], a[hi]);
        return i + 1;
    }

    // Dung STACK TUONG MINH (khong de quy ham) de loai bo hoan toan rui ro
    // tran ngan xep goi ham khi mang lon / phan hoach lech; dong thoi them
    // ky thuat "de quy duoi tren nhanh lon hon" (tail recursion elimination)
    // dam bao do sau stack luon O(log n).
    inline void quickSort(vector<double>& a, int lo, int hi) {
        vector<pair<int,int>> st;
        st.reserve(64);
        st.push_back({lo, hi});
        while (!st.empty()) {
            auto [l, h] = st.back();
            st.pop_back();
            while (l < h) {
                int p = partitionLomuto(a, l, h);
                // Day nua nho hon vao stack, tu xu ly tiep nua LON hon
                // (dam bao kich thuoc stack toi da la O(log n))
                if (p - l < h - p) {
                    st.push_back({l, p - 1});
                    l = p + 1;
                } else {
                    st.push_back({p + 1, h});
                    h = p - 1;
                }
            }
        }
    }
}

inline void QuickSort(vector<double>& a) {
    if (a.size() < 2) return;
    QS_detail::quickSort(a, 0, (int)a.size() - 1);
}

// ============================== HEAP SORT ==============================
namespace HS_detail {
    inline void siftDown(vector<double>& a, int n, int i) {
        while (true) {
            int largest = i, l = 2 * i + 1, r = 2 * i + 2;
            if (l < n && a[l] > a[largest]) largest = l;
            if (r < n && a[r] > a[largest]) largest = r;
            if (largest == i) break;
            swap(a[i], a[largest]);
            i = largest;
        }
    }
}

inline void HeapSort(vector<double>& a) {
    int n = (int)a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        HS_detail::siftDown(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        HS_detail::siftDown(a, i, 0);
    }
}

// ============================== MERGE SORT ==============================
namespace MS_detail {
    inline void mergeRuns(vector<double>& a, vector<double>& tmp, int lo, int mid, int hi) {
        int i = lo, j = mid + 1, k = lo;
        while (i <= mid && j <= hi)
            tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i <= mid) tmp[k++] = a[i++];
        while (j <= hi)  tmp[k++] = a[j++];
        for (k = lo; k <= hi; k++) a[k] = tmp[k];
    }

    inline void mergeSort(vector<double>& a, vector<double>& tmp, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        mergeSort(a, tmp, lo, mid);
        mergeSort(a, tmp, mid + 1, hi);
        mergeRuns(a, tmp, lo, mid, hi);
    }
}

inline void MergeSort(vector<double>& a) {
    if (a.size() < 2) return;
    vector<double> tmp(a.size());
    MS_detail::mergeSort(a, tmp, 0, (int)a.size() - 1);
}
