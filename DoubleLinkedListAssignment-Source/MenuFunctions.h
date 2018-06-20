#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

void PrintMenu();

// gets input from keyboard and convert to integer
int getInputValAsInt(int *errstatus);

// gets menu choice with protection of values
int getMenuChoice(int *errstatus);

//flushes buffer and wait for getchar to resume
void PressEnterToContinue();

//Carry out choice from user input
void carryOutChoice(HEADER* head, int choice);

#endif /* MENUFUNCTIONS_H */
