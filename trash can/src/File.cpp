#include "File.hpp"
template <class T>
class File : public FileBase
{
protected:
    const int infoLen;
    static constexpr bool isVirtual = std::is_polymorphic<T>::value;
    static const VPTR vptr = *(VPTR *)&T();
    static constexpr int ST = sizeof(T) - sizeof(VPTR);
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
            *ptr = vptr;
        }
        else
            this->fread(tmp, ST);
    }

public:
    File() : FileBase() {}
    File(const string &fileName, bool isReload, int _infoLen = 0) : FileBase(fileName, isReload), infoLen(_infoLen)
    {
        int tmp = 0;
        file.seekp((headLen + 1) * SI);
        for (int i = headLen; i < headLen + infoLen; i++)
            this->fwrite(&tmp);
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