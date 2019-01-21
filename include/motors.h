#define MOTORS_H
void move_forward (int distance);
void sg_motor (int port, int time, int speed);
void throw (void);
int get_ball(int move_value);
int catch_ball(void);
void search_ball_left(int distance_max);
void search_ball_right(int distance_max);
void move_backward (int distance);
void turn_gyro_right(int degree);
void turn_gyro_left(int degree);
//void turn_gyro_left_1(int degree);
//void turn_gyro_left2(int degree);
void turn_left (int degree);
void turn_right (int degree);
extern int val;
extern const char const *color[];
