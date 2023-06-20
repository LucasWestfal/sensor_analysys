// Create a code to receive data from 4 different load cells attached to a HX711 and 4 different pressure sensors attached to the ADCs of the ESP32
// The data will be saved into a sd card

#include <Arduino.h>
#include <HX711.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// // Define the pins used by the first load cell
// #define DOUT1  25
// #define CLK1   26
// // Define the pins used by the second load cell
// #define DOUT2  14
// #define CLK2   32
// // Define the pins used by the third load cell
// #define DOUT3  15
// #define CLK3   33
// // Define the pins used by the fourth load cell
// #define DOUT4  27
// #define CLK4   12

// // Define the pins used by the pressure sensors
// #define ADC1 34 // A2
// #define ADC2 39 // A3
// #define ADC3 36 // A4
// #define ADC4 35 //  A5

// Define the pins used by the first load cell
#define DOUT1  2
#define CLK1   3
// Define the pins used by the second load cell
#define DOUT2  4
#define CLK2   5
// Define the pins used by the third load cell
#define DOUT3  6
#define CLK3   7
// Define the pins used by the fourth load cell
#define DOUT4  8
#define CLK4   9

// Define the pins used by the pressure sensors
#define ADC1 A0 // A2
#define ADC2 A1 // A3
#define ADC3 A2 // A4
#define ADC4 A3 //  A5

// Define the pins used by the SD card
// #define SD_CS  5

// Define the pins used by the button to control the data collection
#define BUTTON_PIN 10

// Define the number of samples to be collected
#define SAMPLES 50

// Initialize the HX711 objects
HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

void setup()
{
    Serial.begin(115200);

    delay(500);

    // Initialize the HX711
    scale1.begin(DOUT1, CLK1);
    scale2.begin(DOUT2, CLK2);
    scale3.begin(DOUT3, CLK3);
    scale4.begin(DOUT4, CLK4);

    delay(2000);

    // Check if the HX711 is connected
    if (!scale1.is_ready())
    {
        Serial.println("HX711 No.1 not found");
        // return;
    }
    if (!scale2.is_ready())
    {
        Serial.println("HX711 No.2 not found");
        // return;
    }
    if (!scale3.is_ready())
    {
        Serial.println("HX711 No.3 not found");
        // return;
    }
    if (!scale4.is_ready())
    {
        Serial.println("HX711 No.4 not found");
        // return;
    }

    // Initialize the pressure sensors pins
    pinMode(ADC1, INPUT);
    pinMode(ADC2, INPUT);
    pinMode(ADC3, INPUT);
    pinMode(ADC4, INPUT);

    // Initialize the button pin
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
    // If the button is pressed, start the data collection
    if (digitalRead(BUTTON_PIN) == LOW)
    {

        // Serial.println("Starting data collection");
        // Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    
        for (int i=0; i<SAMPLES; i++){
            // Read the data from the load cells
            long reading1 = scale1.read();
            long reading2 = scale2.read();
            long reading3 = scale3.read();
            long reading4 = scale4.read();

            // Read the data from the pressure sensors
            int reading5 = analogRead(ADC1);
            int reading6 = analogRead(ADC2);
            int reading7 = analogRead(ADC3);
            int reading8 = analogRead(ADC4);

            // Print the data into the serial monitor
            Serial.print(millis());
            Serial.print(", ");
            Serial.print(reading1);
            Serial.print(", ");
            Serial.print(reading2);
            Serial.print(", ");
            Serial.print(reading3);
            Serial.print(", ");
            Serial.print(reading4);
            Serial.print(", ");
            Serial.print(reading5);
            Serial.print(", ");
            Serial.print(reading6);
            Serial.print(", ");
            Serial.print(reading7);
            Serial.print(", ");
            Serial.println(reading8);

        }

        // Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        // Serial.println("Data collection finished\n");
        
    }
}
