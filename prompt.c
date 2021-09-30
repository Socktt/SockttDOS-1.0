/*
SockttDOS Prompt
Copyright Sockttsoft 2021
Made by Socktt
*/

#include "vga.h"
#include "kb.h"
#include "system.h"
#include "typeDef.h"

/*
Called in kb.c whenever the enter key is pressed. InputArray = char array of the input string
*/
void parseInput(char InputArray[])
{
    if(!strcmp(InputArray, "hello"))
    {
        print("\nHi Holden\n");
    }
    putCh(10);                                  // New line
    promptDisplayInputField();                  // Display prompt
    return;
}

/*
IDK felt like the right thing to do
*/
void promptDisplayInputField()
{
    print(">> ");
    return;
}

/*
Initialize the prompt.
*/
void promptInit()
{
    promptDisplayInputField();
    addFunctionToCallbackArray(parseInput);
}