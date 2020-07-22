#include "MQBasis.hpp"
#include "controlData.hpp"
#include "json.h"
#include "meshData.hpp"
#include "simulationDomain.hpp"

#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    // ****************************************************************************
    // parse arguemnt
    // ****************************************************************************
    cxxopts::Options options("RBFCM CFD",
                             "Radial basis function collocation method (RBFCM) "
                             "for computational fluid dynamics");

    options.add_options()("c,case", "Case Path", cxxopts::value<std::string>())(
        "h,help", "Print usage");

    auto optionResult = options.parse(argc, argv);

    if (optionResult.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // ****************************************************************************
    // build control data
    // ****************************************************************************
    std::shared_ptr<controlData> myControlData;
    if (optionResult.count("case"))
        myControlData = std::make_shared<controlData>(
            optionResult["case"].as<std::string>());
    else
        myControlData = std::make_shared<controlData>();

    // ****************************************************************************
    // Build mesh data
    // ****************************************************************************
    auto myMeshData = std::make_shared<MeshData>(myControlData);
    if (!myMeshData->isReadGood()) return 0;

    // ****************************************************************************
    // Define RBF Type
    // ****************************************************************************
    auto myRBFBasis = std::make_shared<MQBasis>(myControlData);

    // ****************************************************************************
    // Define Solver
    // ****************************************************************************
    SimulationDomain mySimulationDomain(myControlData, myMeshData, myRBFBasis);
    mySimulationDomain.solveDomain();

    std::cout << "test ok" << std::endl;
    return 0;
}