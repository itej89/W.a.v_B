#pragma once


#include "GlobalContext.h"
#include "EasingFunctions.h"
#include "CommandHandler.h"



typedef struct MotionRuntimeParameters{
    //Final Angle(in PWM DUTYCYCLE) at which servo motion completed for last trigger
      unsigned int MOTION_MARKER_ANGLE;

    /*
     * Parameter to be used during motion
     */
    //Runtime Easing Angle(in PWM DUTYCYCLE) - 
    //  this should be updated as marker angle after motion completion 
      unsigned int CURRENT_ANGLE;
     //Runtime Easing step Time
      int CURRENT_STEP_TIME;
     //latest step of angle from marker that is calculated by easing function
      double EASING_STEP;
  };

  
//Structure variable that maintains the runtime parameters
MotionRuntimeParameters MOTION_PARAMETERS = {1500, 1500, 0, 0};


template<typename T> void moveServo(T ease);

template<typename T> void moveServo(T ease){

      if(MOTION_PARAMETERS.CURRENT_STEP_TIME > DATA_REGISTERS_WORKING_COPY->TIMING)
      {
        MOTION_PARAMETERS.CURRENT_STEP_TIME = DATA_REGISTERS_WORKING_COPY->TIMING;
      }

      switch(DATA_REGISTERS_WORKING_COPY->EASING_CURVE_TYPE)
      {
        case IN:
        MOTION_PARAMETERS.EASING_STEP = ease.easeIn(MOTION_PARAMETERS.CURRENT_STEP_TIME);
        break;
        case OU:
        MOTION_PARAMETERS.EASING_STEP = ease.easeOut(MOTION_PARAMETERS.CURRENT_STEP_TIME);
        break;
        case IO:
        MOTION_PARAMETERS.EASING_STEP = ease.easeInOut(MOTION_PARAMETERS.CURRENT_STEP_TIME);
        break;
      }

      
      DEBUG_PRINT_STRING("Moving Servo : ");
      DEBUG_PRINT_STRING("\n");
      DEBUG_PRINT_STRING("MOTION_MARKER_ANGLE : ");
      DEBUG_PRINT_VALUE(MOTION_PARAMETERS.MOTION_MARKER_ANGLE);
      DEBUG_PRINT_STRING("\n");
      DEBUG_PRINT_STRING("CURRENT_ANGLE : ");
      DEBUG_PRINT_VALUE(MOTION_PARAMETERS.CURRENT_ANGLE);
      DEBUG_PRINT_STRING("\n");
      DEBUG_PRINT_STRING("REquested ANGLE : ");
      DEBUG_PRINT_VALUE(DATA_REGISTERS_WORKING_COPY->ANGLE);
      DEBUG_PRINT_STRING("\n");
      DEBUG_PRINT_STRING("EASING_STEP : ");
      DEBUG_PRINT_VALUE(MOTION_PARAMETERS.EASING_STEP);
      DEBUG_PRINT_STRING("\n");
        
      if(MOTION_PARAMETERS.MOTION_MARKER_ANGLE < DATA_REGISTERS_WORKING_COPY->ANGLE){
          MOTION_PARAMETERS.CURRENT_ANGLE = MOTION_PARAMETERS.MOTION_MARKER_ANGLE + MOTION_PARAMETERS.EASING_STEP;
          servo_motor.writeMicroseconds(MOTION_PARAMETERS.CURRENT_ANGLE);
          _STATUS_REGISTERS->CURRENT_ANGLE = MOTION_PARAMETERS.CURRENT_ANGLE;
      }
      else
       if(MOTION_PARAMETERS.MOTION_MARKER_ANGLE > DATA_REGISTERS_WORKING_COPY->ANGLE){
           MOTION_PARAMETERS.CURRENT_ANGLE = MOTION_PARAMETERS.MOTION_MARKER_ANGLE - MOTION_PARAMETERS.EASING_STEP;
           servo_motor.writeMicroseconds(MOTION_PARAMETERS.CURRENT_ANGLE);
          _STATUS_REGISTERS->CURRENT_ANGLE = MOTION_PARAMETERS.CURRENT_ANGLE;
      }
  }


/*
  Timer2 event handler that provides the time step 
  to compute easing funciton
*/
void SetEasingTime_ms(){
  MOTION_PARAMETERS.CURRENT_STEP_TIME++;
}




void ready_for_motion(){
  MOTION_PARAMETERS.CURRENT_STEP_TIME = 0;
  clone_data_registers();
  ready_easing_curve(MOTION_PARAMETERS.MOTION_MARKER_ANGLE);
}


void handle_motion_requests(){

      if(TRIGGER_REQUEST_COUNT > 0)
      {


        DEBUG_PRINT_STRING("Entered motion loop.");

          TRIGGER_REQUEST_COUNT = 1;
          ready_for_motion();
          delay(DATA_REGISTERS_WORKING_COPY->DELAY);

 
        MsTimer2::start();
            
        while(MOTION_PARAMETERS.CURRENT_STEP_TIME <= DATA_REGISTERS_WORKING_COPY->TIMING && TRIGGER_REQUEST_COUNT == 1)
        {
          
        DEBUG_PRINT_STRING("\n");
        DEBUG_PRINT_STRING("Current step time : ");
        DEBUG_PRINT_VALUE(MOTION_PARAMETERS.CURRENT_STEP_TIME);
        DEBUG_PRINT_STRING("\n");
  
        //Stop current Servo Motion if new motion is triggered
       // if(IsMotionInterruptTriggered) break;
  
        switch(DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION)
        {
          case SIN:
          moveServo(sineEase);
          break;
          case QAD:
          moveServo(quadraticEase);
          break;
          case LIN:
          moveServo(linearEase);
          break;
          case EXP:
          moveServo(exponentialEase);
          break;
          case ELA:
          moveServo(elasticEase);
          break;
          case CIR:
          moveServo(circularEase);
          break;
          case BOU:
          moveServo(bounceEase);
          break;
          case BAK:
          moveServo(backEase);
          break;
          case TRI:
          moveServo(triangularEase);
          break;
          case TRW:
          moveServo(triangularWaveEase);
          break;
          case SNW:
          moveServo(sineWaveEase);
          break;
          case SPR:
          moveServo(springWaveEase);
          break;
        }
        
         delayMicroseconds(100);
        
        }
  
        MsTimer2::stop();
  
        switch(DATA_REGISTERS_WORKING_COPY->EASING_FUNCTION)
        {
          case TRI:
          case TRW:
          case SNW:
          case SPR:
            MOTION_PARAMETERS.MOTION_MARKER_ANGLE = MOTION_PARAMETERS.CURRENT_ANGLE;
            break;
          default:
            MOTION_PARAMETERS.MOTION_MARKER_ANGLE = DATA_REGISTERS_WORKING_COPY->ANGLE;
          
        }
    

        
        DEBUG_PRINT_STRING("Motion ended. TRIGGER_REQUEST_COUNT : ");
        DEBUG_PRINT_VALUE(TRIGGER_REQUEST_COUNT);
        DEBUG_PRINT_STRING("\n");
        
        if(TRIGGER_REQUEST_COUNT > 0)
        {
          TRIGGER_REQUEST_COUNT --;
        }  
      }

      check_calibration_request();
}
