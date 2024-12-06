#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
// including necessary libraries 

RF24 radio(8,10); // (CE, CSN)

#define X_joystick A0
#define Y_joystick A1
int F_or_B ;
int L_or_R ;

const byte address[6] = "00001";
struct data{
 int Channel_1;
 int Channel_2;
};
data send_data;

void setup() {
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_MAX);
radio.setDataRate(RF24_250KBPS);
radio.stopListening();
Serial.begin(9600);
}

void loop(){
F_or_B = analogRead(X_joystick);
Serial.print("  Joystick Value F or B :  ");
Serial.print(F_or_B);
L_or_R = analogRead(Y_joystick); 
Serial.print("   Joystick Value L or R :  ");
Serial.println(L_or_R);

if ( F_or_B > 650 ){
  Serial.print ("  forward  ");
  }
else if ( F_or_B < 350){
   Serial.print ("   back   ");
  }
else if (L_or_R < 350){
   Serial.print("   left   ");
  }
else if ( L_or_R > 650){
   Serial.print("   right   ");
  }

 send_data.Channel_1 = F_or_B;
 send_data.Channel_2 = L_or_R;
 radio.write(&send_data, sizeof(data));
}
