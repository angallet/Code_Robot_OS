#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <sys/socket.h>
#include <math.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define SERV_ADDR   "A0:E6:F8:DC:88:B9"     /* Whatever the address of the server is */
#define TEAM_ID     2                       /* Your team ID */

#define MSG_ACK     0
#define MSG_START    1
#define MSG_STOP   2
#define MSG_KICK    3
#define MSG_SCORE 	    4
#define MSG_CUSTOM 	    8
#define MESSAGE_MAX_LENGHT    58

#define Sleep( msec ) usleep(( msec ) * 1000 )

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


void bluetooth_send_ack(void)
{
          char send_message[9];
          ((uint16_t *) send_message) = msg_id++;
          send_message[MSG_ID_LSB] = *((char *) &(msg_id));
          send_message[MSG_ID_MSB] = *(((char *) &(msg_id))+1);
          send_message[MSG_SRC] = TEAM_ID;
          send_message[MSG_DST] = SERV_ADDR;
          send_message[MSG_TYPE] = MSG_ACK;


  write(s, send_message, 9);

}

void bluetooth_received_ack(void)
{

}

void bluetooth_received_start(void)
{

}

void bluetooth_received_stop(void)
{

}

void bluetooth_received_kick(void)
{

}

void bluetooth_send_score(int score)
{


}
int s;                                          // Bluetooth socket
enum BtState bluetooth_state = DISCONNECTED;    // State of connexion
uint16_t msg_id = 0;                            // As msg_id++ is called before send, first message have id 1
uint16_t ack_msg_id = 0;                        // Last acknowledged message (should be equal to msg_id)

/**
 * Function called to init the connexion with the server.
 * Called on every connexion attempt
 * @return  1 if connected, 0 otherwise
 */

int init_bluetooth( void )
{
        struct sockaddr_rc addr = { 0 };
        int status;
        //struct timeval timeout;
        //timeout.tv_sec = READ_TIMEOUT_SEC;
        //timeout.tv_usec = 0;

        // allocate a socket
        s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        //setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout,sizeof(struct timeval));    // Set a timeout

        // set the connection parameters (who to connect to)
        addr.rc_family = AF_BLUETOOTH;
        addr.rc_channel = (uint8_t) 1;
        str2ba(SERV_ADDR, &addr.rc_bdaddr);

        // connect to server
        status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

        // if not connected
        if( status != 0 ) {
                print_error("Failed to connect to server...");
                bluetooth_state = DISCONNECTED;
                return ( 1 ); // TODO change to 0 when server is available
        }
        bluetooth_state = CONNECTED;
        return ( 1 );
}

        status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

        // if not connected
        if( status != 0 ) {
                print_error("Failed to connect to server...");
                bluetooth_state = DISCONNECTED;
                return ( 1 ); // TODO change to 0 when server is available
        }
        bluetooth_state = CONNECTED;
        return ( 1 );
}



void *bluetooth_main(void *arg) {
        char receive_message[MESSAGE_MAX_LENGHT];
        uint16_t message_id;

        while (alive) {
                while (alive && (bluetooth_state == DISCONNECTED)) {                  // If not connected, try to reconnect every
                        sleep( RECONNEXION_PERIOD_SEC );
                        init_bluetooth();
                }
                if (!alive) break;                                          // Quit faster

                int bytes_read = read(s, receive_message, MESSAGE_MAX_LENGHT); // Block until a message is received

                if (bytes_read < 0) {                                       // Test if server is still alive
                        print_error("Server unexpectedly closed connection...");
                        bluetooth_state = DISCONNECTED;
                        close(s);
                        continue;
                }
                if ( bytes_read == 0 ) continue;                    // Timeout
                if ( bytes_read < 5 ) continue;                     // Bad format
                if (receive_message[MSG_SRC] != SERVER_TEAM_ID) continue;  // Bad sender (to prevent from other robot attack)
                if (receive_message[MSG_DST] != TEAM_ID) continue;  // Bad destination

                switch(receive_message[MSG_TYPE]) {
                case MSG_TYPE_ACK:
                        message_id = receive_message[6] << 8 | receive_message[5];
                        if (message_id < ack_msg_id)
                                print_error("Ack of an old message");
                        if (message_id > msg_id)
                                print_error("Ack of a message not sent yet");
                        if (message_id > ack_msg_id + 1)
                                print_error("Message(s) lost (ack not received)");
                        if (receive_message[7] != 0)
                                print_error("Message misunderstood by server");
                        ack_msg_id = message_id;
                        break;
                case MSG_TYPE_START:
                        print_console("Game start sent by server");
                        start_received();
                        break;
                case MSG_TYPE_STOP:
                        print_console("Game stop sent by server");
                        stop_received();
                        break;
                case MSG_TYPE_KICK:
                        print_error("Defendum got kicked by server");
                        kicked();
                        break;
                }
        }
        close(s);
        bluetooth_state = DISCONNECTED;
        pthread_exit(NULL);
}
void bluetooth_close()
{
    bluetooth_state = DISCONNECTED;
    shutdown(s, SHUT_RDWR);
}
