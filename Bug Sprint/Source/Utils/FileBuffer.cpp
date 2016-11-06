//
// Created by Rafal Grodzinski on 06/11/2016.
//

#include "FileBuffer.h"

using namespace std;


FileBuffer::FileBuffer(FileBuffer &other)
{
    setg(other.eback(), other.eback(), other.egptr());
}


FileBuffer::FileBuffer(const FileBuffer &other)
{
    setg(other.eback(), other.eback(), other.egptr());
}


FileBuffer::FileBuffer(void *data, long dataLength)
{
    this->dataLength = dataLength;

    this->data = shared_ptr<char>(new char[this->dataLength]());
    memcpy(this->data.get(), (char *)data, this->dataLength);

    setg(this->data.get(), this->data.get(), this->data.get() + this->dataLength);
}
