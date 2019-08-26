


int get_current_minutes(){
  int current_minutes=(Clock.getHour(h12, PM)*60)+Clock.getMinute();
  return current_minutes;
}

int calc_minutes(int hour, int minute){
  int calc_minutes=(hour*60)+minute;
  return calc_minutes;
}
