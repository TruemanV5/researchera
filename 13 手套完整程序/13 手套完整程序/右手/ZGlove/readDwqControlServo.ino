/*读取电位器采集值，转化为舵机的控制量*/
void readDwqControlServo(){
    static int old_pos[DWQ_NUM] ={0},old_pos1=0;
    static int temp[DWQ_NUM] = {0},temp1=0;
    for(byte i = 0; i < DWQ_NUM; i++){//优化限制
        ADCRead();
        temp[i] = read_dwq[i];
        if(temp[i] < ADC_MIN[i]){
            temp[i] = ADC_MIN[i];
         }else if(temp[i] > ADC_MAX[i]){
            temp[i] = ADC_MAX[i];
        } else{     
            ;
        }                             
        switch (i){//将采集到的电位器值，映射到手掌可控变量范围内       
            case 0: pos[0] = map(temp[0], ADC_MIN[0], ADC_MAX[0], 2000, 1000); break;
            case 1: pos[1] = map(temp[1], ADC_MIN[1], ADC_MAX[1], 1000, 2000); break;
            case 2: pos[2] = map(temp[2], ADC_MIN[2], ADC_MAX[2], 1000, 2000); break;
            case 3: pos[3] = map(temp[3], ADC_MIN[3], ADC_MAX[3], 2000, 1000); break;
            case 4: pos[4] = map(temp[4], ADC_MIN[4], ADC_MAX[4], 2000, 1000); break;
            default : Serial.println("error\n");                               break;
        }
        myservo[i+1].writeMicroseconds(pos[i]);   // 给舵机写入角度,i+1错开云台舵机
    }//有数据变化时才会发送数据
    temp1 = Filter();
    if(abs(temp1-old_pos1)>3 && (temp1>260||temp1< 410)){
        pos1 = map(temp1, 260, 410, 510, 2490);   
        old_pos1 = temp1;
        myservo[0].writeMicroseconds(pos1);//云台舵机接到0号舵机
    }     
}
