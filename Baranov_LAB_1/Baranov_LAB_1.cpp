#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

char vizner(char& symbol, char& key, bool& decrypt) {
	int new_symbol;
    if (decrypt) { 
        new_symbol = symbol - key;
    }
    else { 
        new_symbol = symbol + key;
    }
    while (new_symbol < 0) {
        new_symbol += 256;
	}
    while (new_symbol > 255) {
        new_symbol -= 256;
    }
	return char(new_symbol);
}


void encryptDecryptFile(bool decrypt) {
    cout << "Введите название файла [без расширения], в котором размещен текст:" << endl;
    string fileName;
    getline(cin, fileName);

    ifstream fin(fileName + ".txt", ios::binary);
    if (!fin.is_open()) {
        cout << "Такого файла не существует, введите имя корректно!" << endl;
        return;
    }

    cout << "Введите ключевое слово:" << endl;
    string key;
    getline(cin, key);
    if (key.empty()) {
        cout << "Ключ не может быть пустым!" << endl;
        return;
    }

    string outFileName = decrypt ? "decryption.txt" : "encryption.txt";
    ofstream fout(outFileName, ios::binary);

    char ch;
    int i = 0;
    while (fin.get(ch)) {
        fout << vizner(ch, key[i % key.size()], decrypt);
        i++;
    }

    fin.close();
    fout.close();

    if (decrypt) {
        cout << "Файл расшифрован успешно! Результаты в файле: decryption.txt" << endl;
    }
    else {
        cout << "Файл зашифрован успешно! Результаты в файле: encryption.txt" << endl;
    }
}


int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    while (true) {
        cout << "///////Главное меню///////" << endl;
        cout << "1) Зашифровать текст" << endl;
        cout << "2) Дешифровать текст" << endl;
        cout << "0) Выход" << endl;
        cout << "Введите нужную команду: ";

        int x;
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от 0 до 2." << endl;
            continue;
        }
        cin.ignore(10000, '\n');

        switch (x) {
        case 1:
            cout << "Зашифрование..." << endl;
            encryptDecryptFile(false);
            break;

        case 2:
            cout << "Дешифрование..." << endl;
            encryptDecryptFile(true);
            break;

        case 0:
            cout << "Выход из программы." << endl;
            return 0;

        default:
            cout << "Неверная команда!" << endl;
        }
    }

    return 0;
}
