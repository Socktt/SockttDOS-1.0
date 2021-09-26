#include "vga.h"
#include "typeDef.h"
#include "system.h"

#define BUFFER_LEN 256	// Length of input buffer

unsigned char kbdus[128] =
{
		0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
		0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
		0,	/* Alt */
	' ',	/* Space bar */
		0,	/* Caps lock */
		0,	/* 59 - F1 key ... > */
		0,   0,   0,   0,   0,   0,   0,   0,
		0,	/* < ... F10 */
		0,	/* 69 - Num lock*/
		0,	/* Scroll Lock */
		0,	/* Home key */
		0,	/* Up Arrow */
		0,	/* Page Up */
	'-',
		0,	/* Left Arrow */
		0,
		0,	/* Right Arrow */
	'+',
		0,	/* 79 - End key*/
		0,	/* Down Arrow */
		0,	/* Page Down */
		0,	/* Insert Key */
		0,	/* Delete Key */
		0,   0,   0,
		0,	/* F11 Key */
		0,	/* F12 Key */
		0,	/* All other keys are undefined */
};

char InputBuffer[BUFFER_LEN]; 								// Buffer to store input string
uint8_t BufferIndex = 0;									// Index of string buffer

void * callbackArrayKeyboardInput[256];						// Callback array to store function pointers to be called on input
uint8_t callbackArrayKeyboardInputIndex = 0;				// Index of callback array

/*
Called on press of enter key, used to process string entered and figure out what to do with it
*/
void processInputString()
{
	for (uint8_t i = 0; i < 256; i++)
	{
		if (callbackArrayKeyboardInput[i] == 0)				// Checks if a function is on the callback array or if its just blank space
		{
			break;
		}
		void (*callbackFuntion) (char InputBuffer[]);		// Make blank function
		callbackFuntion = callbackArrayKeyboardInput[i];	// Set blank function to the function pointer in the array
		callbackFuntion(InputBuffer);						// Call the function
	}
	memset(InputBuffer, 0, BUFFER_LEN);						// Clear input buffer
	BufferIndex = 0;										// Reset buffer index
	return;
}

/*
Adds a function to the callback array for keyboard input.
*/
void * addFunctionToCallbackArray(void * functionPointer)
{
	callbackArrayKeyboardInput[callbackArrayKeyboardInputIndex] = functionPointer;
	callbackArrayKeyboardInputIndex++;
	return functionPointer;
}

/*
Removes the last function from the callback array for keyboard input, functions like the pop command in assembly
*/
void * removeLastFuntionFromCallbackArray()
{
	callbackArrayKeyboardInputIndex--;
	void * functionPointer = callbackArrayKeyboardInput[callbackArrayKeyboardInputIndex];
	callbackArrayKeyboardInput[callbackArrayKeyboardInputIndex] = 0;
	return functionPointer;
}

/*
Keyboard handler, attached to interrupt 1
*/
void keyboard_handler(struct regs *r)
{
	unsigned char Scancode;									// Input Scancode

	Scancode = inb(0x60);									// Read from keyboard to get pressed key

	if (!(Scancode & 0x80))									// Check if key pressed is a down key or if it is a key being released
	{
		if (kbdus[Scancode] == '\n')						// Check if new like (aka enter)
		{
			processInputString();							// Process the input string when enter is pressed
		}
		else
		{
			putCh(kbdus[Scancode]);
			if (BufferIndex > BUFFER_LEN)
			{
				processInputString();
			}
			InputBuffer[BufferIndex] = kbdus[Scancode];		// append character to input buffer
			BufferIndex++;
		}
	}
}

/*
Installs the keyboard handler, attaches to interrupt 1
*/
void keyboard_install()
{
		irq_install_handler(1, keyboard_handler);
}