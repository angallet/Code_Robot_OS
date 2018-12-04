#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__
#include <windows.h>
// UNIX //////////////////////////////////////////
#else
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )
#endif
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

#define MOTOR_LEFT     OUTA
#define MOTOR_RIGHT    OUTD
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )


static bool _check_pressed( uint8_t sn )
{
    int val;
    if ( sn == SENSOR__NONE_ ) {
        return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
    }
    return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}
int main( void )
{
    char s[ 256 ];
    int val;
    uint8_t snA,snD, sn_touch;
    FLAGS_T state;
    uint32_t n, i, ii;
    printf( "Waiting the EV3 brick online...\n" );
    if ( ev3_init() < 1 ) return ( 1 );
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );
    ev3_sensor_init();
    printf( "Found sensors:\n" );
    if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
        printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
    } else {
        printf( "TOUCH sensor is NOT found, press UP on the EV3 brick for EXIT...\n" );
    }
    if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) {
        tacho_stop( MOTOR_BOTH );
        while(tacho_is_running( MOTOR_BOTH ))
            sleep_ms(100);
        tacho_set_speed_sp( MOTOR_BOTH, 2000 );
        tacho_run_forever( MOTOR_BOTH );

    } else {
        printf( "LEGO_EV3_M_MOTOR is NOT found\n" );
    }


    ev3_uninit();
    printf( "\n*** ( EV3 ) Bye! ***\n" );
    return ( 0 );
}
