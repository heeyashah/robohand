#include <Servo.h>
// Define constants for data reception
#define numOfValsRec 5
#define digitsPerValRec 1

// Create Servo objects for the servos controlling each finger 
Servo servoThumb; 
Servo servoIndex; 
Servo servoMiddle; 
Servo servoRing; 
Servo servoPinky; 

// Arrays and variables for data reception and processing 
int valsRec[numOfValsRec]; //Array to store received values
int stringLength = numOfValsRec * digitsPerValRec + 1; //Length of received string ($00000)
int counter=0; // Counter to track received characters
bool counterStart = false; // Flag indicating start of counter
String receviedString; //String to hold recevied data 

void setup (){
  Serial.begin(9600); // Tnitializing Serial Communication
  // Indicating what pin each servo is connected to 
  servoThumb.attach(3);
  servoIndex.attach(7);
  servoMiddle.attach(5); 
  servoRing.attach(9); 
  servoPinky.attach(11); 

}

void receiveData(){
while (Serial.available()){
char c = Serial.read();

  if (c=='$'){
    counterStart = true; // Start counting characters after receiving '$'
  }
  if (counterStart){
    if (counter < stringLength){
      receviedString += c; // Add the received character to the string 
      counter ++;
    }
    if (counter >= stringLength){
        for (int i = 0; i<numOfValsRec; i++){
            int num = (i * digitsPerValRec) + 1;
            valsRec[i] = receviedString.substring(num,num+digitsPerValRec) .toInt ();
            }
            receviedString = ""; // Reset received string
            counter = 0; //Reset counter
            counterStart = false; //Reset counter start flag
    }
  }
}

}

void loop(){
  receiveData(); // Call the receiveData function to handle serial data reception
  
  // Set servo angles based on received values (1 for open, 0 for closed)
  if (valsRec[0] == 1){servoThumb.write(0);} else{servoThumb.write(180);}
  if (valsRec[1] == 1){servoIndex.write(0);} else{servoIndex.write(180);}
  if (valsRec[2] == 1){servoMiddle.write(0);} else{servoMiddle.write(180);}
  if (valsRec[3] == 1){servoRing.write(0);} else{servoRing.write(180);}
  if (valsRec[4] == 1){servoPinky.write(0);} else{servoPinky.write(180);}
}