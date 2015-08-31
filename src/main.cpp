/********
 * bingrep looks for a binary pattern inside a binary file.
 * You can use hexadecimal patterns as well.
 * 
 * @Name: binfinder
 * @Date: 2015-01-24
 * @Author: Ernesto Messina
*/
#include <cstring>
#include <vector>
#include <thread>
#include <future>
#include "utils.h"
#include "bingrep.h"


int main(int argc, char **argv)
{
	/**
	 * Armar busquedas binarias predefinidas por tipo de archivos (buscar por su header). Por ejemplo: todo los archivos PDF
	*/
	// Process input
	DirTreeReader *dtr {};
	std::vector<std::bitset<8>> vecPat;
	unsigned char optField = read_opt(argc, argv, "fl");
	if ((optField & OPTIONS::INVALID) == OPTIONS::INVALID)
	{
		show_usages(argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(((optField & OPTIONS::NONE) == OPTIONS::NONE) && argc == 3)
	{
		if (read_patterns(&vecPat, argv[2]) == -1)
		{
			show_usages(argv[0]);
			exit(EXIT_FAILURE);
		}
		dtr = new DirTreeReader(argv[1]);
	}
	else if(((optField & OPTIONS::NONE) == OPTIONS::NONE) && argc == 4)
	{
		if (read_patterns(&vecPat, argv[3]) == -1)
		{
			show_usages(argv[0]);
			exit(EXIT_FAILURE);
		}
		dtr = new DirTreeReader(argv[2]);
	}
	else
	{
		show_usages(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	
	std::cout << "Number of CPU cores: " << std::thread::hardware_concurrency() << std::endl;
	std::vector<std::string> files = dtr->loadFiles();
//	for (uint i = 0; i < files.size(); ++i)
//		std::cout << files.at(i) << std::endl;
	std::cout << "Total files read: " << dtr->getTotalFiles() << std::endl;
	
	
	int offset { -1 };
	std::future<int> fut {};
	BinFinder bf(files.at(0));
	for (uint i = 0; i < files.size(); ++i)
	{
		bf.setFile(files.at(i));
		if ((optField & OPTIONS::CURR_FILE) == OPTIONS::CURR_FILE)
			std::cout << "Looking into " << files.at(i) << std::endl;
		if ((optField & OPTIONS::CREAT_LOG) == OPTIONS::CREAT_LOG)
			fut = std::async(std::launch::async, &BinFinder::containsInFile, &bf, vecPat, 1, true);	// std::launch::async force async to create a thread
		else
			fut = std::async(std::launch::async, &BinFinder::containsInFile, &bf, vecPat, 1, false);	// std::launch::async force async to create a thread
		offset = fut.get();
		if (offset > -1)
			std::cout << "Found in: " << files.at(i) << " at offset: " << std::hex << "0x" << offset << std::endl;
	}

	if (dtr) delete dtr;
	exit(EXIT_SUCCESS);
}