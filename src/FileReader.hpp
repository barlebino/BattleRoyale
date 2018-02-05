#pragma once
#ifndef _FILE_READER_HPP_
#define _FILE_READER_HPP_
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

inline bool readTextFile(const std::string & filepath, std::string & dst) {
    std::ifstream ifs(filepath);
    if (!ifs.good()) {
        return false;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    dst = ss.str();

    return true;
}

class FileReader {
    public:
        std::string readFile();
        int loadLevel(std::string & file);

};

#endif