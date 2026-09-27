#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

char matrix[5][5];

// Hàm chuẩn hóa chuỗi: Chỉ giữ lại chữ cái, viết hoa và chuyển J thành I
string formatString(const string& str) {
    string res = "";
    for (char c : str) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }
    return res;
}

// Xây dựng ma trận Playfair 5x5 từ khóa
void buildMatrix(const string& key) {
    string formattedKey = formatString(key);
    bool used[26] = {false};
    used['J' - 'A'] = true; // Xem J như I nên đánh dấu là đã dùng

    int row = 0, col = 0;
    
    // Điền khóa vào ma trận
    for (char c : formattedKey) {
        if (!used[c - 'A']) {
            matrix[row][col] = c;
            used[c - 'A'] = true;
            col++;
            if (col == 5) { col = 0; row++; }
        }
    }
    
    // Điền các chữ cái còn lại trong bảng chữ cái
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            matrix[row][col] = c;
            used[c - 'A'] = true;
            col++;
            if (col == 5) { col = 0; row++; }
        }
    }
}

// Hiển thị ma trận 5x5 ra màn hình
void printMatrix() {
    cout << "\n[Ma tran Playfair 5x5]:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Tìm tọa độ (hàng, cột) của một ký tự trong ma trận
void findPosition(char c, int &row, int &col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; col = j;
                return;
            }
        }
    }
}

// Hàm mã hóa
string encrypt(const string& text) {
    string formatted = formatString(text);
    string prepared = "";
    
    // Tách cặp và chèn 'X' nếu có 2 ký tự giống nhau liên tiếp
    for (size_t i = 0; i < formatted.length(); i++) {
        prepared += formatted[i];
        if (i + 1 < formatted.length() && formatted[i] == formatted[i+1]) {
            prepared += 'X';
        }
    }
    // Nếu độ dài lẻ, chêm thêm 'X' vào cuối
    if (prepared.length() % 2 != 0) prepared += 'X';

    string result = "";
    for (size_t i = 0; i < prepared.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(prepared[i], r1, c1);
        findPosition(prepared[i+1], r2, c2);

        if (r1 == r2) { // Cùng hàng: Dịch phải
            result += matrix[r1][(c1 + 1) % 5];
            result += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Cùng cột: Dịch xuống
            result += matrix[(r1 + 1) % 5][c1];
            result += matrix[(r2 + 1) % 5][c2];
        } else { // Hình chữ nhật: Đổi góc
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

// Hàm giải mã
string decrypt(const string& text) {
    string formatted = formatString(text);
    string result = "";
    
    for (size_t i = 0; i < formatted.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(formatted[i], r1, c1);
        findPosition(formatted[i+1], r2, c2);

        if (r1 == r2) { // Cùng hàng: Dịch trái (+4 là tương đương -1 trong modulo 5)
            result += matrix[r1][(c1 + 4) % 5];
            result += matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) { // Cùng cột: Dịch lên
            result += matrix[(r1 + 4) % 5][c1];
            result += matrix[(r2 + 4) % 5][c2];
        } else { // Hình chữ nhật: Đổi góc
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

int main() {
    cout << "=== CHUONG TRINH MA HOA / GIAI MA PLAYFAIR CIPHER ===\n";
    cout << "Chon che do (e: Ma hoa | d: Giai ma): ";
    char mode;
    cin >> mode;
    cin.ignore();

    cout << "Nhap khoa (Key): ";
    string key;
    getline(cin, key);

    buildMatrix(key);
    printMatrix();

    cout << "Nhap van ban: ";
    string text;
    getline(cin, text);

    if (mode == 'e' || mode == 'E') {
        cout << "\n=> Van ban ma hoa (Ciphertext): \n" << encrypt(text) << "\n";
    } else if (mode == 'd' || mode == 'D') {
        cout << "\n=> Van ban giai ma (Plaintext): \n" << decrypt(text) << "\n";
    } else {
        cout << "Che do khong hop le!\n";
    }

    return 0;
}