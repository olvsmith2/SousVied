//Oli Smith June 20th 2020

#include <Keypad.h> //Keypad libary
#include <OneWire.h>
#include <DallasTemperature.h> //Temp sensor libaries
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Initialize an instance of class LiquidCrystal_I2C

//Constants and pins
const int RelayPin = 3;      // the number of the relay pin
const byte ROWS = 4; // Rows of keypad
const byte COLS = 4; // Columns of keypad
const int ONE_WIRE_BUS = 2; // Data wire of temp sensor

//Keypad
char keys[ROWS][COLS] = {
  {'1','2','3','/'},
  {'4','5','6','/'},
  {'7','8','9','/'},
  {'*','0','b','/'}
}; //Defines the symbols on the buttons of the keypad

byte rowPins[ROWS] = {8, 9, 10, 11}; //Connected to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //Connected to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // Initialize an instance of class NewKeypad


// Variables
int RelayState = LOW; 
unsigned long setTemp = 15;    
unsigned long currTemp = 21;    
unsigned long PreviousTime = 0;
unsigned long interval = 1000;
unsigned long mins = 00;
unsigned long hours = 00;

//Temp sensor
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire); // Pass oneWire reference to DallasTemperature library
 
 
void setup() {
  Serial.begin(9600);
  sensors.begin();  // Start up the library
  pinMode(RelayPin, OUTPUT); //Declaring digital pins
  pinMode(ONE_WIRE_BUS, INPUT); //Declaring digital pins

  // Initiate the LCD and Keypad:
  lcd.init();
  lcd.backlight();
  
}

void NewTemp() {
  int TempLength = 0;
  setTemp = 0;
  char key = keypad.getKey();
  while (true) {
    char key = keypad.getKey();
    if (key == 'b') {
      break; 
    }
    if ((key == '0')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '1')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '2')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '3')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '4')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '5')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '6')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '7')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '8')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '9')&&(TempLength<2)) {      
      int keyInt = key - '0';
      setTemp = setTemp*10+keyInt;
      TempLength = TempLength + 1;
      UpdateScreen();
    }
    if ((key == '*')&&(TempLength>0)) {      
      setTemp /= 10;
      TempLength = TempLength - 1;
      UpdateScreen();
    }
  }
}

void UpdateScreen()
{
    // Prints current temperature and target temperature to the screen to the lcd screen
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Current:");
  lcd.setCursor(8, 0); 
  lcd.print(currTemp);
  lcd.setCursor(0, 1); 
  lcd.print("Target:");
  lcd.setCursor(7, 1); 
  lcd.print(setTemp);
  lcd.setCursor(11, 1); 
  lcd.print(hours);
  lcd.print(":");
  lcd.print(mins);
}


void loop() {
  char key = keypad.getKey();
  if (key == '/') {
    RelayState = LOW;
    digitalWrite(RelayPin, RelayState);
    NewTemp();
  }
  mins= ((millis() - PreviousTime)%3600000)/60000;
  hours= (millis() - PreviousTime)/3600000;
  
  UpdateScreen();
  
  digitalWrite(RelayPin, RelayState);
  
  sensors.requestTemperatures();
  
  currTemp = sensors.getTempCByIndex(0);
  if (currTemp < -10 ||  currTemp > 84){
    RelayState = LOW;
  } //Temperature missreading shut off
  
  if (currTemp < setTemp) {
    RelayState = HIGH;
  }
  
  if (currTemp >= setTemp) {
    RelayState = LOW;
  }

} 
