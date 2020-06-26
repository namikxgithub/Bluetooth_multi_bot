//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(11,12);    //RX,TX

#define ra 5
#define rb 6
#define la 9
#define lb 10

float ty_const =  0.0186;
int encoderPin1 = 2;
int encoderPin2 = 3;

int encoderval_r = 0,r = 0,eval_r = 0;
float d_r = 0,dt_r = 0;
int encoderval_l = 0,l = 0,eval_l = 0;
float d_l = 0,dt_l = 0;

long previousMillis = 0;
long interval = 2000;
float d = 0, dt = 0,dp = 0, vt = 0;

int lastMSB = 0;
int lastLSB = 0;

int ch = 0 , i = 0 ,mval = 80,spd = mval * 2.5;
char Incoming_value = 0;



void forward()
{     
      analogWrite(ra, spd);
      analogWrite(rb, LOW);
      analogWrite(la, spd);
      analogWrite(lb, LOW); 
      l=0;r=0;}

void back()
 {    analogWrite(ra, LOW);
      analogWrite(rb, spd); 
      analogWrite(la, LOW);
      analogWrite(lb, spd);
      l=1;r=1;}

void left()
{     analogWrite(ra, spd);
      analogWrite(rb, LOW); 
      analogWrite(la,LOW);
      analogWrite(lb, spd); 
      l=1;r=0;}

void right()
{     analogWrite(ra, LOW);
      analogWrite(rb, spd); 
      analogWrite(la, spd);
      analogWrite(lb, LOW); 
      l=0;r=1;}
      
void stopp()
{     analogWrite(ra, LOW);
      analogWrite(rb, LOW); 
      analogWrite(la, LOW);
      analogWrite(lb, LOW); }
      

void updateEncoder_r()
{
  int MSB = digitalRead(encoderPin1);
  if(MSB!=lastMSB)
  encoderval_r++; d_r = encoderval_r * ty_const;
  if(r==1)
    {eval_r--;
      dt_r = eval_r * ty_const;}
    if(r==0)
    {eval_r++;
      dt_r = eval_r * ty_const;}
  lastMSB=MSB;
  }
  
void updateEncoder_l()
{
  int LSB = digitalRead(encoderPin2);
  if(LSB!=lastLSB)
  encoderval_l++; d_l = encoderval_l * ty_const;
   if(l==1)
    {eval_l--;
      dt_l = eval_l * ty_const;}
    if(l==0)
    {eval_l++;
      dt_l = eval_l * ty_const;}
  lastLSB=LSB;
  }

    void calculate()
  {
  
    d = (d_r + d_l)/2;
 
    dt = (dt_r + dt_l)/2;
    }



    

    void bl()
    {
      if(Serial.available() > 0)  
  {
    //print_val();  

     Incoming_value = Serial.read();
           
    if(Incoming_value == '0')             
      forward();
        
        
    else if(Incoming_value == '1')       
      back();
      
       else if(Incoming_value == '2')       
      left();

       else if(Incoming_value == '3')       
     right();
     
     else if(Incoming_value == '5')       
     {
      if(mval-10>=10)
      mval = mval - 10;
      spd = mval * 2.5;
     }

     else if(Incoming_value == '4')       
     {
      if(mval+10<=100)
      mval = mval + 10;
      spd = mval * 2.5;
     }

     else if(Incoming_value == '6')       
     {
      stopp();
     }

 }
      }
  

  void print_val()
{
    Serial.print("In val = "); 
    Serial.print(Incoming_value);
    Serial.print("|");
    //Serial.print("Motor speed = "); 
    Serial.print(mval);
     Serial.print("%"); 
    Serial.print("|");
   // Serial.print("left val = ");
    Serial.print(d_l);
     Serial.print(" cm");
    Serial.print("|");
    //Serial.print("right val = ");
    Serial.print( d_r);
    Serial.print(" cm");
     Serial.print("|");
    //Serial.print("distance = ");
    Serial.print( d);
    Serial.print(" cm");
    Serial.print("|");
    Serial.print( dt);
    Serial.print(" cm");
     Serial.print("|");
    Serial.print(vt);
    Serial.print(" cm/h");
    Serial.println(" ");
}


                
void setup() 
{
   //mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(6,  OUTPUT);
  pinMode(5,  OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); 
  digitalWrite(encoderPin2, HIGH); 
  attachInterrupt(0, updateEncoder_r, CHANGE); 
  attachInterrupt(1, updateEncoder_l, CHANGE);

  
 stopp();
  
}

void loop()
{
     
 bl();
 
calculate();



 unsigned long currentMillis = millis();

if (currentMillis - previousMillis > interval) 
{
 previousMillis = currentMillis;
 vt = ((dt - dp)/interval)*3600;
      dp = dt;
 print_val();  

}
     
} 
