/*以固定格式发送数据,定时500毫秒发一次*/
void uart1_send(){    
    static char cmd_return[100];
    if(flag1==0){
        sprintf(cmd_return,"{#000P%04dT0500!#001P%04dT0050!#002P%04dT0050!#003P%04dT0050!#004P%04dT0050!#005P%04dT0050!   SZ}", pos1, pos[0], pos[1], pos[2], pos[3], pos[4]);
        Serial.println(cmd_return);          
    }else{
        sprintf(cmd_return,"{#000P%04dT0500!#001P%04dT0050!#002P%04dT0050!#003P%04dT0050!#004P%04dT0050!#005P%04dT0050!   SZ}", 1500, pos[0], pos[1], pos[2], pos[3], pos[4]);
        Serial.println(cmd_return);  
   }
}
