#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3f,  20, 4);


int sensorPin1 = A3;

int done = 0;

double Thermistor1(int RawADC) {
  double Temp1;
  Temp1 = log(10000.0*((1024.0/RawADC-1))); 
  Temp1 = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp1 * Temp1 ))* Temp1 );
  Temp1 = Temp1 - 273.15;            // Convert Kelvin to Celcius
   //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   return Temp1;
}

int sensorPin = A5;

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
   //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   return Temp;
}




void setup() {
  
  Serial.begin(9600);
  lcd.begin();

}

void loop() {
  int readVal=analogRead(sensorPin);
  double temp =  Thermistor(readVal);

   int readVal1=analogRead(sensorPin1);
   double temp1 =  Thermistor1(readVal1);
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Inside :");  
  lcd.setCursor(9,0);
  lcd.print(temp);

  lcd.setCursor(14,0);
  lcd.print((char)223);
  
  lcd.setCursor(9, 1);
  lcd.print(temp1);
  lcd.setCursor(0,1);
  lcd.print("Outside:");
  
  lcd.setCursor(14,1);
  lcd.print((char)223);

  int done = temp - temp1;
  lcd.setCursor(0,3);
  lcd.print("Difference");
  lcd.setCursor(11,3);
  lcd.print(done);

  
if(done>-1) {
  lcd.setCursor(12,3);
  lcd.print(" ");
    }
}
