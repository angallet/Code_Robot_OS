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

void move_forward (int distance)
{
  uint8_t sn;
  int port=65;
  int time=5000;//60/(M_PI*5.6*300);
  sg_motor(port, time, 300);
  port=68;
  sg_motor(port, time, 300);
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
  int port=66;
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
    int port=66;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      set_tacho_position_sp(sn, 20);
      set_tacho_speed_sp( sn, 1049);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      Sleep(500);
    }
}

void enable_catapult(void)
{
    uint8_t sn;
    int port=66;
    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
      set_tacho_position_sp(sn, -20);
      set_tacho_speed_sp( sn, 1049);
      set_tacho_command_inx(sn, TACHO_RUN_TO_REL_POS);
      Sleep(500);
    }
}

void get_ball(void)
{
    int motor_lift = 66;
    sg_motor(motor_lift,800,-500);
    Sleep(1000);
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
