#include "AirConditioner.h"
#include <iostream>
#include <fstream>
#include <cmath>

// ����������� ��� ����������
AirConditioner::AirConditioner() : weight(0), temperature(0), year(0), totalTempChange(0), settingsCount(0) {}

// ����������� � �����������
AirConditioner::AirConditioner(const std::string& brand, const std::string& model, double weight, int year)
    : brand(brand), model(model), weight(weight), year(year), temperature(0), totalTempChange(0), settingsCount(0) {}

// ����� ��������� ������
void AirConditioner::setMode(const std::string& mode) {
    this->mode = mode;
    std::cout << "����� ������������ " << brand << " " << model << " ���������� ��: " << mode << std::endl;
}

// ����� ��������� �����������
void AirConditioner::setTemperature(double temperature) {
    double tempChange = temperature - this->temperature;
    this->temperature = temperature;
    totalTempChange += std::abs(tempChange);
    settingsCount++;
    std::cout << "����������� ������������ " << brand << " " << model << " ����������� ��: " << temperature << "�C" << std::endl;
}

// ����� ��������� �������� ��������� �����������
double AirConditioner::getAverageTemperatureChange() const {
    return settingsCount > 0 ? totalTempChange / settingsCount : 0;
}

// ����� ������������ (��� ����������)
void AirConditioner::serialize() const {
    serialize("air_conditioner.dat");
}

// ����� �������������� (��� ����������)
void AirConditioner::deserialize() {
    deserialize("air_conditioner.dat");
}

// ����� ������������ (� ���������� ����� �����)
void AirConditioner::serialize(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        size_t brandSize = brand.size();
        size_t modelSize = model.size();
        size_t modeSize = mode.size();

        file.write(reinterpret_cast<const char*>(&brandSize), sizeof(size_t));
        file.write(brand.c_str(), brandSize);
        file.write(reinterpret_cast<const char*>(&modelSize), sizeof(size_t));
        file.write(model.c_str(), modelSize);
        file.write(reinterpret_cast<const char*>(&weight), sizeof(double));
        file.write(reinterpret_cast<const char*>(&temperature), sizeof(double));
        file.write(reinterpret_cast<const char*>(&modeSize), sizeof(size_t));
        file.write(mode.c_str(), modeSize);
        file.write(reinterpret_cast<const char*>(&year), sizeof(int));
        file.write(reinterpret_cast<const char*>(&totalTempChange), sizeof(double));
        file.write(reinterpret_cast<const char*>(&settingsCount), sizeof(int));

        std::cout << "������ ������������ ��������� � ����: " << filename << std::endl;
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������: " << filename << std::endl;
    }
}

// ����� �������������� (� ���������� ����� �����)
void AirConditioner::deserialize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        size_t brandSize, modelSize, modeSize;

        file.read(reinterpret_cast<char*>(&brandSize), sizeof(size_t));
        brand.resize(brandSize);
        file.read(&brand[0], brandSize);
        file.read(reinterpret_cast<char*>(&modelSize), sizeof(size_t));
        model.resize(modelSize);
        file.read(&model[0], modelSize);
        file.read(reinterpret_cast<char*>(&weight), sizeof(double));
        file.read(reinterpret_cast<char*>(&temperature), sizeof(double));
        file.read(reinterpret_cast<char*>(&modeSize), sizeof(size_t));
        mode.resize(modeSize);
        file.read(&mode[0], modeSize);
        file.read(reinterpret_cast<char*>(&year), sizeof(int));
        file.read(reinterpret_cast<char*>(&totalTempChange), sizeof(double));
        file.read(reinterpret_cast<char*>(&settingsCount), sizeof(int));

        std::cout << "������ ������������ ��������� �� �����: " << filename << std::endl;
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������: " << filename << std::endl;
    }
}

// ����� ������ ���������� � ������������
void AirConditioner::printInfo() const {
    std::cout << "���������� � ������������:" << std::endl;
    std::cout << "�����: " << brand << std::endl;
    std::cout << "������: " << model << std::endl;
    std::cout << "���: " << weight << " ��" << std::endl;
    std::cout << "������� �����������: " << temperature << "�C" << std::endl;
    std::cout << "�����: " << mode << std::endl;
    std::cout << "��� �������: " << year << std::endl;
    std::cout << "������� ��������� �����������: " << getAverageTemperatureChange() << "�C" << std::endl;
}
