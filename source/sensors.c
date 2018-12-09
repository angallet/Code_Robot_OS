#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "colors.h"
#include "distance.h"
#include "sensors.h"

int init_sensors(void)
{
  if(!init_distance()) return 0;
  if(!init_color_sensor()) return 0;

  distance_update();
  color_update();

  return 1;
}

void *sensors_main(void *arg)
{
  while(powered)
  {
    distance_update();
    color_update();
  }
  pthread_exit(NULL);
}
