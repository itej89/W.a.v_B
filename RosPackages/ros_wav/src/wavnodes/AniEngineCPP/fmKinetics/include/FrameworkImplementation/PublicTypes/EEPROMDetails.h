#pragma once 

namespace fmKinetics
{
    class EEPROMDetails
    {
    public:
            int Address;
            int NoOfBytes;
            bool SignedValue = false; //Sign will be stored in EEPROm in last byte as 0 for Positive and 1 for negative

            EEPROMDetails(int addrress, int noOfBytes);

            EEPROMDetails(int addrress, int noOfBytes, int isSigned);

    };

}