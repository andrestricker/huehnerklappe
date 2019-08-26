/*
DS3231_test.pde
Eric Ayars
4/11

Test/demo of read routines for a DS3231 RTC.

Turn on the serial monitor after loading this to check if things are
working as they should.

*/

// Function Prototypes:
void set_display(String line1, String line2="");

// Values for opening/closing the door - configure only this... 
int hours_open=07;
int minutes_open=30;

int hours_close=15;
int minutes_close=0;

int light_threshold=3;


#include <DS3231.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <EEPROM.h>



// DS3231 RTC
DS3231 Clock;

bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;


// SSD1306 OLED
#define I2C_ADDRESS 0x3C
#define RST_PIN -1
SSD1306AsciiWire oled;


// Buttons
int btn_up_pin = 4;
int btn_down_pin = 5;
int btn_ok_pin = 8;
int btn_back_pin = 9;


// Switches (Door)
int sw_top = 6;
int sw_btm = 7; 


// Motor
int motor_pin1 = 2;
int motor_pin2 = 3;


// Light sensor
int lightsensor_pin=A0;
int light_intensity;                                 // Container for the currently measured light intensity
int flattened_light_intensity;
bool light_threshold_passed=false;                   // flag if the threshold has been passed after the n measures
int number_of_light_measures=3;                      // number of measures
int measure_interval=5;                              // measuere every n seconds
int light_measures[3];
int second_measured;
int light_measure_counter=0;


// Idle Display variables
char* idle_display_content="brightness";              // brightness or temperature
String buf_line1;
String buf_line2;
int display_delay=1000;                               // delay after each interaction


// Door states
bool door_is_up=false;
bool door_is_down=false;


// Operating states (start in auto-state)
bool is_auto_state=true;




void loop() {
  light_intensity=get_light_intensity();
  
  //idle display
  if(idle_display_content=="brightness"){
    set_display("Brightness",String(flattened_light_intensity));
  } 
  
  else if(idle_display_content=="temperature"){
    set_display("Temperature",String(get_temperature()));
  }
  
  
  //toggle the auto state on the green button. 
  if(buttonstate(btn_ok_pin)){
    is_auto_state=!is_auto_state;
    if(is_auto_state){
      set_display("Mode","Auto");
      delay(display_delay);
    } else {
      set_display("Mode","Manual");
      delay(display_delay);
    }
  }



//auto mode - look at time/brightness to move the doors
  if(is_auto_state){  
    set_passed_threshold();
      
    if(door_should_be_open() and door_is_down){
      door_up(); 
    }

    if(!door_should_be_open() and door_is_up){
      door_down(); 
    }


// manual mode - use the buttons
  } else {  
    if(buttonstate(btn_up_pin)){
      door_up();
    }
    
    if(buttonstate(btn_down_pin)){
      door_down();
    }
  }

  
  delay(200);
}
