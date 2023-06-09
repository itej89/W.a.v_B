#pragma once

#include "GlobalContext.h"

#include <BackEase.h>
#include <BounceEase.h>
#include <CircularEase.h>
#include <CubicEase.h>
#include <EasingBase.h>
#include <EasingConstants.h>
#include <EasingLibrary.h>
#include <ElasticEase.h>
#include <ExponentialEase.h>
#include <LinearEase.h>
#include <QuadraticEase.h>
#include <SineEase.h>
#include <SineWaveEase.h>
#include <TriangularEase.h>
#include <TriangularWaveEase.h>
#include <SpringWaveEase.h>

#include "PrintHandler.h"

BackEase backEase;                  
BounceEase bounceEase;
CircularEase circularEase;
ElasticEase elasticEase;
ExponentialEase exponentialEase;
LinearEase linearEase;
QuadraticEase quadraticEase;
SineEase sineEase;
TriangularEase triangularEase;
TriangularWaveEase triangularWaveEase;
SineWaveEase sineWaveEase;
SpringWaveEase springWaveEase;
SineEase sineEase_Left;
SineEase sineEase_Right;


/*
 * Function to initialize the requested easing funciton for the actuator actor motion
 */
void ready_easing_curve(unsigned int MOTION_MARKER_ANGLE){

        int angle_change = ((int)DATA_REGISTERS_WORKING_COPY->ANGLE-(int)MOTION_MARKER_ANGLE);
        switch(DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION){
            case SIN:
               sineEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
               sineEase.setTotalChangeInPosition(abs(angle_change));
               break;
            case QAD:
              quadraticEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              quadraticEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case LIN:
              linearEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              linearEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case EXP:
              exponentialEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              exponentialEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case ELA:
              elasticEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              elasticEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case CIR:
              circularEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              circularEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case BOU:
              bounceEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              bounceEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case BAK:
              backEase.setDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              backEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case TRI:
              triangularEase.setDuration(DATA_REGISTERS_WORKING_COPY->FREQUENCY);
              triangularEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case TRW:
              triangularWaveEase.setDuration(DATA_REGISTERS_WORKING_COPY->FREQUENCY);
              triangularWaveEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case SNW:
              sineWaveEase.setDuration(DATA_REGISTERS_WORKING_COPY->FREQUENCY);
              sineWaveEase.setTotalChangeInPosition(abs(angle_change));
              break;
            case SPR:
              springWaveEase.setDuration(DATA_REGISTERS_WORKING_COPY->FREQUENCY);
              springWaveEase.setSpringWaveDamping(DATA_REGISTERS_WORKING_COPY->DAMPING);
              springWaveEase.setSpringWaveVelocity(DATA_REGISTERS_WORKING_COPY->VELOCITY);
              springWaveEase.setTotalDuration(DATA_REGISTERS_WORKING_COPY->TIMING);
              springWaveEase.setTotalChangeInPosition(abs(angle_change));  
              break;
          }
              
}
