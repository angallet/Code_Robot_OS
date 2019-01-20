#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "motors.h"
#include <pthread.h>
#include "bluetooth.h"
#define Sleep( msec ) usleep(( msec ) * 1000 )
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

static bool _check_pressed( uint8_t sn );
int val;
int activated = 0;
int main( void )
{
  uint8_t sn_touch;
  float value;
  uint8_t sn_color;
  uint8_t sn_compass;
  uint8_t sn_sonar;
  int i;
  char s[ 256 ];
  uint32_t n, ii;
  pthread_t thread_id;
    printf("create Thread\n");
    pthread_create(&thread_id, NULL, bluetooth_main, NULL);
    pthread_join(thread_id, NULL);
    printf(" Thread done \n");


    if ( ev3_init() == -1 ) return ( 1 );
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );

    //Run all sensors
    ev3_sensor_init();

    for ( ; ; ){
      // search the color
      if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        printf( "COLOR sensor is found, reading COLOR...\n" );
        if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
          val = 0;
        }
        printf( "\r(%s) \n", color[ val ]);
        fflush( stdout );
      }
        search_ball_right();
      // this is the core part of the main which defines routines
      if (activated){
        // throw the two ball initial ball already installed in the robot
        initial_throw();
        search_ball_right();
      }
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
