
/*
 Arduino RC Connection
Bluetooth Module: 
RX ==> D1
TX ==> D0
GND => GND
VCC ==> 5V
H Bridge: 
IN1 ==> D6
IN2 ==> D7
IN3 ==> D8
IN4 ==> D9
Ultrasonic: 
Trigger ==> D5
Echo ==> A2
GND ==> GND 
VCC ==> 5V

Buzzer:
VCC ==> D3
 */


char t;

#define alert 3
#define fl 6
#define bl 7
#define fr  8
#define br  9
#define ld  10
#define echoPin A2
#define trigPin 5


long duration;
int distance;

void setup() {
pinMode(fl,OUTPUT);   //left motors forward
pinMode(bl,OUTPUT);   //left motors reverse
pinMode(fr,OUTPUT);   //right motors forward
pinMode(br,OUTPUT);   //right motors reverse
pinMode(ld,OUTPUT);   //Led
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(alert,OUTPUT);

Serial.begin(9600);
 
}
 
void loop() {
dist();

while(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}

if(t == 'F'){ //move forward(all motors rotate in forward direction)
  digitalWrite(fl,HIGH);
  digitalWrite(fr,HIGH);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(bl,HIGH);
  digitalWrite(br,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(fr,HIGH);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(fl,HIGH);
}

else if(t == 'W'){    //turn led on or off)
  Serial.println("UV UP");
  digitalWrite(ld,HIGH);
}
else if(t == 'w'){
  Serial.println("UV DOWN");
  digitalWrite(ld,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  Serial.println("STOP");
  digitalWrite(fl,LOW);
  digitalWrite(bl,LOW);
  digitalWrite(fr,LOW);
  digitalWrite(br,LOW);
}

 if(distance < 15 ) {
  digitalWrite(alert,HIGH);// Send 1KHz sound signal...
  delay(500);        // ...for 1 sec
  digitalWrite(alert,LOW);
  noTone(alert);     // Stop sound...
  delay(500);        // ...for 1sec
  digitalWrite(bl,HIGH);
  digitalWrite(br,HIGH);
  delay(100);
  digitalWrite(bl,LOW);
  digitalWrite(br,LOW);
  Serial.println("bussss");
}
delay(100);
}



void dist() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}
