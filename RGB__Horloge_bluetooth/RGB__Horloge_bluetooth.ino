// DS3231_Serial_Hard
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS3231-library to 
// retrieve time- and date-data for you to manipulate.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicat                                                                                                                                       ed SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#include <DS3231.h>
#include <Wire.h>
#define DS3231_I2C_ADDRESS 0x68
// Init the DS3231 using the hardware interface
DS3231  rtc(A4, A5);

// Init a Time-data structure
Time  t;

#include <SoftwareSerial.h>
 
SoftwareSerial SerialBTS(10, 11); // RX | TX

#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 27

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

//essaie avec 12:46
int dH=1;
int mH=4;
int dM=3;
int mM=6;

int leddH[]={0,0,0};
int ledmH[]={0,0,0,0,0,0,0,0,0};
int leddM[]={0,0,0,0,0,0};
int ledmM[]={0,0,0,0,0,0,0,0,0};
int randdH=-1;
int randmH=-1;
int randdM=-1;
int randmM=-1;

int lum=250;

float A=255,B=255,C=0,D=255,E=0,F=0,G=0,N=255,I=0,J=0,K=0,L=255;
float Q=0;
const char LEDRdH='A' ,LEDGdH='B',LEDBdH='C';
const char LEDRmH='D' ,LEDGmH='E',LEDBmH='F';
const char LEDRdM='G' ,LEDGdM='N',LEDBdM='I';
const char LEDRmM='J' ,LEDGmM='K',LEDBmM='L';
const char hiver='Q', ete='m';

int test=-1;
void setup() {
  Wire.begin();
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  
    // Setup Serial connection
  Serial.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  SerialBTS.begin(9600); 

  //rtc.setTime(11,47 , 00);
  }

void loop() {
  
 
  // Read from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    SerialBTS.write(Serial.read());
  

 
  // Get data from the DS3231
  /*
  t = rtc.getTime();
  int H=t.hour;
  int M=t.min;
  */
  if (H>7 and H<21)lum=1;
    
  
  else lum=5;
  dH=int(H/10);
  mH=int(H%10);
  dM=int(M/10);  
  mM=int(M%10);

/*
Serial.println(dH);
Serial.println(mH);
Serial.println(dM);
Serial.println(mM);
 */  
  if ((Q==1)) {
    rtc.setTime(H+1, t.min, t.sec);     // Set the time to 12:00:00 (24hr format); // Si le bouton a un état différent de celui enregistré et  que cet état est "haut"
Q=-1;
  }
   else if ((Q== 0)){
    rtc.setTime(H-1, t.min, t.sec); // Si le bouton a un état différent de celui enregistré et  que cet état est "haut"
Q=-1;
   }
 



  //------------------------------------------
  if (dM!=0){
    for (int i=1;i<=dM;i++){
      randdM=random(0,6);
      while (leddM[randdM]==1){
        randdM=random(0,6);
        if (leddM[randdM]==0)break;
        }
      leddM[randdM]= 1;
      }
    for (int i=0;i<6;i++) if (leddM[i]==1)leds[i+12].setRGB( G/lum, N/lum,I/lum );  
    }
  //--------------------------------------------------------
  
  //------------------------------------------
  if (dH!=0){//si l'heure est à zero sa sert à rien d'allumer une led
    for (int i=0;i<dH;i++){ //je passe dans la boucle autant de fois qu'il y a de led à allumer 
      randdH=random(0,3); //tire une position au hasard en fonction du nombre de position possible
      while (leddH[randdH]==1){ //tant que la position à déja été tirer je recommance
        randdH=random(0,3); //tire une position au hasard en fonction du nombre de position possible
        if (leddH[randdH]==0)break;//je pars de la boucle while si je tombe sur une position pas encore obtenue( je dois le faire sinon ça bug )
        }
      leddH[randdH]= 1; //je met un 1 à la position tiré qui est bonne 
      }
    for (int i=0;i<3;i++)if (leddH[i]==1)leds[i].setRGB( A/lum, B/lum,C/lum); //je regarde à chaque position si la led doit etre allumé ou pas et j'indique qu'elle doit être allumé
    }
  //--------------------------------------------------------
  
  //------------------------------------------
  if (mM!=0){
    for (int i=1;i<=mM;i++){
 
      randmM=random(0,8);
      
      while (ledmM[randmM]==1){
        randmM=random(0,9);
        if (ledmM[randmM]==0)break;
        }       
      ledmM[randmM]= 1;  
      }
      

    for (int i=0;i<9;i++) {
      if (ledmM[i]==1)leds[i+18].setRGB( J/lum, K/lum,L/lum );      
    }
          
    }
    
  //--------------------------------------------------------
  
  
  
    //------------------------------------------
  if (mH!=0){
    for (int i=0;i<mH;i++){
      randmH=random(0,9);
      while (ledmH[randmH]==1){
        randmH=random(0,9);
        if (ledmH[randmH]==0)break;
        }
      ledmH[randmH]= 1;
      }
    for (int i=0;i<9;i++)if (ledmH[i]==1)leds[i+3].setRGB( D/lum, E/lum,F/lum );
    }
  //--------------------------------------------------------

  
  FastLED.show();//toute les led qui ont été indiqué comme étant allumé, je les allume

for (int x=0; x < 10000; x++) {     // Wait for 1 second
      delay(1);
      bluetooth();
     Serial.println(N);
    
   }
    

  for(int dot = 0; dot < NUM_LEDS; dot++)leds[dot] = CRGB::Black; //j'indique que toute les leds doivent être éteinte 
  FastLED.show();//je les éteins
  
  
  //-----------------
  for (int i=0;i<=3;i++)leddH[i]=0; //je réinitialise mes listes
  //-------------------
 
  //-----------------
  for (int i=0;i<=9;i++)ledmH[i]=0;
  //-------------------

  //-----------------
  for (int i=0;i<=6;i++)leddM[i]=0;
  //-------------------
  
  //-----------------
  for (int i=0;i<=9;i++) {
    ledmM[i]=0;
  }
  //-------------------
   
  }

void bluetooth()
{
  
  // Read from HC-05 and send it to Arduino Serial Monitor
  if (SerialBTS.available())
  {
    
    char couleur=SerialBTS.read();

    switch (couleur)
    {
      case LEDRdH:
      {

        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        A=float(data.toInt());
    
      
      break;
      }
    case LEDGdH:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        B=float(data.toInt());
      
      break;
      }
    case LEDBdH:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        C=float(data.toInt());
      
      break;
    }
    case LEDRmH:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        D=float(data.toInt());
      
      break;
    }
    case LEDGmH:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        E=float(data.toInt());
      
      break;
    }
    case LEDBmH:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        F=float(data.toInt());
      
      break;
    }
    case LEDRdM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        G=float(data.toInt());
      
      break;
    }
    case LEDGdM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        Serial.print(data.toInt());
        N=float(data.toInt());
      
      break;
    }
    case LEDBdM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        I=float(data.toInt());
      
      break;
    }
    case LEDRmM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        J=float(data.toInt());
      
      break;
    }
    case LEDGmM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        K=float(data.toInt());
      
      break;
    }
    case LEDBmM:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        L=float(data.toInt());
      
      break;
    }
    case hiver:
      {
        char BUFFER[SerialBTS.available()];
        String data="";
        while(SerialBTS.available())
        {
          delay(1);
          data+=char(SerialBTS.read());
        }
        Q=float(data.toInt());
   
      break;
    }
    
    }
  
  }
  
}
