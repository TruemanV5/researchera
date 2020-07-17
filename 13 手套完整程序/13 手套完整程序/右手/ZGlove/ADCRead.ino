/*读取电位器值*/
void ADCRead(){
    static long sum[DWQ_NUM] = {0}; 
    static int temp[DWQ_NUM] = {0};
    for(byte i = 0; i < 3; i++){//读取三次累加
        for(byte j = 0; j < DWQ_NUM; j++){
            temp[j] = analogRead(dwq_pin[j]);
            sum[j] += temp[j]; 
            temp[j] = 0;   
        } 
    }   
    for(byte i = 0; i < DWQ_NUM ; i++) {//求取旋钮平均值
        read_dwq[i] = sum[i]/3;
        sum[i]=0;
        //Serial.println(read_dwq[i]);  
    }    
}
