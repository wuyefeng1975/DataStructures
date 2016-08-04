#include<sys/time.h>

struct timeval start_time_value, end_time_value; 

float get_time_elapsed()
{
    struct timeval elapsed_time_value;

    timersub(&end_time_value, &start_time_value, &elapsed_time_value);
    float m_second = (float)elapsed_time_value.tv_usec / 1000000.0;
    int second = (int)elapsed_time_value.tv_sec;
     
    return  (float)( second + m_second );
}

void start_tick()
{
    gettimeofday(&start_time_value, NULL);
}

float stop_tick()
{
    gettimeofday(&end_time_value, NULL);
    
    return get_time_elapsed();
}

