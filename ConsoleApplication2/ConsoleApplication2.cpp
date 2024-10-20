#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip> 
#include <limits>

class Fraction {
private:
    int numerator;   // Числитель дроби
    int denominator; // Знаменатель дроби
    static int instanceCount; // Статический счетчик созданных экземпляров

    // Статический метод для нахождения наибольшего общего делителя (НОД)
    static int gcd(int n, int m) {
        return m == 0 ? n : gcd(m, n % m);
    }

public:
    // Конструктор с параметрами по умолчанию
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        reduce(); // Сокращаем дробь при создании
        instanceCount++; // Увеличиваем счетчик экземпляров
    }

    // Деструктор
    ~Fraction() {
        instanceCount--; // Уменьшаем счетчик экземпляров при удалении объекта
    }

    // Метод для сокращения дроби
    void reduce() {
        int common = gcd(std::abs(numerator), std::abs(denominator));
        numerator /= common;
        denominator /= common;
        // Обеспечиваем, чтобы знак был у числителя, а знаменатель всегда положительный
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // Перегрузка оператора сложения
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator);
    }

    // Перегрузка оператора вычитания
    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
            denominator * other.denominator);
    }

    // Перегрузка оператора умножения
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    // Перегрузка оператора деления
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::runtime_error("Деление на ноль");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }

    // Статический метод для вывода десятичной дроби в виде обыкновенной (версия для double)
    static void printAsFraction(double decimal_fraction) {
        const long long PRECISION = 100; // 9 decimal places of precision
        long long integral = std::floor(decimal_fraction);
        long long fractional = std::round((decimal_fraction - integral) * PRECISION);

        Fraction result(integral * PRECISION + fractional, PRECISION);
        result.reduce();

        std::cout << std::fixed << std::setprecision(9) << decimal_fraction
            << " в виде обыкновенной дроби: " << result << std::endl;
    }

    // Исправленный метод printAsFraction для строки
    static void printAsFraction(const char* decimal_fraction) {
        double value = std::stod(decimal_fraction);
        printAsFraction(value);
    }

    static int getInstanceCount() {
        return instanceCount;
    }
};

int Fraction::instanceCount = 0;

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание объектов класса Fraction
    Fraction f1(1, 2);
    Fraction f2(3, 4);

    // Вывод созданных дробей
    std::cout << "f1 = " << f1 << std::endl;
    std::cout << "f2 = " << f2 << std::endl;

    // Демонстрация арифметических операций
    std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
    std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
    std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
    std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;

    // Вывод количества созданных экземпляров
    std::cout << "Количество созданных экземпляров Fraction: " << Fraction::getInstanceCount() << std::endl;

    // Демонстрация работы статических методов printAsFraction
    Fraction::printAsFraction(0.25);
    Fraction::printAsFraction(0.50);

    return 0;
}