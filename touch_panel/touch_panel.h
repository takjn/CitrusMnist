// 参照：タッチスクリーンをARDUINOから使う
// http://gaje.jp/technotes/touch_screen/

// Assign analog pins to the touch screen terminals
//
#define xPositive_A 14
#define yPositive_A 15
#define xNegative_A 16
#define yNegative_A 17
 
// We also digitalWrite on above pins
//
#define xPositive_D 14
#define yPositive_D 15
#define xNegative_D 16
#define yNegative_D 17

void ts_Reset();
void ts_ReadPosition(uint8_t, uint8_t, uint8_t, uint8_t , uint8_t, uint8_t, int* , int* );
int ts_ReadXPosition();
int ts_ReadYPosition();
