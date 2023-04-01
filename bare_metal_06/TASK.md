# Bare Metal Training 06: I2C

## Assignment
1. Need to create library that will work with PWM LED controller (PCA9685).
We need a way to enable/disable all outputs, set duty cycle, set PWM frequency, enable/disable sleep mode.
LED controller functionality should be moved to separate *.c file.
All public function prototypes (API) should be provided by *.h file.
2. I2C1 channel should be used to communicate with LED controller. SCK = 50 kHz (check frequency with signal analyzer see p. 5).
3. Functional testing should be made with help of PC (UART console) – send commands / receive status.
   
## [Solution](Core/)
Library is split into [api](Core/Inc/pwmctl_api.h), [client base](Core/Inc/pwmctl_client_functions.h) and [uart client](Core/Inc/pwmctl_uart_client.h).

Api has defines for each register and flag. It also has function *Init* for initializing i2c interface that will be used for communication with controlled, and *Set*, which sets passed flags and values to register using i2c. Values for the function can be connected with bitwise OR operation ('|'), and !~ can be used for reverse effect. Both functions are defined in [this file](Core/Src/pwmctl_api.c)
Usage looks like that:
```c
PWMCTL_Set(PWMCTL_REG_MODE1, status == ENABLED ? PWMCTL_FLAG_MODE1_SLEEP : PWMCTL_FLAG_MODE1_DEFAULT&~PWMCTL_FLAG_MODE1_SLEEP);
```
Here sleep mode will be turned on and of depending on the value assigned to *status*. This will later be used in client functions.

Client function are defined [here](Core/Src/pwmctl_client_functions.c). There are 4 functions implemented for those functionality, that is described in the assignment:
- *Set_All_Leds_Status*
- *Set_Duty_Cycle*
- *Set_Frequency*
- *Set_Sleep_Mode_Status*
They change controller's registers values and additionaly store these values in static variables. Additional function *Get_Data* is used to get copies of these variables (this way they are incapsulated).

UART Client is a UART implementation of client with UI, that uses this library. It's implementation can be found [here](Core/Src/pwmctl_uart_client.c). It has only 2 public functions:
- *Client_Init* - used for setting uart interface that will later be used
- *Start_Session* - to call only one session (wait for only one command from UART)

There are some functions, that aren't accessible outside source file of the UART client, such as:
- *Print_Output* to transmit string with UART
- *Set_Output* to set string, that will be transmitted with the next call of *Print_Output*
- *Read_Input* to request operation of receiving data from UART and wait until it's received (implemented by overloading UART receivement callback to set the special flag to 1 when data is received, and calling loop with only one exit condition - user input is received)
- *Generate_Status_Message* to set output to formatted string with data, that's got from *CLIENT_Get_Data* function, this is the status that'll be printed after every change.

*Start_Session* uses previously these function in this algorithm(following code is the brief version of original):
```c
HAL_StatusTypeDef result;

// print menu
Set_Output(_menu_msg);
result = Print_Output();
if(result != HAL_OK)
{
	return result;
}

// get the option user chooses
result = Read_Input(1);

// if option was successfully chosen, execute it
if(result == HAL_OK) {
    // switch-statement to check, which action user choice is responsible for
	switch(_input_buf[0]) {
        // toggle leds
		case '1':
			PWMCTL_CLIENT_Set_All_Leds_Status(ENABLED);
			break;
		case '2':
			PWMCTL_CLIENT_Set_All_Leds_Status(DISABLED);
			break;

        //set duty cycle (which user has to enter)
		case '3':
			Set_Output("Enter new duty cycle: ");
			Print_Output();
			Read_Input(3);
			PWMCTL_CLIENT_Set_Duty_Cycle(atoi(_input_buf));
			break;

        //set frequency (which user has to enter)
		case '4':
			Set_Output("Enter new frequency: ");
			Print_Output();
			Read_Input(4);
			PWMCTL_CLIENT_Set_Frequency(atoi(_input_buf));
			break;
            
        // toggle sleep mode
		case '5':
			PWMCTL_CLIENT_Set_Sleep_Mode_Status(ENABLED);
			break;
		case '6':
			PWMCTL_CLIENT_Set_Sleep_Mode_Status(DISABLED);
			break;
            
        // incorrect input case
		default:
		Set_Output("Incorrect user input\n\r");
		Print_Output();
		return HAL_ERROR;
		break;
    }
}

// Printing status message if session is successful
Generate_Status_Message();
result = Print_Output();
```

Usage example can be found [here](Core/Src/main.c) and looks like this: 
```c
PWMCTL_Init(&hi2c1);
PWMCTL_UART_Client_Init(&huart3);

while (1)
{
  PWMCTL_UART_Start_Session();
}
```

## Additional Materials
Capture of the signal trace of the program in execution and screenshots can be found here:
[Google Drive Folder With Additional Materials](https://drive.google.com/drive/folders/1CB5wJMLiPjn8TY64PBcKrBWYUuPAKrq8?usp=share_link)
