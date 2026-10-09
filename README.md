# So sánh thực nghiệm: Quicksort, Heapsort, Mergesort và std::sort

Bài tập thử nghiệm thời gian sắp xếp 4 cách sắp xếp (3 thuật toán tự cài đặt +
hàm `sort()` chuẩn của C++) trên 10 bộ dữ liệu số thực, mỗi bộ \~1.000.000 phần tử.

## Cấu trúc thư mục

```
.
├── src/                        Mã nguồn C++
│   ├── gen\_data.cpp             Sinh 10 bộ dữ liệu
│   ├── sort\_algorithms.h        Cài đặt QuickSort, HeapSort, MergeSort
│   ├── benchmark.cpp            Đo thời gian 1 thuật toán trên 1 file dữ liệu
├── data/                        10 bộ dữ liệu đã sinh (dataset\_01..10)
├── results/
│   ├── results.csv               Kết quả thô 
├── report/
│   ├── BaoCao\_KetQuaThuNghiem.docx
│   ├── BaoCao\_KetQuaThuNghiem.pdf
└── README.md
```

## Kết quả tóm tắt (thời gian trung bình trên 10 bộ dữ liệu, ms)

|Thuật toán|Thời gian TB (ms)|
|-|-|
|sort (C++)|59.9289|
|Quicksort (median-of-three)|56.6983|
|Mergesort|80.9313|
|Heapsort|125.3156|



