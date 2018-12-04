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
  tacho_stop(MOTOR_BOTH);
  while(tacho_is_running( MOTOR_BOTH ))
    set_tacho_speed_sp( MOTOR_BOTH, 200 );
  set_tacho_time_sp( MOTOR_BOTH, 5000 );
  set_tacho_command_inx( MOTOR_BOTH, TACHO_RUN_TIMED );
}
