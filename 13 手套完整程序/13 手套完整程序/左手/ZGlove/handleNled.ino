/*处理工作指示灯，每个1S闪烁一次*/
void handleNled() {
    static bool val = 0;
    static unsigned long systick_ms_bak = 0;
    if(handleTimePeriod(&systick_ms_bak, 1000))return;  
    digitalWrite(LED_PIN, val);
    val = !val;
}
