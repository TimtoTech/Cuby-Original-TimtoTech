//----------------------------------------------------------Initialisation Servos----------------------------------------------------------------------------
//Function to initialise cuby's servos controlled by PCA9685 I2C Module

//Init servos at start
void Init_Servo(){
     Serial.println("Init servos");
     for (uint8_t i = 0; i < nbPCAServo; i++) {
        pca.writeMicroseconds(i + 4, AngleToImp(CURRENT_POS[i],i) ); delay(300);       //set servos to its init position
        if(i + 4 != 6){
          pca.setPin(i + 4,0,true);
        }
        //pca.setPin(i + 4,0,true);                                                      // deactivate pin i ie motor can be mooved
     }
}

//Change the speed or the servo
void SETUP_SPEED(uint8_t ARML, uint8_t ARMR, uint8_t MOUTH , uint8_t EYES , uint8_t BROWL , uint8_t BROWR , uint8_t FLAG ){
    SERVOS_SPEED[0] = ARML ;
    SERVOS_SPEED[1] = ARMR ; 
    SERVOS_SPEED[2] = MOUTH ;
    SERVOS_SPEED[3] = EYES ;
    SERVOS_SPEED[4] = BROWL ;
    SERVOS_SPEED[5] = BROWR ;
    SERVOS_SPEED[6] = FLAG ;
}

//------------------------------------------------------------------------------------------------------------

//Move the flag n time
void Moove_Flag(int n){
    UPDATE() ;
    for(uint8_t i = 0; i < n ; i++){
           NEXT_POS[6] = FLAG_POS[2] ;
           UPDATE() ;
           delay(100);
           NEXT_POS[6] = FLAG_POS[1] ;
           UPDATE() ;
           delay(100);
    }
    NEXT_POS[6] = FLAG_POS[0] ;
    UPDATE() ;
}


//Both arm reset button
void Reset_2_arm() {
    NEXT_POS[0] = ARML_POS[1] ;
    NEXT_POS[1] = ARMR_POS[1] ;
    UPDATE() ;
    delay(100);
    NEXT_POS[0] = ARML_POS[0] ;
    NEXT_POS[1] = ARMR_POS[0] ;
    UPDATE() ;
}

//Reset the button with right hand
void Reset_Right(){
    NEXT_POS[1] = ARMR_POS[1] ;
    UPDATE() ;
    delay(100);
    NEXT_POS[1] = ARMR_POS[0] ;
    UPDATE() ;
}

//Reset the button with left hand
void Reset_Left() {
    NEXT_POS[0] = ARML_POS[1] ;
    UPDATE() ;
    delay(100);
    NEXT_POS[0] = ARML_POS[0] ;
    UPDATE() ;
}
