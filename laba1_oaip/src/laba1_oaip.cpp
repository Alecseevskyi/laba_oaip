#include <iostream>
using namespace std;

// Функция для сортировки массива пузырьком по убыванию
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                // Обмен элементов
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int n = 10;
    int arr[n];
    int sum = 0;
    int max;

    // Заполнение массива числами от пользователя
    cout << "Введите 10 целых чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> arr[i];
    }

    // Вывод элементов массива
    cout << "\nЭлементы первоначального массива: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Вычисление суммы элементов
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "Сумма всех элементов: " << sum << endl;

    // Поиск максимального элемента
    max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    cout << "Максимальный элемент: " << max << endl;

    // Вызов функции сортировки
    sort(arr, n);

    // Вывод отсортированного массива
    cout << "Массив после сортировки по убыванию: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
