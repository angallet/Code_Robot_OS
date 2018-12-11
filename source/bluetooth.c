#define SERV_ADDR   "dc:53:60:ad:61:90"     /* Whatever the address of the server is */
#define TEAM_ID     1                       /* Your team ID */

#define MSG_ACK     0
#define MSG_START    1
#define MSG_STOP   2
#define MSG_KICK    3
#define MSG_SCORE 	    4
#define MSG_CUSTOM 	    8

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
