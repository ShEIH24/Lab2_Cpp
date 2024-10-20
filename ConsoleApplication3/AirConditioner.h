#ifndef AIR_CONDITIONER_H
#define AIR_CONDITIONER_H

#include <string>
#include <fstream>
#include <iostream>

class AirConditioner {
private:
    std::string brand;
    std::string model;
    double weight;
    double temperature;
    std::string mode;
    int year;
    double totalTempChange;
    int settingsCount;

public:
    // Конструктор без параметров
    AirConditioner();

    // Конструктор с параметрами
    AirConditioner(const std::string& brand, const std::string& model, double weight, int year);

    // Геттеры
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    double getWeight() const { return weight; }
    double getTemperature() const { return temperature; }
    std::string getMode() const { return mode; }
    int getYear() const { return year; }

    // Сеттеры
    void setBrand(const std::string& brand) { this->brand = brand; }
    void setModel(const std::string& model) { this->model = model; }
    void setWeight(double weight) { this->weight = weight; }
    void setYear(int year) { this->year = year; }

    // Методы для настройки кондиционера
    void setMode(const std::string& mode);
    void setTemperature(double temperature);

    // Метод для получения среднего изменения температуры
    double getAverageTemperatureChange() const;

    // Методы сериализации и десериализации
    void serialize() const;
    void deserialize();
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);

    // Метод для вывода информации о кондиционере
    void printInfo() const;
};

#endif // AIR_CONDITIONER_H