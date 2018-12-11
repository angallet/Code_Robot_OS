#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "brick.h"
#include "main.h"
#include "bluetooth.h"
#include "display.h"
#include "behaviour.h"

int read_from_server (int sock, char *buffer, size_t maxSize);


void bluetooth_send_ack(void);

void bluetooth_received_ack(void);

void bluetooth_received_start(void);

void bluetooth_received_stop(void);

void bluetooth_received_kick(void);

void bluetooth_send_score(int score);
