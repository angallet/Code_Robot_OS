#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "motors.h"
#include "distance.h"
#include "colors.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

static bool _check_pressed( uint8_t sn );

int color_val = 0, distance_value;

int main( void )
{
  int val;
  uint8_t sn_touch;
  float value;
  uint8_t sn;

    if ( ev3_init() == -1 ) return ( 1 );
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );

    //Run all sensors
    ev3_sensor_init();

    throw();
    //quarter_turn();
    Sleep( 5000 );
    while(1){
        //move_forward(50);
        if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
          printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
        }
        if ( _check_pressed( sn_touch )) break;
        Sleep( 200 );
        printf( "\r        " );
        fflush( stdout );
    }
    ev3_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );

    return ( 0 );
}



static bool _check_pressed( uint8_t sn )
{
  int val;

    if ( sn == SENSOR__NONE_ ) {
        return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
    }
    return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}
