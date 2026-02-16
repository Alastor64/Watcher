#pragma once
#include "Mydef.hpp"
const std::string DATA_PATH = "./";
class FileBase
{

protected:
    fstream file;
    static constexpr int SI = sizeof(int); // sizeof(int)
    void fwrite(const void *ptr, int _size = SI);
    void fread(void *ptr, int _size = SI);

public:
    FileBase() {}
    FileBase(const string &fileName, bool isReload);
    ~FileBase();
};