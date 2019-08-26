

// returns the state of the buttons
bool buttonstate(int buttonpin){
  int buttonState = digitalRead(buttonpin);
 
  if (buttonState == HIGH) {
    
    return false;
  } else {
    
    return true;
  }
}
