#include "AirConditioner.h"
#include <iostream>
#include <memory>

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание двух кондиционеров в куче
    std::unique_ptr<AirConditioner> ac1 = std::make_unique<AirConditioner>("Samsung", "WindFree", 12.5, 2023);
    std::unique_ptr<AirConditioner> ac2 = std::make_unique<AirConditioner>("LG", "Artcool", 10.8, 2022);

    // Создание кондиционера в стеке
    AirConditioner ac3;
    ac3.setBrand("Daikin");
    ac3.setModel("Perfera");
    ac3.setWeight(9.5);
    ac3.setYear(2024);

    // Имитация настройки кондиционеров персоналом (3 раза)
    for (int i = 0; i < 3; ++i) {
        std::cout << "\nНастройка кондиционеров (итерация " << i + 1 << "):\n";

        // Настройка первого кондиционера
        ac1->setMode("Охлаждение");
        ac1->setTemperature(22.0 - i);  // Каждый раз немного холоднее

        // Настройка второго кондиционера
        ac2->setMode("Вентиляция");

        // Настройка третьего кондиционера
        if (i % 2 == 0) {
            ac3.setMode("Охлаждение");
            ac3.setTemperature(24.0 - i * 0.5);
        }
        else {
            ac3.setMode("Осушение");
        }
    }

    // Вывод информации об использовании кондиционеров
    std::cout << "\nИтоговая информация об использовании кондиционеров:\n";
    ac1->printInfo();
    std::cout << std::endl;
    ac2->printInfo();
    std::cout << std::endl;
    ac3.printInfo();

    // Демонстрация сериализации и десериализации
    ac1->serialize("ac1.dat");
    AirConditioner loadedAC;
    loadedAC.deserialize("ac1.dat");
    std::cout << "\nЗагруженный кондиционер из файла:\n";
    loadedAC.printInfo();

    return 0;
}