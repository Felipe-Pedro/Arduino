#include <NewPing.h>

#include <LiquidCrystal.h>

#define ECHO 12
#define TRG 13

#define CMB 11
#define MTB 10

LiquidCrystal lcd(2,3,4,5,7,8,9);
NewPing sonar = NewPing(TRG, ECHO, 4000);

void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2);
  
  pinMode(CMB, INPUT_PULLUP);
  pinMode(MTB, INPUT_PULLUP);

  lcd.print("Distance: ");
  lcd.setCursor(0, 1);
  lcd.print("Maximum:   4,00m");
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = sonar.ping_cm();

  if(digitalRead(CMB) == LOW) {
    writeLCD(distance, true);
    while(digitalRead(CMB) == LOW) {
      
    }
  }else if(digitalRead(MTB) == LOW) {
    writeLCD(distance, false);
    while(digitalRead(MTB) == LOW) {
      
    }
  }
}

void clearDistance() {
  lcd.setCursor(11, 0);
  lcd.print("     ");
  lcd.setCursor(11, 0);
}

String formatDistance(String distance) {
  String model = "0,00";
  for(int i=distance.length()-1, z=3, cont=0; cont<distance.length(); i--, z--, cont++) {
    if(z == 1) {
      i++;
      cont--;
    } else {
      model[z] = distance[i];
    }
  }
  return model;  
}

void writeLCD(int distance, bool cm) {
  if(cm) {
    clearDistance();
    lcd.print(distance);
    lcd.print("cm");
  }else {
    String distanceStr = String(distance); //Transforma int em string
    clearDistance();
    String formattedDistance = formatDistance(distanceStr);
    lcd.print(formattedDistance);
    lcd.print("m");
  }
}
