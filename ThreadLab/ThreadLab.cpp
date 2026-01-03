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

    // 1. Ввод данных
    cout << "Введите размер массива: ";
    cin >> arraySize;
    if (arraySize <= 0) { cout << "Неверный размер"; return 0; }

    arrayPtr = new int[arraySize];
    cout << "Введите " << arraySize << " чисел: ";
    for (int i = 0; i < arraySize; i++) cin >> arrayPtr[i];

    // 2. Создание потоков

    
    HANDLE hMinMax = CreateThread(NULL, 0, MinMaxThread, NULL, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, AverageThread, NULL, 0, NULL);

    if (hMinMax == NULL || hAverage == NULL) {
        cout << "Ошибка при создании потоков!\n";
        return 1;
    }

    // 3. Синхронизация
    // WaitForSingleObject замораживает main, пока поток не подаст сигнал о завершении
    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    // Закрываем дескрипторы (освобождаем ресурсы системы)
    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    // 4. Модификация массива 
    int replacementValue = (int)averageResult;

    arrayPtr[minIndex] = replacementValue;
    arrayPtr[maxIndex] = replacementValue;

    // 5. Вывод итогового массива
    cout << "\nРезультаты обработки:\n";
    cout << "Минимум и максимум заменены на: " << replacementValue << endl;
    cout << "Итоговый массив: ";
    for (int i = 0; i < arraySize; i++) {
        cout << arrayPtr[i] << " ";
    }
    cout << endl;

    delete[] arrayPtr;
    return 0;
}