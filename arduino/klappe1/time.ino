int get_current_minutes(){
  int current_minutes=(Clock.getHour(h12, PM)*60)+Clock.getMinute();
  return current_minutes;
}

int calc_minutes(int hour, int minute){
  int calc_minutes=(hour*60)+minute;
  return calc_minutes;
}

String get_date_string(){
  int clock_day=Clock.getDate();
  int clock_month=Clock.getMonth(Century);
  String day_string=pad_two(clock_day);  
  String month_string=pad_two(clock_month);
     
  return day_string+date_delimiter+month_string+date_delimiter+"20"+String(Clock.getYear());
}

String get_time_string(){
  int clock_hour=Clock.getHour(h12, PM);
  int clock_minute=Clock.getMinute();
  int clock_second=Clock.getSecond();
  String hour_string=pad_two(clock_hour);
  String minute_string=pad_two(clock_minute);
  String second_string=pad_two(clock_second);

  return hour_string+time_delimiter+minute_string+time_delimiter+second_string;
  
  
}

String pad_two(int nbr){
  String out;
  if(nbr<10){
    out="0"+String(nbr);
  } else {
    out=String(nbr);
  }
  return out;
}
