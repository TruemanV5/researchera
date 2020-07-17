
/*时间处理函数，判断当前时间减去上次时间点是否达到设定的时间段，
要是达到则返回0，达不到返回1*/
bool handleTimePeriod( unsigned long *ptr_time, unsigned int time_period) {
    if((millis() - *ptr_time) < time_period) {
        return 1;  
    } else{
         *ptr_time = millis();
         return 0;
    }
}
