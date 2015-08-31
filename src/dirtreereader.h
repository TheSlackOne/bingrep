#ifndef _DIRTREEREADER_H
#define _DIRTREEREADER_H

#include <iostream>
#include <ftw.h>	// ftw, nftw
#include <vector>


class DirTreeReader
{
public:
	DirTreeReader(const std::string& fpath, int typeflag = FTW_DEPTH | FTW_PHYS);
	DirTreeReader(DirTreeReader&& rdt);
	DirTreeReader(const DirTreeReader& rdt);
	~DirTreeReader();
	
	DirTreeReader& operator=(DirTreeReader&& rdt);
	DirTreeReader& operator=(const DirTreeReader& rdt);
	
	int explore(int noFd = 20) const;
	const std::vector<std::string>& loadFiles(int noFd = 20);
	const std::vector<std::string>& loadDirs(int noFd = 20);
	int getTotalFiles() const;
	int getTotalDirs() const;
	
	static DirTreeReader *pThis;
	
protected:
	static int showInfo(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwBuff);
	static int getFiles(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwBuff);
	static int getDirs(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwBuff);
	
private:
	std::string path;
	int typeFlag;
	std::vector<std::string> files;
	std::vector<std::string> dirs;
};


#endif // _DIRTREEREADER_H
