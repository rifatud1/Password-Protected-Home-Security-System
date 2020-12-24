//Developed by Md. Rifat Uddin

#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String password = "1234"; 
int position = 0;

int wrong = 0; 


int relay = 13;
int buzzer = 12;
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);



int total = 0;

void setup()
{
  
 pinMode(relay,OUTPUT);
 pinMode(buzzer, OUTPUT);
 
lcd.init();
lcd.init();
lcd.backlight();
lcd.print("     CSE461 Project     ");
lcd.setCursor(0,1);
lcd.print("   Locking System   ");
lcd.setCursor(0,2);
lcd.print("By: Rifat Tasdid");
lcd.setCursor(0,3);
lcd.print("By: Umme Nigah");
delay(3000);
lcd.clear();
setLocked(true);
delay(20);
}

void loop()
{
  
  lcd.clear();
  lcd.print(" Enter Password: ");
  delay(100);
  
 char pressed=keypad.getKey();
 String key[3];
  
 if(pressed)
 {
  lcd.clear();
  lcd.print(" Enter Unlock Code: ");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }

    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position] )
      {
          wrong++;
          position ++;
      }

    if(position == 4){
          if( wrong >0)
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.setCursor(0,2);
                lcd.print("    Wrong Code!     ");
                delay(1000);
                setLocked(true);
            }

          else if(position == 4 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.setCursor(0,1);
                lcd.print("      Welcome!     ");
                lcd.setCursor(5,2);
                lcd.print(" Door Open");
                delay(2000);
                setLocked(false);
            }

             if(total ==3)
            {
                total=0;
                buzzer_beep();
                delay(500);
            }

        }

   }

   
}

void setLocked(int locked)
  {
    if (locked)
      {
          digitalWrite(relay, LOW);
          delay(1000);
      }
    else
      {
          
          digitalWrite(relay, HIGH);
          delay(2000);
          
      }
  }
void buzzer_beep()
{
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("    WARNING  !!!!   ");
   lcd.setCursor(0,2);
   lcd.print("   Access Denied");
   for (int i=0;i<3;i++){
   digitalWrite(buzzer,HIGH);
   delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
   }
}
