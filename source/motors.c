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

#define MOTOR_A 65
#define MOTOR_B 68
#define MOTOR_LIFT 66
#define MOTOR_CATAPULT 67
//const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

// function to move forward a set distance given by the parameters distance
void move_forward (int distance)
{
  uint8_t sn;
  // computation of the time necessary to move of the corresponding distance
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(MOTOR_A, time, SPEED);
  sg_motor(MOTOR_B, time, SPEED);
  Sleep(time);
}

// function to move backward a set distance given by the parameters distance
void move_backward (int distance)
{
  uint8_t sn;
  // computation of the time necessary to move of the corresponding distance
  int time= (int)(distance/12.6)*1000;
  printf("the robot will run during : %d\n",time);
  sg_motor(MOTOR_A, time, -SPEED);
  sg_motor(MOTOR_B, time, -SPEED);
  Sleep(time);
}

// function to turn right using the gyroscope
void turn_gyro_right(int degree)
{
  uint8_t sn_gyro;
  uint8_t sn_motorA;
  uint8_t sn_motorB;
  int port_gyro = 50;
  float angle;
  int og_angle;
  int max_iter = 50;
  int current_diff = 0;
  int counter = 0;
  printf("Enter the function turn_gyro_right, degree = %d\n",degree);
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_A,0, &sn_motorA, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_B,0, &sn_motorB, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    get_sensor_value0(sn_gyro, &angle );
    og_angle= (int) angle % 360;
    set_tacho_speed_sp( sn_motorA, -30);
    set_tacho_speed_sp(sn_motorB, 30);
    set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );

    while (abs((int)angle-og_angle)%360 < degree)
    {
      printf("og_angle = %d, angle = %d, diff = %d \n", og_angle,(int) angle%360, (int)angle%360-og_angle);
      fflush(stdout);
      if (current_diff == (int)angle%360-og_angle) counter ++;
      else{
	counter = 0;
	current_diff = (int)angle%360-og_angle;
      }
      if (counter == max_iter) break;
      get_sensor_value0(sn_gyro, &angle);
     }
    fflush(stdout);
    set_tacho_speed_sp( sn_motorA, 0);
    set_tacho_speed_sp( sn_motorB, 0);
    set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
  }
}


// function to turn left using the gyroscope
void turn_gyro_left(int degree)
{
  uint8_t sn_gyro;
  uint8_t sn_motorA;
  uint8_t sn_motorB;
  int port_gyro = 50;
  float angle;
  int og_angle;
  int max_iter = 50;
  int current_diff = 0;
  int counter = 0;
  printf("Enter the function turn_gyro_right, degree = %d\n",degree);
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_A,0, &sn_motorA, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_B,0, &sn_motorB, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    get_sensor_value0(sn_gyro, &angle );
    og_angle= (int) angle % 360;
    set_tacho_speed_sp( sn_motorA, 30);
    set_tacho_speed_sp(sn_motorB, -30);
    set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );

    while (abs((int)angle-og_angle)%360 < degree)
    {
      printf("og_angle = %d, angle = %d, diff = %d , counter = %d\n", og_angle,(int) angle%360, (int)angle%360-og_angle, counter);
      fflush(stdout);
      /*if (current_diff == (int)angle%360-og_angle) counter ++;
      else{
	counter = 0;
	current_diff = (int)angle%360-og_angle;
      }
      if (counter == max_iter) break;*/
      get_sensor_value0(sn_gyro, &angle);
     }
    //printf("After the while");
    fflush(stdout);
    set_tacho_speed_sp( sn_motorA, 0);
    set_tacho_speed_sp( sn_motorB, 0);
    set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
  }
}

// function to turn left on one wheel using the gyroscope
void turn_gyro_left_1(int degree)
{
  uint8_t sn_gyro;
  uint8_t sn_motorB;
  int port_gyro = 50;
  float angle;
  int og_angle;
  int max_iter = 50;
  int current_diff = 0;
  int counter = 0;
  printf("Enter the function turn_gyro_right, degree = %d\n",degree);
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_B,0, &sn_motorB, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    get_sensor_value0(sn_gyro, &angle );
    og_angle= (int) angle % 360;
    set_tacho_speed_sp( sn_motorB, 60);
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );

    while (abs((int)angle-og_angle)%360 < degree)
    {
      //printf("og_angle = %d, angle = %d, diff = %d , counter = %d\n", og_angle,(int) angle%360, (int)angle%360-og_angle, counter);
      fflush(stdout);
      if (current_diff == (int)angle%360-og_angle) counter ++;
      else{
	counter = 0;
	current_diff = (int)angle%360-og_angle;
      }
      if (counter == max_iter) break;
      get_sensor_value0(sn_gyro, &angle);
     }
    //printf("After the while");
    fflush(stdout);
    set_tacho_speed_sp( sn_motorB, 0);
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
  }
}
// function to turn left using the gyroscope
void turn_gyro_left2(int degree)
{
  uint8_t sn_gyro;
  uint8_t sn_motorA;
  uint8_t sn_motorB;
  int port_gyro = 50;
  float angle;
  int og_angle;
  int max_iter = 50;
  int current_diff = 0;
  int counter = 0;
  int time = 100;
  printf("Enter the function turn_gyro_right, degree = %d\n",degree);
  if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_A,0, &sn_motorA, 0 ) &&
  ev3_search_tacho_plugged_in(MOTOR_B,0, &sn_motorB, 0 ))
  {
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
    get_sensor_value0(sn_gyro, &angle );
    og_angle= (int) angle % 360;
    set_tacho_speed_sp( sn_motorA, 30);
    set_tacho_speed_sp(sn_motorB, -30);
    set_tacho_time_sp( sn_motorA, time );
    set_tacho_time_sp( sn_motorB, time );
    set_tacho_command_inx( sn_motorA, TACHO_RUN_TIMED );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_TIMED );

    while (abs((int)angle-og_angle)%360 < degree)
    {
      //printf("og_angle = %d, angle = %d, diff = %d \n", og_angle,(int) angle%360, (int)angle%360-og_angle);
      fflush(stdout);

      set_tacho_speed_sp( sn_motorA, 30);
      set_tacho_speed_sp(sn_motorB, -30);
      set_tacho_time_sp( sn_motorA, time );
      set_tacho_time_sp( sn_motorB, time );
      set_tacho_command_inx( sn_motorA, TACHO_RUN_TIMED );
      set_tacho_command_inx( sn_motorB, TACHO_RUN_TIMED );
      Sleep(100);
      if (current_diff == (int)angle%360-og_angle) counter ++;
      else{
	counter = 0;
	current_diff = (int)angle%360-og_angle;
      }
      if (counter == max_iter) break;
      get_sensor_value0(sn_gyro, &angle);
     }
    printf("After the while");
    fflush(stdout);
    set_tacho_speed_sp( sn_motorA, 0);
    set_tacho_speed_sp( sn_motorB, 0);
    set_tacho_command_inx( sn_motorA, TACHO_RUN_FOREVER );
    set_tacho_command_inx( sn_motorB, TACHO_RUN_FOREVER );
    set_tacho_stop_action_inx( sn_motorA, TACHO_COAST );
    set_tacho_stop_action_inx( sn_motorB, TACHO_COAST );
  }
}


// function to turn left
void turn_left (int degree)
{
      //printf("enter into the function turn\n");
      uint8_t sn;
      int time;
      time = 60*degree; // 540/180 : 540 time  3 factor
      sg_motor(MOTOR_A, time, 30);
      sg_motor(MOTOR_B, time, -30);
      Sleep(time);
}

// function to turn right
void turn_right (int degree)
{
      //printf("enter into the function turn\n");
      uint8_t sn;
      int time;
      time = 60*degree; // 540/180 : 540 time  3 factor
      sg_motor(MOTOR_A, time, -30);
      sg_motor(MOTOR_B, time, 30);
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


// function to permform a 3 point throw
void throw (void)
{
  uint8_t sn;
  if ( ev3_search_tacho_plugged_in(MOTOR_CATAPULT,0, &sn, 0 )) {
    // set the position
    set_tacho_position_sp(sn, 140);
    // set the speed
    set_tacho_speed_sp( sn, 1049);
    // initiate the command with the position and speed given previously
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);

    Sleep(500);

    set_tacho_position_sp(sn, -30);
    set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
    Sleep(500);
    set_tacho_stop_action_inx( sn, TACHO_COAST );
    robotscore();
  }
}


// function to perform the initial throw
void initial_throw(void)
{
  // throw the first ball
  throw();
  // turn the inner motor, the motor which perform the action of lifting the ball
  sg_motor(MOTOR_LIFT ,1000,-300);
  Sleep(1500);
  // throw the second ball

  throw();
}

// function to disable catapult
void disable_catapult(void)
{
    uint8_t sn;
    if ( ev3_search_tacho_plugged_in(MOTOR_CATAPULT,0, &sn, 0 )) {
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
    if ( ev3_search_tacho_plugged_in(MOTOR_CATAPULT,0, &sn, 0 )) {
        printf("enable_catapult\n" );

      set_tacho_position_sp(sn, -140);
      set_tacho_speed_sp( sn, 500);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      set_tacho_stop_action_inx( sn, TACHO_COAST );

      Sleep(1000);


    }
}


// function to get the ball
int get_ball(int move_value)
{
    int flag = 0;
    printf("Enter in the function getball22\n");
    disable_catapult();

    move_forward(move_value);

    Sleep(500);
     flag =catch_ball();
    Sleep(500);

    move_backward(move_value);
    enable_catapult();
    sg_motor(MOTOR_LIFT,390,-300);
    return flag;
}

// function to catch the ball
int catch_ball(void)
{
    printf("Enter in the function catch_ball \n");
    uint8_t sn_color;
    // turn the inner motor, the motor which perform the action of lifting the ball
    sg_motor(MOTOR_LIFT,350,-300);
    Sleep(500);
    if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) ) {
          val = 0;
        }
        printf( "COLOR sensor is found, the color is (%s) \n", color[val]  );
        fflush( stdout );
      }
    if (val != 0) {
	printf("A ball has been caught\n");
      return 1;
    }
  return 0;
}


// function to search the ball
void search_ball_left(int distance_max)
{
    int i;
    float current_value, previous_value;
    uint8_t sn_sonar;
    int angle;
    int prev_distance=10000;
    int threshold = 50;
    int flag_detected = 0;
    int flag_ball_caught =0;
    printf("SONAR found, reading sonar. It will print 36 values \n");
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
        if ( !get_sensor_value0(sn_sonar, &previous_value )) {
            previous_value = 0;
        }
        // the robot will rotate and search for the ball accordingly to the protocol define below
        for(i=0; i < 18; i++)
        {
          turn_gyro_left(5);
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
              turn_gyro_right(10);
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

            turn_gyro_left(6);
            turn_gyro_left(180);

            flag_ball_caught =get_ball(min(current_value/10 + 8, distance_max));
            printf("I will do a turn ...");
            turn_gyro_right(180);
        }

        // get back to the initial angle
        if (i>0) turn_gyro_right(5*i);

        turn_gyro_right(6);
        // if the ball is detected then it throw the ball
        if (flag_detected && flag_ball_caught){
            throw();
        }
    }
}

// function to search the ball
void search_ball_right(int distance_max)
{
    int i;
    float current_value, previous_value;
    uint8_t sn_sonar;
    int angle;
    int prev_distance=10000;
    int threshold = 50;
    int flag_detected = 0;
    int flag_ball_caught = 0;
    printf("SONAR found, reading sonar. It will print 36 values \n");
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
        if ( !get_sensor_value0(sn_sonar, &previous_value )) {
            previous_value = 0;
        }
        // the robot will rotate and search for the ball accordingly to the protocol define below
        for(i=0; i < 18; i++)
        {
          turn_gyro_right(5);
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
              turn_gyro_left(15);
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

            turn_gyro_right(6);
            turn_gyro_right(180);

            flag_ball_caught = get_ball(min(current_value/10 + 8, distance_max));

            turn_gyro_left(180);
        }

        // get back to the initial angle
        if (i>0) turn_gyro_left(5*i);

        turn_gyro_left(6);
        // if the ball is detected then it throw the ball
        if (flag_detected && flag_ball_caught){
            throw();
        }
    }
}
