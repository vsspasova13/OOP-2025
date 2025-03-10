#include <iostream>
#include <fstream>

constexpr int MAX_NAME = 20;

struct WorkAd
{
    char name[MAX_NAME];
    size_t workers;
    long long salary;
};

void readAd(WorkAd& ad, std::istream& ifs)
{
    ifs.read(ad.name, MAX_NAME);
    ifs.read((char*)&ad.workers, sizeof(size_t));
    ifs.read((char*)&ad.salary, sizeof(long long));
}

WorkAd* readAds(int n, std::istream& ifs)
{
    WorkAd* ads = new WorkAd[n];
    for (int i = 0; i < n; i++)
    {
        readAd(ads[i], ifs);
    }
    return ads;
}

void writeAd(const WorkAd& ad, std::ofstream& ofs)
{
    ofs.write(ad.name, MAX_NAME);
    ofs.write((const char*)&ad.workers, sizeof(size_t));
    ofs.write((const char*)&ad.salary, sizeof(long long));
}


void writeAds(int n, std::ofstream& ofs, const WorkAd*& ads)
{
    for (int i = 0; i < n; i++)
    {
        writeAd(ads[i], ofs);
    }
}

void readAndWrite()
{
    int n; 
    std::cin >> n;

    WorkAd* ads = readAds(n, std::cin);
    std::ofstream ofs("ads.dat", std::ios::in | std::ios::binary);
    writeAds(n, ofs, ads);
    delete[] ads;
}

void filterOffers(const char* filePath, long long minSalary)
{
    std::ifstream ifs(filePath, std::ios::binary);
    std::ofstream ofs("valis.dat", std::ios::in | std::ios::binary);
    WorkAd ad;
    while (!ifs.eof())
    {
        readAd(ad, ifs);
        if (ad.salary >= minSalary)
            writeAd(ad, ofs);
    }
}

bool existOffer(const char* filePath, const char* name)
{
    std::ifstream ifs(filePath, std::ios::binary);
    WorkAd ad;
    while (!ifs.eof())
    {
        readAd(ad, ifs);
        if (strcmp(name, ad.name) == 0)
            return true;
    }
    return false;

}

int main()
{
    
}
