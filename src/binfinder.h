#ifndef _BINFINDER_H
#define _BINFINDER_H

#include <bitset>	// bitset
#include <iomanip>	// setfill, setw
#include <fstream>
#include <vector>


class BinFinder
{
public:
	explicit BinFinder(const std::string filePath);
	BinFinder(BinFinder&& bf);
	BinFinder(const BinFinder& bf);
	~BinFinder();
	
	BinFinder& operator=(BinFinder&& bf);
	BinFinder& operator=(const BinFinder& bf);
	
	int containsInFile(const std::vector<std::bitset<8>>& vecBin, const uint failsAllowed = 1, const bool createLog = false);
	int sizeOfFile();
	void setFile(const std::string& newPath);

private:
	void log(const std::vector<std::bitset<8>>& vec, const int i, const int j, const int blckIt);

private:
	char *buff;
	std::bitset<8> comp;
	std::string path;
	std::ifstream file;
	std::ofstream flog;
};


#endif	// _BINFINDER_H
