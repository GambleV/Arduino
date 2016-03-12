#define CLK_PIN 2 //順時針轉動時CLK腳位就會呈低電位
#define DT_PIN 3 //讀取DT資料腳位,HIGH代表正轉
#define SW_PIN 4  //SW開關腳位

unsigned long time = 0;
volatile long position = 0;
volatile long num = 0;

void setup() {
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP); // 輸入模式並啟用內建上拉電阻
  attachInterrupt(0, RotaryEncoder, LOW);
  Serial.begin(9600);
  time = millis();
}
void loop() {
  if (digitalRead(SW_PIN) == LOW) { // 按下開關，歸零
    position = 0;
    Serial.println("count reset to 0");
    delay(300);
  }
  while (num != position) {
    num = position;
    Serial.println(num);
    //Serial.print(digitalRead(CLK_PIN));
    //Serial.print(digitalRead(DT_PIN));
    //Serial.println(digitalRead(SW_PIN));
  }
}


void RotaryEncoder() {
  int temp = digitalRead(CLK_PIN);
  if ((millis() - time) > 2) {
    if ( temp == LOW) {
      position++;
    } else {
      if ( temp == HIGH){
        position--;
      }
    }
  }
  time = millis();
}
