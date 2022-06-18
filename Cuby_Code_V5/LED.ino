//----------------------------------------------------------------LED COLOR----------------------------------------------------------------------------------

//Update NEXT_SIDE_COLOR ARRAY
void NEXT_SIDE_COLOR(uint16_t FRONT, uint16_t BACK , uint16_t LEFT , uint16_t RIGHT , uint16_t TOP , uint16_t EYES_LEFT , uint16_t EYES_RIGHT ){
    Next_Side_Color[0] = FRONT ;
    Next_Side_Color[1] = BACK ; 
    Next_Side_Color[2] = LEFT ;
    Next_Side_Color[3] = RIGHT ;
    Next_Side_Color[4] = TOP ;
    Next_Side_Color[5] = EYES_LEFT ;
    Next_Side_Color[6] = EYES_RIGHT ;
}
//Update SET_SIDE_COLOR ARRAY and instant appply the color
void SET_SIDE_COLOR(uint16_t FRONT, uint16_t BACK , uint16_t LEFT , uint16_t RIGHT , uint16_t TOP , uint16_t EYES_LEFT , uint16_t EYES_RIGHT ){
    NEXT_SIDE_COLOR( FRONT,  BACK ,  LEFT ,  RIGHT ,  TOP ,  EYES_LEFT , EYES_RIGHT);
    Current_Side_Color[0] = FRONT ;
    Current_Side_Color[1] = BACK ; 
    Current_Side_Color[2] = LEFT ;
    Current_Side_Color[3] = RIGHT ;
    Current_Side_Color[4] = TOP ;
    Current_Side_Color[5] = EYES_LEFT ;
    Current_Side_Color[6] = EYES_RIGHT ;
    APPLY_COLOR_SIDE();
    FastLED.show();
}

//--------------------------------------------------BRIGHTNESS-----------------------------------------------------------

//Update NEXT_SIDE_BRIGHTNESS ARRAY
void NEXT_SIDE_BRIGHTNESS(uint8_t FRONT, uint8_t BACK , uint8_t LEFT , uint8_t RIGHT , uint8_t TOP, uint8_t EYES_LEFT , uint8_t EYES_RIGHT ){
    Next_Side_Brightness[0] = FRONT ;
    Next_Side_Brightness[1] = BACK ; 
    Next_Side_Brightness[2] = LEFT ;
    Next_Side_Brightness[3] = RIGHT ;
    Next_Side_Brightness[4] = TOP ;
    Next_Side_Brightness[5] = EYES_LEFT ;
    Next_Side_Brightness[6] = EYES_RIGHT ;
}

//Update SET_SIDE_BRIGHTNESS ARRAY and instant update the brightness
void SET_SIDE_BRIGHTNESS(uint8_t FRONT, uint8_t BACK , uint8_t LEFT , uint8_t RIGHT , uint8_t TOP , uint8_t EYES_LEFT , uint8_t EYES_RIGHT ){
    NEXT_SIDE_BRIGHTNESS( FRONT,  BACK ,  LEFT ,  RIGHT ,  TOP ,  EYES_LEFT , EYES_RIGHT);
    Current_Side_Brightness[0] = FRONT ;
    Current_Side_Brightness[1] = BACK ; 
    Current_Side_Brightness[2] = LEFT ;
    Current_Side_Brightness[3] = RIGHT ;
    Current_Side_Brightness[4] = TOP ;
    Current_Side_Brightness[5] = EYES_LEFT ;
    Current_Side_Brightness[6] = EYES_RIGHT ;
    APPLY_COLOR_SIDE();
    FastLED.show();
}

//---------------------------------------------------------------APPLY CHANGE-----------------------------------------------------------------------------

//Update the color of each led based on the ALL_SIDE array 
void APPLY_COLOR_SIDE(){
  //Parcours les SIDE
  for (uint8_t SIDE_INDEX = 0; SIDE_INDEX < 5; ++SIDE_INDEX) {
    uint8_t NB_LEDS = ALL_SIDE[SIDE_INDEX][0];
    for (uint8_t Index = 1; Index < NB_LEDS; ++Index) {
      uint8_t LED_NUM = ALL_SIDE[SIDE_INDEX][Index];
      if ( LED_NUM >= NUM_LEDS_STRIP_1 ) {
          LED_NUM = LED_NUM - NUM_LEDS_STRIP_1 ;
          Strip_2[LED_NUM] = CHSV(Current_Side_Color[SIDE_INDEX], 255, Current_Side_Brightness[SIDE_INDEX]);
      }
      else {
         Strip_1[LED_NUM] = CHSV(Current_Side_Color[SIDE_INDEX], 255, Current_Side_Brightness[SIDE_INDEX]);
      }
    }
  }
  //If brihgness under low level , cut off the brighness 
  if(Current_Side_Brightness[5]<5 and Next_Side_Brightness[5]<5){
      Current_Side_Brightness[5] = 0 ;
  }
  if(Current_Side_Brightness[6]<5 and Next_Side_Brightness[6]<5){
      Current_Side_Brightness[6] = 0 ;
  }
  //Update eyes color
  Strip_2[LED_EYES[1] - NUM_LEDS_STRIP_1] = CHSV(Current_Side_Color[5],255, Current_Side_Brightness[5]);
  Strip_2[LED_EYES[2] - NUM_LEDS_STRIP_1] = CHSV(Current_Side_Color[6],255, Current_Side_Brightness[6]);
}

//------------------------------------------------Starting------------------------------------------------------

//Start sequence 
//Start by cutting of brighness and color 
//Then update eyes  colors slowly
void Start_Sequence(){
    Serial.println("Starting sequence");
    dt = 0 ;
    //Turn off leds
    SET_SIDE_COLOR(0,0,0,0,0,0,0) ; 
    SET_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
    UPDATE() ;
    delay(100) ;
    //Color eyes
    dt = 5 ;
    SET_SIDE_COLOR(0,0,0,0,0,190,190) ;  
    NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,255,255) ;
    UPDATE() ; 
    dt = 30 ;
}

//The test function triggered with the red button on PCB
void TestAnimation(){
    Serial.println("Testing Cuby");
    dt = 10 ;
    SET_SIDE_COLOR(50,100,150,180,250,180,180) ; 
    SET_SIDE_BRIGHTNESS(255,255,255,255,255,255,255) ;

    NEXT_POS[6] = FLAG_POS[0] ;
    NEXT_POS[0] = ARML_POS[0] ;
    NEXT_POS[1] = ARMR_POS[0] ;
    NEXT_POS[2] = MOUTH_POS[0] ;
    NEXT_POS[3] = EYES_POS[0] ;
    NEXT_POS[4] = BROWL_POS[1] ;
    NEXT_POS[5] = BROWR_POS[1] ;
    NEXT_POS[6] = FLAG_POS[0] ;
    UPDATE() ;
    delay(3000);

    dt = 5 ;
    NEXT_POS[0] = ARML_POS[1] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[0] = ARML_POS[0] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[0] = ARML_POS[2] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[0] = ARML_POS[0] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[1] = ARMR_POS[1] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[1] = ARMR_POS[0] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[1] = ARMR_POS[2] ;
    UPDATE() ;
    delay(1000);

    NEXT_POS[1] = ARMR_POS[0] ;
    UPDATE() ;
    delay(1000);
    

    NEXT_POS[6] = FLAG_POS[1] ;
    NEXT_POS[3] = EYES_POS[1] ;
    NEXT_POS[2] = MOUTH_POS[1] ;
    NEXT_POS[4] = BROWL_POS[0] ;
    NEXT_POS[5] = BROWR_POS[0] ;
    UPDATE() ;
    delay(1000);
    NEXT_POS[6] = FLAG_POS[2] ;
    NEXT_POS[3] = EYES_POS[2] ;
    NEXT_POS[2] = MOUTH_POS[2] ;
    NEXT_POS[4] = BROWL_POS[2] ;
    NEXT_POS[5] = BROWR_POS[2] ;
    UPDATE() ;
    delay(1000);
}
    
