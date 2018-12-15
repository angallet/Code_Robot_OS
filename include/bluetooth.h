#ifndef OS_ROBOT_BLUETOOTH_H
#define OS_ROBOT_BLUETOOTH_H

// Server communications
#define TEAM_ID                 2   // Team ID for bluetooth communication with server
#define SERVER_TEAM_ID          0xFF
#define SERV_ADDR               "A0:E6:F8:DC:88:B9"     // Watever the address of the server is
#define READ_TIMEOUT_SEC        2
#define RECONNEXION_PERIOD_SEC  2

// State
enum BtState {
        DISCONNECTED,
        CONNECTED,
};

// Protocol header positions
enum {
        MSG_ID_LSB,
        MSG_ID_MSB,
        MSG_SRC,
        MSG_DST,
        MSG_TYPE,
};

// Message types
enum {
        MSG_ACK,
        MSG_START,
        MSG_STOP,
        MSG_KICK,
        MSG_SCORE,
        MSG_CUSTOM
};

// Prototypes
int init_bluetooth( void );
void *bluetooth_main( void *arg );
int read_from_server (int sock, char *buffer, size_t maxSize);


void bluetooth_send_ack(void);

void bluetooth_received_ack(void);

void bluetooth_received_start(void);

void bluetooth_received_stop(void);

void bluetooth_received_kick(void);

void bluetooth_send_score(int score);
void bluetooth_close();

#endif //OS_ROBOT_BLUETOOTH_H
