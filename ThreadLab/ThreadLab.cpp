#include <iostream>
#include <windows.h> 

using namespace std;


int* arrayPtr = nullptr;
int arraySize = 0;

int main() {
   
    setlocale(LC_ALL, "Russian");

    // 1. Ввод массива с консоли
    cout << "Введите размер массива: ";
    cin >> arraySize;

    if (arraySize <= 0) {
        cout << "Ошибка: размер массива должен быть больше 0.\n";
        return 1; // Завершаем с ошибкой
    }

    arrayPtr = new int[arraySize]; // Выделение памяти
    cout << "Введите " << arraySize << " целых чисел через пробел:\n";
    for (int i = 0; i < arraySize; i++) {
        cin >> arrayPtr[i];
    }

    cout << "\n[Debug]: Массив успешно создан.\n";

    // Здесь позже будет создание потоков

    delete[] arrayPtr; // Освобождение памяти
    return 0;
}