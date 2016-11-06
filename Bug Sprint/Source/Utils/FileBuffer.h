//
// Created by Rafal Grodzinski on 06/11/2016.
//

#ifndef FILEBUFFER_H
#define FILEBUFFER_H

#include <iostream>
#include <memory>


class FileBuffer: public std::streambuf
{
public:
    FileBuffer(FileBuffer &other);
    FileBuffer(const FileBuffer &other);
    FileBuffer(void *data, long length);

private:
    std::shared_ptr<char> data;
    long dataLength;
};

#endif
