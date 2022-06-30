//----------------------------------------------------------------Annexes------------------------------------------------------------------------------------
//Update time
void Time_Update(){
    Time = Min() ;
    Waited = Time - Time_0 ;
}

//----------------------------------------------------------Convert Angle->Impul-----------------------------------------------------------------------------

//Function angle to impulson usualy (0-180° to 400-2400us)
uint16_t AngleToImp(double x,uint8_t i){
     float imp=(x - MIN_ANG[i]) * (MAX_IMP[i]-MIN_IMP[i]) / (MAX_ANG[i]-MIN_ANG[i]) + MIN_IMP[i];
     imp=max(imp,MIN_IMP[i]);
     imp=min(imp,MAX_IMP[i]);
     return imp;
}

//-----------------------------------------------------------------Calcul time-------------------------------------------------------------------------------

//Update time
float Min() {
  float Temps ;
  float NbRollOver = 0;
  float MinDebordement = 71582;
  float LastMin = 0 ;
  float CurrentMin = ((millis())*0.001)/60;
  
  if (CurrentMin < LastMin) {
     NbRollOver += 1;
  }
  LastMin = CurrentMin ;
  Temps = NbRollOver*MinDebordement+CurrentMin ;

  return Temps ;
}

//-------------------------------------------------------Check Noze + Generate Rd Number---------------------------------------------------------------------

//Generate random waiting fuction every 30 sec
void Veille() {
  if(0.50 < Waited - floor(Waited) and Waited - floor(Waited ) < 0.52 and Waited < 5){
    RdNumber = random(300, 305);
  }
}

//Update noze state and generate random number for the animation and update the Time reference
void CheckNoze() {
  NozLeftState = digitalRead(NozLeftPin) ;
  NozRightState = digitalRead(NozRightPin)  ;
  TestMode = digitalRead(TestModePin)  ;
  
  if (NozLeftState == HIGH){
      RdNumber = random(100, 131) ;
      Time_0 = Min() ;
    }
  else if (NozRightState == HIGH){
      RdNumber = random(200, 231) ;
      Time_0 = Min() ;
    }
}

//Check if left button trigerer
bool CheckLeft() {
  NozLeftState = digitalRead(NozLeftPin) ;
  if (NozLeftState == HIGH){
        return true ;
    }
  return false ;
}

//Check if right button trigerer
bool CheckRight() {
  NozRightState = digitalRead(NozRightPin)  ;
  if (NozRightState == HIGH){
        return true ;
    }
  return false ;
}
