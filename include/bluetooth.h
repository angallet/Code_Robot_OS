#ifndef BLUETOOTH_H
#define BLUETOOTH_H

extern int alive;


// State
enum BtState {
        DISCONNECTED,
        CONNECTED,
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
void robotscore();
extern void *mybluetooth( void *arg );
int read_from_server (int sock, char *buffer, size_t maxSize);



void bluetooth_close();

#endif
