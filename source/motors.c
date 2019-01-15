#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "brick.h"
#include "motors.h"
#include "bluetooth.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#define M_PI 3.14159265358979323846
#define SPEED 250
//////////////////////////////////////////////////
#endif

// function to move forward a set distance given by the parameters distance
void move_forward (int distance)
{
  uint8_t sn;
  int port=65;
  // computation of the time necessary to move of the corresponding distance
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(port, time, SPEED);
  port=68;
  sg_motor(port, time, SPEED);
  Sleep(time);
}

// function to move backward a set distance given by the parameters distance
void move_backward (int distance)
{
  uint8_t sn;
  int port=65;
  // computation of the time necessary to move of the corresponding distance
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(port, time, -SPEED);
  port=68;
  sg_motor(port, time, -SPEED);
  Sleep(time);
}

// function to turn right using the gyroscope
void turn_gyro_right(float degree)
{
  uint8_t sn_gyro;
  uint8_t sn_motorA;
  uint8_t sn_motorB;
  int port_gyro = 50;
  int port_motorA = 65;
  int port_motorD = 68;
  float angle;
  float og_angle;
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 ) &&
  ev3_search_tacho_plugged_in(port_motorA,0, &sn_motorA, 0 ) &&
  ev3_search_tacho_plugged_in(port_motorD,0, &sn_motorB, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    get_sensor_value0(sn_gyro, &angle );
    og_angle=angle % 360.0;
    while (abs(angle%360.0-og_angle) <= degree)
    {
      printf("og_angle = %d, angle = %d, diff = %d\n", og_angle, angle%360.0, angle%360.0-og_angle);
      fflush(stdout);
      get_sensor_value0(sn_gyro, &angle);
      set_tacho_speed_sp( sn_motorA, -30);
      set_tacho_time_sp(sn_motorB, 30);
      set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
      set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    }
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
  }
}

// function to turn left
void turn_left (int degree)
{
      //printf("enter into the function turn\n");
      uint8_t sn;
      int port=65;
      int time;
      time = 60*degree; // 540/180 : 540 time  3 factor
      sg_motor(port, time, 30);
      port=68;
      sg_motor(port, time, -30);
      Sleep(time);
}

// function to turn right
void turn_right (int degree)
{
      //printf("enter into the function turn\n");
      uint8_t sn;
      int port=65;
      int time;
      time = 60*degree; // 540/180 : 540 time  3 factor
      sg_motor(port, time, -30);
      port=68;
      sg_motor(port, time, 30);
      Sleep(time);
}

// function to run a single motor during a given time at a given speed
void sg_motor (int port, int time, int speed)
{
    uint8_t sn;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      //printf("Motor on port %d run at speed = %d\n", port, speed );
      set_tacho_stop_action_inx( sn, TACHO_COAST );
      set_tacho_speed_sp( sn, speed);
      set_tacho_time_sp( sn, time );
      set_tacho_command_inx( sn, TACHO_RUN_TIMED );
    }
}

// funcion to turn a quarter turn on the left
void quarter_turn (void)
{
  uint8_t sn;
  int port=65;
  sg_motor(port, 540, 300);
  port=68;
  sg_motor(port, 540, -300);
}

// function to permform a 3 point throw
void throw (void)
{
  uint8_t sn;
  int port=67;
  if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
    // set the position
    set_tacho_position_sp(sn, 140);
    // set the speed
    set_tacho_speed_sp( sn, 1049);
    // initiate the command with the position and speed given previously
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);

    Sleep(500);

    set_tacho_position_sp(sn, -30);
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
    set_tacho_stop_action_inx( sn, TACHO_COAST );
//TO DO : decomment only after the merge with bluetooth
//    robotscore();
  }
}


// function to perform the initial throw
void initial_throw(void)
{
  int motor_lift = 66;
  // throw the first ball
  throw();
  // turn the inner motor, the motor which perform the action of lifting the ball
  sg_motor(motor_lift,1000,-300);
  // throw the second ball
  throw();
}

// function to disable catapult
void disable_catapult(void)
{
    uint8_t sn;
    int port=67;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      printf("disable_catapult\n");

      set_tacho_position_sp(sn, 140);
      set_tacho_speed_sp( sn, 500);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);

      Sleep(1000);
    }
}

// function to enable the catapult 
void enable_catapult(void)
{
    uint8_t sn;
    int port=67;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
        printf("enable_catapult\n" );

      set_tacho_position_sp(sn, -140);
      set_tacho_speed_sp( sn, 500);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      set_tacho_stop_action_inx( sn, TACHO_COAST );

      Sleep(1000);


    }
}

// function to get the ball
void get_ball(int move_value)
{
    int motor_lift = 66;

    printf( "%d this is the color\n", val);
    fflush( stdout );
    printf("get_ball\n" );

    disable_catapult();

    move_forward(move_value/10 + 8);

    enable_catapult();
    
    // turn the inner motor, the motor which perform the action of lifting the ball
    sg_motor(motor_lift,1000,-300);

    Sleep(3000);

    move_backward(move_value/10 + 8);
}

// function to search the ball 
void search_ball(void)
{
    int i;
    float current_value, previous_value;
    uint8_t sn_sonar;
    int angle;
    int prev_distance=10000;
    int threshold = 50;
    int flag_detected = 0;

    printf("SONAR found, reading sonar. It will print 36 values \n");
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
        if ( !get_sensor_value0(sn_sonar, &previous_value )) {
            previous_value = 0;
        }
        // the robot will rotate and search for the ball accordingly to the protocol define below
        for(i=0; i < 36; i++)
        {
          turn_left(5);
          angle = i*5;
          // get the value of the sonar sensor
          if ( !get_sensor_value0(sn_sonar, &current_value )) {
            current_value = 0;
          }

          printf( "\r%d : current value %f, previous value %f \n", angle, current_value,previous_value);
          // the two followin condition express our way to detect the ball 
          if ((previous_value - current_value > threshold) && (previous_value < 500)) {
              printf("Ball detected\n");
              fflush( stdout );
              Sleep(5000);
              printf("%d\n",i);
              fflush( stdout );

              flag_detected = 1;
              break;
          }
          if ((current_value - previous_value > threshold) && (previous_value < 500)) {
              printf("Ball missed but then detected\n");
              turn_right(10);
              Sleep(5000);
              flag_detected = 1;
              printf("%d\n",i);
              fflush( stdout );

              i -= 3;
              break;
          }
          previous_value = current_value;
          fflush( stdout );
        }
        // if the ball is detected it perform a turn
        if (flag_detected){

            turn_left(6);
            turn_left(165);
          
            get_ball(current_value);
            
            turn_right(165);
        }

        // get back to the initial angle
        while(i>1)
        {
          turn_right(5);

          printf("%d\n",i);
          fflush( stdout );
          i--;
        }
        turn_right(6);
        // if the ball is detected then it throw the ball
        if (flag_detected){
            throw();
        }
    }
}
