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

    return fileString;
}


void File::load()
{
    if(!fileString.empty())
        return;

    ifstream file;
    file.open(filePath);
    if(!file.good())
        throw string("Could not open file " + filePath);

    stringstream fileBuffer;
    fileBuffer << file.rdbuf();
    fileString = fileBuffer.str();

    file.close();
}
