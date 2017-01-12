//created by Kartik Madhira and Ammar Gandhi
//kartikmadhira1@gmail.com  
//ammar.cma@gmail.com

#include <LiquidCrystal.h>

LiquidCrystal lcd(53,51,49,47,45,43); 
//hare krishna 
//will only be using 5 of  the 7 irs
int sel_b =      5;
int up_b  =      4;
int down_b=     7 ;
int count; 
int m11   =      13;
int m12    =     12;
int PWM_m1  =    11;
int PWM_m2   =   10;
int m21       =  6;
int m22        = 8;
int Mmax        =255;
int l3          =A6;
int r3          =A5;
int l2          =A0;
int  l1          =A1; 
int  c          = A2;
int r1          =A3;
int r2          =A4;
int fwdspeed    =180;
int basespeed   =120;
float kp=7,ki=0,kd=5;
void fastforward();
float raw_output,raw2_output,proportional,derivative,integral,integrand,rate;
boolean start;
int output,L1,L2,C,R1,R2,R3,L3,final_error,M1,M2,motor_speed1,motor_speed2,error,preverror; 

void setup() 
{
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.print("----ENIGMA----");
delay(6000);
lcd.clear();
lcd.write("By :-");
delay(1000);
lcd.clear();
lcd.write("Kartik Madhira");
delay(2000);
lcd.clear();
lcd.write("and");
delay(1000);
lcd.clear();
lcd.write("Ammar Gandhi");
delay(2000);
pinMode(sel_b,INPUT);
pinMode(up_b,INPUT);
pinMode(down_b,INPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A5,INPUT);
pinMode(A6,INPUT);

pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
pinMode(PWM_m1,OUTPUT);
pinMode(PWM_m2,OUTPUT);
push_settings();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(start==true){
//error generation;
L3=digitalRead(l3);
L2=digitalRead(l2);
L1=digitalRead(l1);
C=digitalRead(c);
R1=digitalRead(r1);
R2=digitalRead(r2);
R3=digitalRead(r3);

//digitalWrite(3,HI
  if(R3==0&&R2==0)
  {
    error=5;
  }
  else if(R2==0&&R1==0)
  {
    error=10; 
  }  
  
  else if (R1==0&&C==0)
  {
    error=35;
  }
   else if(C==0)
  {
    error=20;
  }
  else if(L1==0&&C==0)
  {
   error=25;
  }
  else if(L1==0&&L2==0)
  {
    error=30;
  }
   else if(L2==0&&L3==0)
  {
    error=35;
  }
  else if( R2==0&&R3==0&&C==0&&R1==0)
   {
   error=5;
 }


final_error=error-20;
integral=integral+error;
motor_speed1=kp*final_error+kd*(final_error-preverror)+ki*integral;
preverror=final_error;

M1=basespeed-motor_speed1;
M2=basespeed+motor_speed1;

if(M1>Mmax)
{
  M1=Mmax;
}
 if(M2>Mmax)
 {
   M2=Mmax;
 }
if(M1<0)
{M1=0;
}
 if(M2<0)
 {
  M2=0;
 }



{
digitalWrite(m11,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m22,HIGH);
  analogWrite (PWM_m1,M1);
  analogWrite (PWM_m2,M2);
}

} 
}

int  push_settings()
{
++count;
if(count==1)
{
  lcd.clear();
  lcd.print("Set Kp-");
  kp=set(kp);
++count;
}
delay(100);
if (count==2)
{lcd.clear();
lcd.print("Set Kd-");
kd=set(kd);
++count;
}
delay(100);
if (count==3)
{
  lcd.clear();
lcd.print("Set Ki-");
ki=set(ki);
++count;
}
delay(100);
if (count==4)
{

lcd.clear();
lcd.print("Set Basespeed");
basespeed=set(basespeed);
  ++count;
}  
delay(100);
if(count>4)
{
  lcd.clear();

  lcd.print("Bang On!");
 
  start=true;
}
}
float set(float a )
{
delay(100);
lcd.setCursor(0,1);
lcd.print(a);

while((digitalRead(sel_b)==LOW))
{
  
  
    if((digitalRead(up_b)==HIGH))
    { 
      lcd.clear();
      //incrementing by 0.1
      a*=10;
      a++;
      a/=10;
      lcd.setCursor(0,1);
      lcd.print(a);
    }
     if ((digitalRead(down_b)==HIGH))
     {
      
      a*=10;
      a--;
      a/=10;
      
      lcd.setCursor(0,1);
      lcd.print(a);
     }
     
  delay(100);
     
    }
    return(a);
} 


