#define enA 10 // controls left Motor
#define enB 5 // controls Right Motor

int trigPin=12;
int echoPin=13;
int motor1L =A1; //Left Motor
int motor1R =A0;

int motor2L = A2; //Right Motor
int motor2R = A3;
const int sensorPin1 = 2;// first IR Sensor
const int sensorPin2 = 4; //second IR Sensor
int sensorValue1 = 0;   
int sensorValue2 = 0;   

boolean state = true;// use to the intersection counting

int fd;

int sp=150;// speed at which the motors are to run

int L_Sensor = 2; 
int R_Sensor = 4; 
long  distance;
 int countx=0;
 int county=0;



void setup(){
Serial.begin(9600);
 
analogWrite(enA, sp); 
analogWrite(enB, sp);

// setting all inputs and outputs
 pinMode (trigPin, OUTPUT);
 pinMode (echoPin, INPUT); 
 pinMode(motor1L, OUTPUT);
 pinMode(motor1R, OUTPUT);
 pinMode(motor2L, OUTPUT);
 pinMode(motor2R, OUTPUT);
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(L_Sensor, INPUT);
 pinMode(R_Sensor, INPUT);
  

 
 }

void loop(){
  
// Ultrasonic Sensor calibration
fd=obstacle();
Serial.print("FD ");
Serial.println(fd); 
delay(500);*/
// reading the sebsors values
sensorValue1 = digitalRead(sensorPin1);
sensorValue2 = digitalRead(sensorPin2);

// IR  Sensor calibration
Serial.print("Pin 1: ");
Serial.print(sensorValue1);
Serial.print(" / Pin 2: ");
Serial.println(sensorValue2);
Serial.println("--------");

// checking via serial monitor if sensors are counting after each intersection
Serial.print("counterX: ");
Serial.print(countx);
Serial.print("counterY: ");
Serial.print(county);
delay(100);
 

// counting on the X-axis
if ((digitalRead(L_Sensor) == 0)&&(digitalRead(R_Sensor) == 0)&&(state))
  {
   countx++;
   state=false;
  }


// checking number of intersections then stoping the car
if (countx==2)
  {
    stop_V();delay(1);
    turnLeft();
  }



// counting on the Y-axis
if ((digitalRead(L_Sensor) == 0)&&(digitalRead(R_Sensor) == 0)&&(state)&&(countx==2))
  {
    county++; 
    state=false;
  }
if (county==2)
  {
    stop_V();

  }



if ((digitalRead(L_Sensor) == 1)&&(digitalRead(R_Sensor) == 1 ))
  {
  forward();
  state=true;
  delay(100);
  }


//calling the 3 functions to keep the car driving and and aligning
if ((digitalRead(L_Sensor) == 1)&&(digitalRead(R_Sensor) == 1 ))
  {
  forward();
  }
  
if ((digitalRead(L_Sensor) == 0)&&(digitalRead(R_Sensor) == 1))
  {
  turnLeft();
  delay(1);
  }
  
if ((digitalRead(L_Sensor) == 1)&&(digitalRead(R_Sensor) == 0))
  {turnRight();
  delay(1); 
  
  }


}

long obstacle(){
int duration;
int distance;
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(20);
 digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  
  delay(25);

  /*Distance = (Time x speed of sound (340 m/s))/2||distance is measured in cm */
 distance = duration*0.034/2;
 return distance;

 
 if ( distance<5)// checking how far the obstacle is and stoping the car
  {
  stop_V();
  delay(1);
  }
}
  
// function tells the car to stop
void stop_V(){
 digitalWrite(motor1L, LOW);
 digitalWrite(motor1R,LOW);
 digitalWrite(motor2L, LOW);
 digitalWrite(motor2R, LOW);
}

// function tells the car to keep driving forward
void forward(){
 digitalWrite(motor1L, HIGH);
 digitalWrite(motor1R, LOW);
 digitalWrite(motor2L, HIGH);
 digitalWrite(motor2R, LOW); 
 
analogWrite(enA, sp);
analogWrite(enB, sp);
  
}

// function used to prevent the robot from moving too far to the left
void turnRight(){
digitalWrite(motor1L, HIGH);
digitalWrite(motor1R, LOW);
digitalWrite(motor2L, LOW);
digitalWrite(motor2R, LOW); 

analogWrite(enA, sp); 
analogWrite(enB, 0);

}
// function used to prevent the robot from moving too far to the right
void turnLeft(){
digitalWrite(motor1L, LOW);
digitalWrite(motor1R, LOW);
digitalWrite(motor2L, HIGH);
digitalWrite(motor2R, LOW);  

analogWrite(enA, 0); 
analogWrite(enB, sp);

}
