#ifndef A3_MODELIMPORTER_H
#define A3_MODELIMPORTER_H

#include <vector>

class a3Scene;
class a3Shape;

class a3ModelImporter
{
public:
    a3ModelImporter();

    std::vector<a3Shape*>* load(const char* filePath);

private:
    class a3Importer;
    a3Importer* importer;

    //a3Scene* scene
};

#endif