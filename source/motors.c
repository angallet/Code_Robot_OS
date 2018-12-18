#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "brick.h"
#include "motors.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#define MOTOR_LEFT     OUTD
#define MOTOR_RIGHT    OUTA
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )
#define M_PI 3.14159265358979323846
#define SPEED 250
//////////////////////////////////////////////////
#endif


/*
void quarter_turn(void)
{
  int port=65;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      int max_speed;
      get_tacho_max_speed( sn, &max_speed );
      set_tacho_stop_action_inx( sn, TACHO_COAST );
      set_tacho_speed_sp( sn, max_speed/5);
}
*/
//126cm/10s
//0.126m/s
//12,6cm/s
//distance in centimeter
void move_forward (int distance)
{
  uint8_t sn;
  int port=65;
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(port, time, SPEED);
  port=68;
  sg_motor(port, time, SPEED);
  Sleep(time);
}

void move_backward (int distance)
{
  uint8_t sn;
  int port=65;
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(port, time, -SPEED);
  port=68;
  sg_motor(port, time, -SPEED);
  Sleep(time);
}

void turn_gyro_right(int degree)
{
  uint8_t sn_gyro;
  uint_8 sn_motorA;
  uint_8 sn_motorB;
  int port_gyro = 50;
  int port_motorA = 65;
  int port_motorD = 68;
  int angle;
  int og_angle
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_color, 0 ) &&
  ev3_search_tacho_plugged_in(port_motorA,0, &sn_motorA, 0 ) &&
  ev3_search_tacho_plugged_in(port_motorA,0, &sn_motorA, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    if ( !get_sensor_value0(sn_gyro, &og_angle )) {
      og_angle=0;
    }
    while (angle-og_angle <= degree)
    {
      printf("og_angle = %d, angle = %d, diff = %d\n", og_angle, angle, angle-og_angle);
      fflush();
      get_sensor_value(sn_gyro, &angle);
      set_tacho_speed_sp( sn_motorA, -30);
      set_tacho_time_sp(sn_motorB, 30);
      set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
      set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    }
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
}

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


void sg_motor_deg (int port, int deg, int speed)
{
    uint8_t sn;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      set_tacho_stop_action_inx( sn, TACHO_COAST );
      set_tacho_position_sp(sn, deg);
      set_tacho_speed_sp( sn, speed);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
    }
}

void sg_motor (int port, int time, int speed)
{
    uint8_t sn;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      //printf( "LEGO_EV3_M_MOTOR 1 is found, run...\n" );
      //printf("  speed = %d\n", speed );
      set_tacho_stop_action_inx( sn, TACHO_COAST );
      set_tacho_speed_sp( sn, speed);
      set_tacho_time_sp( sn, time );
      set_tacho_command_inx( sn, TACHO_RUN_TIMED );
    }
}




void init_motors(void)
{
    if (tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_))
    {
        tacho_reset(MOTOR_BOTH);
        set_tacho_stop_action_inx(MOTOR_BOTH, TACHO_COAST);
        printf("Motors found\n");
    }
    else
    {
        printf("Check the connection of the motor, ");
        printf("unable to establish connection");
    }
}


void quarter_turn (void)
{
  uint8_t sn;
  int port=65;
  sg_motor(port, 540, 300);
  port=68;
  sg_motor(port, 540, -300);
}

void throw (void)
{
  uint8_t sn;
  int port=67;
  if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
    set_tacho_position_sp(sn, 140);
    set_tacho_speed_sp( sn, 1049);
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
    Sleep(500);
    set_tacho_position_sp(sn, -30);
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
    set_tacho_stop_action_inx( sn, TACHO_COAST );
  }
}

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

void get_ball(int move_value)
{
    int motor_lift = 66;
    printf("get_ball\n" );
    disable_catapult();
    move_forward(move_value/10 + 10);
    enable_catapult();
    // turn the little motor
    sg_motor(motor_lift,1000,-300);
    Sleep(3000);
    move_backward(move_value/10 + 10);
}

/*

void get_ball_2(void){
    int motor_lift = 66;
    uint8_t sn;
    if ( ev3_search_tacho_plugged_in(motor_lift,0, &sn, 0 )) {
      set_tacho_position_sp(sn, -180);
      set_tacho_speed_sp( sn, 300);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      Sleep(500);
    }
}
*/

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
        for(i=0; i < 36; i++)
        {
          turn_left(5);
          angle = i*5;
          if ( !get_sensor_value0(sn_sonar, &current_value )) {
            current_value = 0;
          }
          printf( "\r%d : current value %f, previous value %f \n", angle, current_value,previous_value);
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
        if (flag_detected){
            turn_left(6);
            turn_left(165);
            get_ball(current_value);
            turn_right(165);
        }
        while(i>0)
        {
          turn_right(5);
          printf("%d\n",i);
          fflush( stdout );

          i--;
        }
        turn_right(6);
        if (flag_detected){
            throw();
        }
    }
}

/*
void search_ball_right(void)
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
        for(i=0; i < 36; i++)
        {
          turn_right(5);
          angle = i*5;
          if ( !get_sensor_value0(sn_sonar, &current_value )) {
            current_value = 0;
          }
          printf( "\r%d : current value %f, previous value %f \n", angle, current_value,previous_value);
          if ((previous_value - current_value > threshold) && (previous_value < 500)) {
              printf("Ball detected\n");
              fflush( stdout );
              Sleep(5000);
              break;
              flag_detected = 1;
          }
          if ((current_value - previous_value > threshold) && (previous_value < 500)) {
              printf("Ball missed but then detected\n");
              fflush( stdout );
              turn_left(5);
              Sleep(5000);
              flag_detected = 1;
              break;
          }

          previous_value = current_value;
          fflush( stdout );
        }
        if (flag_detected){
          turn_right(6);
          turn_right(162);
          get_ball(current_value);
          turn_left(162);
        }
        while(i>0)
        {
          turn_left(5);
          i--;
        }
        turn_left(5);
        if (flag_detected){
            throw();
        }
}*/
