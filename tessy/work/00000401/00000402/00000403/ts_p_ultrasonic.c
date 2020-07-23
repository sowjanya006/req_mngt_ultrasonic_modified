# 1 "C:/Users/Sowjanya/Desktop/ultrasonic.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/Users/Sowjanya/Desktop/ultrasonic.c"
extern float timedur;
float distance;
typedef enum {obst_near,obst_far,inv_dist,inv_time}status;

status vehdist()
{
   if(timedur > 0.0)
    {
    distance = ((timedur/2)*34.4);
    if (distance < 2 || distance > 80)
     return inv_dist;
    else
    {
    if (distance < 30.0)
     return obst_near;
    else
        return obst_far;
 }
    }
   else
     return inv_time;
}
