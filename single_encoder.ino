 int a1 = 5;
 int a2 = 6;
 int encoderPin1 = 2;
int encoderPin2 = 3;

int lastEncoded = 0;
int encoderval_r = 0;
int encoderval_l = 0;


int lastMSB = 0;
int lastLSB = 0;


 void print_val()
{
    Serial.print("left val = ");
    Serial.print(encoderval_l);
    Serial.print("|");
    Serial.print("right val = ");
    Serial.println(encoderval_r);
}

void setup() {
   Serial.begin (9600);

  pinMode(a1, OUTPUT); 
  pinMode(a2, OUTPUT);
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder_r, CHANGE); 
  attachInterrupt(1, updateEncoder_l, CHANGE);

}

void loop() {
   
  if(Serial.available() > 0)
  {
    if(Serial.read() == '0')
  {
    analogWrite(a1,150);
    analogWrite(a2,0);
    }
    if(Serial.read() == '6')
  {
    analogWrite(a1,0);
    analogWrite(a2,0);
    }
    Serial.print(Serial.read());
    }
  //print_val();
  //delay(1000); 
}

void updateEncoder_r()
{
  int MSB = digitalRead(encoderPin1);
  if(MSB!=lastMSB)
  encoderval_r++;
  lastMSB=MSB;
  }
void updateEncoder_l()
{
  int LSB = digitalRead(encoderPin2);
  if(LSB!=lastLSB)
  encoderval_l++;
  lastLSB=LSB;
  }
