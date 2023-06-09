#pragma once

#include <string.h>

#include "Framework/DataTypes/Constants/CommandLabels.h"

using std::string;

namespace fmKinetics
{
class MachineCommandHelper
{
public:

  int ConvertAngleToPWMValue(int Angle);

  int GetResponseCountForCommand(string CommandType);

  int GetResponseCountForCommand(CommandLabels::CommandTypes::etype CommandType);
};
} // namespace fmKinetics