   //LCD DEFINITIONS
sbit LCD_RS at RB2_bit ;
sbit LCD_EN at RB3_bit ;
sbit LCD_D4 at RB4_bit ;
sbit LCD_D5 at RB5_bit ;
sbit LCD_D6 at RB6_bit ;
sbit LCD_D7 at RB7_bit ;

sbit LCD_RS_Direction at TRISB2_bit ;
sbit LCD_EN_Direction at TRISB3_bit ;
sbit LCD_D4_Direction at TRISB4_bit ;
sbit LCD_D5_Direction at TRISB5_bit ;
sbit LCD_D6_Direction at TRISB6_bit ;
sbit LCD_D7_Direction at TRISB7_bit ;

                    // SET TEMP BUTTONS & INDICATION LEDS
         sbit UP at RC4_bit;
         sbit DOWN at RC5_bit;
         sbit RED  at RC6_bit ;
         sbit GREEN at RC7_bit ;
         
                  // VARIABLES
int x ;
float y ;
 int setT = 25;
float temp ;
int SPA;
int SPEED;
char setText[7];
char temp_txt[15];
char SPEED_txt[7];
                       //MAIN

void main() {
//PINS
trisc.f4 = 1 ;
trisc.f5 = 1 ;


trisc.f6 = 0;
trisc.f7 = 0 ;
RED= 0 ;
GREEN = 0 ;

       //INIT MODULES
lcd_init();
adc_init();
    pwm1_init(2500);
    // SPLASH
lcd_cmd(_lcd_cursor_off);

lcd_out(1,1,"Fan Speed");
lcd_out(2,5,"CONTROLLER");
delay_ms(2000);


      lcd_cmd(_lcd_clear);
while(1){

                 if (  UP = 1 )
                 {

                  setT++ ;
                  lcd_cmd(_lcd_clear);
                 lcd_out(1,4,"SET TEMP")  ;
                 inttostr(setT,setText)    ;
                 ltrim(setText);
                 lcd_out (2,6,setText)  ;
                 delay_ms(500);
                 
                 }
                 if( DOWN = 1){
                             setT-- ;
                  lcd_cmd(_lcd_clear);
                 lcd_out(1,4,"SET TEMP")   ;
                 inttostr(setT,setText)     ;
                 ltrim(setText);
                 lcd_out (2,6,setText)  ;
                 delay_ms(500);
                 
                 }

                delay_ms(500);
x = adc_read(0) ;
y = (x*5.0/1024);
temp = y*100    ;

if( temp>setT  && temp < 50){
SPA = (temp-setT)*255/(50-setT);
      Green =0 ;
      RED = 1 ;
  }
  else if ( temp > 50) {
  SPA = 255;
      Green =0 ;
      RED = 1 ;
  }
else { SPA = 0 ;
RED =0 ;
Green = 1;

}





                 SPEED = 100*SPA/255      ;
               inttostr( SPEED,SPEED_txt);
                   floattostr(temp,temp_txt);


temp_txt[4]= '\0' ;


    pwm1_set_duty(SPA);
    pwm1_start();


          lcd_cmd(_lcd_clear);
lcd_out(1,1,"Temp = ");
lcd_out_cp(temp_txt);
lcd_chr_cp(223); // for Centigrade o
lcd_chr_cp('C');

lcd_out(2,1,"RPM = ");
lcd_out_cp(SPEED_txt);
lcd_chr_cp('%');





}


}
