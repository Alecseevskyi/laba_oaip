#include <iostream>
#include <cctype>

using namespace std;

int main() {
    char input[500]; // Буфер для ввода строки
    cout << "Введите 10 слов на латинице: ";
    cin.getline(input, 500); // Считываем всю строку

    // Объявляем счетчики для всех задач
    int count_a = 0;        // Счетчик слов на 'a'
    int min_len = 1000;     // Минимальная длина слова (инициализируем большим значением)
    int count_b = 0;        // Счетчик букв 'b' во втором слове
    int count_match = 0;    // Счетчик слов с одинаковыми первым и последним символами

    // Переменные для обработки слов
    int word_count = 0;     // Счетчик слов
    int word_start = 0;     // Начальная позиция текущего слова в строке
    int word_len = 0;       // Длина текущего слова
    char current_word[50];  // Буфер для текущего слова

    // Основной цикл обработки строки
    for (int i = 0; input[i] != '\0'; i++) {
        // Если найден пробел или конец строки - заканчиваем текущее слово
        if (input[i] == ' ' || input[i] == '\0') {
            if (word_len > 0) { // Проверяем, что слово не пустое
                word_count++;   // Увеличиваем счетчик слов

                // Копируем текущее слово в отдельный буфер
                for (int j = 0; j < word_len; j++) {
                    current_word[j] = input[word_start + j];
                }
                current_word[word_len] = '\0'; // Добавляем нулевой терминатор

                // ЗАДАНИЕ 1: Проверяем, оканчивается ли слово на 'a' или 'A'
                if (current_word[word_len - 1] == 'a' || current_word[word_len - 1] == 'A') {
                    count_a++;
                }

                // ЗАДАНИЕ 2: Обновляем минимальную длину слова
                if (word_len < min_len) {
                    min_len = word_len;
                }

                // ЗАДАНИЕ 3: Считаем буквы 'b' во втором слове
                if (word_count == 2) {
                    for (int k = 0; k < word_len; k++) {
                        if (current_word[k] == 'b' || current_word[k] == 'B') {
                            count_b++;
                        }
                    }
                }

                // ЗАДАНИЕ 5: Проверяем совпадение первого и последнего символа
                if (current_word[0] == current_word[word_len - 1]) {
                    count_match++;
                }

                // ЗАДАНИЕ 4: Преобразуем слово к нижнему регистру в исходной строке
                for (int j = word_start; j < word_start + word_len; j++) {
                    input[j] = tolower(input[j]);
                }

                // Сбрасываем параметры для следующего слова
                word_len = 0;
                word_start = i + 1; // Начало следующего слова после пробела
            }
        }
        else {
            word_len++; // Увеличиваем длину текущего слова
        }
    }

    // Обрабатываем последнее слово в строке (после последнего пробела)
    if (word_len > 0) {
        word_count++;

        // Копируем последнее слово
        for (int j = 0; j < word_len; j++) {
            current_word[j] = input[word_start + j];
        }
        current_word[word_len] = '\0';

        // Повторяем все проверки для последнего слова
        if (current_word[word_len - 1] == 'a' || current_word[word_len - 1] == 'A') {
            count_a++;
        }

        if (word_len < min_len) {
            min_len = word_len;
        }

        if (current_word[0] == current_word[word_len - 1]) {
            count_match++;
        }

        // Преобразуем последнее слово к нижнему регистру
        for (int j = word_start; j < word_start + word_len; j++) {
            input[j] = tolower(input[j]);
        }
    }

    // Проверяем, что пользователь ввел ровно 10 слов
    if (word_count != 10) {
        cout << "Ошибка: нужно ввести ровно 10 слов! Введено: " << word_count << endl;
        return 1; // Завершаем программу с ошибкой
    }

    // Выводим результаты всех заданий
    cout << "Слова заканчивающиеся на 'a': " << count_a << endl;
    cout << "Длина самого короткого слова: " << min_len << endl;
    cout << "Букв 'b' во втором слове: " << count_b << endl;
    cout << "Строка в нижнем регистре: " << input << endl;
    cout << "Слова с одинаковыми первым и последним символом: " << count_match << endl;

    // ЗАДАНИЕ 6: Поиск самой короткой общей подстроки
    // Упрощенный вариант - ищем хотя бы одну общую букву во всех словах
    char common_char = '\0'; // Переменная для хранения найденной общей буквы

    // Перебираем все буквы алфавита от 'a' до 'z'
    for (char c = 'a'; c <= 'z'; c++) {
        bool found_in_all = true; // Флаг, указывающий что буква есть во всех словах
        int word_idx = 0;         // Индекс текущего слова
        int char_idx = 0;         // Счетчик найденных букв в текущем слове

        // Проверяем наличие буквы c во всех словах
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ' ') { // При переходе к следующему слову
                if (char_idx == 0) { // Если в предыдущем слове не нашли букву c
                    found_in_all = false;
                    break;
                }
                word_idx++;
                char_idx = 0; // Сбрасываем счетчик для нового слова
            }
            else if (input[i] == c) { // Если нашли нужную букву
                char_idx++;
            }
        }

        // Проверяем последнее слово
        if (char_idx == 0) {
            found_in_all = false;
        }

        // Если буква найдена во всех словах - сохраняем ее и выходим из цикла
        if (found_in_all) {
            common_char = c;
            break;
        }
    }

    // Выводим результат поиска общей подстроки
    if (common_char != '\0') {
        cout << "Общая подстрока (буква): " << common_char << endl;
    }
    else {
        cout << "Общая подстрока не найдена" << endl;
    }

    return 0; // Успешное завершение программы
}