#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
 
std::vector<char> toCharVector(std::string str)
{
	std::vector<char> ch;
	for (int i = 0; i < str.length(); i++)
		ch.push_back(str[i]);
	return ch;
}

std::string charVectorToString(std::vector<char> ch)
{
	std::string str;
	for (int i = 0; i < ch.size(); i++)
		str.push_back(ch[i]); 
	return str;
}

int binToDec(std::string bin)
{
	int dec = 0, i = 0, rem;
	long long int n = 0;
	std::istringstream(bin) >> n;
	while (n != 0) {
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2, i);
		++i;
	}

	return dec;
}

char popularBitCol(std::vector<std::vector<char>> binarData, int col)
{
	int count = 0;
	for (int row = 0; row < binarData.size(); row++)
		if (binarData[row][col] - 48)
		{
			count++;
		}
	if(count< binarData.size()-count)
		return '0';
	return '1';
}

std::vector<std::vector<char>> coincidenceBit(std::vector<std::vector<char>> binarData, int col, char bit)
{
	std::vector<std::vector<char>> sample;
	std::vector<char> v;
	for(int row = 0;row< binarData.size();row++)
		if (binarData[row][col] == bit) {
			//sample.push_back(binarData[row]);
			v = binarData[row];
			sample.push_back(v);
		}

	return sample;
}

int main()
{
	std::string path("inputThree.txt");
	
	std::vector<std::vector<char>> binarData; 
	std::vector<std::vector<char>> oxyGenRet;
	std::vector<std::vector<char>> co2ScrRet;
	std::string gamma;
	std::string epsilon;

	std::ifstream in(path);
	std::string line;
	
	if (in.is_open())
	{
		while (getline(in, line))
		{
			binarData.push_back(toCharVector(line));
		}
	}
	else std::cout << "File not found";
	in.close();  

	for (int col = 0; col < binarData[0].size(); col++)
	{
		int count = 0;
		for (int row = 0; row < binarData.size(); row++)
			if (binarData[row][col]-48)
			{
				count++;
			}
		if (count > binarData.size() - count)
		{ 
			gamma.push_back(1+48);
			epsilon.push_back(0 + 48);
		}
		else
		{
			gamma.push_back(0 + 48);
			epsilon.push_back(1 + 48);
		}
	}

	int iter = 0;
	oxyGenRet = binarData;
	char oxyGenRetBit;
	while (oxyGenRet.size() > 1)
	{
		oxyGenRetBit = popularBitCol(oxyGenRet, iter);
		oxyGenRet = coincidenceBit(oxyGenRet, iter, oxyGenRetBit);
		iter++;
		
	}

	iter = 0;
	co2ScrRet = binarData;
	char co2ScrRetBit;
	while (co2ScrRet.size() > 1)
	{
		if (popularBitCol(co2ScrRet, iter) == '0')
			co2ScrRetBit = '1';
		else co2ScrRetBit = '0';
		co2ScrRet = coincidenceBit(co2ScrRet, iter, co2ScrRetBit);
		iter++;
	}

	for (auto const& element : gamma)
		std::cout << element << ' ';
	std::cout << "\n";
	for (auto const& element : epsilon)
		std::cout << element << ' ';
	std::cout << "\n";
	for (auto const& element : oxyGenRet[0] )
		std::cout << element << ' ';
	std::cout << "\n";
	for (auto const& element : co2ScrRet[0])
		std::cout << element << ' ';
	
	std::cout << "\n" << binToDec(gamma) * binToDec(epsilon) << "\n";
	std::cout << binToDec(charVectorToString(oxyGenRet[0]))
		* binToDec(charVectorToString(co2ScrRet[0])) << "\n";

	system("pause");
	return 0;
}