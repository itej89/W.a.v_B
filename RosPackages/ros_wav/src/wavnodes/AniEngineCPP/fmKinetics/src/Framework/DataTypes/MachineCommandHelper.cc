#include "Framework/DataTypes/MachineCommandHelper.h"

namespace fmKinetics
{

int MachineCommandHelper::ConvertAngleToPWMValue(int Angle)
{
    return (((2400 - 544) / 180) * (Angle)) + 544;
}

int MachineCommandHelper::GetResponseCountForCommand(string CommandType)
{
    using namespace CommandLabels;
    CommandTypes _CommandTypes;
    return _CommandTypes.CommandResponseCount.at(CommandTypes().stringtoenum.at(CommandType));
}

int MachineCommandHelper::GetResponseCountForCommand(CommandLabels::CommandTypes::etype CommandType)
{
    using namespace CommandLabels;
    CommandTypes _CommandTypes;
    return (_CommandTypes.CommandResponseCount.at(CommandType));
}

} // namespace fmKinetics