#ifndef FILEHANDLE_HPP
#define FILEHANDLE_HPP
#include <physfs.h>
#include <vector>
#include <string>
#include <cstdint>
#include "FIO.hpp"

namespace PhysFS {

DEFINE_CLASS(FileHandle)

class FileHandle : public Abstract::FIO
{
public:
	enum OpenMode
	{
		PHYSFS_READ,
		PHYSFS_WRITE,
		PHYSFS_APPEND
	};
private:
	PHYSFS_File* fhandle;
	FileHandle(const std::string& path,OpenMode mode);
public:
	static void init(const char *argv0);
	static void deInit();
	static bool isInit();
	static std::string getDirSeparator();
	static std::string getBaseDir();
	static std::string getUserDir();
	static std::string getPrefDir(const std::string& org, const std::string& app);
	static std::string getWriteDir();
	static std::string getLastError();
	static void setWriteDir(const std::string& newDir);
	static void addToSearchPath(const std::string& newDir, const std::string& mountPoint, bool appendToPath);
	static void removeFromSearchPath(const std::string& oldDir);

	static Abstract::stringBuffer enumerateFiles(const std::string& path);
	static Abstract::stringBuffer enumerateFilesFullpath(const std::string& path);
	static Abstract::byteBuffer loadFileIntoBuffer(const std::string& path);
	static std::string stringizeFile(const std::string& path);
	static PHYSFS_Stat stat(const std::string& path);

	~FileHandle();
	static Abstract::sFIO openRead(const std::string& path);
	static Abstract::sFIO openWrite(const std::string& path);
	static Abstract::sFIO openAppend(const std::string& path);

	int64_t read(void* data, int64_t size);
	int64_t seek(int64_t position);
	int64_t tell();
	int64_t size();
	int64_t write(const void* data, int64_t size);
	Abstract::byteBuffer loadIntoBuffer();
	std::string stringize();
	char getc();
};

}
#endif // FILEHANDLE_HPP
