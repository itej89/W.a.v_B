#include "FrameworkImplementation/PublicTypes/EEPROMDetails.h"

namespace fmKinetics
{
           EEPROMDetails::EEPROMDetails(int addrress, int noOfBytes)
            {
                Address  = addrress;
                NoOfBytes = noOfBytes;
            }

            EEPROMDetails::EEPROMDetails(int addrress, int noOfBytes, int isSigned)
            {
                Address  = addrress;
                NoOfBytes = noOfBytes;
                SignedValue = isSigned;
            }
}