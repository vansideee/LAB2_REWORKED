#include <iostream>
#include <windows.h> 

using namespace std;


int* arrayPtr = nullptr;
int arraySize = 0;


int minResult = 0;
int maxResult = 0;

int minIndex = 0;
int maxIndex = 0;

// Поток 1: Поиск минимума и максимума
// Требование: спать 7 мс после каждого сравнения
DWORD WINAPI MinMaxThread(LPVOID lpParam) {
    
    minResult = arrayPtr[0];
    maxResult = arrayPtr[0];
    minIndex = 0;
    maxIndex = 0;

    for (int i = 1; i < arraySize; i++) {
        // Поиск максимума
        if (arrayPtr[i] > maxResult) {
            maxResult = arrayPtr[i];
            maxIndex = i;
        }
        Sleep(7);

        // Поиск минимума
        if (arrayPtr[i] < minResult) {
            minResult = arrayPtr[i];
            minIndex = i;
        }
        Sleep(7); 
    }

    cout << "Поток Min_Max завершил работу. Min: " << minResult << ", Max: " << maxResult << endl;
    return 0;


}


double averageResult = 0.0;

// Поток 2: Поиск среднего значения
// Требование: спать 12 мс после каждой операции суммирования
DWORD WINAPI AverageThread(LPVOID lpParam) {
    double sum = 0;

    for (int i = 0; i < arraySize; i++) {
        sum += arrayPtr[i];
        Sleep(12); 
    }

    averageResult = sum / arraySize;
    cout << "Поток Average завершил работу. Среднее: " << averageResult << endl;
    return 0;
}

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

    

    delete[] arrayPtr; 
    return 0;
}