#define PWMA 6
#define DIRA 8
#define PWMB 5
#define DIRB 7

int i;

void setup(){
  pinMode(6, OUTPUT);//PWM A
  pinMode(8, OUTPUT);//PWM B
  pinMode(5, OUTPUT);//PWM A
  pinMode(7, OUTPUT);//PWM B
  //pinMode();
  
  Serial.begin(9600);
}

void loop(){
  analogRead(A0);
  analogRead(A1);
  
  digitalWrite(8, HIGH);
  analogWrite(6, 100);
  digitalWrite(7, LOW);
  analogWrite(5, 100);
}
