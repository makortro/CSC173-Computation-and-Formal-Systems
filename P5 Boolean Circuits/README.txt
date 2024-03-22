Project 5 - Boolean Circuits
MaKayla Robinson - mrobin45
4/20/22


I did not collaborate with anyone on this project.


To build the project type
        make


To run type
        ./boosim


To get rid of the .o files if you need to run again type
        make clean


The program prints which circuit is being tested, the translation from boolean circuit to logical statement (or boolean function to logical statement for extra credit), the truth table (or boolean function table for extra credit), then it will tell you which functions it’s sending to (the first is the function name for the appropriate circuit, the second is the appropriate test/print function), then it will print the results. Everything is automated, so you just have to run the program.


To handle the NAND and NOR expressions, I used inverted gates before or after passing them through the AND/OR gates.


I implemented extra credit part 1, which you’ll find at the end of the program.


I added these functions inside the main.c file:
static Circuit* circuit_A();
static Circuit* circuit_B();
static Circuit* circuit_C();
static Circuit* circuit_FG(); //extra credit circuit
static void test2In1Out(Circuit* circuit, bool in0, bool in1);
static void test3In2Out(Circuit* circuit, bool in0, bool in1, bool in2);
static void test2Inputs1Output(Circuit* c);
static void test3Inputs1Output(Circuit* c);
static void test3Inputs2Outputs(Circuit* c);