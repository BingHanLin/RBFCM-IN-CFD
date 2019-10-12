
#include "rectangle.hpp"
#include <assert.h>
#include <iostream>
// #include <math.h>
// #include <stdio.h>

Rectangle::Rectangle(int numNodeX, int numNodeY, double sizeX_, double sizeY)
    : numNodeX_(numNodeX),
      numNodeY_(numNodeY),
      sizeX_(sizeX_),
      sizeY_(sizeY),
      centerX_(0.0),
      centerY_(0.0),
      numInnNodes_(0),
      numBouNodes_(0),
      numAllNodes_(0),
      nodes_(),
      normals_()
{
    numInnNodes_ = numNodeX * numNodeY_;
    numBouNodes_ = 2 * numNodeX + 2 * numNodeY_;
    numAllNodes_ = numInnNodes_ + numBouNodes_;

    for (int i = 0; i < numAllNodes_; i++)
    {
        nodes_.push_back(getAllNode(i + 1));
    }

    for (int i = 0; i < numBouNodes_; i++)
    {
        normals_.push_back(getOutNormal(i + 1));
    }

    std::cout << "Rectangular nodes are distributed." << std::endl;

    std::cout << "Number of inner nodes: " << numInnNodes_ << "\n"
              << "Number of boundary nodes: " << numBouNodes_ << "\n"
              << "Number of all nodes: " << numAllNodes_ << std::endl;
}

std::vector<double> Rectangle::getInnerNode(int i) const
{
    assert(i >= 1 && i <= numNodeX_ * numNodeY_);

    std::vector<double> temp(2);

    int I = (i - 1) / numNodeX_;
    int J = (i - 1) % numNodeX_;

    temp[0] = ((double)(J) + 0.5) * sizeX_ / (double)(numNodeX_);
    temp[1] = ((double)(I) + 0.5) * sizeY_ / (double)(numNodeY_);

    temp[0] = temp[0] - sizeX_ / 2. + centerX_;
    temp[1] = temp[1] - sizeY_ / 2. + centerY_;

    return temp;
}

std::vector<double> Rectangle::getBoundaryNode(int i) const
{
    assert(i >= 1 && i <= 2 * (numNodeY_ + numNodeX_));

    std::vector<double> temp(2);

    if (i <= numNodeX_)
    {
        temp[0] = (double)(i - 1) * sizeX_ / (double)(numNodeX_) +
                  .5 * sizeX_ / (double)(numNodeX_);
        temp[1] = sizeY_;
    }
    else if (i <= numNodeX_ + numNodeY_)
    {
        temp[0] = sizeX_;
        temp[1] = sizeY_ - .5 * sizeY_ / (double)(numNodeY_) -
                  (double)(i - numNodeX_ - 1) * sizeY_ / (double)(numNodeY_);
    }
    else if (i <= numNodeX_ + numNodeY_ + numNodeX_)
    {
        temp[0] = sizeX_ - .5 * sizeX_ / (double)(numNodeX_) -
                  (double)(i - numNodeX_ - numNodeY_ - 1) * sizeX_ /
                      (double)(numNodeX_);
        temp[1] = 0.;
    }
    else
    {
        temp[0] = 0.;
        temp[1] = (double)(i - numNodeX_ - numNodeY_ - numNodeX_ - 1) * sizeY_ /
                      (double)(numNodeY_) +
                  .5 * sizeY_ / (double)(numNodeY_);
    }

    temp[0] = temp[0] - sizeX_ / 2. + centerX_;
    temp[1] = temp[1] - sizeY_ / 2. + centerY_;

    return temp;
}

std::vector<double> Rectangle::getAllNode(int i) const
{
    assert(i >= 1 && i <= numNodeX_ * numNodeY_ + 2 * (numNodeY_ + numNodeX_));

    std::vector<double> temp(2);

    if (i <= numNodeX_ * numNodeY_)
        return getInnerNode(i);
    else
        return getBoundaryNode(i - numNodeX_ * numNodeY_);
}

std::vector<double> Rectangle::getOutNormal(int i) const
{
    assert(i >= 1 && i <= 2 * (numNodeY_ + numNodeX_));

    std::vector<double> temp(2);

    if (i <= numNodeX_)
    {
        temp[0] = 0.0;
        temp[1] = 1.0;
    }
    else if (i <= numNodeX_ + numNodeY_)
    {
        temp[0] = 1.0;
        temp[1] = 0.0;
    }
    else if (i <= numNodeX_ + numNodeY_ + numNodeX_)
    {
        temp[0] = 0.0;
        temp[1] = -1.0;
    }
    else
    {
        temp[0] = -1.0;
        temp[1] = 0.0;
    }

    return temp;
}
