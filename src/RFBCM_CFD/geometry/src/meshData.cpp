#include "meshData.hpp"
#include "rectangle.hpp"
#include <iostream>

MeshData::MeshData(nlohmann::json& geometryControlParams)
    : geometryControlParams_(geometryControlParams),
      numInnNodes_(0),
      numBouNodes_(0),
      numAllNodes_(0),
      groupToNodesMap_(),
      nodeToGoupMap_(),
      nodes_(),
      normals_()
{
    if (geometryControlParams_.at("Type") == meshTypeEnum::DEFAULT)
    {
        std::cout << "read nodes from msh file" << std::endl;
        bool isReadSuccess = readFromMsh(geometryControlParams_.at("Path"),
                                         nodes_, groupToNodesMap_);
    }
    else if (geometryControlParams_.at("Type") == meshTypeEnum::RECTNAGLE)
    {
        std::cout << "create rectangle mesh and read from msh file"
                  << std::endl;
    }
    else
    {
        std::cout << "mesh type is not defined" << std::endl;
    }
}