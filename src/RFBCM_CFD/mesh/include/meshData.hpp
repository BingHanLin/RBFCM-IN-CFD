#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include "KDTreeEigenAdaptor.hpp"
#include "boundaryCondition.hpp"
#include "controlData.hpp"
#include "dataStructure.hpp"
#include "enumMap.hpp"
#include "json.h"
#include <vector>

/*************************************************************************


*************************************************************************/

class MeshData
{
   public:
    MeshData(std::shared_ptr<controlData> inControlData);
    ~MeshData(){};

    // std::map<int, std::string> nodeToGoupMap_;
    // std::map<std::string, boundaryCondition> groupToBoundaryConditionMap_;
    // std::map<int, boundaryCondition> nodeToBoundaryConditionMap_;

    std::vector<vec3d<double>>& nodes();
    int numOfNodes() const;
    bool isReadGood() const;

    std::shared_ptr<BoundaryCondition> nodeBC(const int nodeID) const;

    nodesCloud neighborNodesCloud(const int nodeID, const int neighborNum);

    // std::shared_ptr<BoundaryCondition> nodesBC(const int nodeID) const;

   private:
    std::shared_ptr<controlData> controlData_;
    std::vector<vec3d<double>> nodes_;
    std::vector<vec3d<double>> normals_;

    std::map<std::string, std::vector<int>> groupToNodesMap_;
    std::map<std::string, std::shared_ptr<BoundaryCondition>> groupToBCMap_;

    std::vector<std::shared_ptr<BoundaryCondition>> nodesToBC_;
    std::vector<std::string> nodesToGroup_;

    KDTreeEigenAdaptor<std::vector<vec3d<double>>, double, 3> kdTree_;

    int numOfNodes_;
    bool isReadGood_;

    void buildGroupAndMap(const std::map<std::string, std::vector<int>>&
                              groupToNodesMapBeforeCompact);
};

inline std::vector<vec3d<double>>& MeshData::nodes()
{
    return nodes_;
}

inline std::shared_ptr<BoundaryCondition> MeshData::nodeBC(
    const int nodeID) const
{
    return nodesToBC_[nodeID];
}

inline int MeshData::numOfNodes() const
{
    return numOfNodes_;
}

inline bool MeshData::isReadGood() const
{
    return isReadGood_;
}

#endif
