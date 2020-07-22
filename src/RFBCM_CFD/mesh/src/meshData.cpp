#include "meshData.hpp"
#include "constantValueBC.hpp"
#include "readFromMsh.hpp"
#include "rectangle.hpp"

#include <iostream>

MeshData::MeshData(std::shared_ptr<controlData> inControlData)
    : controlData_(inControlData),
      numOfNodes_(),
      groupToNodesMap_(),
      nodes_(),
      normals_(),
      nodesToGroup_(),
      isReadGood_(false)
{
    std::cout << "MeshData" << std::endl;

    meshType meshType = controlData_->paramsDataAt({"geometryControl", "type"});

    std::map<std::string, std::vector<int>> groupToNodesMapBeforeCompact;

    bool isReadSuccess;
    if (meshType == meshType::DEFAULT)
    {
        std::cout << "read nodes from msh file" << std::endl;

        const std::string meshFileName =
            controlData_->paramsDataAt({"geometryControl", "fileName"})
                .get<std::string>();

        const std::string absPath =
            controlData_->workingDir().concat("/" + meshFileName).string();

        isReadGood_ = readFromMsh(absPath, nodes_, normals_,
                                  groupToNodesMapBeforeCompact);
    }
    else if (meshType == meshType::RECTNAGLE)
    {
        std::cout << "create rectangle mesh and read from msh file"
                  << std::endl;
    }
    else
    {
        std::cout << "mesh type is not defined" << std::endl;
    }

    if (isReadGood())
    {
        numOfNodes_ = nodes_.size();
        kdTree_ =
            KDTreeEigenAdaptor<std::vector<vec3d<double>>, double, 3>(nodes_);
        buildGroupAndMap(groupToNodesMapBeforeCompact);
    }
}

void MeshData::buildGroupAndMap(
    const std::map<std::string, std::vector<int>>& groupToNodesMapBeforeCompact)
{
    nodesToGroup_.resize(nodes_.size());
    nodesToBC_.resize(nodes_.size());
    groupToNodesMap_.clear();
    groupToBCMap_.clear();

    // build nodesToGroup_: constantValue
    const auto& constantValueBCData = controlData_->paramsDataAt(
        {"physicsControl", "boundaryConditions", "constantValue"});

    for (const auto& oneBCData : constantValueBCData)
    {
        const std::string groupName = oneBCData.at("groupName");

        for (const int& nodeIndex : groupToNodesMapBeforeCompact.at(groupName))
        {
            nodesToGroup_[nodeIndex] = groupName;
        }

        auto constantValueBC =
            std::make_shared<ConstantValueBC>(oneBCData.at("value"));
        groupToBCMap_.insert({groupName, constantValueBC});
    }

    // build groupToNodesMap_
    for (int nodeID = 0; nodeID < nodes_.size(); nodeID++)
    {
        groupToNodesMap_[nodesToGroup_[nodeID]].push_back(nodeID);
    }

    // build nodesToBC_
    for (const auto& [gropName, nodesID] : groupToNodesMap_)
    {
        for (const int& nodeID : nodesID)
        {
            nodesToBC_[nodeID] = groupToBCMap_[gropName];
        }
    }
}

nodesCloud MeshData::neighborNodesCloud(const int nodeID, const int neighborNum)
{
    std::vector<size_t> neighboursID(neighborNum);
    std::vector<double> outDistSqr(neighborNum);
    kdTree_.query(nodeID, neighborNum, &neighboursID[0], &outDistSqr[0]);

    nodesCloud cloud(neighborNum);
    for (int i = 0; i < neighborNum; i++)
    {
        cloud.id[i] = neighboursID[i];
        cloud.nodes[i] = nodes_[neighboursID[i]];
    }

    return cloud;
}
