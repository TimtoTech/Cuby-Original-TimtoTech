//-------------------------------------------------------------------Animations------------------------------------------------------------------------------

void Animation() {
    
    switch (RdNumber) {
      //----------------------------------------------------------------Left side----------------------------------------------
      case 100:
          //Remet le bras
          dt = 20;
          NEXT_POS[0] = ARML_POS[0] + 15 ;
          UPDATE() ;
          delay(200);
          dt = 0;
          NEXT_POS[0] = ARML_POS[0] ;
          UPDATE() ;
          delay(2000);
          NEXT_POS[0] = ARML_POS[1] ;
          UPDATE() ;
          NEXT_POS[0] = ARML_POS[0] ;
          UPDATE() ;
          ++Emotional_State ;
      break;
      case 101:
          dt = 0;
          Reset_Left();
          ++Emotional_State ;
      break;
      case 102:
          dt = 5;
          NEXT_POS[4] = BROWL_POS[2] ;
          NEXT_POS[5] = BROWR_POS[2] ;
          NEXT_POS[2] = MOUTH_POS[0] ;
          NEXT_POS[3] = EYES_POS[2] ;
          UPDATE() ;
          delay(300);
          Reset_Left();
      break;
      //Sourcil bordel
      case 103:
          dt = 3 ;
          for(int i = 0; i < 20 ; i++) {
            NEXT_POS[4] = random(0,180); ;
            NEXT_POS[5] = random(0,180); ;
            NEXT_POS[3] = random(EYES_POS[1],EYES_POS[2]); ;
            uint8_t EYE_COLOR = random(0,255);
            UPDATE() ;
            SET_SIDE_COLOR(Current_Side_Color[0],Current_Side_Color[1],Current_Side_Color[2],Current_Side_Color[3],Current_Side_Color[4],EYE_COLOR,EYE_COLOR) ;
            delay(random(30,300));
          }
          dt = 5 ;
          Reset_2_arm() ;
      break;
      case 104:
          //Transformation mechant- BUG
          dt = 4 ;
          NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
          UPDATE() ;
          delay(1000);
          SET_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
          SET_SIDE_COLOR(Current_Side_Color[0],Current_Side_Color[1],Current_Side_Color[2],Current_Side_Color[3],Current_Side_Color[4],100,100) ;
          UPDATE() ;
          for(int i = 0; i < 50 ; i++) {
             SET_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
             delay(50-i);
             uint8_t Bright = round(225/50*i + 25) ;
             SET_SIDE_BRIGHTNESS(0,0,0,0,0,Bright,Bright) ;
             delay(50-i);
          }
          Apply_Emotion(3) ;
          dt = 5 ;
          for(int i = 0; i < 2 ; i++){
            NEXT_POS[0] = ARML_POS[1]-35 ;
            NEXT_POS[1] = ARMR_POS[1]+35
            ;
            UPDATE() ;
            delay(100);
            NEXT_POS[0] = ARML_POS[0] ;
            NEXT_POS[1] = ARMR_POS[0] ;
            UPDATE() ;
            delay(300);
          }
          delay(1000);
          dt = 5 ;
          Reset_Left() ;

      break;
      case 105:
          //FORFEIT
          Apply_Emotion(10);
          NEXT_POS[2] = MOUTH_POS[2] ;
          UPDATE() ;
          Moove_Flag(5) ;
          dt = 20 ;
          Apply_Emotion(5);
          Reset_Left() ;
      break;
      case 106:
          //Weirdo
          dt = 1 ;
          NEXT_POS[4] = BROWL_POS[2] + 10 ;
          NEXT_POS[3] = EYES_POS[0] ;
          UPDATE() ;
          delay(1000);
          NEXT_POS[3] = EYES_POS[1] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[2] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[0] ;
          UPDATE() ;
          dt = 7 ;
          Reset_Left() ;
      break;
      case 107:
          //Blink red , then die 
          dt = 10 ;
          delay(1000);
          NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
          UPDATE() ;
          delay(100);
          SET_SIDE_COLOR(100,100,100,100,100,190,190) ;
          dt = 0 ;
          SETUP_SPEED_SIDE(4,4,4,4,4,4,4) ;
          for(int i = 0; i < 3 ; i++) {
             NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
             UPDATE() ;
             delay(10);
             NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
             UPDATE() ;
             delay(10);
             NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
             UPDATE() ;
             delay(10);
             NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
             UPDATE() ;
             delay(500);
          }
          dt = 5 ;
          SETUP_SPEED_SIDE(1,1,1,1,1,1,1) ;
          NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
          UPDATE() ;
          delay(1000);
          NEXT_POS[2] = MOUTH_POS[2] ;
          delay(300) ;
          dt = 50 ;
          NEXT_POS[2] = MOUTH_POS[1] ;
          NEXT_POS[4] = BROWL_POS[2] ;
          NEXT_POS[5] = BROWR_POS[2] ;
          NEXT_POS[6] = FLAG_POS[1] ;
          UPDATE() ;
          delay(300) ;
          Reset_Left() ;
          delay(300) ;
          Apply_Emotion(2);
      break;
      case 108:
          dt = 1 ;
          SET_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
          for(int i = 0; i < 25 ; i++) {
             uint8_t Color_Side_Rd = random(0, 254);
             SET_SIDE_COLOR(Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,254 - Color_Side_Rd,254 - Color_Side_Rd) ;
             delay(550 - i * 20);
          }
          for(int i = 0; i < 75 ; i++) {
             uint8_t Color_Side_Rd = random(0, 254);
             SET_SIDE_COLOR(Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,Color_Side_Rd,254 - Color_Side_Rd,254 - Color_Side_Rd) ;
             delay(50);
          }
          SET_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
          SET_SIDE_COLOR(0,0,0,0,0,190,190) ;
          delay(1000);
          dt = 10 ;
          NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
          UPDATE() ;
          Reset_Left() ;
          delay(500);
          Apply_Emotion(random(0, 10));
      break;
      case 109:
          dt = 1 ;
          NEXT_POS[4] = BROWL_POS[2] ;
          NEXT_POS[5] = BROWR_POS[2] ;
          NEXT_POS[6] = FLAG_POS[1] ;
          NEXT_POS[2] = MOUTH_POS[1] ;
          UPDATE() ;
          delay(100);
          SET_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
          for(int i = 0; i < 50 ; i++) {
             uint8_t Color_Side_Rd = random(0, 254);
             SET_SIDE_COLOR(10,10,10,10,10,Color_Side_Rd,Color_Side_Rd) ;
             delay(60);
          }
          Apply_Emotion(9);
          Reset_2_arm() ;
      break;
      case 110:
          //Oeil qui bug clein d'oeil
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 111:
          //Mouvement bras chelou 
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 112:
          //Feinte de remise nez
          dt = 1 ;
          Reset_2_arm() ;
          //dt = 200 ;
          //NEXT_POS[0] = ARML_POS[0] ;
          //NEXT_POS[1] = ARMR_POS[0] ;
          //NEXT_POS[2] = MOUTH_POS[2] ;
          //NEXT_POS[3] = EYES_POS[1] ;
          //NEXT_POS[4] = BROWL_POS[1] ;
          //NEXT_POS[5] = BROWR_POS[1] ;
          //NEXT_POS[6] = FLAG_POS[0] ;
          //SET_SIDE_COLOR(190,190,190,190,190,190,190) ; 
          //SET_SIDE_BRIGHTNESS(255,255,255,255,255,255,255) ;
          //NEXT_SIDE_COLOR(0,0,0,0,0,0,0) ;
          //NEXT_SIDE_BRIGHTNESS(10,10,10,10,10,10,10) ;
          //UPDATE() ;
          //delay(10000);
      break;
      case 113:
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 114:
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 115:
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 116:
          dt = 1 ;
          Reset_Left() ;
      break;
      case 117:
          dt = 1 ;
          Reset_2_arm() ;
      break;
      case 118:
          NEXT_POS[2] = MOUTH_POS[0] ;
          NEXT_SIDE_COLOR(190,190,190,190,190,190,190) ;
          UPDATE() ;
          while(NozLeftState != 0 or NozRightState != 0){
              NEXT_POS[6] = FLAG_POS[1] ;
              UPDATE() ;
              delay(200);
              NEXT_POS[6] = FLAG_POS[2] ;
              UPDATE() ;
              delay(200); 
              NozLeftState = digitalRead(NozLeftPin) ;
              NozRightState = digitalRead(NozRightPin)  ;
          }
          NEXT_POS[6] = FLAG_POS[0] ;
          UPDATE() ;
          delay(200); 
      break;
      case 119:
          //Ping pong
          dt = 0 ;
          SETUP_SPEED(1, 1, 1, 4, 4, 4, 3) ;
          NEXT_POS[4] = 180 - 70 ;
          NEXT_POS[5] = 0 + 70 ;
          NEXT_POS[3] = EYES_POS[1] ;
          UPDATE() ;
          delay(200);
          for(int i = 0; i < 3 ; i++){
              NEXT_POS[4] = 180 ;
              NEXT_POS[3] = EYES_POS[2] ;
              UPDATE() ;
              delay(70);
              uint8_t EYE_COLOR = random(0,255);
              SET_SIDE_COLOR(Current_Side_Color[0],Current_Side_Color[1],Current_Side_Color[2],Current_Side_Color[3],Current_Side_Color[4],EYE_COLOR,EYE_COLOR) ;
              NEXT_POS[4] = 180 - 70 ;
              UPDATE() ;
              delay(70);

              NEXT_POS[5] = 0 ;
              NEXT_POS[3] = EYES_POS[1] ;
              UPDATE() ;
              delay(70);
              EYE_COLOR = random(0,255);
              SET_SIDE_COLOR(Current_Side_Color[0],Current_Side_Color[1],Current_Side_Color[2],Current_Side_Color[3],Current_Side_Color[4],EYE_COLOR,EYE_COLOR) ;
              NEXT_POS[5] = 0 + 70 ;
              UPDATE() ;
              delay(70);
          }
          SETUP_SPEED(1, 1, 1, 2, 2, 2, 3) ;
          dt = 1 ;
          Reset_Left() ;
          delay(100);
      break;
      case 120:
          dt = 20 ;
          NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,0,0) ;
          UPDATE() ;
          dt = 0 ;
          SETUP_SPEED(10, 10, 2, 1, 5, 5, 3) ;
          Reset_Left() ;
          SETUP_SPEED(1, 1, 2, 1, 5, 5, 3) ;
          delay(1000);
      break;

      // HELP 

      //dt = 200 ;
      //NEXT_POS[0] = ARML_POS[0] ;
      //NEXT_POS[1] = ARMR_POS[0] ;
      //NEXT_POS[2] = MOUTH_POS[2] ;
      //NEXT_POS[3] = EYES_POS[1] ;
      //NEXT_POS[4] = BROWL_POS[1] ;
      //NEXT_POS[5] = BROWR_POS[1] ;
      //NEXT_POS[6] = FLAG_POS[0] ;
      //SET_SIDE_COLOR(190,190,190,190,190,190,190) ; 
      //SET_SIDE_BRIGHTNESS(255,255,255,255,255,255,255) ;
      //NEXT_SIDE_COLOR(0,0,0,0,0,0,0) ;
      //NEXT_SIDE_BRIGHTNESS(10,10,10,10,10,10,10) ;
      //UPDATE() ;
      //delay(10000);

          
      //--------------------------------------------------------Right Side--------------------------------------------------------
      case 200:
          Reset_2_arm() ;
      break;
      case 201:
          Reset_2_arm() ;
      break;
      case 202:
          Reset_2_arm() ;
      break;
      case 203:
          Reset_2_arm() ;
      break;
      case 204:
          Reset_2_arm();
      break;
      case 205:
          Reset_2_arm() ;
      break;
      case 206:
          Reset_2_arm() ;
      break;
      case 207:
          Reset_2_arm() ;
      break;
      case 208:
          Reset_2_arm() ;
      break;
      case 209: 
          Reset_2_arm() ;
      break;
      case 210:
          Reset_2_arm() ;
      break;
      case 211:
          Reset_2_arm() ;
      break;
      case 212:
          Reset_2_arm() ;
      break;
      case 213:
          Reset_Right() ;
      break;
      case 214:
          Reset_Right() ;
      break;
      case 215:
          Reset_Right() ;
      break;
      case 216:
          Reset_Right() ;
      break;
      case 217:
          Reset_Right() ;
      break;
      case 218:
          Reset_Right() ;
      break;
      case 219:
          Reset_Right() ;
      break;
      case 220:
          Reset_Right() ;
      break;
      

 //-------------------------------------------------------Veille----------------------------------------------
      case 300:
          dt = 15 ;
          SETUP_SPEED(1, 1, 2, 1, 5, 5, 3) ;
          NEXT_POS[2] = MOUTH_POS[0] ;
          NEXT_POS[3] = EYES_POS[1] ;
          NEXT_POS[4] = BROWL_POS[0] ;
          NEXT_POS[5] = BROWR_POS[2] ;
          UPDATE() ;
          delay(2000);
          NEXT_POS[3] = EYES_POS[2] ;
          NEXT_POS[4] = BROWL_POS[2] ;
          NEXT_POS[5] = BROWR_POS[0] ;
          UPDATE() ;
          delay(2000);
      break;
      case 301:
          dt = 10 ;
          SETUP_SPEED(1, 1, 2, 1, 5, 5, 3) ;
          NEXT_POS[3] = EYES_POS[1] ;
          delay(100);
          NEXT_POS[3] = EYES_POS[2] ;
          NEXT_POS[0] = ARML_POS[2] ;
          UPDATE() ;
          delay(100);
          NEXT_POS[0] = ARML_POS[0] ;
          NEXT_POS[3] = EYES_POS[1] ;
          UPDATE() ;
          delay(1000);
          NEXT_POS[0] = ARML_POS[1] ;
          NEXT_POS[1] = ARMR_POS[1] ;
          UPDATE() ;
          delay(100);
          NEXT_POS[0] = ARML_POS[0] ;
          NEXT_POS[1] = ARMR_POS[0] ;
          UPDATE() ;
      break;
      case 302:
          dt = 10 ;
          SETUP_SPEED(1, 1, 2, 1, 5, 5, 3) ;
          NEXT_POS[3] = EYES_POS[0] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[2] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[1] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[2] ;
          UPDATE() ;
          delay(500);
          NEXT_POS[3] = EYES_POS[1] ;
          UPDATE() ;
      break;
      case 303:
          Emo = random(0, 10) ;
          delay(1000);
      break;
      case 304:
          dt = 1 ;
          Moove_Flag(8) ;
      break;
      case 305:
          dt = 30 ;
          SETUP_SPEED(1, 1, 2, 1, 5, 5, 3) ;
          NEXT_POS[1] = ARMR_POS[1] + 30 ;
          UPDATE() ;
          delay(1000);
          NEXT_SIDE_BRIGHTNESS(5,5,5,5,5,5,5) ;
          UPDATE() ;
          delay(1000);
          dt = 1 ;
          NEXT_POS[1] = ARMR_POS[2] ;
          UPDATE() ;
          delay(100);
          NEXT_POS[1] = ARMR_POS[0] ;
          UPDATE() ;
          delay(2000);
          NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
          UPDATE() ;
          delay(100);
      break;
  } 
  RdNumber = 0 ;
}

//----------------------------------------------Humeur--------------------------------------------------------

//NEXT_POS[0] = ARML_POS[0] ;
//NEXT_POS[1] = ARMR_POS[0] ;
//NEXT_POS[2] = MOUTH_POS[2] ;
//NEXT_POS[3] = EYES_POS[1] ;
//NEXT_POS[4] = BROWL_POS[1] ;
//NEXT_POS[5] = BROWR_POS[1] ;
//NEXT_POS[6] = FLAG_POS[0] ;

//SET_SIDE_COLOR(190,190,190,190,190,190,190) ; 
//SET_SIDE_BRIGHTNESS(255,255,255,255,255,255,255) ;
        
//NEXT_SIDE_COLOR(0,0,0,0,0,0,0) ;
//NEXT_SIDE_BRIGHTNESS(10,10,10,10,10,10,10) ;


void Emotion(int n){
  dt = 0 ;
  //Basic
  if( n == 0 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(190,190,190,190,190,190,190) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //Sick
  if( n == 1 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[1] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[2] ;
        NEXT_POS[5] = BROWR_POS[2] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(5,5,5,5,5,200,200) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //Sad
  if( n == 2 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[0] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[2] ;
        NEXT_POS[5] = BROWR_POS[2] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(170,170,170,170,170,200,200) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //Angry
  if( n == 3 ){
        dt = 0 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[0] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[0] ;
        NEXT_POS[5] = BROWR_POS[0] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(100,100,100,100,100,100,100) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //Diabolic
  if( n == 4 ){
        dt = 0 ;
        NEXT_POS[0] = ARML_POS[0] + 20 ;
        NEXT_POS[1] = ARMR_POS[0] - 20 ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[0] ;
        NEXT_POS[5] = BROWR_POS[0] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(155,155,155,155,155,145,145) ; 
        NEXT_SIDE_BRIGHTNESS(255,255,255,255,255,255,255) ;
        UPDATE() ;
        delay(100);
  }
  //love 
  if( n == 5 ){
        dt = 0 ;
        NEXT_POS[0] = ARML_POS[0] + 20 ;
        NEXT_POS[1] = ARMR_POS[0] - 20 ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[2] ;
        NEXT_POS[4] = BROWL_POS[2] ;
        NEXT_POS[5] = BROWR_POS[2] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(110,110,110,110,110,110,110) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //Pumpkin
  if( n == 6 ){
        dt = 0 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[1] ;
        NEXT_POS[3] = EYES_POS[2] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[2] ;
        NEXT_SIDE_COLOR(87,87,87,87,87,50,50) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //cold
  if( n == 7 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[1] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[0] ;
        NEXT_POS[5] = BROWR_POS[0] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(165,165,165,165,165,180,180) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //colorfull
  if( n == 8 ){
        dt = 20 ;
        Body_Fade_Color = (Body_Fade_Color%254) + 1 ;
        NEXT_SIDE_COLOR(Body_Fade_Color,Body_Fade_Color,Body_Fade_Color,Body_Fade_Color,Body_Fade_Color,190,190);
        UPDATE() ;
        dt = 10 ;
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
        
  }
  //Colorfull 2
  if( n == 9 ){
        dt = 20 ; 
        NEXT_SIDE_COLOR(random(0, 254),random(0, 254),random(0, 254),random(0, 254),random(0, 254),190,190) ; 
        NEXT_SIDE_BRIGHTNESS(254,254,254,254,254,254,254) ;
        UPDATE() ;
  }
  //White 
  if( n == 10 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(0,0,0,0,0,190,190) ; 
        NEXT_SIDE_BRIGHTNESS(0,0,0,0,0,254,254) ;
        UPDATE() ;
        delay(100);
  }
  //French
  if( n == 11 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(0,0,178,100,0,100,178) ; 
        NEXT_SIDE_BRIGHTNESS(0,0,254,254,0,254,254) ;
        UPDATE() ;
        delay(100);
  }
  if( n == 12 ){
        dt = 3 ;
        NEXT_POS[0] = ARML_POS[0] ;
        NEXT_POS[1] = ARMR_POS[0] ;
        NEXT_POS[2] = MOUTH_POS[2] ;
        NEXT_POS[3] = EYES_POS[0] ;
        NEXT_POS[4] = BROWL_POS[1] ;
        NEXT_POS[5] = BROWR_POS[1] ;
        NEXT_POS[6] = FLAG_POS[0] ;
        NEXT_SIDE_COLOR(0,0,178,50,0,50,178) ; 
        NEXT_SIDE_BRIGHTNESS(0,0,254,254,0,254,254) ;
        UPDATE() ;
        delay(100);
  }
}
