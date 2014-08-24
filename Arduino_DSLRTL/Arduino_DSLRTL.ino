// 
// Arduino_DSLRTL 
//
// Time Lapse Controller using Arduino and Canon D400
// Developed with [embedXcode](http://embedXcode.weebly.com)
// 
// Author	 	Alan
// 				2Dorks
//
// Date			8/23/14 6:12 PM
// Version		<#version#>
// 
// Copyright	© Alan, 2014
// License		<#license#>
//
// See			ReadMe.txt for references
//

// Core library for code-sense

#include "Arduino.h"

// Included user libraries

#include <LiquidCrystal.h>
#include <Button.h>

// Declare LCD display

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variables and constants

const int switchUp = 7;
const int switchDown = 6;
const int selectButton = 8;
int hourVal = 1;
int intervalVal = 1;
int newVal1 = hourVal;
int newVal2 = intervalVal;


void buttonPress(int upPress, int downPress, int selectPress)
{
    if (selectPress == 0)
    {
        lcd.setCursor(0, 1);
        if (upPress == 1 && downPress == 0)
        {
            if (newVal1 < 24)
            {
                newVal1++;
                lcd.print(newVal1);
            }
            else
            {
                lcd.print(newVal1);
            }
        }
        else if (downPress == 1 && upPress == 0)
        {
            if (newVal1 > 1)
            {
                newVal1--;
                lcd.print(newVal1);
            }
            else
            {
                lcd.print(newVal1);
            }
            if (newVal1 < 10)
            {
                lcd.setCursor(1, 1);
                lcd.print(" ");
                lcd.setCursor(0, 1);
            }
        }
        delay(100);
    }
    
    else if (selectPress == 1)
    {
        lcd.setCursor(0, 3);
        if (upPress == 1 && downPress == 0)
        {
            if (newVal2 < 300)
            {
                newVal2++;
                lcd.print(newVal2);
            }
            else
            {
                lcd.print(newVal2);
            }
        }
        else if (downPress == 1 && upPress == 0)
        {
            if (newVal2 > 1)
            {
                newVal2--;
                lcd.print(newVal2);
            }
            else
            {
                lcd.print(newVal2);
            }
            if (newVal2 < 100)
            {
                lcd.setCursor(2, 3);
                lcd.print(" ");
                lcd.setCursor(0, 3);
            }
            if (newVal2 < 10)
            {
                lcd.setCursor(1, 3);
                lcd.print(" ");
                lcd.setCursor(0, 3);
            }
        }
        delay(150);
    }
    
}

void serialDebug(int upButtonDebug, int downButtonDebug, int selectButtonDebug)
{
    Serial.print("Up Button: ");
    Serial.print(upButtonDebug);
    Serial.print(" Down Button: ");
    Serial.print(downButtonDebug);
    Serial.print(" Select Button: ");
    Serial.print(selectButtonDebug);
    Serial.print("\n");
}

void initLCD()
{
    lcd.begin(20, 4); //Initialize LCD screen size
    pinMode(switchUp, INPUT);
    pinMode(switchDown, INPUT);
    lcd.print("Total hours:");
    lcd.setCursor(0, 2);
    lcd.print("Interval:");
    lcd.setCursor(0, 1);
    lcd.print(hourVal);
    lcd.setCursor(0, 3);
    lcd.print(intervalVal);
}

void setup()
{
    Serial.begin(9600); //Open a serial port
    initLCD();
}

void loop()
{
    int buttonUp = digitalRead(switchUp);
    int buttonDown = digitalRead(switchDown);
    int buttonSelect = digitalRead(selectButton);
    serialDebug(buttonUp, buttonDown, buttonSelect);
    buttonPress(buttonUp, buttonDown, buttonSelect);
}
