#include <iostream>
using namespace std;


int main() {
	setlocale(LC_ALL, "ru_RU");
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
			cout << "Ошибка! Введите число от 0 до 2.\n";
			continue;
		}
		switch (x) {
		case 1:
			cout << "Зашифрование..." << endl;
			break;

		case 2:
			cout << "Дешифрование..." << endl;
			break;

		case 0:
			cout << "Выход из программы." << endl;
			return 0;
			break;

		default:
			cout << "Неверная команда!" << endl;
		}
	}
	//проверка
	return 0;
}