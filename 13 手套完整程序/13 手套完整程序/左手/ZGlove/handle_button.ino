
/*校准体感手套电位器范围，使得其和手掌可控范围相一致，达到较好的控制效果*/   
void calibration_ADC_MIN_MAX(){
    if((digitalRead(5)==LOW) && (flag==0)) {//第一次校准，握手值：在舒适的方式下最大程度的握紧手指，此时按下校准按钮
        delay(10);    
        if((digitalRead(5)==LOW) && (flag==0)){
            ADCRead();         
            eepromWrite(ADC_MIN_ADDR, read_dwq);
            flag = 1;  
            eepromRead(ADC_MIN_ADDR, ADC_MIN);
            //Serial.println("ADC_MIN_ADDR");
            BEEP_MJ  
            delay(1500);
        }
    }
    if((digitalRead(5)==LOW) && (flag==1)) {//第二次校准，伸手值：在舒适的方式下最大程度的伸开手指，此时按下校准按钮
        delay(10);    
        if((digitalRead(5)==LOW ) && (flag==1)){
            ADCRead();
            eepromWrite(ADC_MAX_ADDR, read_dwq);
            flag = 0;  
            eepromRead(ADC_MAX_ADDR, ADC_MAX);
            //Serial.println("ADC_MAX_ADDR");
            BEEP_MJ    
            delay(1500);
        }    
    }
    if(digitalRead(4)==LOW) {//第一次校准，握手值：在舒适的方式下最大程度的握紧手指，此时按下校准按钮
        delay(10);    
        if(digitalRead(4)==LOW){
         flag1 =!flag1;  
         BEEP_MJ   
        }
    }   
}
