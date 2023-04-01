# Bare Metal Training 03: Timers and PWM

## Assignment
1. Need to implement PWM signal generator.
2. Timer4 need to be used (this is mandatory).
3. STM32F407 need to be switched for external clock (HSE).
4. 2 buttons would be used to set signal frequency (up and down; +/- 5 kHz step).
5. 2 buttons would be used to set duty cycle (+/- 5% step each button press).
6. Middle button would be used to select signal output (PD15, PD14, PD13, PD12 or no output (disable case)). Cyclic selection scheme.
   
## [Solution](Core/)
All of those values, which needed to be manipulated, are stored in the struct AppData. Only one object of this structure exists in the program.
```c
typedef struct {
	uint32_t Prescaler;
	uint32_t MaxPrescaler;
	unsigned int Channel;
	uint32_t DutyCycle;
	uint32_t MaxDutyCycle;
	uint8_t NeedsUpdate;
} AppData;
```
InitAppData is used to initialize this object. It sets it's default value. Values like *prescaler*, *channel* and *duty cycle* need to be set explicitly, because they depend on the default values of the program. So, before the main cycle, there is a function call, that looks like this:
```c
InitAppData(htim4.Init.Prescaler, TIM_CHANNEL_1, htim4.Init.Period);
```

Callback function is used for handling button presses. It's definition can be found [here](Core/Src/input_handler.c). According to it:
- left button increases frequency
- right button decreases frequency
- upper button increases duty cycle
- lower button decreases duty cycle
- middle button changes led
Every button changes value it's responsible for, and, additionaly, sets *appData.NeedsUpdate* to be equal 1.

[Main cycle](Core/Src/main.c) does nothing if no button was pressed. That's what *appData.NeedsUpdate* is needed for. After button press interrupt is finished, *appData.NeedsUpdate* becomes 1 and code inside if-statement in the cycle is now can be executed.
```c
while (1)
{
	if(appData.NeedsUpdate)
	{
        // all channels are stopped
	    HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	    HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	    HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
	    HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
        
        // duty cycle is set
	    TIM4->CCR1 = appData.DutyCycle;
	    TIM4->CCR2 = appData.DutyCycle;
	    TIM4->CCR3 = appData.DutyCycle;
	    TIM4->CCR4 = appData.DutyCycle;
        
        // frequency is set
	    TIM4->PSC = appData.Prescaler;
        
        // currently set channel is used
	    HAL_TIM_PWM_Start(&htim4, appData.Channel);
        
        // set 0 for NeedsUpdate value, so this block of code won't execute until next button press
	    appData.NeedsUpdate = 0;
  }
}
```

## Additional Materials
Video of the program in execution can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/1kKU8SKkwdhuA87AMPEAEte3yv_m5To_k?usp=share_link)
