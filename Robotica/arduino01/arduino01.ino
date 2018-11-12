
#define PWMA 6
#define DIRA 8
#define PWMB 5
#define DIRB 7

#define MAXVEL 110

int i;

int s1, s2;

int o1,o2,threshold, del;
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
  
  o1 = MAXVEL;
  o2 = MAXVEL;
  threshold = 400;
  del = 35;
  
  Serial.begin(9600);
}

int count=0;
void loop(){
  s1 = analogRead(0);
  s2 = analogRead(1);
  
  if(s2 >threshold){
   if (count >= 100){
     digitalWrite(DIRA, LOW);
     digitalWrite(DIRB, LOW);
     delay(count-80);
     digitalWrite(DIRA, HIGH);
     digitalWrite(DIRB, LOW);
     delay(del+(count-75));
   }else{
     digitalWrite(DIRA, HIGH);
     digitalWrite(DIRB, LOW);
     delay(del);
   }
   count +=20;

   
  }else if(s1 >threshold) {
    
    if (count >= 100){
     digitalWrite(DIRA, LOW);
     digitalWrite(DIRB, LOW);
     delay(count-80);
     
     digitalWrite(DIRA, LOW);
     digitalWrite(DIRB, HIGH);
     delay(del+count-75);
    }else{
      digitalWrite(DIRA, LOW);
      digitalWrite(DIRB, HIGH);
      delay(del);
    }
     count +=20;
  }else {
   digitalWrite(DIRA, LOW);
   digitalWrite(DIRB, LOW);
   count = 0;
  }  
  
  
  //Essa funço tem que ser descomentada apenas quando for testar os sensores com os motores DESLIGADOS
  //printsensors(s1,s2);
  
  analogWrite(PWMA, o1);
  analogWrite(PWMB, o2);
  
  
}
