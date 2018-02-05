#include "FileReader.hpp"

std::string FileReader::readFile() {
    std::string fileStream;
    std::string filePath = "../resources/test.json";

    if (readTextFile(filePath, fileStream)) {
        return fileStream;
    }
    else
        return "bad path";


}

int FileReader::loadLevel(std::string & file) {
    rapidjson::Document document;
    const char filePath[] = "../resources/GameLevel.json";

    
    FILE* fp = fopen(filePath, "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    if (document.ParseStream(is).HasParseError()) {
        std::cout << "bad json file" << std::endl;
        return 1;
    }
    
    // assert(document.IsObject());
    
    //For each object in the json document
    for (auto& m : document.GetObject()) {
        std::cout << m.name.GetString() << std::endl;
        const rapidjson::Value& gameObject = document[m.name.GetString()];

        //Get full filepath and print just the file name
        const rapidjson::Value& objName = gameObject["objName"];
        assert(objName.IsString());
        std::string filePath = objName.GetString();
        std::size_t split = filePath.find_last_of("/\\");  
        std::cout << filePath.substr(split+1)<< std::endl;
      
        //Get position and print out individual x,y,z vals
        const rapidjson::Value& objPosition = gameObject["position"];
        assert(objPosition.IsArray());
        std::cout << "Position:" << std::endl;
        for (int i = 0; i < objPosition.Size(); i++) {
            std::cout << std::to_string(objPosition[i].GetFloat()) << std::endl;
        }

        //Get scale and print out individual x,y,z vals
        const rapidjson::Value& objScale = gameObject["scale"];
        assert(objScale.IsArray());
        std::cout << "Scale:" << std::endl;
        for (int i = 0; i < objScale.Size(); i++) {
            std::cout << std::to_string(objScale[i].GetFloat()) << std::endl;
        }

        //Get rotation and print out individual x,y,z vals
        const rapidjson::Value& objRotation = gameObject["rotation"];
        assert(objRotation.IsArray());
        std::cout << "Rotation:" << std::endl;
        for (int i = 0; i < objRotation.Size(); i++) {
            std::cout << std::to_string(objRotation[i].GetFloat()) << std::endl;
        }

        std::cout << "" << std::endl;
    }

    return 0;
}