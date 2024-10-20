#include <iostream>
#include <iomanip>
#include <algorithm>

// Шаблонный класс Vector для работы с одномерными массивами
template <typename T>
class Vector {
private:
    T* data;  // Указатель на динамический массив
    int size; // Размер массива

public:
    // Конструктор: выделяет память для массива
    Vector(int s) : size(s) {
        data = new T[size];
    }

    // Деструктор: освобождает выделенную память
    ~Vector() {
        delete[] data;
    }

    // Перегрузка оператора [] для доступа к элементам
    T& operator[](int index) {
        return data[index];
    }

    // Константная версия оператора []
    const T& operator[](int index) const {
        return data[index];
    }

    // Префиксный инкремент: увеличивает каждый элемент на 1
    Vector& operator++() {
        for (int i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    // Постфиксный инкремент
    Vector operator++(int) {
        Vector temp = *this;
        ++(*this);
        return temp;
    }

    // Префиксный декремент: уменьшает каждый элемент на 1
    Vector& operator--() {
        for (int i = 0; i < size; ++i) {
            --data[i];
        }
        return *this;
    }

    // Постфиксный декремент
    Vector operator--(int) {
        Vector temp = *this;
        --(*this);
        return temp;
    }

    // Геттер для размера массива
    int getSize() const {
        return size;
    }

    // Геттер для доступа к внутреннему массиву
    T* getData() {
        return data;
    }
};

// Шаблонный класс Matrix для работы с двумерными массивами
template <typename T>
class Matrix {
private:
    T** data; // Указатель на указатель для создания 2D массива
    int rows; // Количество строк
    int cols; // Количество столбцов

public:
    // Конструктор: выделяет память для 2D массива
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    // Деструктор: освобождает выделенную память
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Метод для получения значения элемента
    T at(int i, int j) const {
        return data[i][j];
    }

    // Метод для установки значения элемента
    void setAt(int i, int j, T val) {
        data[i][j] = val;
    }

    // Префиксный инкремент: увеличивает каждый элемент на 1
    Matrix& operator++() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ++data[i][j];
            }
        }
        return *this;
    }

    // Постфиксный инкремент
    Matrix operator++(int) {
        Matrix temp = *this;
        ++(*this);
        return temp;
    }

    // Префиксный декремент: уменьшает каждый элемент на 1
    Matrix& operator--() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                --data[i][j];
            }
        }
        return *this;
    }

    // Постфиксный декремент
    Matrix operator--(int) {
        Matrix temp = *this;
        --(*this);
        return temp;
    }

    // Геттеры для количества строк и столбцов
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

// Функция для инициализации вектора
void initializeArray(Vector<int>& vec) {
    for (int i = 0; i < vec.getSize(); ++i) {
        vec[i] = i * i + 1;
        if (i % 2 == 0) {
            vec[i] *= -1;
        }
    }
}

// Функция для вывода вектора
void printArray(const Vector<int>& vec) {
    for (int i = 0; i < vec.getSize(); ++i) {
        std::cout << std::setw(5) << vec[i];
        if ((i + 1) % 9 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Функция для преобразования вектора в матрицу
void transformArray(Vector<int>& vec1D, Matrix<int>& matrix2D) {
    // Сортировка вектора по убыванию
    std::sort(vec1D.getData(), vec1D.getData() + vec1D.getSize(), std::greater<int>());

    // Заполнение матрицы значениями из вектора
    for (int i = 0; i < matrix2D.getRows(); ++i) {
        for (int j = 0; j < matrix2D.getCols(); ++j) {
            matrix2D.setAt(i, j, vec1D[i * matrix2D.getCols() + j]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int size1D = 18;

    // Создание и инициализация вектора
    Vector<int> vec1D(size1D);
    initializeArray(vec1D);

    std::cout << "1D array:" << std::endl;
    printArray(vec1D);

    // Создание матрицы
    Matrix<int> matrix2D(9, 2);

    // Преобразование вектора в матрицу
    transformArray(vec1D, matrix2D);

    // Вывод матрицы
    std::cout << "2D array:" << std::endl;
    for (int i = 0; i < matrix2D.getRows(); ++i) {
        for (int j = 0; j < matrix2D.getCols(); ++j) {
            std::cout << std::setw(5) << matrix2D.at(i, j);
        }
        std::cout << std::endl;
    }

    return 0;
}