void setup() {
  Serial.begin(9600);
  Serial.println("Starting Setup");

  
  // set pin modes
  Serial.println("Pinmodes");
  pinMode(btn_up_pin,INPUT_PULLUP);
  pinMode(btn_down_pin,INPUT_PULLUP);
  
  pinMode(btn_ok_pin,INPUT_PULLUP);
  pinMode(btn_back_pin,INPUT_PULLUP);
  
  pinMode(sw_top,INPUT_PULLUP);
  pinMode(sw_btm,INPUT_PULLUP);

  pinMode(motor_pin1,OUTPUT);
  pinMode(motor_pin2,OUTPUT);

  
  // Start the I2C interface
  Serial.println("I2C");
  Wire.begin();
  Wire.setClock(400000L);


  // Start the the OLED
  Serial.println("OLED");
  #if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
  #else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  #endif // RST_PIN >= 0
  oled.setFont(Arial14);

  // Use true, normal mode, since default for Adafruit display is remap mode.
  oled.displayRemap(true);
  oled.clear();


  // lower door as a start and greet whoever is there.
  set_display("Hello","Ladies");
  delay(3000); 
  door_down();
  
  Serial.println("End of Setup");
}
