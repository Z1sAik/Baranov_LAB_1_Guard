#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <windows.h>
#include <codecvt>
using namespace std;

wchar_t vizner(wchar_t symbol, wchar_t key, bool decrypt) {
	int base, size;
	int symbol_index, key_index, new_symbol_index;

	if (symbol >= L'А' && symbol <= L'Я') {
		base = L'А'; size = 32; symbol_index = symbol - base;
	}
	else if (symbol >= L'а' && symbol <= L'я') {
		base = L'а'; size = 32; symbol_index = symbol - base;
	}
	else if (symbol >= L'A' && symbol <= L'Z') {
		base = L'A'; size = 26; symbol_index = symbol - base;
	}
	else if (symbol >= L'a' && symbol <= L'z') {
		base = L'a'; size = 26; symbol_index = symbol - base;
	}
	else {
		return symbol;
	}

	int key_base;
	if (key >= L'А' && key <= L'Я') {
		key_base = L'А';
	}
	else if (key >= L'а' && key <= L'я') {
		key_base = L'а';
	}
	else if (key >= L'A' && key <= L'Z') {
		key_base = L'A';
	}
	else if (key >= L'a' && key <= L'z') {
		key_base = L'a';
	}
	else {
		cout << "Ошибка: ключ должен содержать только буквы!" << endl;
		exit(1);
	}

	key_index = (key - key_base) % size;

	if (decrypt)
		new_symbol_index = (symbol_index - key_index + size) % size;
	else
		new_symbol_index = (symbol_index + key_index) % size;

	return wchar_t(base + new_symbol_index);
}


void encryptDecryptFile(bool decrypt) {

	cout << "Введите название файла [без расширения], в котором размещен текст:" << endl;
	wstring fileName;
	getline(wcin, fileName);

	wifstream fin(fileName + L".txt");
	fin.imbue(locale("en_US.UTF-8"));
	if (!fin.is_open()) {
		cout << "Такого файла не существует, введите имя корректно!" << endl;
		return;
	}

	cout << "Введите ключевое слово:" << endl;
	wstring key;
	getline(wcin, key);
	if (key.empty()) {
		cout << "Ключ не может быть пустым!" << endl;
		return;
	}

	string outFileName = decrypt ? "decryption.txt" : "encryption.txt";
	wofstream fout(outFileName);
	fout.imbue(locale("en_US.UTF-8"));;

	wchar_t ch;
	int i = 0;
	while (fin.get(ch)) {
		wchar_t newCh = vizner(ch, key[i % key.size()], decrypt);

		fout.put(newCh);

		if ((ch >= L'А' && ch <= L'Я') || (ch >= L'а' && ch <= L'я') || (ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z'))
		{
			i++;
		}
	}

	fin.close();
	fout.close();

	if (decrypt)
		cout << "Файл расшифрован успешно! Результаты в файле: decryption.txt" << endl;
	else
		cout << "Файл зашифрован успешно! Результаты в файле: encryption.txt" << endl;
}


int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	locale::global(locale(".1251"));
	wcin.imbue(locale());
	wcout.imbue(locale());

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
			break;

		default:
			cout << "Неверная команда!" << endl;
		}
	}

	return 0;
}