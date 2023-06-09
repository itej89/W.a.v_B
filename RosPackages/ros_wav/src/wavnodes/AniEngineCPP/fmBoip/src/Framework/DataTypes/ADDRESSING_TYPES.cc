

#include "Framework/DataTypes/ADDRESSING_TYPES.h"

namespace fmBoip
{

    std::map<std::string, ADDRESSING_TYPES::MessageType> ADDRESSING_TYPES::ANI_DOIPTesterAddressingTypeMap;

    ADDRESSING_TYPES::ADDRESSING_TYPES()
    {
        ANI_DOIPTesterAddressingTypeMap.insert(std::make_pair<std::string, MessageType>("Physical", PHYSICAL));
        ANI_DOIPTesterAddressingTypeMap.insert(std::make_pair<std::string, MessageType>("Functional", FUNCTIONAL));
    }
}
