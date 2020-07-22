#include "controlData.hpp"
#include <fstream>
#include <iostream>

controlData::controlData(const std::filesystem::path workingDir_)
    : workingDir_(workingDir_)
{
    std::cout << "working directory: " << workingDir_.string() << std::endl;
    readParamsData();
}

void controlData::readParamsData()
{
    std::ifstream paramsStream(workingDir().concat("/params.json").string());
    if (paramsStream.good())
    {
        paramsStream >> paramsData_;
    }
}

std::filesystem::path controlData::workingDir() const
{
    return workingDir_;
}

std::filesystem::path controlData::vtkDir() const
{
    return workingDir().concat("/vtk");
}

nlohmann::json controlData::paramsDataAt(
    const std::vector<std::string> searchEntries)
{
    nlohmann::json queryJSON = paramsData_;

    for (auto oneEntry : searchEntries)
    {
        queryJSON = queryJSON.at(oneEntry);
    }
    return queryJSON;
}
