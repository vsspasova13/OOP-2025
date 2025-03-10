#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

void writeNumbers(std::ofstream& ofs, int* nums, int size)
{
	ofs.write((const char*)&size, sizeof(int));
	ofs.write((const char*)nums, size*sizeof(int));
}

int* readNumbers(std::ifstream& ifs, int& size)
{
	ifs.read((char*)&size, sizeof(int));
	int* nums = new int[size];
	ifs.read((char*)nums, size * sizeof(int));
	return nums;
}

int main()
{
	int n;
	std::cin >> n;
	int* nums = new int[n];
	for (int i = 0; i < n; i++)
	{
		std::cin >> nums[i];
	}
	std::ofstream ofs("numbers.dat", std::ios::binary);
	if (!ofs.is_open())
	{
		std::cout << "error";
		return 0;
	}
	writeNumbers(ofs, nums, n);
	ofs.close();

	std::ifstream ifs("numbers.dat", std::ios::binary);
	if (!ifs.is_open())
	{
		std::cout << "error";
		return 0;
	}
	int size=0;

	int* res = readNumbers(ifs, size);

	for (int i = 0; i < size; i++)
	{
		if((i+1)%3==0)
			std::cout << res[i] << " ";
	}

}
