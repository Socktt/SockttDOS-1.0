/*
SockttDOS Prompt
Copyright Sockttsoft 2021
Made by Socktt & Holden
*/

#include "vga.h"
#include "kb.h"
#include "system.h"
#include "typeDef.h"

void tokenize(InputArray)
{

    return;
}

/*
Called in kb.c whenever the enter key is pressed. InputArray = char array of the input string
*/
void parseInput(char InputArray[])
{
    putCh(10);
    print(InputArray);
    if(!strcmp(InputArray, "hello"))
    {
        print("\nHi Holden\n");
    }
    else if(!strcmp(InputArray, "spacequacker"))
    {
        print("\nHolden is amazing and beautiful\n");
    }
    putCh(10);                                  // New line
    promptDisplayInputField();                  // Display prompt
    return;
}

/*
IDK felt like the right thing to do - me too
*/
void promptDisplayInputField()
{
    print("$ ");
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