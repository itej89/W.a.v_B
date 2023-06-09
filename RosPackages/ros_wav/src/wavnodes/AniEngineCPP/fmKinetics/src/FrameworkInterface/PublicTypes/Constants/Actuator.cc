#include "FrameworkImplementation/PublicTypes/Constants/Actuator.h"
namespace fmKinetics
{
    Actuator::Actuator(){}

    Actuator::Actuator(int value) {
        Value = (etype)value;
    }

    int Actuator::getValue() {
        return Value;
    }
}