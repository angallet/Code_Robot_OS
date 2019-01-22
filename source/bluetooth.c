#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "bluetooth.h"
#include <stdarg.h>
#include <time.h>
#include <sys/socket.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"



#define Sleep( msec ) usleep(( msec ) * 1000 )


#define SERV_ADDR       "3C:A0:67:9C:64:BC"  /* Whatever the address of the server is */
#define TEAM_ID     1                       /* Your team ID */
#define SERVER_TEAM_ID          0xFF
#define MSG_ACK     0
#define MSG_START    1
#define MSG_STOP   2
#define MSG_KICK    3
#define MSG_SCORE 	    4
#define MSG_CUSTOM 	    8
#define MESSAGE_MAX_LENGHT 58



int s;
int activated;
uint16_t msgId = 0;                                         // Bluetooth socket
enum BtState bluetooth_state = DISCONNECTED;    // State of connexion
uint16_t ack_msg_id = 0;



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



void robotscore () {
  char string[58];
  srand(time(NULL));
  /* Send 3 SCORE messages */
  int i;
    *((uint16_t *) string) = msgId++;
    string[2] = TEAM_ID;
    string[3] = 0xFF;
    string[4] = MSG_SCORE;
    string[5] = 3;          /* send a 3 points each time robot throw the ball */
    write(s, string, 6);
    Sleep( 1000 );
    ack_msg_id = msgId;
    printf("ok score sent to server\n");

}



int init_bluetooth( void )
{
  struct sockaddr_rc addr = { 0 };
  int status;
  activated=0;

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
      activated=1;


    }

  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }

  return 0;
}



void *mybluetooth(void *arg) {
        char string[MESSAGE_MAX_LENGHT];
        uint16_t message_id;

          printf("thread is created\n");
              //  while (bluetooth_state == DISCONNECTED) {                  // If not connected, try to reconnect
                  init_bluetooth();
                  printf("blue is created\n");
                  //activated=1;
              //  }
                while(1){
                activated=1;
                read_from_server (s, string, MESSAGE_MAX_LENGHT);; // Block until a message is received

                //if (string[2] == SERVER_TEAM_ID) continue;  // Bad sender (to prevent from other robot attack)
                //if (string[3] == TEAM_ID) continue;  // Bad destination

                if (string[4] == MSG_STOP) {
                  printf ("Received stop message!\n");
                  int port = 65;
                  for (port = 65; port < 69; port++) {
                    uint8_t sn;
                    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
                    set_tacho_speed_sp( sn, 0);
                    set_tacho_command_inx( sn, TACHO_RUN_FOREVER );
                    set_tacho_stop_action_inx( sn, TACHO_COAST );
                    }
                  }
                  exit(0);


                }
                if (string[4] == MSG_KICK) {
                  printf ("Received kick message!\n");
                  int port = 65;
                  for (port = 65; port < 69; port++) {
                    uint8_t sn;
                    if ( ev3_search_tacho_plugged_in(port,0, &sn, 0 )) {
                    set_tacho_speed_sp( sn, 0);
                    set_tacho_command_inx( sn, TACHO_RUN_FOREVER );
                    set_tacho_stop_action_inx( sn, TACHO_COAST );
                    }
                  }
                  exit(0);


                }

        }

        close(s);
        bluetooth_state = DISCONNECTED;
        pthread_exit(NULL);
}
