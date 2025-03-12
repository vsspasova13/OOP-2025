#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable:4996)

struct Task
{
private:
    char* name = nullptr;
    char* descr = nullptr;
    int points = 0;

    void free()
    {
        delete[] name;
        delete[] descr;
        name = nullptr;
        descr = nullptr;
        points = 0;
    }

public:
    Task() = default;

    void setName(const char* name)
    {
        size_t len = strlen(name);
        delete[] this->name;
        this->name = new char[len+1];
        strcpy(this->name, name);
    }

    void setDescription(const char* d)
    {
        size_t len = strlen(d);
        delete[] this->descr;
        this->descr = new char[len+1];
        strcpy(this->descr, d);
    }

    void setPoints(int p)
    {
        this->points = p;
    }

    void writeToFile(std::ofstream& ofs) const
    {
        if (!ofs.is_open())
        {
            std::cout << "error while opening the file" << std::endl;
        }

        size_t nameLen = strlen(this->name);
        ofs.write((const char*)&nameLen, sizeof(nameLen));
        ofs.write((const char*)this->name, nameLen);

        size_t dLen = strlen(this->descr);
        ofs.write((const char*)&dLen, sizeof(dLen));
        ofs.write((const char*)this->descr, dLen);

        ofs.write((const char*)&points, sizeof(points));
    }

    void readFromFile(std::ifstream& ifs)
    {
        if (!ifs.is_open())
        {
            std::cout << "error while opening the file" << std::endl;
        }

        size_t nameLen = 0;
        ifs.read((char*)&nameLen, sizeof(nameLen));
        this->name = new char[nameLen+1];
        ifs.read((char*)this->name, nameLen);
        this->name[nameLen] = '\0';

        size_t dLen = 0;
        ifs.read((char*)&dLen, sizeof(dLen));
        this->descr = new char[dLen+1];
        ifs.read((char*)this->descr, dLen);
        this->descr[dLen] = '\0';

        ifs.read((char*)&this->points, sizeof(this->points));
    }

    int getPoints()const
    {
        return this->points;
    }

    const char* getName()const
    {
        return this->name;
    }

    const char* getDescr()const
    {
        return this->descr;
    }

    ~Task()
    {
        free();
    }
};

constexpr int TASKS_SIZE = 20;

struct Exam
{
private:
    Task tasks[TASKS_SIZE];
    size_t size = 0;
    int minPoints = 0;

public:
    void addTask(const Task& t)
    {
        if (size == TASKS_SIZE)
        {
            std::cout << "not enough space" << std::endl; return;
        }

        tasks[size].setName(t.getName());//? tva taka li se pravi bez operator =
        tasks[size].setDescription(t.getDescr());//?
        tasks[size].setPoints(t.getPoints());//?
        size++;
    }

    void writeToFile(const char* fileName) const
    {
        std::ofstream ofs(fileName, std::ios::binary);

        if (!ofs.is_open())
        {
            std::cout << "error while opening the file" << std::endl;
        }

        ofs.write((const char*)&size, sizeof(size));
        for (int i = 0; i < size; i++)
        {
            tasks[i].writeToFile(ofs);
        }
        ofs.write((const char*)&minPoints, sizeof(minPoints));

        ofs.close();
    }

    void readFromFile(const char* fileName)
    {
        std::ifstream ifs(fileName, std::ios::binary);

        if (!ifs.is_open())
        {
            std::cout << "error while opening the file" << std::endl;
        }

        ifs.read((char*)&size, sizeof(size));
        if (size > TASKS_SIZE)
        {
            std::cout << "size larger than max size" << std::endl;
            return;
        }

        for (int i = 0; i < size; i++)
        {
            tasks[i].readFromFile(ifs);
        }

        ifs.read((char*)&minPoints, sizeof(minPoints));

        ifs.close();
    }

    void setMinPoints(int p)
    {
        this->minPoints = p;
    }

    int getMax()const
    {
        if (size == 0) return -1;

        int max = 0;
        for (int i = 0; i < size; i++)
        {
            if (tasks[i].getPoints() > max)
                max = tasks[i].getPoints();
        }
        return max;
    }
};

int main()
{
    Task t1, t2, t3;
    t1.setName("Task 1");
    t1.setDescription("problem 1");
    t1.setPoints(50);

    t2.setName("Task 2");
    t2.setDescription("problem 2");
    t2.setPoints(30);

    t3.setName("Task 3");
    t3.setDescription("problem 3");
    t3.setPoints(70);

    Exam exam1;
    exam1.addTask(t1);
    exam1.addTask(t2);
    exam1.addTask(t3);
    exam1.setMinPoints(40);

    exam1.writeToFile("exam_data.bin");
   
    Exam exam2;
    exam2.readFromFile("exam_data.bin");
    
    std::cout << "Maximum points in a task: " << exam2.getMax();
}

