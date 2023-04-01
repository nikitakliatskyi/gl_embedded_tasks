# Bare Metal Training 05: UART

## Assignment
1. Need to start UART3 with following settings: baud rate 115200, 8bit, no parity, 1 stop bit.
2. Need to control all 4 LED states with help of the PC keyboard. Keyboard button toggles LED state (via console). Current LED state printed to the console.
3. Need to control all 4 LED states with help of buttons SWT1, SWT3, SWT4, SWT5 (on the GL board) – toggle mode. Current LED state printed to the console.
4. One time per 5 seconds, actual temperature (external analog sensor at GL board) value should be printed at console (Celsius degrees).
   
## [Solution](Core/)
Timer started in the main function, so it could be used for reading and printing a temperature every 5 second. He has these two values set up like that:
```c
htim4.Init.Prescaler = 16000;
htim4.Init.Period = 5000;
```
Prescaler = 16000 means, that it's going to count only up to 1000 per second.
Then Period = 5000, so that callback function for timer handling would be called when timer will count up to 5000 - once per 5 seconds.
Then, inside timer callback function, next function is called:
```c
HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adcValue, ADC_VALUES_AMOUNT);
```
So ADC would read temperature only when timer counts up to 5000 (once per 5s), store the result inside adcValue and call callback function.

Main loop reads UART in using DMA every iteration. When a value is read, callback function is called. Value is stored into variable *receivedChar*.
```c
HAL_UART_Receive_DMA(&huart3, &receivedChar, 1);
```

Created structure LedInfo for saving information about led itself, and LedControlInfo to store info about keys that activate the certain led. 
```c
typedef struct {
	uint16_t Pin;
	volatile GPIO_PinState State;
	char* Color;
} LedInfo;

typedef struct {
	LedInfo* Led;
	uint16_t ToggleButtonPin;
	uint8_t ToggleChar;
} LedControlInfo;
```

Objects of these structures are created for each led and LedControlInfo objects are additionaly stored in array ledsControls, that will be later iterated. They can be found in [this file](Core/Src/app_data.c).
The same file also has functions to toggle leds, sending formatted string with information about LedInfo passed into it with UART, function to send formatted string with temperature in it with UART and function *GetTemperature*, that uses following formula to calculate temperature from adc value it gets:
```c
float vout = VREF / 4096.0f * adcValue ; // getting current voltage
float temp = (VT0 - vout) / VC; // substracting *current voltage* from *voltage for 0 temperature* to get temperature starting from 0, then divide it by *voltage per celcius* to get human-readable data in celcius
```

There is [this file](Core/Src/callbacks.c), that defines callback functions for button press, uart data received.
Both of them iterate through the already mentioned array with LedControlInfo objects, and, if pressed button or character, sent with uart, equal to ToggleButtonPin/ToggleChar of this object respectively, they toggle this led and send it's info with uart.
The same file also stores a callback function for an ADC read complete, which simply uses GetTemperature and SendTemperature to calculate and send temperature with uart.

## Additional Materials
Capture of the signal trace of the program in execution and video of it's work can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/1WvgExX_pEbaVpuRnxkrR92r-_ukl9fdo?usp=share_link)
