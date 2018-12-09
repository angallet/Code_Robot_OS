#include <pthread.h>
#include "distance.h"
#include "brick.h"
#include "main.h"


int init_distance(void)
{
  if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0))
  {
    printf("SONAR found, reading sonar...\n");
    return(1);
  }
  printf("sensor not found")
  return ( 0 );
}

int distance_update(void)
{
  if(!get_sensor_value(sn_sonar, &distance_value) return 0;
}
