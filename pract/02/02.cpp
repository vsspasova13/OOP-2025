#include <iostream>
#include <fstream>

int countSymbol(std::ifstream& ifs, char ch)
{
    int count = 0;
    int currPos = ifs.tellg();
    ifs.seekg(ifs.beg);

    while (!ifs.eof())
    {
        char c = ifs.get();
        if (c == ch)count++;
    }

    ifs.clear();
    ifs.seekg(currPos);
    return count;
}

//2
void readFromFile(std::fstream& ifs)
{
    int sum, p;
    ifs >> sum >> p;
    std::cout << sum - p;
}

//3
void sortAsc(int*& arr, size_t n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minInd = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j]<arr[minInd])
            {

                minInd = j;
            }
        }
        if (minInd != i) std::swap(arr[i], arr[minInd]);
    }

}

void sortDesc(int*& arr, size_t n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minInd = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j] > arr[minInd])
            {

                minInd = j;
            }
        }
        if (minInd != i) std::swap(arr[i], arr[minInd]);
    }
}

//4
constexpr int MAXNAMELENGTH = 50;
constexpr int MAXGRADESCOUNT = 100;

enum Major
{
    SE, CS, IS, I, None
};


struct Student
{
    char name[MAXNAMELENGTH];
    int grades[MAXGRADESCOUNT];
    size_t gradesCount;
    Major major;
};

const char* majorToString(Major m)
{
    switch (m)
    {
    case SE: return "SE"; break;
    case IS: return "IS"; break;
    case CS: return "CS"; break;
    case I: return "I"; break;
    default: return "none";

    }
}

Major strToMajor(const char* s)
{
    if (strcmp(s, "SE") == 0)return SE;
    else if (strcmp(s, "IS") == 0)return IS;
    else if (strcmp(s, "I") == 0)return I;
    else if (strcmp(s, "CS") == 0)return CS;
    else return None;

}

void saveStudentToFile(const Student& s, std::ofstream& ofs)
{
    ofs << s.name << " " << s.gradesCount << " ";
    for (int i = 0; i < s.gradesCount; i++)
    {
        ofs << s.grades[i] << " ";
    }
    ofs<< majorToString(s.major) << std::endl;
}

void readStudentFromFile(Student& s, std::ifstream& ifs)
{

    ifs >> s.name >> s.gradesCount;
    for (int i = 0; i < s.gradesCount; i++)
    {
        ifs >> s.grades[i];
    }
    char major[10];
    ifs >> major;
    s.major = strToMajor(major);
   
}

void writeStudentArrayToFile(const char* filename, const Student* students, size_t size)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        std::cout << "error";
        return;
    }
    ofs << size << std::endl;
    for (int i = 0; i < size; i++)
    {
        saveStudentToFile(students[i], ofs);
        ofs << std::endl;
    }
}

Student* readStudentArrayFromFile(const char* filename, size_t& size)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cout << "error";
        return nullptr;
    }
    ifs >> size;
    //ifs.ignore();
    Student* students = new Student[size];

    for (int i = 0; i < size; i++)
    {
        readStudentFromFile(students[i], ifs);
        ifs.ignore();
    }
    return students;
}

//5
struct Point
{
    int x;
    int y;
};

void readPoint(Point& p, std::istream& ifs)
{
    
    ifs>> p.x >> p.y;
    

}

void printPoint(const Point& p, std::ostream& ofs)
{
    ofs << p.x << " " << p.y<<" ";
}

double distCentre(const Point& p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double distanceBetweenTwoPoints(const Point& p1, const Point& p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//2

struct Triangle
{
    Point p1;
    Point p2;
    Point p3;
};

void readTriangle(Triangle& t, std::istream& ifs)
{
    readPoint(t.p1, ifs);
    readPoint(t.p2, ifs);
    readPoint(t.p3, ifs);
}

void printTriangle(const Triangle& t, std::ostream& ofs)
{
    printPoint(t.p1, ofs); ofs << ", ";
    printPoint(t.p2, ofs); ofs << ", ";
    printPoint(t.p3, ofs); ofs << std::endl;
  
}

double getPerimeter(const Triangle& t)
{
    double a = distanceBetweenTwoPoints(t.p1, t.p2);
    double b = distanceBetweenTwoPoints(t.p3, t.p2);
    double c = distanceBetweenTwoPoints(t.p1, t.p3);

    double p = a + b + c;
    return p;
}

double getArea(const Triangle& t)
{
    double a = distanceBetweenTwoPoints(t.p1, t.p2);
    double b = distanceBetweenTwoPoints(t.p3, t.p2);
    double c = distanceBetweenTwoPoints(t.p1, t.p3);

    double p = getPerimeter(t) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

enum TriangleType
{
    EquilateralTriangle,
    IsoscelesTriangle,
    ScaleneTriangle
};

TriangleType getType(const Triangle& t)
{
    double a = distanceBetweenTwoPoints(t.p1, t.p2);
    double b = distanceBetweenTwoPoints(t.p3, t.p2);
    double c = distanceBetweenTwoPoints(t.p1, t.p3);

    if (a - b < 0.000001 && b - c < 0.000001 && a - c < 0.000001) return TriangleType::EquilateralTriangle;
    else if (a - b < 0.000001 && b - c < 0.000001 || b - c < 0.000001 && a - c < 0.000001 || a - b < 0.000001 && a - c < 0.000001)
        return TriangleType::IsoscelesTriangle;
    else return TriangleType::ScaleneTriangle;
}

int main()
{
    /*
    std::ifstream ifs("test.TXT");
    if (!ifs.is_open())
    {
        std::cout << "error";
        return 0;
    }

    std::cout << countSymbol(ifs, ',');
    */

    /*
    int a, b, c;
    std::cin >> a >> b >> c;
    std::fstream fs("result.txt", std::ios::in | std::ios::out | std::ios::trunc);
    if (!fs.is_open())
    {
        std::cout << "error";
        return 0;
    }
    int sum = a + b + c;
    int p = a * b * c;
    fs << sum << " " << p;
    
    fs.seekg(0, std::ios::beg);
  
    readFromFile(fs);
    */

    /*
    int n;
    std::ifstream ifs("input.txt");
    if (!ifs.is_open())
    {
        std::cout << "error" << std::endl;
        return 0;
    }

    ifs.seekg(0, std::ios::end);

    if (ifs.tellg()==0) { std::cout << "empty"; return 0; }

    ifs.seekg(0, std::ios::beg);

    ifs >> n;
    ifs.ignore();
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        ifs >> arr[i];
    }
    ifs.close();

    sortAsc(arr, n);
    std::ofstream ofs("ascending.txt");
    ofs << n << std::endl;
    for (int i = 0; i < n; i++)
    {
        ofs << arr[i]<<" ";
    }
    ofs.close();
    sortDesc(arr, n);
    std::ofstream ofs2("descending.txt");
    ofs << n << std::endl;
    for (int i = 0; i < n; i++)
    {
        ofs2 << arr[i]<<" ";
    }
    ofs2.close();
    */

    /*
    Student students[2] = {
       {"Ivan", {6, 5, 4, 5, 6}, 5, SE},
       {"Petar", {5, 5, 6, 6, 5}, 5, CS}
    };

    writeStudentArrayToFile("students.txt", students, 2);

    size_t size = 0;
    Student* loadedStudents = readStudentArrayFromFile("students.txt", size);

    if (loadedStudents) {
        for (size_t i = 0; i < size; i++) {
            std::cout << "Name: " << loadedStudents[i].name
                << ", Grades Count: " << loadedStudents[i].gradesCount
                << ", Major: " << majorToString(loadedStudents[i].major) << std::endl;
        }
        delete[] loadedStudents;
    }

    return 0;
    */

    size_t size;
    std::cin >> size;
    Point* points = new Point[size];
    for (int i = 0; i < size; i++)
    {
        readPoint(points[i], std::cin);
    }

    std::ofstream ofs("inputTr.txt");
    if (!ofs.is_open())
    {
        std::cout << "error";
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        printPoint(points[i], ofs);
    }
    ofs.close();
    
    std::ifstream ifs("inputTr.txt");
    if (size % 3 != 0) size = size / 3;
    Triangle* tr = new Triangle[size];
    for (int i = 0; i < size; i++)
    {
        readTriangle(tr[i], ifs);
    }

    for (int i = 0; i < size; i++)
    {
        printTriangle(tr[i], std::cout);
    }

}
