#include "File.hpp"
// protected:
void FileBase::fwrite(const void *ptr, int _size)
{
    file.write(reinterpret_cast<const char *>(ptr), _size);
}
void FileBase::fread(void *ptr, int _size)
{
    file.read(reinterpret_cast<char *>(ptr), _size);
}

// public:
FileBase::FileBase(const string &fileName, bool isReload)
{
    if (!isReload)
    {
        file.open(DATA_PATH + fileName, ios::trunc | ios::out | ios::binary);
        file.close();
    }
    file.open(DATA_PATH + fileName, ios::in | ios::out | ios::binary);
    if (!file)
        throw "founding file \"" + fileName + "\" failed";
}
FileBase::~FileBase()
{
    file.close();
}