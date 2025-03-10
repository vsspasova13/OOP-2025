#include <iostream>
#include <sstream>
#include <string>
#include <climits>

constexpr int MAXSIZE = 1024;

int main()
{
    //1
    char str[MAXSIZE];
    std::cin.getline(str, MAXSIZE);
    std::stringstream ss(str);
    int i, sum = 0, count = 0, min = INT_MAX, max = INT_MIN;
  
    while (ss >> i)
    {
        sum += i;
        count++;
        if (i < min)min = i;
        if (i > max)max = i;
    }
    std::cout <<"sum: "<<sum<<std::endl;
    std::cout << "sredno-aritm: " << sum / count << std::endl;
    std::cout << "min: " << min << ", max: " << max << std::endl;

}
