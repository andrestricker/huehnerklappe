// set the display. Comparing lines to display with lines already displayed to avoid flickering

void set_display(String line1, String line2){
  if(line1!=buf_line1 or line2!=buf_line2){
    buf_line1=line1;
    buf_line2=line2;
    oled.clear();
    oled.println(buf_line1);
    oled.print(buf_line2);
  }
}
