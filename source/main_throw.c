#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "motors.h"
#include <stdarg.h>
#include <time.h>
#include <sys/socket.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>




#define Sleep( msec ) usleep(( msec ) * 1000 )
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))
#define SERV_ADDR       "3C:A0:67:9C:64:BC"  /* Whatever the address of the server is */
#define TEAM_ID     1                       /* Your team ID */

#define MSG_ACK     0
#define MSG_START    1
#define MSG_STOP   2
#define MSG_KICK    3
#define MSG_SCORE 	    4
#define MSG_CUSTOM 	    8

static bool _check_pressed( uint8_t sn );

int s;
uint16_t msgId = 0;


int read_from_server (int sock, char *buffer, size_t maxSize) {
  int bytes_read = read (sock, buffer, maxSize);

  if (bytes_read <= 0) {
    fprintf (stderr, "Server unexpectedly closed connection...\n");
    close (s);
    exit (EXIT_FAILURE);
  }

  printf ("[DEBUG] received %d bytes\n", bytes_read);

  return bytes_read;
}

void robot () {
  char string[58];
  char type;
  printf ("I'm navigating...\n");

  srand(time(NULL));
  /* Send 3 SCORE messages */
  int i;
    *((uint16_t *) string) = msgId++;
    string[2] = TEAM_ID;
    string[3] = 0xFF;
    string[4] = MSG_SCORE;
    string[5] = 3;          /* x */
    write(s, string, 6);
    Sleep( 1000 );



  printf("I'm waiting for the stop message");
  while(1){
    //Wait for stop message
    read_from_server (s, string, 58);
    type = string[4];
    if (type ==MSG_STOP){
      return;
    }
  }
}



int main( int argc, char **argv )
{
  int val;
  uint8_t sn_touch;
  float value;
  uint8_t sn_color;
  uint8_t sn_compass;
  uint8_t sn_sonar;
  int i;
  uint32_t n, ii;
  struct sockaddr_rc addr = { 0 };
  int status;

    if ( ev3_init() == -1 ) return ( 1 );
    /* allocate a socket */
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    /* set the connection parameters (who to connect to) */
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba (SERV_ADDR, &addr.rc_bdaddr);

    /* connect to server */
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    /* if connected */
    if( status == 0 ) {
      char string[58];

      /* Wait for START message */
      read_from_server (s, string, 9);
      if (string[4] == MSG_START) {
        printf ("Received start message!\n");


      }
    while ( ev3_tacho_init() < 1 ) Sleep( 1000 );
    printf( "*** ( EV3 ) Hello! ***\n" );

    //Run all sensors
    ev3_sensor_init();
    throw();
    Sleep( 5000 );

      robot();
      close (s);

      sleep (5);

    } else {
      fprintf (stderr, "Failed to connect to server...\n");
      sleep (2);
      exit (EXIT_FAILURE);
    }

    close(s);
    return 0;
    ev3_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );

    return ( 0 );
}
