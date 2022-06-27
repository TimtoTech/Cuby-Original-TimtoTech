




//Nano 328p old bootloader

// Color Memo
// Color  0      50       100       150          200           250
//       Green   Yellow  red    violet bleu     Bleu clair    Vert  


//Licence


//------------------------------------------------------------------SERVOS CONFIG------------------------------------------------------------------------------

//Libraries
#include <Wire.h>                                //https://www.arduino.cc/en/reference/wire
#include <Adafruit_PWMServoDriver.h>             //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#include <FastLED.h>                             //https://github.com/FastLED/FastLED
#define nbPCAServo 7                             // Number of servos
#define NUM_LEDS_STRIP_1 21                      // Nb leds Strip 1
#define NUM_LEDS_STRIP_2 35                      // Nb leds Strip 2

//Declare the pca module
Adafruit_PWMServoDriver pca= Adafruit_PWMServoDriver(0x40);

//------------------------------------------------------------------SERVOS CONFIG------------------------------------------------------------------------------

// Servos Index 
// 4-Left arm | 5-Right arm | 6-Mouth | 7-Eyes | 8-Left eyebrow | 9-Right eyebrow | 10-Flag

//Offset for all the servos ( only positiv number ) , standar offset at 20 , ajust it if needed
const uint8_t OFFSET_ARML = 20 ;                        
const uint8_t OFFSET_ARMR = 20 ;
const uint8_t OFFSET_MOUTH = 20 ;
const uint8_t OFFSET_EYES = 20 ;
const uint8_t OFFSET_BROWL = 20 ;
const uint8_t OFFSET_BROWR = 10 ;
const uint8_t OFFSET_FLAG = 20 ;

//Store the most used angle for each servos
uint8_t ARML_POS [3] = {20+OFFSET_ARML, 87 +OFFSET_ARML, 100+OFFSET_ARML} ;             //Close , reset button , push button
uint8_t ARMR_POS [3] = {130+OFFSET_ARMR, 76+OFFSET_ARMR, 50+OFFSET_ARMR} ;              //Close , reset button , push button
uint8_t MOUTH_POS [3] = {105+OFFSET_MOUTH, 75+OFFSET_MOUTH, 55+OFFSET_MOUTH} ;         //Happy , Sick , Sad
uint8_t EYES_POS [3] = {62+OFFSET_EYES, 30+OFFSET_EYES, 80+OFFSET_EYES} ;               //Mid , left , right
uint8_t BROWL_POS [3] = {25+OFFSET_BROWL, 55+OFFSET_BROWL, 75+OFFSET_BROWL} ;           //Sad , normal , angry
uint8_t BROWR_POS [3] = {115+OFFSET_BROWR, 90+OFFSET_BROWR, 75+OFFSET_BROWR} ;          //Sad , normal , angry
uint8_t FLAG_POS [3] = {30 +OFFSET_FLAG, 140+OFFSET_FLAG, 90+OFFSET_FLAG} ;             //Close , full , half

//Store the curent position of the servos in this order : 
// LEFT ARM, RIGHT ARM , MOUTH , EYES , LEFT EYES BROWN , RIGHT EYE BROWN , FLAG
uint8_t CURRENT_POS [nbPCAServo] = {ARML_POS[0], ARMR_POS[0], MOUTH_POS[0], EYES_POS[0], BROWL_POS[1], BROWR_POS[1], FLAG_POS[0]};      //Current angle of the servo , init 

//Store the next position of the servos in the same order
uint8_t NEXT_POS [nbPCAServo] = {CURRENT_POS[0], CURRENT_POS[1], CURRENT_POS[2], CURRENT_POS[3], CURRENT_POS[4], CURRENT_POS[5], CURRENT_POS[6]}; 

//Store the speed of each servos ( inc for each loop ) 
uint8_t SERVOS_SPEED [nbPCAServo] = {1, 1, 2, 1, 5, 5, 3} ;

//Constante for the servos PWM impulsion to angle ( for the MG90S ) 
const uint16_t MIN_IMP [nbPCAServo] = {500, 500, 500, 500, 500, 500, 500};
const uint16_t MAX_IMP [nbPCAServo] = {2500, 2500, 2500, 2500, 2500, 2500, 2500};
const uint8_t MIN_ANG [nbPCAServo] = {0, 0, 0, 0, 0, 0, 0};
const uint8_t MAX_ANG [nbPCAServo] = {180, 180, 180, 180, 180, 180, 180};

//------------------------------------------------------------------LED CONFIG---------------------------------------------------------------------------------

//Declare strip led
CRGB Strip_1[NUM_LEDS_STRIP_1];
CRGB Strip_2[NUM_LEDS_STRIP_2];

//Data pin for strip led
const uint8_t Pin_Strip_1 = 8 ;
const uint8_t Pin_Strip_2 = 7 ;

//Store the brightness and color of each side in this order  :
// FRONT , BACK , LEFT , RIGHT , TOP  , EYES LEFT , EYES RIGHT 
uint16_t Current_Side_Color [7] = {0,0,0,0,0,0,0} ;
uint16_t Next_Side_Color [7] = {120,120,120,120,120,80,200} ;  
uint8_t Current_Side_Brightness [7] = {100,100,100,100,100,100,100} ;  
uint8_t Next_Side_Brightness [7] = {100,100,100,100,100,100,100} ;  
uint8_t Speed_Side [7] = {1,1,1,1,1,1,1} ; 

//Store the color for the fade animation 
uint8_t Body_Fade_Color = 0 ;

//Store the index of each led side per side
//Exemple : led on the right side got led with index 0 1 2 3 4 5 6 7 8 9 10 11 12 , first number is the size of the array
const uint16_t LED_RIGHT [14] = {14,0,1,2,3,4,5,6,7,8,9,10,11,12} ; 
const uint16_t LED_BACK [9]  = {9,13,14,15,16,17,18,19,20} ;    
const uint16_t LED_LEFT [14]  = {14,21,22,23,24,25,26,27,28,29,30,31,32,33} ;  
const uint16_t LED_TOP [13]   = {13,34,35,36,37,38,39,40,41,42,43,44,45} ;  
const uint16_t LED_FRONT [11] = {11,46,47,48,49,50,51,52,53} ;    
const uint16_t LED_EYES [3]   = {3,54,55} ;   
 
//Next array countain all the side array
const uint16_t* ALL_SIDE [6] = { LED_FRONT,LED_BACK,LED_LEFT,LED_RIGHT,LED_TOP,LED_EYES };

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//Delta time (ms) for slowing the update loop , increasy this value slow the anymation.
uint8_t dt = 0 ; 

//Other Variables
float Time ;        //Store the current time
float Time_0 ;      //Store the time origin
float Waited ;      //Total time waited time-time0

uint16_t RdNumber ;             //Random number chossen for each interaction ( each rd number associated to one animation )
uint8_t Emo ;               //The current emotion 
uint8_t Emotional_State = 0 ;   // not really used yet , it's for a ladder of emotion , the more you play , the more the robot is ennoyed

const uint8_t NozLeftPin = 3 ;  //Pin for the left noze
const uint8_t NozRightPin = 2 ; //Pin for the right noze
const uint8_t TestModePin = 6 ; //Pin for the red button on the pcb

//Store the state of each button
bool NozLeftState ;
bool NozRightState ;
bool TestMode ;

//-----------------------------------------------------------------Setup------------------------------------------------------------------------------------

void setup(){
    //Init Serial USB
    Serial.begin(9600);
    Serial.println("Initialize System");

    //Init the pca module
    pca.begin();
    pca.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

    //Setup LED
    FastLED.addLeds<WS2812B, Pin_Strip_1>(Strip_1, NUM_LEDS_STRIP_1); //Strip 1
    FastLED.addLeds<WS2812B, Pin_Strip_2>(Strip_2, NUM_LEDS_STRIP_2); //Strip 2

    //Init Time
    Time_0 = Min() ;
    Time = Min() ;

    //Init the button 
    pinMode(NozLeftPin, INPUT);     //Pin Noze Left button
    pinMode(NozRightPin, INPUT);    //Pin Noze Right button 
    pinMode(TestModePin, INPUT);    //Pin test button

    //Read State of all the button
    NozLeftState = digitalRead(NozLeftPin);
    NozRightState = digitalRead(NozRightPin)  ;
    TestMode = digitalRead(TestModePin)  ;

    //Random seed generation
    randomSeed(analogRead(0));  

    //Random start emo and color for the fade animation
    Emo = 0 ; //random(0, 11) ;
    Body_Fade_Color = random(0,255); ;

    //Init Servos
    Init_Servo();

    //Start Sequence
    Start_Sequence();
} 

//-------------------------------------------------------------------Main Loop-------------------------------------------------------------------------------
void loop(){
    
    CheckNoze() ;

    //IF test mode 
    if(TestMode == HIGH){
      //If left noze activated -> Servos min position
      if (NozLeftState == HIGH){
        dt = 3 ;
        Serial.println("Test Mode : Left , Min");
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(50,100,150,200,250,190,190) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(1000);
      
      }
      //If right noze activated -> Servos max position
      else if (NozRightState == HIGH){
        dt = 3 ;
        Serial.println("Test Mode : Right , Max");
        NEXT_POS[0] = ARML_POS[1] ;
        NEXT_POS[1] = ARMR_POS[1] ;
        NEXT_POS[2] = MOUTH_POS[1] ;
        NEXT_POS[3] = EYES_POS[1] ;
        NEXT_POS[4] = BROWL_POS[2] ;
        NEXT_POS[5] = BROWR_POS[2] ;
        NEXT_POS[6] = FLAG_POS[2] ;
        NEXT_SIDE_COLOR(50,100,150,200,250,190,190) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(5000);

        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[0] ;
        NEXT_POS[3] = EYES_POS[2] ;
        NEXT_POS[4] = BROWL_POS[0] ;
        NEXT_POS[5] = BROWR_POS[0] ;
        NEXT_POS[6] = FLAG_POS[1] ;
        NEXT_SIDE_COLOR(50,100,150,200,250,190,190) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(5000);

      }
    }

    //if not in factory mode 
    else{
      Veille() ;                //Check is we need to play waiting animation
      Time_Update() ;           //Updated time waited
      CheckNoze() ;             //Check the noze state
      Display() ;               //Display information if debug needed
      Animation() ;             //Play an animation if the noze have been pushed
      Apply_Emotion(Emo) ;      //Play the current emotion
    }
}

//----------------------------------------------------------------Display------------------------------------------------------------------------------------

//Print for debug
void Display(){
  Serial.print(RdNumber) ;
  Serial.print("  |  ") ;
  Serial.print(NozLeftState) ;
  Serial.print("  |  ") ;
  Serial.print(NozRightState) ;
  Serial.print("  |  ") ;
  Serial.print(TestMode) ;
  Serial.print("  |  ") ;
  Serial.print(Waited) ;
  Serial.print("  |  ") ;
  Serial.print(Emotional_State) ;
  Serial.print("  |  ") ;
  Serial.print(Emo) ;
  Serial.println(" ") ;
}
