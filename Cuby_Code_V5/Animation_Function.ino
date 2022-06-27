//---------------------------------------------------------------UPDATE ALL----------------------------------------------------------------------------------

//Update brighness , servos , side color based on the NEXT value
void UPDATE(){
    while(Check_All() == false){
        //Update les servos 1 par un 
        for(uint8_t Servos = 0; Servos < nbPCAServo ; Servos++){
           if( Check_Position_Servos(Servos) == false){
              if (NEXT_POS[Servos] > CURRENT_POS[Servos]){
                 CURRENT_POS[Servos] = CURRENT_POS[Servos] + SERVOS_SPEED[Servos] ;
              }
              else{
                 CURRENT_POS[Servos] = CURRENT_POS[Servos] - SERVOS_SPEED[Servos] ;
            }
            pca.writeMicroseconds(Servos + 4 , AngleToImp(CURRENT_POS[Servos],Servos) );
          }
        }
        
        //Update led brightness
        for(uint8_t i = 0; i < 7 ; i++) {
          //On calcul l'inc
          if(abs(Next_Side_Brightness[i] - Current_Side_Brightness[i]) > Speed_Side[i]){
              if (Next_Side_Brightness[i] > Current_Side_Brightness[i]){
                 Current_Side_Brightness[i] = Current_Side_Brightness[i] + Speed_Side[i] ;
              }
              else{
                 Current_Side_Brightness[i] = Current_Side_Brightness[i] - Speed_Side[i] ;
              }
          }
        }
        
        //Calc the leds color side by side 
        for(uint8_t i = 0; i < 7 ; i++) {
          //On calcul l'inc
          if(abs(Next_Side_Color[i] - Current_Side_Color[i]) > Speed_Side[i]){
              if (Next_Side_Color[i] > Current_Side_Color[i]){
                 Current_Side_Color[i] = Current_Side_Color[i] + Speed_Side[i] ;
              }
              else{
                 Current_Side_Color[i] = Current_Side_Color[i] - Speed_Side[i] ;
              }
          }
        }
        //Apply color
        APPLY_COLOR_SIDE() ;
        FastLED.show();

        //Slow down the loop
        delay(dt); 
    }
    //Desactive l'alim de tout les servos ( evite qu'ils forcent)
    for(uint8_t Servos = 0; Servos < nbPCAServo ; Servos++){
        if(Servos != 6){
          pca.setPin(Servos + 4,0,true);
        }
    }
}

//-------------------------------------------------------Check final state-----------------------------------------------------------------------------------
//Check if we reach the wanted value , if good stop updating
bool Check_All(){
    for(uint8_t Servos = 0; Servos < nbPCAServo ; Servos++){
        int Distance = abs(NEXT_POS[Servos] - CURRENT_POS[Servos]) ;
        if( Distance > SERVOS_SPEED[Servos]){
            return false ;
        }
    }
    for(uint8_t i = 0; i < 7 ; i++) {
        int Distance = abs(Next_Side_Brightness[i] - Current_Side_Brightness[i]) ;
        if(Distance > Speed_Side[i]){
            return false ;
        } 
    }
    for(uint8_t i = 0; i < 6 ; i++) {
        int Distance = abs(Next_Side_Color[i] - Current_Side_Color[i]) ;
        if(Distance > Speed_Side[i]){
            return false ;
        } 
    }
    return true ;
}

//Check if servos in good position
bool Check_Position_Servos(uint8_t Servos){
    if(abs(NEXT_POS[Servos] - CURRENT_POS[Servos]) > SERVOS_SPEED[Servos]){
         return false ;
    }
    return true ;
}

//Apply the emotion
void Apply_Emotion(uint8_t Emotion_Number){
    Emo = Emotion_Number ;
    Emotion(Emo) ;
}
