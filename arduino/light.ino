
int get_light_intensity(){
  analogRead(lightsensor_pin);
}

// check if the light has passed the threshold. If so, set global var to true. If not, aset to false
// The number of measures and the interval is set in the klappe-tab

void set_passed_threshold(){
  if(Clock.getSecond() % measure_interval == 0 and second_measured != Clock.getSecond()){ 
    second_measured=Clock.getSecond();
    light_measures[light_measure_counter]=light_intensity;
    light_measure_counter++;
    if(light_measure_counter==number_of_light_measures){
      int sum=0;
      for (int i = 0; i < number_of_light_measures; i++){
        sum+=light_measures[i];
      }
      light_measure_counter=0;
      flattened_light_intensity=sum/number_of_light_measures;
      if(sum>=light_threshold*number_of_light_measures){
        light_threshold_passed=true;
      } else {
        light_threshold_passed=false;
      }
    }
    
     
  }
}
