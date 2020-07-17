/*读取已存储的电位器值，第一个形参是存储起始地址，第二个形参是读取到这个变量中*/
void eepromRead(unsigned int addr, unsigned int data[]){
    static int data_addr = addr;//存储地址 
    for(byte i = 0, data_addr = addr; i < DWQ_NUM ; i++) {//取值存储到EEPROM的旋钮值并复制给dwq_init_value
        for(byte j = 0; j < INT_DATA_TYPE ; j++){//拆分读出
           init_val[i].b[j] = EEPROM.read(data_addr++);
        }
        data[i] = init_val[i].a;
    }    
}
