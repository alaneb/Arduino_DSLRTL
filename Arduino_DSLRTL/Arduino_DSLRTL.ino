//
// TLController
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author	 	Mark Lange
// 				TwoDorks
//
// Date			8/23/14 6:06 PM
// Version		<#version#>
//
// Copyright	© Mark Lange, 2014
// License		<#license#>
//
// See			ReadMe.txt for references
//


// Core library for code-sense
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif

// Include application, user and local libraries


// Time Lapse Controller for Canon Rebel XTi
#include <LiquidCrystal.h>
#include <Button.h>

LiquidCrystal lcd(12,11,5,4,3,2);
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Button buttonUp = Button(7,PULLDOWN);
Button buttonDown = Button(6,PULLDOWN);
Button buttonSelect = Button(8,PULLDOWN);

//const int switchUp = 7;
//const int switchDown = 6;
//const int selectButton = 8;
int hourVal = 1;
int intervalVal = 1;
int select = 0;
//int newVal1 = hourVal;
//int newVal2 = intervalVal;


void initLCD()
{
    lcd.begin(20, 4); //Initialize LCD screen size
    //pinMode(switchUp, INPUT);
    //pinMode(switchDown, INPUT);
    lcd.print("Total hours:");
    lcd.setCursor(0, 2);
    lcd.print("Interval:");
    lcd.setCursor(0, 1);
    lcd.print(hourVal);
    lcd.setCursor(0, 3);
    lcd.print(intervalVal);
}

void configSelect()
{
    if (buttonSelect.isPressed())
    {
        //select = 1;
        lcd.setCursor(15, 2);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print("#");
        lcd.setCursor(0, 1);
    }
    else if (buttonSelect.isPressed())
    {
        //select = 0;
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(15, 2);
        lcd.print("#");
        lcd.setCursor(0, 3);
    }
    delay(75);
}

void buttonUPPress()
{
    //Button up for the Hours interval
    if (select == 0)
    {
        lcd.setCursor(0, 1);
        if (buttonUp.stateChanged() && buttonUp.isPressed() && hourVal < 24)
        {
            hourVal++;
            lcd.print(hourVal);
            delay(500);
        }
        else if (!buttonUp.stateChanged() && buttonUp.isPressed() && hourVal < 24)
        {
            hourVal++;
            lcd.print(hourVal);
            delay(150);
        }
    }
    //Button up for the seconds interval
    if (select == 1)
    {
        lcd.setCursor(0, 3);
        if (buttonUp.stateChanged() && buttonUp.isPressed() && intervalVal < 300)
        {
            intervalVal++;
            lcd.print(intervalVal);
            delay(500);
        }
        else if (!buttonUp.stateChanged() && buttonUp.isPressed() && intervalVal < 300)
        {
            intervalVal++;
            lcd.print(intervalVal);
            delay(150);
        }
    }
    delay(75);
}

void buttonDownPress()
{
    if (select == 0)
    {
        if (buttonDown.stateChanged() && buttonDown.isPressed() && hourVal > 1)
        {
            hourVal--;
            lcd.print(hourVal);
            delay(500);
        }
        else if (!buttonDown.stateChanged() && buttonDown.isPressed() && hourVal > 1)
        {
            hourVal--;
            if (hourVal < 10)
            {
                lcd.setCursor(1,1);
                lcd.print(" ");
                lcd.setCursor(0,1);
            }
            lcd.print(hourVal);
            delay(150);
        }
    }
    if (select == 1)
    {
        if (buttonDown.stateChanged() && buttonDown.isPressed() && intervalVal > 1)
        {
            intervalVal--;
            lcd.print(intervalVal);
            delay(500);
        }
        else if (!buttonDown.stateChanged() && buttonDown.isPressed() && intervalVal > 1)
        {
            intervalVal--;
            if (intervalVal < 10)
            {
                lcd.setCursor(1,1);
                lcd.print(" ");
                lcd.setCursor(0,1);
            }
            lcd.print(intervalVal);
            delay(150);
        }
    }
}

void serialDebug()
{
    Serial.print("Up StateChanged: ");
    Serial.print(buttonUp.isPressed());
    Serial.print(" Down StateChanged: ");
    Serial.print(buttonDown.isPressed());
    Serial.print(" Select Button: ");
    Serial.print(buttonSelect.isPressed());
    Serial.print(" Select: ");
    Serial.print(select);
    Serial.print("\n");
}

void setup()
{
    Serial.begin(9600); //Open a serial port
    initLCD();
}

void loop()
{
    /*
     int buttonUp = digitalRead(switchUp);
     int buttonDown = digitalRead(switchDown);
     int buttonSelect = digitalRead(selectButton);
     serialDebug(buttonUp, buttonDown, buttonSelect);
     buttonPress(buttonUp, buttonDown, buttonSelect);
     */
    configSelect();
    buttonUPPress();
    buttonDownPress();
    serialDebug();
    delay(75);
}

