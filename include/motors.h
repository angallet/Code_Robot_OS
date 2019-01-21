#define MOTORS_H
void move_forward (int distance);
void sg_motor (int port, int time, int speed);
void throw (void);
void get_ball(int move_value, int *flag_ball_caught);
void catch_ball(int *flag_ball_caught);
void search_ball_left(void);
void search_ball_right(void);
void move_backward (int distance);
void turn_gyro_right(int degree);
void turn_gyro_left(int degree);
void turn_gyro_left2(int degree);
void turn_left (int degree);
void turn_right (int degree);
extern int val;
extern const char const *color[];
