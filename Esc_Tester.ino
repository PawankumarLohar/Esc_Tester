
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Servo ESC;     // create servo object to control the ESC
int potValue;  // value from the analog pin
int  new_potValue ;
float pulsewidth=0;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // Address 0x3D for 128x64
    delay(2000);
   display.clearDisplay();
   display.setTextColor(WHITE, BLACK);// Display static text
   // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
}




void loop() {
  display.clearDisplay(); 
  display.setCursor(0, 20);
  display.setTextSize(2);
  display.print("(On Time)");
  display.setCursor(0, 40);
  potValue = analogRead(A2);   // reads the value of the potentiometer (value between 0 and 1023)
  new_potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  
  ESC.write(new_potValue);    // Send the signal to the ESC
  pulsewidth=new_potValue;
  pulsewidth=pulsewidth * 0.005555 + 1;
  display.setTextSize(3);
  display.print(pulsewidth,3);
  display.setCursor(90, 40);
  display.print("ms");
  delay(50);
  display.display();
}
