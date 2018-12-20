#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,  20, 4);

int sensorPin1 = A3;
int done = 0;

int sw = 8;

double Thermistor1(int RawADC) {
  double Temp1;
  Temp1 = log(10000.0*((1024.0/RawADC-1))); 
  Temp1 = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp1 * Temp1 ))* Temp1 );
  Temp1 = Temp1 - 273.15;            // Convert Kelvin to Celcius
   return Temp1;
}

int sensorPin = A5;

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
   return Temp;
}

void setup() {
  
  Serial.begin(9600); //Starts Serial
  lcd.begin();        //Starts LCD

  pinMode(sw, OUTPUT);

  lcd.setCursor(0,0);           //prints Inside at 0,0
  lcd.print("Inside :");

  lcd.setCursor(0,1);           //prints Outside at 0,1
  lcd.print("Outside:");

  lcd.setCursor(0,3);           //prints Difference this is relative to the inside temp at 0,3
  lcd.print("Difference");

  lcd.setCursor(16,0);
  lcd.print("Fan");

}

void loop() {
 int readVal=analogRead(sensorPin);       //Reads Data from Pin
  double temp =  Thermistor(readVal);    

 int readVal1=analogRead(sensorPin1);     //Reads Data from second pin
 double temp1 =  Thermistor1(readVal1);
  delay(500);
  
  lcd.setCursor(9,0); 
  lcd.print(temp);             //Prints temp data at 9,0

  lcd.setCursor(14,0);        //Adds the degrees symbol at 14,0
    lcd.print((char)223);
  
  lcd.setCursor(9, 1);       //Prints the second pin data
    lcd.print(temp1);

  
  lcd.setCursor(14,1);      //Added the degree symbol at 14,1
    lcd.print((char)223);

 int done = temp - temp1;    //Calculates the difference between the temps

  lcd.setCursor(11,3);      
    lcd.print(done);        //prints the Difference between the two temps
  lcd.setCursor(13,3);
    lcd.print((char)223);   //Adds the degree symbol


if(temp>27 || temp1>27) {    //Checks if one of the sensors is above 27 degrees C
  lcd.setCursor(7,2);
    lcd.print("Cooling"); //Prints if one of the sensors are over 27
    digitalWrite(sw, HIGH);
    
    lcd.setCursor(16,1);
    lcd.print("ON ");      //Prints ON when the Fan is turned on
    
} else {
  lcd.setCursor(7,2);             //Clears the message of not over 27
    lcd.print("         ");
    digitalWrite(sw, LOW);      //Turns off fan when not above 27

    lcd.setCursor(16,1);      //Replaces ON with OFF
    lcd.print("OFF");         //Prints OFF when below 27
}

  
if(done>-1) {
  lcd.setCursor(12,3);    //Adds and removes the degree symbol depending if its a - or not
   lcd.print((char)223);
  lcd.setCursor(13,3);
    lcd.print(" ");   //Removes degree symbol
    }
}
