#include <MsTimer2.h>
#include <Servo.h>            // 调用Servo.h库
#include <EEPROM.h>           //调用<EEPROM.h库
#define  SERVO_NUM  6          //宏定义舵机数
#define  DWQ_NUM    5          //宏定义舵机数
#define  LED_PIN    13         //宏定义工作指示灯引脚
#define  BEEP_PIN   3          //宏定义蜂鸣器引脚
#define  KEY_J   4             //宏定义校准引脚
#define  KEY_M   5             //宏定义模式引脚
//#define  PWM_MAX    2000      //映射范围的最大值
//#define  PWM_MIN    1000      //映射范围的最小值
#define  ADC_MIN_ADDR   0     //握紧时采集电位器值起始地址
#define  ADC_MAX_ADDR   30    //张手时采集电位器值起始地址
#define INT_DATA_TYPE   2     //数据类型,数据类型=几个字节就是几，相当于数据拆分成字节
#define  FILTER_N       9     //中位值滤波法   
#define BEEP_MJ {digitalWrite(BEEP_PIN, LOW); delay(300); digitalWrite(BEEP_PIN, HIGH);}

unsigned int ADC_MAX[DWQ_NUM] = {612, 612, 612, 612, 612}; //默认握紧时采集电位器值
unsigned int ADC_MIN[DWQ_NUM] = {412, 412, 412, 412, 412}; //默认张手时采集电位器值
unsigned int pos[DWQ_NUM] = {0};                           //变量pos用来存储舵机位置
unsigned int pos1 = 0;  
int xx=0, yy = 0, zz = 0;  
unsigned int dwq_init_value[DWQ_NUM] = {0};       //电位器初始值
unsigned int read_dwq[DWQ_NUM] = {0};             //读取电位器值
byte servo_pin[SERVO_NUM] = {11,10, 9, 8, 7, 6}; //定义舵机控制引脚数组
byte dwq_pin[DWQ_NUM] = {A6, A5, A4, A3, A2};    //定义电位器引脚数组
Servo myservo[SERVO_NUM];                        //创建舵机类数组
/****************** INTERRUPT ******************/
/*      Uncomment If Attaching Interrupt       */

bool flag = 0;                                       //定义一个标志位变量，用来判断校准
bool flag1 = 0;                                      //定义一个标志位变量，用来判断工作模式
union intData{                                       //申明一个共用体，两个变量公用一个存储空间
    int a;
    char b[2];
};
intData init_val[DWQ_NUM];

void setup(){
    Serial.begin(115200);                   //初始化波特率为115200
    pinMode(LED_PIN, OUTPUT);               //设置LED引脚为输出模式
    pinMode(BEEP_PIN, OUTPUT);              //设置蜂鸣器引脚为输出模式
    digitalWrite(BEEP_PIN, HIGH);
    pinMode(4, INPUT_PULLUP);              //将模式按键对应引脚设置为内部上拉输入模式，防止误判
    pinMode(5, INPUT_PULLUP);              //将校准按键对应引脚设置为内部上拉输入模式，防止误判
    for(byte i = 0; i < SERVO_NUM; i++){
         myservo[i].attach(servo_pin[i]);   // 将5引脚与声明的舵机对象连接起来
         myservo[i].writeMicroseconds(1500);       
    } 
    eepromRead(ADC_MIN_ADDR, ADC_MIN);//读取存储到的电位器值
    eepromRead(ADC_MAX_ADDR, ADC_MAX);
                        
    MsTimer2::set(50, uart1_send); // 500ms period
    MsTimer2::start();
    BEEP_MJ     //鸣叫一声，初始化完成
}

void loop(){ 
    handleNled();               //工作指示灯处理函数，一秒闪烁一次
    readDwqControlServo();      //
    calibration_ADC_MIN_MAX();  //
}




