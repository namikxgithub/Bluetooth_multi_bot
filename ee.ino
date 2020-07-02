#define era 2
#define erb 3
#define ela 11
#define elb 8

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void encoder_change()
{
 int a = digitalRead(era);
 int b = digitalRead(erb);
 int c = digitalRead(ela);
 int d = digitalRead(elb);

 int encoded = (a << 1) |b;
  int sum  = (lastEncoded << 2) | encoded; 

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; 
 }

void print_encoder_val()
{
Serial.print("encoder = ");
Serial.println(encoderValue);
//Serial.print("     right encoder = ");
//Serial.println(ENCR);
}
 
void setup() {
  Serial.begin(9600);
  pinMode(2,  INPUT); 
  pinMode(3,  INPUT); 
  pinMode(11, INPUT); 
  pinMode(8, INPUT);
}

void loop() {
encoder_change();
print_encoder_val();
}
