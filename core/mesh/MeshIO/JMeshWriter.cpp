//
// Created by timo.homburg on 20.01.2025.
//

#include "JMeshWriter.h"
#include <fstream>
#include <iostream>

bool JMeshWriter::writeFile(const std::filesystem::path &rFilename, const std::vector<sVertexProperties> &rVertexProps,
                           const std::vector<sFaceProperties> &rFaceProps, MeshSeedExt &rMeshSeed) {
    std::fstream filestr;
    filestr.imbue(std::locale("C"));
    filestr.open(rFilename, std::fstream::out);
    if (!filestr.is_open()) {
        std::cerr << "[JSONWriter] Could not open file: '" << rFilename << "'.\n";
        return false;
    }
    filestr << "{\n";
    return true;
};
