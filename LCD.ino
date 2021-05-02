#include <LiquidCrystal.h>

#define TIMEFLAG (millis()- startTime - counter*60000)

// orange wires --> LEDs, yellow/blue wires --> LCD, green wire --> buzzer,
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int buzzer1 = 9, button = 7, resetPin = 8, ldrpin = A3;
const int LED1 = 13, LED2 = 10, LED3 = 6;
      int minute = 0;
      int counter = 0;
      int val = 0;
      int startflag = 0, ledflag = 0;
      unsigned long startTime = 0;
      
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int LDRsensor(long val)
{
  if (val < 500)
  {
    return 1;
  }
  return 0;
}


//Function implementing LED flash pattern
void LEDflash()
{  
   digitalWrite(LED2, LOW);
   digitalWrite(LED1, HIGH);
   digitalWrite(LED3,HIGH);
   delay(500);
   digitalWrite(LED1, LOW);
   digitalWrite(LED3, LOW);
   digitalWrite(LED2, HIGH);
   delay(500);
   if (startflag > 10000)    
       pinMode(resetPin, OUTPUT);
}

void reprint()
{
  lcd.clear();
  lcd.print("  TIME ELAPSED");
  lcd.setCursor(6, 1);
}


void setup() {
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD.
  lcd.print("  TIME ELAPSED");
 
  //Sets up Buzzer:
   pinMode(buzzer1, OUTPUT);
   
  //Sets up Switch:
  //pinMode(button, INPUT);
  
  //Sets up Reset Pin:
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, LOW);

  //Sets up LED Pins:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  
  //Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  int digitalval = 0;
  Serial.print(val);
  Serial.print(" ");
  Serial.print(digitalval);
  Serial.print(" ");
  Serial.print(startflag);

  
  val = analogRead(ldrpin);
  
  digitalval = LDRsensor(val);
  
  if (digitalval == 1)
  {
    startflag += 1;
  }
   
  if (startflag == 1)
  {
    startTime = millis();
    startflag += 1;
  }

  Serial.print(startflag);
  Serial.print("\n");   

  if (startflag >= 2)
  {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(6, 1);
    lcd.print(minute);
    lcd.print(":");
    // print the number of seconds since reset:

    if (TIMEFLAG < 10000)
    {
      lcd.print(0);
    }

    if (TIMEFLAG == 10000)
    {
      reprint();
    }
  
  
    lcd.print(TIMEFLAG / 1000);
  
    if (TIMEFLAG >= 60000)
    {
      counter += 1;
      minute += 1;
      reprint();
    }

    if (millis()- startTime >= 5000)
    {
      tone(buzzer1, 600);
      while(startflag <= 10000)
      {
        LEDflash();
      }
      
 
    }

    
   }

  
  
}
