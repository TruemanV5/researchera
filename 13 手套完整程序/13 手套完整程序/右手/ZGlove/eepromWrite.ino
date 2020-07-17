/*写入读取到的电位器值，第一个形参是存储起始地址，第二个形参是要存储到变量*/
void eepromWrite(unsigned int addr, unsigned int data[]){
    static int data_addr = addr;//存储地址 
    for(byte i = 0, data_addr = addr; i < DWQ_NUM; i++) {//求取旋钮平均值，存储到EEPROM
        init_val[i].a = data[i];
        for(byte j = 0; j < INT_DATA_TYPE ; j++){//拆分写入
            EEPROM.write(data_addr++, init_val[i].b[j]);
        }
    }        
}
