#include <iostream>

struct Point
{
    int x;
    int y;
};

void readPoint(Point& p)
{
   
    std::cin >> p.x >> p.y;
   
}

void printPoint(const Point& p)
{
    std::cout << p.x << " " << p.y << std::endl;
}

double distCentre(const Point& p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2));
}

double distanceBetweenTwoPoints(const Point& p1, const Point& p2)
{
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

//2

struct Triangle
{
    Point p1;
    Point p2;
    Point p3;
};

void readTriangle(Triangle& t)
{
    readPoint(t.p1);
    readPoint(t.p2);
    readPoint(t.p3);
}

void printTriangle(const Triangle& t)
{
    printPoint(t.p1);
    printPoint(t.p2);
    printPoint(t.p3);
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

void insertionSort(Triangle*& triangles, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        int minInd = i;
        for (int j = i; j < n; j++)
        {
            if (getArea(triangles[minInd]) > getArea(triangles[j]))
            {
               
                minInd = j;
             }
        }
        if(minInd!=i) std::swap(triangles[i], triangles[minInd]);
    }
}

//3
constexpr int MAXNAMESIZE = 256;

struct Student
{
    char name[MAXNAMESIZE];
    char surname[MAXNAMESIZE];
    char egn[10];
    StudentType type;
};

void printStudent(const Student& s) {
    std::cout << s.name << " " << s.surname << " " << s.egn << " " << s.age << " " << std::endl;
}

enum StudentType
{
    Freshman,
    Sophomore,
    Junior,
    Senior
};

struct University
{
    char name[MAXNAMESIZE];
    Student* students;
    size_t studentsCount;

};


bool hasStudent(const University& u, const Student& s)
{
    for (int i = 0; i < u.studentsCount; i++)
    {
        if (strcmp(u.students[i].egn, s.egn) == 0)return true;
    }
    return false;
}

void addStudent(University& u, const Student& s)
{
    if (hasStudent(u, s))return;
    u.studentsCount++;
    u.students[u.studentsCount - 1] = s;
}

void removeStudent(University& u, const char* egn)
{
    bool dali = false;
    for (int i = 0; i < u.studentsCount-1; i++)
    {
        if (strcmp(u.students[i].egn, egn) == 0)

        {
            std::swap(u.students[i], u.students[i + 1]); dali = true;
        }
    }
    
    if (dali)
    {
        u.studentsCount--;
    }
}

void printStudents(const University& u, StudentType type)
{
    for (int i = 0; i < u.studentsCount; i++)
    {
        if (u.students[i].type == type)
            printStudent(u.students[i]);
    }
}

int main()
{
    int n;
    std::cin >> n;
    Triangle* triangles = new Triangle[n];
    for (int i = 0; i < n; i++)
    {
        Triangle t;
        readTriangle(triangles[i]);
    }

    insertionSort(triangles, n);
    for (int i = 0; i < n; i++)
    {
        printTriangle(triangles[i]);
    }

    delete[] triangles;
}
