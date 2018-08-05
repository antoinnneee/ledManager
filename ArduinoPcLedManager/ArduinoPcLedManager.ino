
#define PLEDR0 3
#define PLEDG0 2
#define PLEDB0 4
#define PLEDL0 5

#include <EEPROM.h>


int address = 0;
bool  debugEnable = false;

unsigned char   lightIntensity;

unsigned char   ledColor[3];

void serialEvent(){
  while (Serial.available())
  {
    char c = 0;
    Serial.readBytes(&c, 1);
    if (c == 'R')
    {
      Serial.readBytes(&c, 1);
      ledColor[0] = c;
      setColor();
    }
    else if (c == 'G')
    {
      Serial.readBytes(&c, 1);
      ledColor[1] = c;
      setColor();
    }
    else if (c == 'B')
    {
      Serial.readBytes(&c, 1);
      ledColor[2] = c; 
      setColor();
    }
    else if (c == 'P')
    {
      Serial.println("pong"); // echo for test
    }
    else if (c == 'L')
    {
      Serial.readBytes(&c, 1);
      lightIntensity = 255 - c ;
      setColor();
    }
    else if (c == 'D')
    {
      Serial.readBytes(&c, 1);
      debugEnable = c;      
    }
  }
}

void setColor()
{
    analogWrite(PLEDR0, ledColor[0]);
    analogWrite(PLEDG0, ledColor[1]);
    analogWrite(PLEDB0, ledColor[2]);  
    analogWrite(PLEDL0, lightIntensity);  
    
    EEPROM.write(address, ledColor[0]);
    EEPROM.write(address + 1, ledColor[1]);
    EEPROM.write(address + 2, ledColor[2]);
    EEPROM.write(address + 3, lightIntensity);
    if (debugEnable)
    {
        Serial.print("set Color [R, G, B, L] : [");
        Serial.print(ledColor[0]);
        Serial.print(", ");
        Serial.print(ledColor[1]);
        Serial.print(", ");
        Serial.print(ledColor[2]);
        Serial.print(", ");
        Serial.print(ledColor[3]);
        Serial.println("]");
    }
}


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(PLEDR0, OUTPUT);
    pinMode(PLEDG0, OUTPUT);
    pinMode(PLEDB0, OUTPUT);
    pinMode(PLEDL0, OUTPUT);
    Serial.setTimeout(5000);
    memset(ledColor, 0, 3);
    ledColor[0] = EEPROM.read(address);
    ledColor[1] = EEPROM.read(address + 1);
    ledColor[2] = EEPROM.read(address + 2);
    lightIntensity = EEPROM.read(address + 3);
    setColor();
}

void loop() {
  // put your main code here, to run repeatedly:

}
