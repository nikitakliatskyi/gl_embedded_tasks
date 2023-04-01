# Bare Metal Training 02: LEDs, Buttons, Interrupts.

## Assignment
1. Need to implement at least 3 blinking schemes for all 4 LEDs on the board.
2. 2 buttons would be used to select scheme (next one, previous one).
3. 2 buttons would be used to select blinking speed (speed up, slow down).
4. Button at the middle of cross should be used to turn on/off blinking.
5. All buttons need to be processed by interrupts.

## [Solution](Core/)
Structure Scheme is used as a query of LEDs. It's elements - pointer *Order* and integer *Size* - make it possible to store and use an array of any size inside this structure object. It's used inside the structure SchemeData. SchemeData can have any amount of Schemes. It also stores other parameters, such as: *Delay* to control blinking speed, *IsTurnedOn* to turn and off blinking, SchemeIndex and LedIndex to change Schemes on button press and iterate through it's leds in the cycle. Only one object of SchemeData exists, it's values are initialized inside InitSchemeData function.
```c
typedef struct {
    uint16_t Size;
    uint16_t *Order;
} Scheme;

typedef struct {
    uint16_t SchemesAmount;
    Scheme *Schemes;
    uint32_t Delay;
    uint8_t IsTurnedOn;
    uint16_t SchemeIndex;
    uint16_t LedIndex;
} SchemeData;
```

There are functions InitSchemeData and DestroySchemeData, used as constructor and destructor of the main SchemeData object. Their definition can be found [here](Core/Src/scheme.c). InitSchemeData sets all of the default values. To set schemes it allocates memory and initialize those schemes with memcpy. The process looks like this:
```c
schemeData.Schemes = (Scheme*)calloc(schemeData.SchemesAmount, sizeof(Scheme));

schemeData.Schemes[0].Size = 4;
schemeData.Schemes[1].Size = 4;
schemeData.Schemes[2].Size = 2;

for(int i = 0; i < schemeData.SchemesAmount; i++)
{
	schemeData.Schemes[i].Order = (uint16_t*)calloc(schemeData.Schemes[i].Size, sizeof(uint16_t));
}
    
// array for a scheme is being created in the stack and it's values are being copied to the schemes, that are located in the heap. This arrays won't take up memory, but their copies are already saved in the scheme
memcpy(schemeData.Schemes[0].Order, (uint16_t []){ GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 }, 4 * sizeof(uint16_t));
memcpy(schemeData.Schemes[1].Order, (uint16_t []){ GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12 }, 4 * sizeof(uint16_t));
memcpy(schemeData.Schemes[2].Order, (uint16_t []){ GPIO_PIN_12|GPIO_PIN_14, GPIO_PIN_13|GPIO_PIN_15 }, 2 * sizeof(uint16_t));
```
Any amount of schemes of any size can be set using this variables. Dynamic memory allocation is the reason for the existence of DestroySchemeData. Memory is freed by iterating through every scheme and freeing it's *orders* (schemes array). In the end it frees array of those schemes. Function also decrements *SchemesAmount*, and not it's copy, so, after *SchemeData* is destroyed, amount of schemes is also going to be 0.
```c
while(schemeData.SchemesAmount) {
	free(schemeData.Schemes[schemeData.SchemesAmount-1].Order);
	schemeData.SchemesAmount--;
}
free(schemeData.Schemes);
```

There is a callback function, needed to handle button presses. It accepts *GPIO_Pin* as it's only parameter. As interrupt occurs, it calls this function, passing pin which represents pressed button. The function makes certain actions depending on the value passed into it.
Function implementation can be found [here](Core/Src/scheme_control_buttons_handler.c). In short:
- PC11 (right button) accelerates blinking speed
- PC9 (left button) slows down blinking speed
- PC6 (upper button) choose next scheme
- PC8 (lower button) choose previous scheme
- PA15 (middle button) is used to toggle blinking
Each button press simply changes the value it's responsible for.

[Main](Core/Src/main.c) function calls InitSchemeData before main cycle, and DestroySchemeData after. Cycle itself, if blinking is turned on, turns on and off LEDs, that are meant to be blinking in this iteration. It uses values of *schemeData* as current LEDs and delay between turning on and off. On each iteration it sets next LED of queue as current and first, if the last LED of queue was current in the iteration.
```c
 while (1)
{
  if(schemeData.IsTurnedOn)
  {
	HAL_GPIO_WritePin(GPIOD, schemeData.Schemes[schemeData.SchemeIndex].Order[schemeData.LedIndex], GPIO_PIN_SET);
	HAL_Delay(schemeData.Delay);
	HAL_GPIO_WritePin(GPIOD, schemeData.Schemes[schemeData.SchemeIndex].Order[schemeData.LedIndex], GPIO_PIN_RESET);
	schemeData.LedIndex++;
	schemeData.LedIndex %= schemeData.Schemes[schemeData.SchemeIndex].Size;
  }
}
```
Values change right after interrupt finishes, meaning even if a button was pressed before iteration finished, it starts using updated values from the moment button was pressed.

## Additional Materials
Video of the program in execution can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/14SK4sr8kpaA1hRTGKvtYQE5u56KCLYzZ?usp=share_link)
