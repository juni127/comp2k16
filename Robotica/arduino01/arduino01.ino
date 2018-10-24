
#define PWMA 6
#define DIRA 8
#define PWMB 5
#define DIRB 7

int i;

int s1, s2;

void setup(){
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);

  
  Serial.begin(9600);
}

void loop(){
  s1 = analogRead(0);
  s2 = analogRead(1);
  
  int o1 = 0;
  int o2 = 0;
  byte teste = 127;
  

  if(s2 < 500)
   o1 = teste;
  
  digitalWrite(DIRA, HIGH);
  analogWrite(PWMA, o1);

  if(s1 < 500)
    o2 = teste;
  
  digitalWrite(DIRB, HIGH);
  analogWrite(PWMB, o2);

  Serial.print("A0: ");
  Serial.print(s1);
  Serial.print("  x  ");
  Serial.print("A1: ");
  Serial.println(s2);
  delay(500);
}
