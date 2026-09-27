# Lab 01: Mật mã học cổ điển

## 1. Mục tiêu bài thực hành
- Hiểu và cài đặt được các hệ mật mã cổ điển: Caesar, Playfair, Vigenère và Affine.
- Nắm vững các điểm yếu của hệ mật mã thay thế (Substitution Ciphers).
- Áp dụng các kỹ thuật thám mã: Phân tích tần suất (Frequency Analysis), leo đồi (Hill Climbing), chỉ số trùng hợp (Index of Coincidence) và kiểm định Chi-bình phương (Chi-squared).

## 2. Nội dung chính & Cấu trúc mã nguồn
Các chương trình được viết bằng ngôn ngữ **C++** và chia thành các thư mục tương ứng với từng nhiệm vụ trong Lab:

- **Task 2.1 (Caesar Cipher):** Cài đặt thuật toán dịch vòng và xây dựng công cụ phá mã tự động (Brute-force) dựa trên từ điển tiếng Anh.
- **Task 2.3 (Mono-alphabetic Cipher):** Ứng dụng thuật toán Hill Climbing kết hợp dữ liệu N-gram để tự động giải mã. 
- **Task 2.4 (Playfair Cipher):** Xây dựng ma trận khóa 5x5, xử lý các quy tắc chia cặp (digraph) và chêm ký tự `X`.
- **Task 2.5 (Vigenère Cipher):** Cài đặt hệ mật đa bảng chữ cái, sinh dòng khóa (keystream) và mã hóa dựa trên công thức đại số.
- **Task 2.6 (Vigenère Cryptanalysis):** Công cụ tự động phá mã. Sử dụng **IoC** để đoán chiều dài khóa và **Chi-squared** để nội suy từng ký tự khóa.
- **Task 2.7 (Affine Cipher - Mở rộng):** Cài đặt hệ mật Affine. Viết hàm tìm ước chung lớn nhất (GCD) và nghịch đảo modulo.

## 3. Hướng dẫn biên dịch và chạy chương trình

Yêu cầu hệ thống: Đã cài đặt trình biên dịch C++ (GCC/Clang trên macOS).

**Bước 1:** Mở Terminal và di chuyển (cd) vào thư mục chứa code cần chạy.
**Bước 2:** Biên dịch mã nguồn bằng g++. Ví dụ với file bài 2.4:
`g++ nv2.4.cpp -o nv2.4`
**Bước 3:** Chạy file thực thi:
`./nv2.4`
**Bước 4:** Làm theo các chỉ dẫn hiển thị trên giao diện console. Để kết thúc nhập đối với các đoạn ciphertext dài (Nhiệm vụ 2.3, 2.6), hãy nhấn `Enter` 2 lần.