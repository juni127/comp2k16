
#define PWMA 6
#define DIRA 8
#define PWMB 5
#define DIRB 7

#define MAXVEL 125

int i;

int s1, s2;

int threshold, del = 20;
byte teste;



//Funço que imprime o valor dos sensores de brilho
void printsensors(int s1, int s2){
  //disconecte o motor na hora de ler os sensores!
  
  Serial.print("A0: ");
  Serial.print(s1);
  Serial.print("  x  ");
  Serial.print("A1: ");
  Serial.println(s2);
  
  delay(500);
  
}


void setup(){
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  
  threshold = 500;
  
  Serial.begin(9600);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  analogWrite(PWMA, MAXVEL);
  analogWrite(PWMB, MAXVEL);
}




void loop(){
  s1 = analogRead(0);
  s2 = analogRead(1);

  if(s2 >threshold){
   digitalWrite(DIRA, HIGH);
   delay(del);
  }else if(s1 >threshold){
    digitalWrite(DIRB, HIGH);
    delay(del);
  }else {
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
  }  
  
  
  //Essa funço tem que ser descomentada apenas quando for testar os sensores com os motores DESLIGADOS
  //printsensors(s1,s2);  
  
}

