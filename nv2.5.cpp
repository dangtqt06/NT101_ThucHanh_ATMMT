#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Chuẩn hóa dữ liệu: Chuyển về cùng một kiểu chữ in hoa và loại bỏ ký tự không phải alphabet
string normalize(const string& text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }
    return result;
}

// Sinh chuỗi khóa lặp lại có cùng độ dài với văn bản cần xử lý
string generateKeyStream(const string& text, const string& key) {
    string keyStream = "";
    string normKey = normalize(key);
    for (size_t i = 0, j = 0; i < text.length(); ++i) {
        keyStream += normKey[j % normKey.length()];
        j++;
    }
    return keyStream;
}

// Hàm mã hóa Vigenère
string encryptVigenere(const string& text, const string& key) {
    string normText = normalize(text);
    string keyStream = generateKeyStream(normText, key);
    string cipherText = "";

    for (size_t i = 0; i < normText.length(); ++i) {
        int p = normText[i] - 'A'; // Chuyển ký tự bản rõ thành số (0-25)
        int k = keyStream[i] - 'A'; // Chuyển ký tự khóa thành số (0-25)
        
        // Công thức mã hóa: C = (p + k) mod 26
        char c = (p + k) % 26 + 'A'; 
        cipherText += c;
    }
    return cipherText;
}

// Hàm giải mã Vigenère
string decryptVigenere(const string& text, const string& key) {
    string normText = normalize(text);
    string keyStream = generateKeyStream(normText, key);
    string plainText = "";

    for (size_t i = 0; i < normText.length(); ++i) {
        int c = normText[i] - 'A';
        int k = keyStream[i] - 'A';
        
        // Công thức giải mã: p = (C - k + 26) mod 26
        char p = (c - k + 26) % 26 + 'A'; 
        plainText += p;
    }
    return plainText;
}

int main() {
    cout << "=== CHUONG TRINH MA HOA / GIAI MA VIGENERE CIPHER ===\n";
    cout << "Chon che do (e: Ma hoa | d: Giai ma): ";
    char mode;
    cin >> mode;
    cin.ignore();

    cout << "Nhap khoa (Key): ";
    string key;
    getline(cin, key);

    cout << "Nhap van ban (Plaintext/Ciphertext): ";
    string text;
    getline(cin, text);

    if (mode == 'e' || mode == 'E') {
        cout << "\n=> Van ban ma hoa (Ciphertext): \n" << encryptVigenere(text, key) << "\n";
    } else if (mode == 'd' || mode == 'D') {
        cout << "\n=> Van ban giai ma (Plaintext): \n" << decryptVigenere(text, key) << "\n";
    } else {
        cout << "Che do khong hop le!\n";
    }

    return 0;
}