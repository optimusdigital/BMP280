//libraries used by LCD
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

//libraries used by BMP280 GY

#include "SparkFunBME280.h"


//library used by both components
#include <SPI.h>

//define the color white
#define WHITE   0xFFFF



BME280 mySensor;


//these two pins are used by the LCD 
#define __CS 10
#define __DC 9


TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);


void setup() {
	tft.begin();

  
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;
  

  //***Operation settings*****************************//
  
  //runMode can be:
  //  0, Sleep mode
  //  1 or 2, Forced mode
  //  3, Normal mode
  mySensor.settings.runMode = 3; //Normal mode
  
  //tStandby can be:
  //  0, 0.5ms
  //  1, 62.5ms
  //  2, 125ms
  //  3, 250ms
  //  4, 500ms
  //  5, 1000ms
  //  6, 10ms
  //  7, 20ms
  mySensor.settings.tStandby = 0;
  
  //filter can be off or number of FIR coefficients to use:
  //  0, filter off
  //  1, coefficients = 2
  //  2, coefficients = 4
  //  3, coefficients = 8
  //  4, coefficients = 16
  mySensor.settings.filter = 0;
  
  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.tempOverSample = 1;

  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    mySensor.settings.pressOverSample = 1;

  mySensor.begin();
  
  //wait 1000ms so the BMP280 have enough time to turn on.


 
  //setup the size and colour of the text on the LCD
  tft.setTextColor(WHITE);
  tft.setTextSize(1);


 
}

int refreshRate=5000; //used to control the rate of refresh of the screen ( in ms)

//these variables are used to store the temperature,pressure and altitude
float temp;
long pressure;
float altitude;

void loop()
{ 
  //read the temperature from the BMP280  
  temp=mySensor.readTempC();

  //read the pressure from the BMP280
  pressure=mySensor.readFloatPressure();

  //read the altitude from the BMP280
  altitude=mySensor.readFloatAltitudeMeters();


  //display the temperature 
  tft.setCursor(5,10);
  tft.print("Temperatura: ");
  tft.setCursor(75,10);
  tft.print(temp);
  tft.setCursor(115,10);
  tft.print("C");

 //display the pressure
  tft.setCursor(5,40);
  tft.print("Presiune: ");
  tft.setCursor(75,40);
  tft.print(pressure);
  tft.setCursor(115,40);
  tft.print("Pa");

 //display the altitude  
  tft.setCursor(5,70);
  tft.print("Altitudine: ");
  tft.setCursor(75,70);
  tft.print(altitude);
  tft.setCursor(115,70);
  tft.print("m");
 
  delay(refreshRate);  
  
  tft.fillScreen();


}



"# Tutorial Optimus" 
