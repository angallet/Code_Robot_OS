#include <pthread.h>
#include "colors.h"
#include "brick.h"
#include "main.h"

int init_distance(void)
{
  if (ev3_search_sensor(LEGO_EV3_US, &sn_color,0))
  {
    printf("COLOR sensor found, reading COLOR...\n");
    return(1);
  }
  printf("COLOR sensor not found")
  return ( 0 );
}

void color_update(void)
{
        get_sensor_value( 0, sn_color, &color_val);
}
