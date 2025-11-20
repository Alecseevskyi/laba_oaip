#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Структура для хранения данных о книге
struct Book {
    string title;
    string author;
    int year;
};

// Функция для добавления тестовых книг (как в документе - создание и заполнение)
void addSampleBooks() {
    ofstream outFile("books.txt");

    if (!outFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    // Добавляем тестовые книги используя оператор << как в документе
    outFile << "Война и мир" << endl;
    outFile << "Лев Толстой" << endl;
    outFile << 1869 << endl;

    outFile << "Преступление и наказание" << endl;
    outFile << "Федор Достоевский" << endl;
    outFile << 1866 << endl;

    outFile << "Мастер и Маргарита" << endl;
    outFile << "Михаил Булгаков" << endl;
    outFile << 1967 << endl;

    outFile << "1984" << endl;
    outFile << "Джордж Оруэлл" << endl;
    outFile << 1949 << endl;

    outFile.close();
    cout << "Тестовые книги добавлены в файл books.txt" << endl;
}

// Функция для чтения всех книг из файла (как в документе - использование >> и getline)
vector<Book> readBooksFromFile() {
    vector<Book> books;
    ifstream inFile("books.txt");

    if (!inFile.is_open()) {
        cerr << "File not found." << endl;
        return books;
    }

    Book book;
    string line;
    while (getline(inFile, book.title)) {
        if (book.title.empty()) continue;

        getline(inFile, book.author);
        inFile >> book.year;
        inFile.ignore(); // Игнорируем символ новой строки после числа

        books.push_back(book);
    }

    inFile.close();
    return books;
}

// Функция для добавления книги в файл (как в документе - открытие в режиме добавления)
void addBookToFile() {
    ofstream outFile("books.txt", ios::app);

    if (!outFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    Book book;
    cout << "Введите данные о книге (пустое название для завершения):" << endl;

    while (true) {
        cout << "Название книги: ";
        getline(cin, book.title);

        if (book.title.empty()) {
            break;
        }

        cout << "Автор: ";
        getline(cin, book.author);

        cout << "Год издания: ";
        cin >> book.year;
        cin.ignore();

        // Записываем книгу в файл используя оператор << как в документе
        outFile << book.title << endl;
        outFile << book.author << endl;
        outFile << book.year << endl;

        cout << "Книга добавлена успешно!" << endl << endl;
    }

    outFile.close();
}

// Функция для поиска книги по названию
void searchBook() {
    ifstream inFile("books.txt");

    if (!inFile.is_open()) {
        cerr << "File not found." << endl;
        return;
    }

    string searchTitle;
    cout << "Введите название книги для поиска: ";
    getline(cin, searchTitle);

    ofstream outLog("output.txt", ios::app);
    outLog << "=== РЕЗУЛЬТАТЫ ПОИСКА ===" << endl;
    outLog << "Поиск: " << searchTitle << endl;

    Book book;
    bool found = false;

    while (getline(inFile, book.title)) {
        getline(inFile, book.author);
        inFile >> book.year;
        inFile.ignore();

        if (book.title.find(searchTitle) != string::npos) {
            cout << "Найдена книга: " << book.title << ", "
                << book.author << ", " << book.year << endl;
            outLog << "Найдена: " << book.title << ", "
                << book.author << ", " << book.year << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книга с названием \"" << searchTitle << "\" не найдена." << endl;
        outLog << "Не найдено." << endl;
    }

    outLog << "=======================" << endl << endl;
    outLog.close();
    inFile.close();
}

// Функция для сортировки книг
void sortBooks() {
    vector<Book> books = readBooksFromFile();

    if (books.empty()) {
        cout << "Файл пуст или не существует!" << endl;
        return;
    }

    int choice;
    cout << "Выберите критерий сортировки:" << endl;
    cout << "1 - По автору" << endl;
    cout << "2 - По году издания" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore();

    ofstream outLog("output.txt", ios::app);
    outLog << "=== РЕЗУЛЬТАТЫ СОРТИРОВКИ ===" << endl;

    if (choice == 1) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.author < b.author;
            });
        cout << "Книги отсортированы по автору." << endl;
        outLog << "Сортировка по автору:" << endl;
    }
    else if (choice == 2) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.year < b.year;
            });
        cout << "Книги отсортированы по году издания." << endl;
        outLog << "Сортировка по году:" << endl;
    }
    else {
        cout << "Неверный выбор!" << endl;
        outLog.close();
        return;
    }

    // Записываем отсортированные данные обратно в файл
    ofstream outFile("books.txt");
    if (!outFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    // Вывод отсортированного списка
    cout << endl << "Отсортированный список:" << endl;
    for (const auto& book : books) {
        cout << book.title << ", " << book.author << ", " << book.year << endl;
        outLog << book.title << ", " << book.author << ", " << book.year << endl;

        // Записываем в файл используя оператор <<
        outFile << book.title << endl;
        outFile << book.author << endl;
        outFile << book.year << endl;
    }

    outFile.close();
    outLog << "========================" << endl << endl;
    outLog.close();
}

// Функция для вывода книг по году (как в документе - вывод определенных данных по запросу)
void showBooksByYear() {
    ifstream inFile("books.txt");

    if (!inFile.is_open()) {
        cerr << "File not found." << endl;
        return;
    }

    int maxYear;
    cout << "Введите максимальный год издания: ";
    cin >> maxYear;
    cin.ignore();

    ofstream outLog("output.txt", ios::app);
    outLog << "=== КНИГИ ДО " << maxYear << " ГОДА ===" << endl;

    Book book;
    bool found = false;
    cout << endl << "Книги изданные до " << maxYear << " года:" << endl;

    while (getline(inFile, book.title)) {
        getline(inFile, book.author);
        inFile >> book.year;
        inFile.ignore();

        if (book.year <= maxYear) {
            cout << book.title << ", " << book.author << ", " << book.year << endl;
            outLog << book.title << ", " << book.author << ", " << book.year << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книг, изданных до " << maxYear << " года, не найдено." << endl;
        outLog << "Не найдено." << endl;
    }

    outLog << "========================" << endl << endl;
    outLog.close();
    inFile.close();
}

// Функция для вывода всех книг
void displayAllBooks() {
    ifstream inFile("books.txt");

    if (!inFile.is_open()) {
        cerr << "File not found." << endl;
        return;
    }

    ofstream outLog("output.txt", ios::app);
    outLog << "=== ВСЕ КНИГИ ===" << endl;

    Book book;
    cout << "Список всех книг:" << endl;

    while (getline(inFile, book.title)) {
        getline(inFile, book.author);
        inFile >> book.year;
        inFile.ignore();

        cout << book.title << ", " << book.author << ", " << book.year << endl;
        outLog << book.title << ", " << book.author << ", " << book.year << endl;
    }

    outLog << "=================" << endl << endl;
    outLog.close();
    inFile.close();
}

// Основное меню программы (как в документе - использование do-while и switch-case)
void showMenu() {
    cout << "=== МЕНЮ УПРАВЛЕНИЯ БИБЛИОТЕКОЙ ===" << endl;
    cout << "1 - Добавить книгу" << endl;
    cout << "2 - Поиск книги по названию" << endl;
    cout << "3 - Сортировка книг" << endl;
    cout << "4 - Показать книги по году" << endl;
    cout << "5 - Показать все книги" << endl;
    cout << "6 - Добавить тестовые книги" << endl;
    cout << "0 - Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    int choice;

    // Очищаем файл output.txt при запуске программы
    ofstream clearFile("output.txt");
    if (clearFile.is_open()) {
        clearFile.close();
    }

    cout << "Добро пожаловать в систему управления библиотекой!" << endl;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addBookToFile();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            sortBooks();
            break;
        case 4:
            showBooksByYear();
            break;
        case 5:
            displayAllBooks();
            break;
        case 6:
            addSampleBooks();
            break;
        case 0:
            cout << "Программа завершена. Результаты сохранены в output.txt" << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        cout << endl;

    } while (choice != 0);

    return 0;
}
