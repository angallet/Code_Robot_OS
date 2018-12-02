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
    if ( ev3_search_tacho( LEGO_EV3_M_MOTOR, &snA, 0 ) && ev3_search_tacho( LEGO_EV3_M_MOTOR, &snD, 0 )) {
        int max_speed;
        printf( "LEGO_EV3_M_MOTOR is found, run for 5 sec...\n" );
        get_tacho_max_speed( snA, &max_speed );
        get_tacho_max_speed( snD, &max_speed );
        printf("  max_speed = %d\n", max_speed );
        set_tacho_stop_action_inx( snA, TACHO_COAST);
        set_tacho_stop_action_inx( snD, TACHO_COAST);
        set_tacho_speed_sp( snA, max_speed * 2 / 3 );
        set_tacho_speed_sp( snD, max_speed * 2 / 3 );
        set_tacho_time_sp( snA, 5000 );
        set_tacho_time_sp( snD, 5000 );
        set_tacho_ramp_up_sp( snA, 2000 );
        set_tacho_ramp_up_sp( snD, 2000 );
        set_tacho_ramp_down_sp( snA, 2000 );
        set_tacho_ramp_down_sp( snD, 2000 );
        set_tacho_command_inx( snA, TACHO_RUN_TIMED );
        set_tacho_command_inx( snD, TACHO_RUN_TIMED );
        /* Wait tacho stop */
        Sleep( 100 );
        do {
            get_tacho_state_flags( snA, &state );
            get_tacho_state_flags( snD, &state );
       } while ( state );
    } else {
        printf( "LEGO_EV3_M_MOTOR is NOT found\n" );
    }
    if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
        printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
    } else {
        printf( "TOUCH sensor is NOT found, press UP on the EV3 brick for EXIT...\n" );
    }
        
    ev3_uninit();
    printf( "\n*** ( EV3 ) Bye! ***\n" );
    return ( 0 );
}
