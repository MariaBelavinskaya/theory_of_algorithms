#include <iostream>
#include <random>
using namespace std;

size_t GetSize();
void ArrayPrint(const int* myArray, size_t size);
int* FillRandomArray(size_t size, int minValue, int maxValue);

void qsortRecursive(int* Array, int size, int& counter2) {
    int i = 0;
    int j = size - 1;
    int mid = Array[size / 2];

    do {
        counter2 += 1;
        while (Array[i] < mid) {
            i++;
        }
        while (Array[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = Array[i];
            Array[i] = Array[j];
            Array[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) {
        counter2 += 1;
        qsortRecursive(Array, j + 1, counter2);
    }
    if (i < size) {
        counter2 += 1;
        qsortRecursive(&Array[i], size - i, counter2);
    }
}

void insertionSort(int* Array, size_t size, int& counter) {
    for (size_t i = 1; i < size; i++) {
        int key = Array[i];
        size_t j = i - 1;
        while (j >= 0 && Array[j] > key) {
            Array[j + 1] = Array[j];
            j--;
            counter++;
        }
        Array[j + 1] = key;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    size_t size = GetSize();

    if (size == 0)
        return 1;

    int* myArray = nullptr;
    auto minValue = -100;
    auto maxValue = 100;
    auto counter1 = 0;
    auto counter2 = 0;
    auto counter3 = 0.0;
    auto counter4 = 0.0;
    auto counter5 = 0.0;
    auto counter6 = 0.0;
    auto temprorary = 0;
    myArray = FillRandomArray(size, minValue, maxValue);

    for (int a = 0; a < 10; a++) {
        counter2 = 0;
        counter1 = 0;

        // Сортировка пузырьком
        for (int index = 0; index < size - 1; index++) {
            for (int j = 0; j < size - index - 1; j++) {
                counter1 += 1;
                if (myArray[j] > myArray[j + 1]) {
                    temprorary = myArray[j];
                    myArray[j] = myArray[j + 1];
                    myArray[j + 1] = temprorary;
                }
            }
        }
        counter3 += counter1;

        // Быстрая сортировка
        int* Array = FillRandomArray(size, minValue, maxValue);
        qsortRecursive(Array, size, counter2);
        counter4 += counter2;

        // Сортировка вставками
        int* ArrayForInsertion = FillRandomArray(size, minValue, maxValue);
        int counterInsertion = 0;
        insertionSort(ArrayForInsertion, size, counterInsertion);
        counter5 += counterInsertion;

        cout << "Результаты подсчётов " << a + 1 << " эксперимента: "
            << "Пузырьком: " << counter1 << ", "
            << "Быстрой сортировкой: " << counter2 << ", "
            << "Сортировкой вставками: " << counterInsertion << endl;

        delete[] Array;
        delete[] ArrayForInsertion;
    }
    cout << "Средние результаты: " << endl
        << "Пузырьком: " << counter3 / 10.0 << endl
        << "Быстрой сортировкой: " << counter4 / 10.0 << endl
        << "Сортировкой вставками: " << counter5 / 10.0 << endl;

    delete[] myArray;
    return 0;
}

size_t GetSize() {
    int size = 0;
    cout << "Введите размер массива" << endl;
    cin >> size;
    if (size <= 0) {
        cout << "Введён неверный размер";
        return 0;
    }
    else {
        return size;
    }
}

void ArrayPrint(const int* myArray, const size_t size) {
    if (myArray == nullptr) {
        cout << "Массива не существует";
    }
    else {
        cout << "\nМассив:\n";
        for (size_t index = 0; index < size; index++) {
            cout << myArray[index] << " ";
        }
        cout << "\n";
    }
}

int* FillRandomArray(const size_t size, const int minValue, const int maxValue) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> uniformIntDistribution(minValue, maxValue);
    auto* myArray = new int[size];

    for (size_t index = 0; index < size; index++) {
        myArray[index] = uniformIntDistribution(gen);
    }
    return myArray;
}