// Sample code for e-AI

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "eAI_translated/Typedef.h"
#include "eAI_translated/input_image_0.h"
#include "eAI_translated/layer_graph.h"
TPrecision* dnn_compute(TPrecision* input_img);

#include "touch_panel/touch_panel.h"
#ifdef __cplusplus
}
#endif

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono24pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define TOUCH_SCREEN_MIN_X 110
#define TOUCH_SCREEN_MIN_Y 90
#define TOUCH_SCREEN_MAX_X 470
#define TOUCH_SCREEN_MAX_Y 520

#define TOUCH_SCREEN_GRID 14

int buffer[TOUCH_SCREEN_GRID][TOUCH_SCREEN_GRID];
int mode = 0;
int interval = 0;
#define CHECK_DELAY 30

void clearBuffer() {
    for (int y=0; y<TOUCH_SCREEN_GRID; y++) {
        for (int x=0; x<TOUCH_SCREEN_GRID; x++) {
            buffer[y][x] = 0;
        }
    }
}

void printBuffer() {
    for (int y=0; y<TOUCH_SCREEN_GRID; y++) {
        for (int x=0; x<TOUCH_SCREEN_GRID; x++) {
            if (buffer[y][x]) {
                Serial.print(buffer[y][x]);
            }
            else {
                Serial.print(" ");
            }
        }
        Serial.println();
    }
    Serial.println();
}


void setup()
{
    Serial.begin(115200);
    ts_Reset();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
    display.clearDisplay();
    display.display();
}

int prediction() {
    int ret = -1;
    TPrecision *prediction;
    TPrecision *input_img;
    TsInt i;

    long time_start = millis();
    
    input_img = data_in;
    prediction = (TPrecision*) (intptr_t) dnn_compute( input_img);

    Serial.print("Dnn Compute time(ms):");
    Serial.println(millis() - time_start);
    for(i = 0;i < 10;i++){
    	Serial.print(i); Serial.print(":");
    	Serial.println(prediction[i]);
    	
    	if (prediction[i] > 0.7) {
    	    ret = i;
    	}
    }
    return ret;
}

void loop()
{
  int x, y;
 
  x = ts_ReadXPosition();   // eat
  delay(1);                 // sleep
  y = ts_ReadYPosition();   // eat
  
  if (x<TOUCH_SCREEN_MIN_X || y<TOUCH_SCREEN_MIN_Y) {
    if (mode == 1) {
      
      if (interval < CHECK_DELAY) {
        delay(10);
        interval++;
      }
      else {
        printBuffer();
        mode = 0;
        
        int i=0;
        for (int y=0; y<TOUCH_SCREEN_GRID; y++) {
            for (int p=0; p<(28 / TOUCH_SCREEN_GRID); p++) {
                for (int x=0; x<TOUCH_SCREEN_GRID; x++) {
                    for (int q=0; q<(28 / TOUCH_SCREEN_GRID); q++) {
                        data_in[i++] = buffer[y][x];

                        if (buffer[y][x]) {
                            display.drawPixel(x, y, WHITE);
                        }
                    }
                }
            }
        }
        int ret = prediction();

        // print result
        display.setTextColor(WHITE);
        display.setFont(&FreeMono24pt7b);
        display.setTextSize(2);
        display.setCursor(36, 60);

        if (ret < 0) {
            Serial.println("cannot detect.");
            display.print("-");
        }
        else {
            Serial.println();
            Serial.print("result: ");
            Serial.println(ret);
            display.print(ret);
        }

        display.display();
      } 
    }
  }
  else {
    if (mode == 0) {
        clearBuffer();
        display.clearDisplay();
        mode = 1;
    }
    interval = 0;

    // Serial.print(x, DEC);
    // Serial.print(", ");
    // Serial.print(y, DEC);
    // Serial.println();
    
    int tx = map(x, TOUCH_SCREEN_MIN_X, TOUCH_SCREEN_MAX_X, 0, TOUCH_SCREEN_GRID - 1);
    int ty = map(y, TOUCH_SCREEN_MIN_Y, TOUCH_SCREEN_MAX_Y, TOUCH_SCREEN_GRID - 1, 0);
    buffer[ty][tx] = 1;
  }
}
