@@ -0,0 +1,122 @@
//Hare Krishna
Author:Kartik Madhira
//www.techspirityou.blogpspot.com

int m11   =      13;
int m12    =     12;
int PWM_m1  =    11;
int PWM_m2   =   10;
int m21       =  6;
int m22        = 8;
int Mmax        =250;
int l3          =2;
int r3          =A5;
int l2          =A0;
int  l1          =A1;
int  c          = A2;
int r1          =A3;
int r2          =A4;
int fwdspeed    =180;
int basespeed   =150;
float   kp        =6;
int  ki          =0;
float  kd     =  0;
void fastforward();
float raw_output,raw2_output,proportional,derivative,integral,integrand,rate;
int output,L1,L2,C,R1,R2,R3,L3,final_error,M1,M2,motor_speed1,motor_speed2,error,preverror; 
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(3,OUTPUT);//MOTOR LOGIC ;
pinMode(m11,OUTPUT);
pinMode(m12,OUTPUT);
pinMode(m21,OUTPUT);
pinMode(m22,OUTPUT);
pinMode(PWM_m1,OUTPUT);
pinMode(PWM_m2,OUTPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//error generation;
L3=digitalRead(l3);
L2=digitalRead(l2);
L1=digitalRead(l1);
C=digitalRead(c);
R1=digitalRead(r1);
R2=digitalRead(r2);
R3=digitalRead(r3);

digitalWrite(3,HIGH);//MOTOR LOGIC; 

 if(R3==0&&L3==0)
  {
    error=20; 
  }
  
 else if(R3==0&&R2==0)
  {
    error=35; 
  }
 else if(R2==0&&R1==0)
  {
    error=30; 
  }
  else if(R1==0&&C==0)
  {
    error=25;
  }
   else if(C==0)
  {
    error=20;
  }
  else if(L1==0&&C==0)
  {
   error=15;
  }
  else if(L2==0&&L1==0)
  {
    error=10;
  }
   else if(L3==0&&L2==0)
  {
    error=5;
  }

final_error=error-20;
integral+=error; 
motor_speed1=kp*final_error+kd*(final_error-preverror)+ki*integral*ki;
preverror=final_error;

M1=basespeed-motor_speed1;
M2=basespeed+motor_speed1;

if(M1>Mmax)
  M1=Mmax;
 if(M2>Mmax)
  M2=Mmax;
if(M1<0)
M1=0;
 if(M2<0)
  M2=0;

Serial.print(M2);
Serial.println('/n');

{
digitalWrite(m11,LOW);
  digitalWrite(m21,LOW);
  digitalWrite(m12,HIGH);
  digitalWrite(m22,HIGH);
  analogWrite (PWM_m1,M1);
  analogWrite (PWM_m2,M2);
}
}

