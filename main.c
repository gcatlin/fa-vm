#include <stdbool.h>
#include <stdio.h> // printf

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum {
   A, B, C, D, E, F,
   IP, SP,
   NUM_REGISTERS
} Registers;

#define ip (registers[IP]) // Instruction pointer
#define sp (registers[SP]) // Stack pointer

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

// int ip = 0; // instruction pointer
// int sp = -1;
int stack[256];
int registers[NUM_REGISTERS];

bool running = true;

int fetch() {
    return program[ip];
}

void eval(int instr) {
    int x, y;
    switch (instr) {
        case ADD:
            y = stack[sp--];
            x = stack[sp--];
            stack[++sp] = x + y;
            break;
        case PSH:
            stack[++sp] = program[++ip];
            break;
        case POP:
            x = stack[sp--];
            printf("POP: %d\n", x);
            break;
        case HLT:
            running = false;
            break;
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++; // increment instruction pointer
    }
}
