#include <Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>

const int rs = 7, en = 6, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo;
const byte ROWS = 4; 
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0,A1,A2,A3}; 
byte colPins[COLS] = {A4,A5,3,2}; 
int l=0,a=0,b=0,f=0;
char newpwd[5];
char repwd[5];
char password[5]="1234";
char input[5];
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void set()
{
  l=0; a=0; b=0;
  for(int i=0;i<=4;i++)
  {
  input[i]='\0';
  repwd[i]='\0';
  newpwd[i]='\0';
  }
  lcd.clear();
}
void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  servo.attach(12);
  servo.write(90);
  pinMode(10,OUTPUT);
  pinMode(4,OUTPUT);
 lcd.begin(16, 2);

}
  
void loop()
{   
    lcd.setCursor(0, 1);
    char customKey = customKeypad.getKey();
    if(customKey)
    {
    if(l<4 && customKey!='C'){
    input[l++]=customKey; 
    lcd.print(input);
    }
    }
    if(l==4)
    {
      if(customKey=='A')
      {
        if(strcmp(input,password)==0)
        {
        lcd.print("LOGIN GRANTED");
        servo.write(15);
        delay(2000);
        set();
        }
        else
        {
          lcd.print("LOGIN FAILED");
          for(int i=0; i<4;i++)
          {
            digitalWrite(13,HIGH);
            digitalWrite(4,HIGH);
            delay(1000);
            digitalWrite(4,LOW);
            digitalWrite(13,LOW);
            delay(1000);
          }
          set();
        }
      }
      if(customKey=='B')
        {
          if(strcmp(input,password)==0)
             {
               lcd.print("ENTER A NEW PASSWORD");
               delay(2000);
               lcd.clear();
               while(1)
                    {
                     char newKey = customKeypad.getKey();
                     if(newKey)
                       {
                        if(a<4)
                          {
                            newpwd[a++]=newKey; 
                            lcd.print(newpwd);
                            delay(500);
                            lcd.clear();
                          }
                        else
                        {
                          if(f==0)
                           {
                             lcd.print("Re ENTER the new password");
                             delay(2000);
                             f=1;
                             lcd.clear();
                           }
                        if(newKey!='B')
                        repwd[b++]=newKey;
                        lcd.print(repwd);
                        delay(500);
                        lcd.clear();
     
                        if(strcmp(repwd,newpwd)==0)
                        {
                          lcd.clear();
                          lcd.print("SET");
                          
                          for(int i=0; i<15;i++)
                             {
                              digitalWrite(13,HIGH);
                              
                              delay(100);
                              digitalWrite(13,LOW);
                              
                              delay(100);
                             }                          
                          strcpy(password,repwd);
                          set();
                          servo.write(90);
                          delay(2000); 
                          break;
                        }
                        else if(b==4 && strcmp(repwd,newpwd)!=0)
                        {
                          lcd.print("ERROR");
                          for(int i=0; i<15;i++)
                            {
                             digitalWrite(13,HIGH);
                             digitalWrite(4,HIGH);
                             delay(500);
                             digitalWrite(4,LOW);
                             digitalWrite(13,LOW);
                             delay(500);
                            }
                          set();
                          break;
                        }
                        }
                        }
                   }
              }
        } 
    }
    if(customKey=='C')
    {
      servo.write(90);
      lcd.print("LOCKED");
      delay(2000);
     set(); 
    }
    if(customKey=='D')
    set();
}
