# Bare Metal Training 04: ADC TempSensor

## Assignment
1. Need to read voltage from potentiometer (connect it to IN3 channel). Show voltage with help of BLUE led (light intensity change). Too high voltage needs to be indicated with RED led (see p.4).
2. Need to read temperature from internal temperature sensor (inside STM32F407). Show temperature with help of ORANGE led (light intensity change). Too high temperature needs to be indicated with RED led (see p.4).
3. Need to read temperature from external analog temperature sensor (present at GL board). Show temperature with help of GREEN led (light intensity change). Too high temperature needs to be indicated with RED led (see p.4).
4. RED led should be turned off if no “emergency citation” present (see p.1,2,3 “too high cases”). It should bling with 1Hz frequency if we have “one emergency situation”, it should blink with 2.5Hz frequency for case when we have 2 “emergency situations” at the same time. And 5Hz – if all 3 “emergencies” present.

## [Solution](Core/)
Structure Emergencies is used to store data of which emergencies are present (each field represents certain emergency it's named after). Only one structure exists during the program.
```c
typedef struct {
	volatile uint32_t VoltageIsHigh : 1;
	volatile uint32_t InTempIsHigh : 1;
	volatile uint32_t ExTempIsHigh : 1;
} Emergencies;
```
There are also some variables used.
```c
const uint32_t red_led_freq_states[MAX_EMERGENCIES_AMNT] = { 1, 2.5, 5 }; // stores dividers for red led frequency so it could be 5Hz, 2.5Hz and 1Hz depending on emergencies amount
volatile uint32_t adc_values[MAX_EMERGENCIES_AMNT]; // buffer to store values from adc
volatile uint32_t current_emergencies_amnt = 0; // to store amount of present emergencies
```
Function *UpdateEmergencies* is used to update information about current emergencies is used. It's implementation can be found [here](Core/Src/app_data.c)

All the main logic of the program, which is described below, is located [here](Core/Src/main.c).

Function *HandleRedLight* simply toggles red led state with delay = 500 / *red led freq states array[current emergencies amount]*, so, when there are 3 emergencies, delay == 500 / 5 == 100ms (5 full blink cycles per second == 5Hz), 500 / 2.5 == 200ms (2.5 full blink cycles per second == 2.5Hz) in the case of two, and 500 / 1 == 500ms (1 full blink cycle per second == 1Hz) in the case of 1. It's also doesn't blink at all if no emergencies present.
It's being called in the main loop of the program.

There is a code before main loop, that starts a timer for green, orange and blue leds.
```c
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
```
Next line starts ADC in DMA mode and sets adc to use, buffer for values and space of the buffer, that's meant for values ADC returns.
```c
HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, adc_values_amount);
```

ADC callback, that is called every time ADC has read values it is set up to read, calls *UpdateEmergencies*, passing read values, emergencies structure to update it and emergencies amount variable to store this amount there. Then it sets duty cycle of green, orange and blue led depending on emergencies that are currently present.

## Additional Materials
Video of the program in execution can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/1soJVGMDn1IEcnw3ZYTjPV-7SKdtxIARp?usp=share_link)
