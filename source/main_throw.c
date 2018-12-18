#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "motors.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static bool _check_pressed( uint8_t sn );

int main( void )
{
  int val;
  uint8_t sn_touch;
  float value;
  uint8_t sn_color;
  uint8_t sn_compass;
  uint8_t sn_sonar;
  int i;
  char s[ 256 ];
  uint32_t n, ii;

    if ( ev3_init() == -1 ) return ( 1 );
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );

    //Run all sensors
    ev3_sensor_init();
    throw();
    Sleep( 5000 );
    ev3_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );

    return ( 0 );
}
