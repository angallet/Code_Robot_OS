#define MOTORS_H
void move_forward (int distance);
void sg_motor_deg (int port, int deg, int speed);
void sg_motor (int port, int time, int speed);
void init_motors(void);
void quarter_turn (void);
void throw (void);
void get_ball(int move_value);
void get_ball22(int move_value, int *flag_ball_caught);
void turn (int degree);
void search_ball_left(void);
void search_ball_right(void);
void move_backward (int distance);
void turn_gyro_right(int degree);
void turn_gyro_left(int degree);
extern int val;
//void search_ball_right(void);
