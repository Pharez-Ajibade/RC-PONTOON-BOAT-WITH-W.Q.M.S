#include <Servo.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
// including necessary libraries 

int Throttle = 500; // set throttle joystic value
int L_or_R = 500; // set directional control joystic value

RF24 radio(8, 10); // (CE, CSN)

const byte address[6] = "00001"; 

struct data {
  int Channel_1;
  int Channel_2;
};

data receive_data;

Servo Left_ESC; // CREATING SERVO OBJECTS
Servo Right_ESC; // CREATING SERVO OBJECTS

void setup() {
  // put your setup code here, to run once: 
Serial.begin(9600);

Left_ESC.attach(6,1000,2000);
Right_ESC.attach(7,1000,2000); 

radio.begin();
radio.openReadingPipe(0,address);
radio.setPALevel(RF24_PA_MAX);
radio.setDataRate(RF24_250KBPS);
radio.startListening();

 while(radio.available() != true) {
 Serial.println("RADIO NOT CONNECTED");
 }
}

void loop() {
 while(radio.available()) {
    radio.read(&receive_data, sizeof(data));
  Serial.print(receive_data.Channel_1); 
    Serial.print("  "); 
  Serial.println(receive_data.Channel_2); 

   Throttle = receive_data.Channel_1;
   int ThrottleL = 0 ;
   int ThrottleR = 0 ;
   L_or_R = receive_data.Channel_2;

   Throttle = map(Throttle, 500, 1023, 0, 180); // if you can make joystick compliant in one direction to get 0 to 1023
   Throttle = constrain(Throttle, 0, 180);
   
   
  
   if ( L_or_R < 460){ /// turn left
    int L_val = map(L_or_R, 460, 0, 0, Throttle);
     ThrottleL = Throttle - L_val; // reduce left throttle by degree of joystick movement to to left
    }  
  else{
     ThrottleL = Throttle ;
    }
  
  if (L_or_R > 560){ // turn right
     int R_val = map(L_or_R, 560, 1023, 0, Throttle);
     ThrottleR = Throttle - R_val; // reduce right throttle by degree of joystick movement to to left
   }
   else{
   ThrottleR = Throttle ;  
    }
   
   Left_ESC.write(ThrottleL);
   Right_ESC.write(ThrottleR);

  Serial.print(" Left Throttle speed : ");
  Serial.print(ThrottleL);
  Serial.print("  "); 
  Serial.print(" Right Throttle speed : ");
  Serial.println(ThrottleR);
 
 }
}
