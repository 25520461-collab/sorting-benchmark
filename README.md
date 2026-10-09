# So sánh thực nghiệm: Quicksort vs Heapsort vs Mergesort vs std::sort

Bài tập thử nghiệm thời gian sắp xếp 4 cách sắp xếp (3 thuật toán tự cài đặt +
hàm `sort()` chuẩn của C++) trên 10 bộ dữ liệu số thực, mỗi bộ ~1.000.000 phần tử.

> Hướng dẫn: `docs/HUONG_DAN.html`. Giáo trình phân tích chi tiết từng dòng code và
> cách giải thích kết quả: `docs/GIAO_TRINH_PHAN_TICH.html` — mở bằng trình duyệt.
>
> **Lưu ý:** số liệu mẫu trong repo được đo trên một máy chủ Linux 1 nhân. Hãy chạy lại
> trên máy của bạn và khai báo đúng cấu hình máy trong báo cáo.

## Cấu trúc thư mục

```
.
├── src/                        Mã nguồn C++
│   ├── gen_data.cpp             Sinh 10 bộ dữ liệu
│   ├── sort_algorithms.h        Cài đặt QuickSort, HeapSort, MergeSort
│   ├── benchmark.cpp            Đo thời gian 1 thuật toán trên 1 file dữ liệu
│   ├── demo_naive_pivot.cpp     Thí nghiệm phụ: minh chứng QuickSort pivot-cuối suy biến
│   ├── extra_experiments.cpp    Thí nghiệm mở rộng: tăng trưởng theo n, Quicksort trên mảng toàn phần tử bằng nhau
│   └── make_report_assets.py    Tổng hợp results.csv -> bảng + biểu đồ
├── data/                        10 bộ dữ liệu đã sinh (dataset_01..10)
├── results/
│   ├── results.csv               Kết quả thô (40 dòng: thuật toán x dataset)
│   ├── summary_table.csv         Bảng tổng hợp theo đúng định dạng báo cáo
│   ├── repeat_runs.csv           Đo lặp 5 lần (bộ 1, 2, 3) để thấy nhiễu đo
│   └── extra_experiments.txt     Kết quả thí nghiệm mở rộng
├── report/
│   ├── BaoCao_KetQuaThuNghiem.docx
│   ├── BaoCao_KetQuaThuNghiem.pdf   ← file nộp bài
│   ├── chart.png
│   └── build_report.js
├── docs/
│   ├── HUONG_DAN.html            Hướng dẫn: môi trường, lý thuyết, GitHub từng bước
│   ├── GIAO_TRINH_PHAN_TICH.html Giáo trình phân tích từng dòng code, kết quả, phản biện, bài tập
│   └── QUY_TRINH_TUNG_BUOC.html  Quy trình bấm-gì-mở-gì: Visual Studio, Git, GitHub, báo cáo; lỗi LNK2005/LNK1169
└── README.md
```

## Cách chạy lại từ đầu

```bash
# 1. Bien dich
cd src
g++ -O2 -std=c++17 -o gen_data gen_data.cpp
g++ -O2 -std=c++17 -o benchmark benchmark.cpp

# 2. Sinh du lieu (1 trieu phan tu / bo, 10 bo)
./gen_data 1000000 ../data

# 3. Chay benchmark cho toan bo 10 dataset x 4 thuat toan
cd ..
echo "algorithm,dataset,n,time_ms" > results/results.csv
for f in data/dataset_*.txt; do
  for algo in quicksort heapsort mergesort stdsort; do
    ./src/benchmark "$algo" "$f" >> results/results.csv
  done
done

# 4. Tong hop bang + bieu do
python3 src/make_report_assets.py
```

## Kết quả tóm tắt (thời gian trung bình trên 10 bộ dữ liệu, ms)

| Thuật toán | Thời gian TB (ms) |
|---|---|
| sort (C++, introsort) | 68.79 |
| Quicksort (median-of-three) | 81.19 |
| Mergesort | 111.07 |
| Heapsort | 185.59 |

Chi tiết phân tích xem trong `report/BaoCao_KetQuaThuNghiem.pdf` và `docs/HUONG_DAN.html`.

## Môi trường thử nghiệm

- Biên dịch bằng `g++ 13.3`, cờ tối ưu `-O2 -std=c++17` (tương đương Release build trong Visual Studio).
- Đo thời gian bằng `std::chrono::high_resolution_clock`, chỉ tính thời gian sắp xếp (không tính thời gian đọc file).
