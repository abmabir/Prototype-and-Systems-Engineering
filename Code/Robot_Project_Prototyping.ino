#define enA 10
#define enB 5

/*Port assignment*/
int trigPin=12;
int echoPin=13;
int motor1L =A1;
int motor1R =A0;

int motor2L = A2;
int motor2R = A3;
const int sensorPin1 = 2;
const int sensorPin2 = 4;
int L_Sensor = 2; 
int R_Sensor = 4;


 /*Variable declaration*/
int sensorValue1 = 0;   
int sensorValue2 = 0; 
int fd;
int sp=150;
long  distance;


void setup(){
Serial.begin(9600);

/*Defining what get to be input or output*/

 pinMode (trigPin, OUTPUT);
 pinMode (echoPin, INPUT);  
  
analogWrite(enA, sp); 
analogWrite(enB, sp);
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

 /*Checking how far the obstacle is*/ 
if ( distance<5){stop_V();/*delay(1)*/;}

/*Testing the ultrasonic sensor*/
fd=data();
Serial.print("FD ");
Serial.println(fd); 
delay(500);

/*Calibration of the IR sensors*/
sensorValue1 = digitalRead(sensorPin1);
sensorValue2 = digitalRead(sensorPin2);
Serial.print("Pin 1: ");
Serial.print(sensorValue1);
Serial.print(" / Pin 2: ");
Serial.println(sensorValue2);
Serial.println("--------");
delay(2000);
 

/*If both sensors dont see any black color car stop*/
if ((digitalRead(L_Sensor) == 0)&&(digitalRead(R_Sensor) == 0)){stop_V();delay(1);}

if ((digitalRead(L_Sensor) == 1)&&(digitalRead(R_Sensor) == 1)){forward();delay(1);}

if ((digitalRead(L_Sensor) == 0)&&(digitalRead(R_Sensor) == 1)){turnLeft();delay(1);}

if ((digitalRead(L_Sensor) == 1)&&(digitalRead(R_Sensor) == 0)){turnRight();delay(1);}


}

long data(){
int duration;
int dist;
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(20);
 digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  
  delay(25);
 dist = (duration*765.*5280.*12) /(3600.*1000000);
 distance=dist/2;
     return distance;
 if ( distance<5){stop_V();delay(1);}
}
  
/*function that brings the car to a stop*/
void stop_V(){
 digitalWrite(motor1L, LOW);
 digitalWrite(motor1R,LOW);
 digitalWrite(motor2L, LOW);
 digitalWrite(motor2R, LOW);
 
}

/*function to make robot move forward*/
void forward(){
 digitalWrite(motor1L, HIGH);
 digitalWrite(motor1R, LOW);
 digitalWrite(motor2L, HIGH);
 digitalWrite(motor2R, LOW); 


  
}

/*function that turns the car to the right*/
void turnRight(){
digitalWrite(motor1L, HIGH);
digitalWrite(motor1R, LOW);
digitalWrite(motor2L, LOW);
digitalWrite(motor2R, LOW);  

}
/*function that turns the car to the left*/
void turnLeft(){
digitalWrite(motor1L, LOW);
digitalWrite(motor1R, LOW);
digitalWrite(motor2L, HIGH);
digitalWrite(motor2R, LOW);  

}
