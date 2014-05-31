
#ifndef _CONSTANT_TIME_GROUP_COLLECTION_H_
#define _CONSTANT_TIME_GROUP_COLLECTION_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <deque>
#include <math.h>
#include "Random.h"
#include "ConstantTimeGroup.h"

namespace StochLib
{
 class ConstantTimeGroupCollection
 {
 public:

  ConstantTimeGroupCollection(std::size_t numberOfReactions);

  void build(std::vector<double> &propensities);
  void update(std::size_t reactionIndex, double oldPropensity, double newPropensity);

  int selectReaction(StochLib::RandomGenerator &randomGenerator);

  double getPropensitySum();

  int getGroup(double propensityValue);

  void addGroup(int groupExponent);

  void recalculatePropensitySum();

#ifdef DEBUG
  void printGroups();
#endif

 private:
  ConstantTimeGroupCollection();

  std::deque<ConstantTimeGroup> groups;

  double propensitySum;
  int maxGroupExponent;
  int minGroupExponent;

  std::vector<int> withinGroupIndexes;

#ifdef DEBUG
 public:
#endif
  int selectGroupIndex(StochLib::RandomGenerator &randomGenerator);
 };
}

#endif

