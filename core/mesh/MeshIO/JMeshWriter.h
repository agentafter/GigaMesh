//
// Created by timo.homburg on 20.01.2025.
//

#ifndef GIGAMESH_JMESHWRITER_H
#define GIGAMESH_JMESHWRITER_H
#include <fstream>
#include <iostream>
#include "MeshWriter.h"

class JMeshWriter : public MeshWriter {


public:
    JMeshWriter() = default;

    // MeshWriter interface
public:
    bool writeFile(const std::filesystem::path& rFilename, const std::vector<sVertexProperties>& rVertexProps, const std::vector<sFaceProperties>& rFaceProps, MeshSeedExt& rMeshSeed) override;

};

#endif //GIGAMESH_JMESHWRITER_H
