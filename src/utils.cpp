#include <string.h>
#include <sstream>
#include <fstream>
#include <sys/stat.h>	// stat()
#include "utils.h"


void show_usages(char *argv0)
{
	std::cout << "Usage: " << argv0 << " " << "[option] <searching path> <expression file>" << std::endl << std::endl;
    std::cout << "    -v    Verbose. Shows the file being scanned." << std::endl;
    std::cout << "    -f    Generates log file. Slow!." << std::endl << std::endl;
	std::cout << "  e.g:" << std::endl;
	std::cout << "  1) " << argv0 << " /home/darkBit pattern.txt" << std::endl;
	std::cout << "  2) " << argv0 << " -l /home/darkBit pattern.txt" << std::endl << std::endl;
}

unsigned char read_opt(int argc, char *const *argv, const char *options)
{
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
	{
		show_usages(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	unsigned char opt { OPTIONS::NONE };
	int c {};
	while((c = getopt(argc, argv, options)) != -1)
	{
		//std::cout << "getopt = " << c << std::endl;	//debug
		switch (c)
		{
            case 'f':
			{
				opt |= OPTIONS::CREAT_LOG;
				break;
			}
            case 'v':
			{
				opt |= OPTIONS::CURR_FILE;
				break;
			}
			case ':':	// Option requires and argument
			{
				opt = OPTIONS::INVALID;
				break;
			}
			case '?':	// Invalid option
			{
				if (c == 0)	// c is empty
					opt = OPTIONS::NONE;
				else
				{
					std::cerr << "Invalid option: " << optopt << std::endl;
					opt = OPTIONS::INVALID;
				}
			}
		}
	}
	
	return opt;
}

int read_patterns(std::vector<std::bitset<8>> *patVec, const std::string path)
{
	struct stat s;
	if (path.empty() || !patVec)
		return -1;
	else if (stat(path.c_str(), &s) == 0)
		if(!S_ISREG(s.st_mode)) return -1;
	
	std::stringstream ss_pat {};
	std::string s_pat {};
	int hex_pat {};
	std::ifstream f(path);
	if (!f.is_open()) return -1;
	
	while (!f.eof())
	{
		// Converts from string to hex
		f >> s_pat;
		ss_pat << s_pat;
		ss_pat >> std::hex >> hex_pat;
		
		patVec->push_back(hex_pat);
		ss_pat.clear();
	}
	
	return 0;
}
