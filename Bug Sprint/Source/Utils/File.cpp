//
//  File.cpp
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#include "File.h"

#include <fstream>
#include <sstream>
#include <memory>
#include "FileBuffer.h"
#include "SystemUtils.h"

using namespace std;


File::File(const string &fileName)
{
    filePath = SystemUtils::pathForFileName(fileName);
    if(filePath.empty())
        throw string("Could not find file " + fileName);
}


const std::string &File::getFilePath() const
{
    return filePath;
}


const std::string &File::getString()
{
    load();

    return stringData;
}


void File::load()
{
    if(!stringData.empty())
        return;

    FileBuffer fileBuffer = SystemUtils::bufferForFileName(filePath);
    istream fileStream(&fileBuffer);
    if(!fileStream.good())
        throw string("Could not open file " + filePath);

    stringstream stringStream;
    stringStream << fileStream.rdbuf();
    stringData = stringStream.str();
}
