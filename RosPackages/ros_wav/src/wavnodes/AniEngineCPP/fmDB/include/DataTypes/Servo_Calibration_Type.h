#pragma once

#include <string>

#include "Constants/DB_Table_Columns.h"

using std::string;

namespace fmDB
{
    class Servo_Calibration_Type
    {
        public:
            string Name = "";
            int Degree = 0;
            int ADC = 0;



           
            Servo_Calibration_Type(string name, int degree,  int adc)
            {
                Name = name;
                Degree = degree;
                ADC = adc;
            }

            Servo_Calibration_Type(int degree, int adc)
            {
                Degree = degree;
                ADC = adc;
            }

            Servo_Calibration_Type()
            {

            }
    };
}