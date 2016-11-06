//
//  File.h
//  Bug Sprint
//
//  Created by Rafal Grodzinski on 17/10/2016.
//  Copyright © 2016 UnalignedByte. All rights reserved.
//

#ifndef FILE_H
#define FILE_H

#include <string>


class File
{
public:
    File(const std::string &fileName);

    const std::string &getFilePath() const;
    const std::string &getString();

private:
    std::string filePath;
    std::string stringData;

    void load();
};

#endif
