#ifndef BOUNDARYCONDITIONS_HPP
#define BOUNDARYCONDITIONS_HPP

#include "MQBasis.hpp"
#include "dataStructure.hpp"
#include "enumMap.hpp"

#include <Eigen/Dense>
#include <Eigen/Sparse>

class MeshData;

class BoundaryCondition
{
   public:
    BoundaryCondition(MeshData* mesh);

    virtual void fillCoeffMatrix(
        const size_t nodeID, std::shared_ptr<MQBasis> RBFBasis,
        Eigen::SparseMatrix<double>& spMatrix) const = 0;

    virtual void fillRhsVector(const size_t nodeID,
                               std::shared_ptr<MQBasis> RBFBasis,
                               Eigen::VectorXd& rhsVec) const = 0;

   protected:
    MeshData* mesh_;
};

#endif