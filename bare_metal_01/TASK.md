# Bare Metal Training 01: Hello World

## Assignment
Need to implement custom scheme for LED blinking on the board “X-Mas Lights”.
All 4 LEDs need to be used.
LEDs should blink constantly (round cycle).
   
## [Solution](Core/Src/main.c)
Pins D12-D15 are responsible for 4 LEDs of the device.
To make round cycle of blinkig LEDs, an array was created with PINs of all LEDs lined up in queue. 
```c
uint16_t scheme[] = { GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 };
```
Variables storing index and amount of array elements are created to be used for iterating through an array
```c
size_t led_index = 0;
size_t scheme_len = sizeof(scheme) / sizeof(uint16_t);
```

Main cycle of the program turns on current led, and, after half-a-second, turns it off.
Then, it increments an index to set the next led in queue to blink in the next cycle iteration.
Last line of 
```c
while (1)
{
  // === Turns on current LED for half-a-second
  HAL_GPIO_WritePin(GPIOD, scheme[led_index], GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(GPIOD, scheme[led_index], GPIO_PIN_RESET);
  // ===
  
  led_index++; // sets next led in queue to be current 

  /* 
  * set first LED (index == 0) to be current in the case the queue made a full cycle 
  * if led_index == 4 (last possible index == 3), and scheme_len == 4, 
  * then led_index = 4 % 4 == 0
  * so, after the last LED blinked, the cycle returns to the first LED
  * /
  led_index %= scheme_len; 
}
```

## Additional Materials
Capture of the signal trace of the program in execution and video of it's work can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/13FWfMYV8YhLMWUgaIcAt2L-L_YFgmlWL?usp=share_link)
