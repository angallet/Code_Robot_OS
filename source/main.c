#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "motors.c"
#define Sleep( msec ) usleep(( msec ) * 1000 )

static bool _check_pressed( uint8_t sn );


int main( void ){
    if ( ev3_init() == -1 ) return ( 1 );
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );
    run();

}



static bool _check_pressed( uint8_t sn )
{
  int val;

    if ( sn == SENSOR__NONE_ ) {
        return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
    }
    return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}
