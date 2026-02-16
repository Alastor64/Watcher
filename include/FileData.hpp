#pragma once
#include "File.hpp"
template <class T>
class FileData : protected File<T>
{
protected:
    int last;
    int size;
    static constexpr int dHeadLen = 2;

public:
    FileData() : File<T>() {}
    FileData(const string &fileName, bool isReload, int _infoLen = 0, int _headLen = 0) : File<T>(fileName, isReload, _infoLen, _headLen + dHeadLen)
    {
        if (!isReload)
        {
            this->file.seekp(0);
            last = -1;
            size = 0;
            this->fwrite(&last);
            this->fwrite(&size);
        }
        else
        {
            this->file.seekg(0);
            this->fread(&last);
            this->fread(&size);
        }
    }
    int push(const T &tmp)
    {
        int rt;
        if (last != -1)
        {
            rt = last;
            this->file.seekg((this->headLen + this->infoLen) * this->SI + rt * this->ST);
            this->fread(&last);
        }
        else
            rt = size++;
        this->write(tmp, rt);
        return rt;
    }
    void get(T &tmp, int index)
    {
        this->read(tmp, index);
    }
    T get(int index)
    {
        T tmp;
        this->read(tmp, index);
        return std::move(tmp);
    }
    void update(const T &tmp, int index)
    {
        this->write(tmp, index);
    }
    void pop(int index)
    {
        this->file.seekp((this->headLen + this->infoLen) * this->SI + index * this->ST);
        this->fwrite(&last);
        last = (this->headLen + this->infoLen) * this->SI + index * this->ST;
    }
};