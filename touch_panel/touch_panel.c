#include <Arduino.h>
#include "touch_panel.h"

/**
 * Set the touch screen to non-measuring state
 */
void ts_Reset()
{
    // change all pins to output mode
    pinMode( xPositive_D, OUTPUT );
    pinMode( xNegative_D, OUTPUT );
    pinMode( yPositive_D, OUTPUT );
    pinMode( yNegative_D, OUTPUT );
    
    // set low to all pins
    digitalWrite( xPositive_D, LOW );
    digitalWrite( xNegative_D, LOW );
    digitalWrite( yPositive_D, LOW );
    digitalWrite( yNegative_D, LOW );

}
 
/**
 * Shift the touch screen reading state, followed by measurement.
 * This routine sets the state back to non-measuring at the final step.
 */
void ts_ReadPosition(uint8_t resist_Positive_D, uint8_t resist_Negative_D,
                     uint8_t probe_Positive_D, uint8_t probe_Negative_D,
                     uint8_t probe1_A, uint8_t probe2_A,
                     int* value1, int* value2)
{
  digitalWrite( resist_Positive_D, HIGH ); // Set the positive side of resistor terminals.
 
  delayMicroseconds(100);                  // Wait a while for onset of the terminal
 
  pinMode(probe_Positive_D, INPUT);        // Change probe terminals to input mode
  pinMode(probe_Negative_D, INPUT);
 
  delayMicroseconds(100);                  // Wait a while for the probe terminal onsets at the measuring voltage
 
  *value1 = analogRead( probe1_A );        // OK, here we go
 
  // this is optional read for Z-axis      // We may sometimes want to read at opposite side of the probes as well.
  if (value2 != NULL) {
    *value2 = analogRead( probe2_A );
  }
 
  ts_Reset();                              // The measurement finished.  Getting back to normal state.
}
 
/**
 * Read X Position
 */
int ts_ReadXPosition()
{
  int value;
  ts_ReadPosition( xPositive_D, xNegative_D,
                   yPositive_D, yNegative_D,
                   yPositive_A, 0,
                   &value, NULL );
  return value;
}
 
/**
 * Read Y Position
 */
int ts_ReadYPosition()
{
  int value;
  ts_ReadPosition( yPositive_D, yNegative_D,
                   xPositive_D, xNegative_D,
                   xPositive_A, 0,
                   &value, NULL );
  return value;
}
