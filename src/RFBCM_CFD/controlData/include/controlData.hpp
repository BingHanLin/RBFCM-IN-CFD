#ifndef CONTROLDATA_HPP
#define CONTROLDATA_HPP

#include <filesystem>

#include "json.h"

class controlData
{
   public:
    controlData(const std::filesystem::path workingDir_ =
                    std::filesystem::current_path());

    std::filesystem::path workingDir() const;
    std::filesystem::path vtkDir() const;
    nlohmann::json paramsDataAt(const std::vector<std::string> searchEntries);

   private:
    void readParamsData();

    std::filesystem::path workingDir_;
    nlohmann::json paramsData_;
};

#endif
