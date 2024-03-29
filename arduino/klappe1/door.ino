
bool is_top(){
  return buttonstate(sw_top);
}

bool is_bottom(){
  return buttonstate(sw_btm);
}

void door_stop(){
  set_display("Stopping door");
  digitalWrite(motor_pin2, LOW);
  digitalWrite(motor_pin1, LOW);
  
}

void door_up(){
  if(is_top()){
    door_is_down=false;
    door_is_up=true;
    return;
  }
  digitalWrite(motor_pin1, HIGH);
  digitalWrite(motor_pin2, LOW);
  set_display("Moving up");
  while(!is_top()){
    if(buttonstate(btn_back_pin)){
      door_stop();
      delay(display_delay);
      set_auto_state(false);
      return;
    }
    delay(50);
  }
  door_stop();
  door_is_down=false;
  door_is_up=true;
  delay(display_delay);
  oled.clear();

}

void door_down(){
  if(is_bottom()){
    door_is_down=true;
    door_is_up=false;
    return;
  }
  digitalWrite(motor_pin2, HIGH);
  digitalWrite(motor_pin1, LOW);
  set_display("Moving down");
  while(!is_bottom()){
    if(buttonstate(btn_back_pin)){
      door_stop();
      delay(display_delay);
      set_auto_state(false);
      return;
    }
    delay(50);
  }
  door_stop();
  door_is_down=true;
  door_is_up=false;
  delay(display_delay);
  oled.clear();

}

bool door_should_be_open(){
  
  int opening_minutes=calc_minutes(hours_open, minutes_open);
  int closing_minutes=calc_minutes(hours_close, minutes_close);
  
  if((opening_minutes<=get_current_minutes() and top_light_threshold_passed) and (closing_minutes>=get_current_minutes() or bottom_light_threshold_passed)){
    return true;
  }
  return false;
}

void set_auto_state(bool state){
  is_auto_state=state;
  if(state){
      set_display("Mode","Auto");
      delay(display_delay);
    } else {
      set_display("Mode","Manual");
      delay(display_delay);
    }
}
