#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)

struct Car
{
private:
    char* brand = nullptr;
    int year=0;
    int maxSpeed=0;
    int* km=nullptr;
    size_t kmSize=0;

    void free()
    {
        delete[] brand;
        delete[] km;
        brand = nullptr;
        km = nullptr;
        kmSize = 0;
    }
 
public:

    Car() = default;

    Car(const char* name, int year, int maxSpeed, int* km, size_t kmSize)
    {  
      this->year = year;
      this->maxSpeed = maxSpeed;

      this->brand = new char[strlen(name)+1];

      strcpy(this->brand, name);

      this->km = new int[kmSize];
      for (int i = 0; i < kmSize; i++)
      {
          this->km[i] = km[i];
      }
      this->kmSize = kmSize;
    }

    void writeToFile(std::ofstream& ofs) const
    {
        if (!ofs.is_open())
            std::cout << "error while opening the file" << std::endl;

        size_t brandLen = strlen(this->brand);
        ofs.write((const char*)& brandLen, sizeof(brandLen));

        ofs.write((const char*)this->brand, brandLen);

        ofs.write((const char*)&this->year, sizeof(this->year));
        ofs.write((const char*)&this->maxSpeed, sizeof(this->maxSpeed));

        ofs.write((const char*)&this->kmSize, sizeof(this->kmSize));
        ofs.write((const char*)this->km, sizeof(int)*kmSize);
    }

    void readFromFile(std::ifstream& ifs)
    {
        if (!ifs.is_open())
            std::cout << "error while opening the file" << std::endl;

        this->brand = nullptr;
        this->km = nullptr;

        size_t brandLen;
        ifs.read((char*)&brandLen, sizeof(brandLen));

        this->brand = new char[brandLen+1];
        ifs.read((char*)this->brand, brandLen);
        this->brand[brandLen] = '\0';

        ifs.read((char*)&this->year, sizeof(this->year));
        ifs.read((char*)&this->maxSpeed, sizeof(this->maxSpeed));

        ifs.read((char*)&this->kmSize, sizeof(this->kmSize));
        this->km = new int[this->kmSize];
        ifs.read((char*)this->km, sizeof(int)*this->kmSize);
    }

    int getAllKm() const
    {
        int sum = 0;
        for (int i = 0; i < kmSize; i++)
        {
            sum += km[i];
        }
        return sum;
    }

    int getMaxKm() const
    {
        int max = 0; 
        for (int i = 0; i < kmSize; i++)
        {
            if (km[i] > max)max = km[i];
        }
        return max;
    }

    void print()const
    {
        std::cout << "brand: " << this->brand << std::endl;
        std::cout << "year: " << this->year << std::endl;
        std::cout << "max speed: " << this->maxSpeed << std::endl;
        std::cout << "km sum: " << getAllKm() << std::endl;
        std::cout << "most km: " << getMaxKm() << std::endl;
    }

    ~Car()
    {
        free();
    }

};

int main()
{
    const char* brand = "Toyota";
    int year = 2015;
    int maxSpeed = 200;
    int kmArr[] = { 12000, 15000, 18000, 20000 };
    size_t kmSize = 4;

    Car car1(brand, year, maxSpeed, kmArr, kmSize);

    std::ofstream ofs("car_data.bin", std::ios::binary);
    car1.writeToFile(ofs);
    ofs.close();
    
    Car car2;
    std::ifstream ifs("car_data.bin", std::ios::binary);
    car2.readFromFile(ifs);
    ifs.close();

    car2.print();
}


