#pragma once
#include <cstdio>
#include <cerrno>

class FileHandle {
    FILE* file_ptr_p_;
public:
    FileHandle(const char* name, const char* access)
    {
        file_ptr_p_ = fopen(name, access); if (file_ptr_p_ == nullptr) throw Open_error(errno);
    }

    FileHandle(FILE* file_ptr)
    {
        file_ptr_p_ = file_ptr; if (file_ptr_p_ == 0) throw Open_error(errno);
    }

    ~FileHandle() { fclose(file_ptr_p_); }

    inline operator FILE*(void) const
    { return file_ptr_p_; }

    // ...
};

void f(const char* fn)
{
    FileHandle f(fn, "rw");    // open fn for reading and writing
                                // use file through f
}
