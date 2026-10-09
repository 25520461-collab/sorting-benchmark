// gen_data.cpp
// Sinh 10 bo du lieu, moi bo khoang 1 trieu so thuc:
//   - Bo 1: da sap xep TANG DAN
//   - Bo 2: da sap xep GIAM DAN
//   - Bo 3..10: thu tu NGAU NHIEN
//
// Cach dung: ./gen_data <N> <thu_muc_output>
// Vi du:     ./gen_data 1000000 ../data

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

static void writeArray(const string& path, const vector<double>& a) {
    ofstream fout(path);
    if (!fout) {
        cerr << "Khong mo duoc file de ghi: " << path << " (thu muc co ton tai khong?)\n";
        exit(1);
    }
    fout << fixed << setprecision(3);
    fout << a.size() << "\n";
    for (size_t i = 0; i < a.size(); i++) {
        fout << a[i];
        fout << (i + 1 < a.size() ? ' ' : '\n');
    }
}

int main(int argc, char** argv) {
    int n = (argc > 1) ? atoi(argv[1]) : 1000000;
    string outDir = (argc > 2) ? argv[2] : "../data";

    mt19937_64 rng(20261005);                 // seed co dinh -> tai hien duoc ket qua
    uniform_real_distribution<double> dist(0.0, 1000000.0);

    // --- Bo du lieu goc: n so thuc ngau nhien, dung lam nen cho moi bien the ---
    vector<double> base(n);
    for (int i = 0; i < n; i++) base[i] = dist(rng);

    // Bo 1: tang dan
    {
        vector<double> a = base;
        sort(a.begin(), a.end());
        writeArray(outDir + "/dataset_01_asc.txt", a);
        cout << "Da tao dataset_01_asc.txt (" << n << " phan tu, da sap xep tang dan)\n";
    }

    // Bo 2: giam dan
    {
        vector<double> a = base;
        sort(a.begin(), a.end(), greater<double>());
        writeArray(outDir + "/dataset_02_desc.txt", a);
        cout << "Da tao dataset_02_desc.txt (" << n << " phan tu, da sap xep giam dan)\n";
    }

    // Bo 3..10: ngau nhien, moi bo dung mt19937_64 voi seed khac nhau de khong giong nhau
    for (int k = 3; k <= 10; k++) {
        vector<double> a(n);
        mt19937_64 rngK(20261005 + k);
        uniform_real_distribution<double> distK(0.0, 1000000.0);
        for (int i = 0; i < n; i++) a[i] = distK(rngK);

        char name[64];
        snprintf(name, sizeof(name), "/dataset_%02d_random.txt", k);
        writeArray(outDir + name, a);
        cout << "Da tao dataset_" << setw(2) << setfill('0') << k
             << "_random.txt (" << n << " phan tu, ngau nhien)\n";
    }

    cout << "\nHoan tat sinh 10 bo du lieu tai thu muc: " << outDir << "\n";
    return 0;
}
