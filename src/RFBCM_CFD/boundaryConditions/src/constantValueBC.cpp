#include "constantValueBC.hpp"
#include <iostream>

ConstantValueBC::ConstantValueBC(const double constValue)
    : BoundaryCondition(), constValue_(constValue){};

void ConstantValueBC::fillCoeffMatrix(
    const int nodeID, const nodesCloud& cloud,
    std::shared_ptr<MQBasis> RBFBasis,
    Eigen::SparseMatrix<double>& spMatrix) const
{
    // Eigen::VectorXd localVector =
    //     RBFBasis->collectOnNodes(nodesCloud, rbfOperatorType::LAPLACE);

    // for (int i = 0; i < nodesCloudID.size(); i++)
    // {
    //     spMatrix.insert(nodeID, nodesCloudID[i]) = localVector[i];
    // }

    spMatrix.insert(nodeID, nodeID) = 1.0;
}

void ConstantValueBC::fillRhsVector(const int nodeID, const nodesCloud& cloud,
                                    std::shared_ptr<MQBasis> RBFBasis,
                                    Eigen::VectorXd& rhsVec) const
{
    rhsVec(nodeID) = constValue_;
}

// boundaryConditionType ConstantValueBC::type()
// {
//     return boundaryConditionType::constantValue;
// };

// void ConstantValueBC::setRHSValue(double &oneRHS){

// };

// constantValueBC::addNode(const int index)
// {
//     nodeIndices_.push_back(index);
// }