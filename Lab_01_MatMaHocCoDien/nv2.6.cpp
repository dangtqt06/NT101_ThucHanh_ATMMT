#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

// Tần suất xuất hiện của các chữ cái trong tiếng Anh chuẩn
const double ENGLISH_FREQ[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 
    0.06966, 0.00015, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 
    0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 
    0.01974, 0.00074
};

// Chuẩn hóa: Chỉ giữ lại chữ cái và viết hoa
string normalize(const string& text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) result += toupper(c);
    }
    return result;
}

// Tính chỉ số trùng hợp (Index of Coincidence - IoC) của một chuỗi
double calculateIoC(const string& text) {
    int n = text.length();
    if (n <= 1) return 0.0;

    map<char, int> counts;
    for (char c : text) counts[c]++;

    double ioc = 0.0;
    for (auto const& [c, count] : counts) {
        ioc += count * (count - 1);
    }
    return ioc / (n * (n - 1));
}

// Tìm độ dài khóa tốt nhất dựa trên IoC trung bình của các cột
int findKeyLength(const string& text, int maxLen = 20) {
    int bestLen = 1;
    double bestIoC = 0.0;

    cout << "\n[Phan tich IoC de tim do dai khoa]:\n";
    for (int len = 1; len <= maxLen; ++len) {
        double avgIoC = 0.0;
        for (int i = 0; i < len; ++i) {
            string column = "";
            for (size_t j = i; j < text.length(); j += len) {
                column += text[j];
            }
            avgIoC += calculateIoC(column);
        }
        avgIoC /= len;

        // In ra một vài kết quả đầu tiên để xem quá trình
        if (len <= 10) {
            cout << "- Do dai " << len << ": IoC = " << fixed << setprecision(4) << avgIoC << "\n";
        }

        // Chọn độ dài có IoC cao nhất (gần 0.065 cua tieng Anh nhat)
        if (avgIoC > bestIoC) {
            bestIoC = avgIoC;
            bestLen = len;
        }
    }
    return bestLen;
}

// Hàm tính bình phương tối thiểu (Chi-squared) để so sánh tần suất
double chiSquared(const string& text) {
    int n = text.length();
    int counts[26] = {0};
    for (char c : text) counts[c - 'A']++;

    double chiSq = 0.0;
    for (int i = 0; i < 26; ++i) {
        double expected = n * ENGLISH_FREQ[i];
        if (expected > 0) {
            chiSq += pow(counts[i] - expected, 2) / expected;
        }
    }
    return chiSq;
}

// Tìm từng ký tự của khóa bằng phân tích tần suất
string findKey(const string& text, int keyLen) {
    string key = "";
    for (int i = 0; i < keyLen; ++i) {
        string column = "";
        for (size_t j = i; j < text.length(); j += keyLen) {
            column += text[j];
        }

        double minChiSq = 1e9;
        char bestChar = 'A';

        // Thử dịch 26 lần (giống phá mã Caesar cho từng cột)
        for (int shift = 0; shift < 26; ++shift) {
            string shiftedCol = "";
            for (char c : column) {
                shiftedCol += (c - 'A' - shift + 26) % 26 + 'A';
            }

            double chiSq = chiSquared(shiftedCol);
            if (chiSq < minChiSq) {
                minChiSq = chiSq;
                bestChar = shift + 'A';
            }
        }
        key += bestChar;
    }
    return key;
}

// Rút gọn khóa về chu kỳ lặp nhỏ nhất
// Vd: "HCMUITHCMUIT" (do dai 12) thuc chat chi la "HCMUIT" (do dai 6) lap lai 2 lan
// -> hai khoa nay tao ra cung mot keystream nen giai ma ra cung mot ket qua,
//    nhung khoa "that" (ngan nhat) moi la khoa nen bao cao
string reduceKey(const string& key) {
    int n = key.length();
    for (int d = 1; d < n; ++d) {
        if (n % d != 0) continue; // d phai la uoc cua n
        bool periodic = true;
        for (int i = d; i < n; ++i) {
            if (key[i] != key[i % d]) { periodic = false; break; }
        }
        if (periodic) return key.substr(0, d); // tim thay chu ky nho nhat
    }
    return key; // khong rut gon duoc, tra ve nguyen ban
}

// Giải mã Vigenere để hiển thị kết quả cuối cùng
string decryptVigenere(const string& text, const string& key) {
    string result = "";
    int keyLen = key.length();
    int keyIndex = 0;

    for (char c : text) {
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            char base = isUpper ? 'A' : 'a';
            int p = (toupper(c) - 'A' - (key[keyIndex % keyLen] - 'A') + 26) % 26;
            result += p + base;
            keyIndex++;
        } else {
            result += c; // Giữ nguyên khoảng trắng và dấu câu khi in kết quả
        }
    }
    return result;
}

// Đọc toàn bộ ciphertext từ một file văn bản
bool readFromFile(const string& path, string& outText) {
    ifstream file(path);
    if (!file.is_open()) return false;

    stringstream buffer;
    buffer << file.rdbuf();
    outText = buffer.str();
    return true;
}

// Đọc ciphertext trực tiếp từ bàn phím (nhấn Enter 2 lần để kết thúc)
string readFromKeyboard() {
    cout << "Nhap ciphertext (nhan Enter 2 lan de ket thuc):\n";
    string line, rawCiphertext = "";
    while (getline(cin, line) && !line.empty()) {
        rawCiphertext += line + " ";
    }
    return rawCiphertext;
}

int main() {
    cout << "=== CONG CU TU DONG PHA MA VIGENERE ===\n";
    cout << "Chon nguon du lieu:\n";
    cout << "  1. Nhap ciphertext truc tiep tu ban phim\n";
    cout << "  2. Doc ciphertext tu file\n";
    cout << "Lua chon (1/2): ";

    string choice;
    getline(cin, choice);

    string rawCiphertext;

    if (choice == "2") {
        cout << "Nhap duong dan file: ";
        string path;
        getline(cin, path);

        if (!readFromFile(path, rawCiphertext)) {
            cerr << "Khong the mo file: " << path << "\n";
            return 1;
        }
        cout << "Da doc file thanh cong.\n";
    } else {
        rawCiphertext = readFromKeyboard();
    }

    if (rawCiphertext.empty()) {
        cerr << "Ciphertext rong, khong co gi de xu ly.\n";
        return 0;
    }

    // Buoc 1: Chuan hoa
    string normText = normalize(rawCiphertext);
    cout << "\nSo ky tu alphabet sau chuan hoa: " << normText.length() << "\n";

    // Buoc 2: Uoc luong do dai khoa bang IoC
    int keyLen = findKeyLength(normText, 15); // thu tu 1 den 15
    cout << "\n=> Uoc luong do dai khoa (truoc rut gon): " << keyLen << "\n";

    // Buoc 3: Tim khoa bang phan tich tan suat tung nhom
    string foundKey = findKey(normText, keyLen);

    // Buoc 4: Rut gon khoa ve chu ky lap nho nhat (neu co)
    string reducedKey = reduceKey(foundKey);
    if (reducedKey != foundKey) {
        cout << "=> Khoa tim duoc (dang tho): " << foundKey << "\n";
        cout << "=> Khoa sau khi rut gon ve chu ky nho nhat: " << reducedKey << "\n";
    } else {
        cout << "=> Khoa (Key) tim duoc: " << foundKey << "\n";
    }

    // Buoc 5: Giai ma bang khoa da rut gon
    cout << "\n[Ban ro (Plaintext)]:\n";
    cout << decryptVigenere(rawCiphertext, reducedKey) << "\n";

    return 0;
}