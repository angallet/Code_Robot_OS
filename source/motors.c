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
}


//width of the robot (measure at the center of the wheel ) 12cm
void turn (int degree)
{
    uint8_t sn;
    int port =65;
    int deg = (int)(12*degree)/(5.6));
    printf("The robot will rotate wheel %d degree\n",deg);
    sg_motor_deg(port, deg, SPEED);
    port=68;
    sg_motor_deg(port, deg, -SPEED);
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
      printf( "LEGO_EV3_M_MOTOR 1 is found, run...\n" );
      printf("  speed = %d\n", speed );
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

      Sleep(500);
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
      Sleep(500);


    }
}

void get_ball(void)
{
    int motor_lift = 66;
    printf("get_ball\n" );

    sg_motor(motor_lift,1000,-300);
    Sleep(3000);
    /*
  uint8_t sn;
  uint8_t sn_throw;
  int port=67;
  int port_throw=66;
  if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 ) && ev3_search_tacho_plugged_in(port_throw,0, &sn, 0 ))
  {
      set_tacho_position_sp(sn, -100);
      set_tacho_speed_sp( sn, 1049);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      Sleep(3000);
      set_tacho_speed_sp( sn, 0);
      set_tacho_time_sp( sn, 5000 );
      set_tacho_command_inx(sn, TACHO_RUN_TIMED);
      set_tacho_position_sp(sn_throw, 80);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      Sleep(3000);
      throw();
      Sleep(5000);
  }
  */
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
/*
void search_ball(float *value)
{

    int prev_distance=10000;
    int threshold = 300;
    uint8_t sn_sonar;
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
    while(abs(get_sensor_value(sn_sonar, &value )-prev_distance)<threshold) //threshold à déterminer expérimentalement
    {
      quarter_turn();
      Sleep(1000);
      prev_distance = get_sensor_value(sn_sonar, &value);
    }
    move_forward(prev_distance);
    get_ball();
  }
}
*/
