#pragma once
#include "FileBase.hpp"
template <class T>
class File : public FileBase // 读写不涉及vptr
{
protected:
    const int infoLen;
    const int headLen;
    static constexpr bool isVirtual = std::is_polymorphic<T>::value;
    // static const VPTR vptr = *(VPTR *)&T();
    static constexpr int ST = sizeof(T) - sizeof(VPTR) * isVirtual;
    void classWrite(const T *tmp)
    {
        if (isVirtual)
        {
            VPTR *ptr = (VPTR *)tmp;
            this->fwrite(ptr + 1, ST);
        }
        else
            this->fwrite(tmp, ST);
    }
    void classRead(T *tmp)
    {
        if (isVirtual)
        {
            VPTR *ptr = (VPTR *)tmp;
            this->fwrite(ptr + 1, ST);
            // *ptr = vptr;
        }
        else
            this->fread(tmp, ST);
    }

public:
    File() : FileBase(), infoLen(0), headLen(0) {}
    File(const string &fileName, bool isReload, int _infoLen = 0, int _headLen = 0) : FileBase(fileName, isReload), infoLen(_infoLen), headLen(_headLen)
    {
        if (!isReload)
        {
            int tmp = 0;
            file.seekp(headLen * SI);
            for (int i = headLen; i < headLen + infoLen; i++)
                fwrite(&tmp);
        }
    }
    void infoWrite(const int &tmp, int index)
    {
        if (index < 0 || index >= infoLen)
            throw "invalid index when write info " + std::to_string(tmp) + " at " + std::to_string(index);
        file.seekp((headLen + index) * SI);
        this->fwrite(&tmp);
    }
    void infoRead(int &tmp, int index)
    {
        if (index < 0 || index >= infoLen)
            throw "invalid index when read info " + std::to_string(tmp) + " at " + std::to_string(index);
        file.seekg((headLen + index) * SI);
        this->fread(&tmp);
    }
    void write(const T &tmp, int index)
    {
        if (index < 0)
            throw "invalid index when write single " + string(typeid(T).name());
        file.seekp((headLen + infoLen) * SI + index * ST);
        this->classWrite(&tmp);
    }
    void write(const T *tmp, int index, int num)
    {
        if (index < 0)
            throw "invalid index when write " + std::to_string(num) + " " + string(typeid(T).name());
        file.seekp((headLen + infoLen) * SI + index * ST);
        for (int i = 0; i < num; i++)
        {
            this->classWrite(tmp + i);
        }
    }
    void read(T &tmp, int index)
    {
        if (index < 0)
            throw "invalid index when read single " + string(typeid(T).name());
        file.seekg((headLen + infoLen) * SI + index * ST);
        this->classRead(&tmp);
    }
    void read(T *tmp, int index, int num)
    {
        if (index < 0)
            throw "invalid index when read " + std::to_string(num) + " " + string(typeid(T).name());
        file.seekg((headLen + infoLen) * SI + index * ST);
        for (int i = 0; i < num; i++)
        {
            this->classRead(tmp + i);
        }
    }
};