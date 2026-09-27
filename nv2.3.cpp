#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

// Bảng điểm N-gram (Bigram và Trigram phổ biến trong tiếng Anh)
map<string, double> NGRAM_SCORES = {
    {"TH", 3.0}, {"HE", 2.9}, {"IN", 2.8}, {"ER", 2.7}, {"AN", 2.6}, {"RE", 2.5}, {"ND", 2.4},
    {"THE", 5.0}, {"AND", 4.9}, {"ING", 4.8}, {"ENT", 4.7}, {"ION", 4.6}, {"HER", 4.5},
    {"FOR", 4.4}, {"THA", 4.3}, {"NTH", 4.2}, {"INT", 4.1}, {"ERE", 4.0}, {"TIO", 3.9}
};

double calculateFitness(const string& text) {
    double score = 0.0;
    for (size_t i = 0; i + 1 < text.length(); ++i) {
        string bigram = text.substr(i, 2);
        if (NGRAM_SCORES.count(bigram)) score += NGRAM_SCORES[bigram];
    }
    for (size_t i = 0; i + 2 < text.length(); ++i) {
        string trigram = text.substr(i, 3);
        if (NGRAM_SCORES.count(trigram)) score += NGRAM_SCORES[trigram];
    }
    return score;
}

string decryptWithKey(const string& ciphertext, const string& key) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            int index = toupper(c) - 'A';
            char decryptedChar = key[index];
            plaintext += isUpper ? decryptedChar : tolower(decryptedChar);
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

string filterCiphertext(const string& text) {
    string filtered = "";
    for (char c : text) {
        if (isalpha(c)) filtered += toupper(c);
    }
    return filtered;
}

void autoDecrypt(const string& originalCiphertext, int restarts = 20, int maxIterations = 2000) {
    string filteredCipher = filterCiphertext(originalCiphertext);
    
    // Nếu văn bản quá ngắn, cảnh báo người dùng
    if (filteredCipher.length() < 30) {
        cout << "\n[Canh bao]: Van ban qua ngan. Phuong phap thong ke co the khong hoat dong chinh xac!\n";
    }
    
    random_device rd;
    mt19937 gen(rd());
    
    double overallBestScore = -1.0;
    string overallBestKey = "";
    string overallBestPlaintext = "";
    
    cout << "\nDang phan tich tu dong (" << restarts << " vong Random Restart, moi vong " << maxIterations << " buoc)...\n";
    
    for (int r = 0; r < restarts; ++r) {
        string currentKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        shuffle(currentKey.begin(), currentKey.end(), gen);
        
        string currentDecrypted = decryptWithKey(filteredCipher, currentKey);
        double currentScore = calculateFitness(currentDecrypted);
        
        for (int i = 0; i < maxIterations; ++i) {
            string testKey = currentKey;
            
            int idx1 = uniform_int_distribution<>(0, 25)(gen);
            int idx2 = uniform_int_distribution<>(0, 25)(gen);
            swap(testKey[idx1], testKey[idx2]);
            
            string testDecrypted = decryptWithKey(filteredCipher, testKey);
            double testScore = calculateFitness(testDecrypted);
            
            if (testScore > currentScore) {
                currentScore = testScore;
                currentKey = testKey;
            }
        }
        
        if (currentScore > overallBestScore) {
            overallBestScore = currentScore;
            overallBestKey = currentKey;
            overallBestPlaintext = decryptWithKey(originalCiphertext, overallBestKey);
        }
    }
    
    cout << "\n=== KET QUA TOT NHAT THU DUOC ===\n";
    cout << "Diem ngon ngu (Fitness Score): " << overallBestScore << "\n";
    cout << "\n[Bang khoa anh xa - Cipher -> Plain]:\n";
    for (int i = 0; i < 26; ++i) {
        cout << (char)('A' + i) << "->" << overallBestKey[i] << " | ";
    }
    cout << "\n\n[Ban ro (Plaintext)]:\n" << overallBestPlaintext << "\n\n";
}

int main() {
    cout << "=== CONG CU GIAI MA MONO-ALPHABETIC TU DONG ===\n";
    cout << "Huong dan: Copy va dan ciphertext vao day. Ban co the dan nhieu dong.\n";
    cout << "DE KET THUC NHAP: Hay nhan Enter 2 lan (nhap mot dong trong).\n";
    cout << "--------------------------------------------------\n";
    
    string line;
    string ciphertext = "";
    
    while (getline(cin, line) && !line.empty()) {
        ciphertext += line + "\n";
    }
    
    if (ciphertext.empty()) {
        cout << "Ban chua nhap gi ca. Ket thuc chuong trinh.\n";
        return 0;
    }
    
    // Chạy thuật toán với thông số lớn một chút để tăng tỷ lệ chính xác
    autoDecrypt(ciphertext, 40, 4000);
    
    return 0;
}