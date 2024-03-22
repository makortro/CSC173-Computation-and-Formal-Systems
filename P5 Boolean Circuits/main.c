/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Tue Jul 17 16:02:29 EDT 2018 ferguson>
 * 
 * Modified by: MaKayla Robinson - mrobin45
 * Date: 4/17/22
 * Purpose: to fit project 5 prompt
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/*** Header calls for methods I added ***/
static Circuit* circuit_A();
static Circuit* circuit_B();
static Circuit* circuit_C();
static Circuit* circuit_FG(); //extra credit circuit
static void test2In1Out(Circuit* circuit, bool in0, bool in1);
static void test3In2Out(Circuit* circuit, bool in0, bool in1, bool in2);
static void test2Inputs1Output(Circuit* c);
static void test3Inputs1Output(Circuit* c);
static void test3Inputs2Outputs(Circuit* c);

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* and3_Circuit() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_AndGate();
	Gate* A2 = new_AndGate();
	Gate** gates = new_Gate_array(2);
	gates[0] = A1;
	gates[1] = A2;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 2, gates);
	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, z, Gate_getInput(A2, 1));
	Circuit_connect(circuit, Gate_getOutput(A2), out);
	return circuit;
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

int main(int argc, char **argv) {
	Circuit* circuit = and3_Circuit();
	printf("The and3 circuit (AND of three inputs):\n");
	Circuit_dump(circuit);
	printf("\n");
	printf("Testing: Some input(s) false: should be false\n");
	test3In1Out(circuit, true, true, false);
	printf("Testing: All inputs true: should be true\n");
	test3In1Out(circuit, true, true, true);
	printf("Note: Your program needs to test all possible combinations of input values,\nin order from all false to all true, using a single function.\n");
	Circuit_free(circuit);

	/*
	 * a) (x AND (NOT y)) OR ((NOT x) AND y) ~~~ x(-y) + (-x)y
	 * b) NOT((NOT(x AND y)) AND (NOT(x AND y))) ~~~ -(-(xy)-(xy))
	 * c) ((x AND y) OR (x AND z)) OR (y AND z) ~~~ (xy + xz) + yz
	*/
	printf("\n\n===== CIRCUIT A =====\n\n");
	printf("Translation from boolean circuit to logical statement:\n");
	printf("\t(x AND (NOT y)) OR ((NOT x) AND y)\n");
	printf("Truth table:\n");
	printf("\tx\ty\t-x\t-y\tx(-y)\t(-x)y\tx(-y)+(-x)y\n");
	printf("\t-----------------------------------------------------------\n");
	printf("\tf\tf\tt\tt\tf\tf\tf\n");
	printf("\tf\tt\tt\tf\tf\tt\tt\n");
	printf("\tt\tf\tf\tt\tt\tf\tt\n");
	printf("\tt\tt\tf\tf\tf\tf\tf\n");
	printf("Sending to circuit_A() to create circuit...\n");
	Circuit* a = circuit_A();
	printf("Sending to test2Inputs1Output() to test x, y inputs...\n");
	printf("x y -> x(-y)+(-x)y\n");
	printf("------------------\n");
	test2Inputs1Output(a);
	
	printf("\n\n===== CIRCUIT B =====\n\n");
	printf("Translation from boolean circuit to logical statement:\n");
	printf("\tNOT((NOT(x AND y)) AND (NOT(x AND y)))\n");
	printf("Truth table:\n");
	printf("\tx\ty\txy\t-(xy)\t-(xy)\t-(xy)-(xy)\t-(-(xy)-(xy))\n");
	printf("\t---------------------------------------------------------------------\n");
	printf("\tf\tf\tf\tt\tt\tt\t\tf\n");
	printf("\tf\tt\tf\tt\tt\tt\t\tf\n");
	printf("\tt\tf\tf\tt\tt\tt\t\tf\n");
	printf("\tt\tt\tt\tf\tf\tf\t\tt\n");
	printf("Sending to circuit_B() to create circuit...\n");
	Circuit* b = circuit_B();
	printf("Sending to test2Inputs1Output() to test x, y inputs...\n");
	printf("x y -> -(-(xy)-(xy))\n");
	printf("--------------------\n");
	test2Inputs1Output(b);
	
	printf("\n\n===== CIRCUIT C =====\n\n");
	printf("Translation from boolean circuit to logical statement...\n");
	printf("\t((x AND y) OR (x AND z)) OR (y AND z)\n");
	printf("Truth table...\n");
	printf("\tx\ty\tz\txy\txz\tyz\t(xy+xz)\t(xy+xz)+yz\n");
	printf("\t------------------------------------------------------------------\n");
	printf("\tf\tf\tf\tf\tf\tf\tf\tf\n");
	printf("\tf\tf\tt\tf\tf\tf\tf\tf\n");
	printf("\tf\tt\tf\tf\tf\tf\tf\tf\n");
	printf("\tf\tt\tt\tf\tf\tt\tf\tt\n");
	printf("\tt\tf\tf\tf\tf\tf\tf\tf\n");
	printf("\tt\tf\tt\tf\tt\tf\tt\tt\n");
	printf("\tt\tt\tf\tt\tf\tf\tt\tt\n");
	printf("\tt\tt\tt\tt\tt\tt\tt\tt\n");
	printf("Sending to circuit_C() to create circuit...\n");
	Circuit* c = circuit_C();
	printf("Sending to test3Inputs1Output() to test x, y, z inputs...\n");
	printf("x y z -> (xy+xz)+yz\n");
	printf("-------------------\n");
	test3Inputs1Output(c);

	printf("\n\n===== EXTRA CREDIT PART 1 =====");
	printf("\n======== CIRCUIT F & G ========\n\n");
	printf("Translation from boolean function to logical statement...\n");
	printf("\tf: NOT(a AND b) OR (NOT(a AND C) AND b) OR NOT(b AND c)\n\t[shorthand: -(ab) + -(ac)b + -(bc)]\n");
	printf("\tg: NOT(a AND b AND c) OR ((NOT a) AND b AND c) OR (a AND (NOT b) AND c) OR (a AND b AND (NOT c))\n\t[shorthand: -(abc) + -(a)bc + -(b)ac + -(c)ab]\n");
	printf("Boolean Function...\n");
	printf("\tx\ty\tz\t|\tf\tg\n");
	printf("\t------------------------------------------\n");
	printf("\t0\t0\t0\t|\t1\t1\n");
	printf("\t0\t0\t1\t|\t1\t0\n");
	printf("\t0\t1\t0\t|\t1\t0\n");
	printf("\t0\t1\t1\t|\t0\t1\n");
	printf("\t1\t0\t0\t|\t1\t0\n");
	printf("\t1\t0\t1\t|\t0\t1\n");
	printf("\t1\t1\t0\t|\t0\t1\n");
	printf("\t1\t1\t1\t|\t0\t0\n");
	printf("Sending to circuit_FG() to create circuit...\n");
	Circuit* fg = circuit_FG();
	printf("Sending to test3Inputs2Outputs() to test a, b, c inputs...\n");
	printf("a b c -> f | g\n");
	printf("--------------\n");
	test3Inputs2Outputs(fg);
	printf("\n\n");
}

/*** Following methods created/added by MaKayla Robinson ***/

/**
 * a) (x AND (NOT y)) OR ((NOT x) AND y) ~~~ x(-y) + (-x)y
 * 			x		y
 * 			| \	  / |
 * 			|  NOT	|
 * 			|  / \	|
 * 			| /   \ |
 * 		   AND	   AND
 * 			|		|
 * 			  \   /
 *			   OR 
 *				|
 * truth table...
 * 	x	y	-x	-y	x(-y)	(-x)y	x(-y)+(-x)y
 * 	f	f	t	t	f		f		f
 * 	f	t	t	f	f		t		t
 * 	t	f	f	t	t		f		t
 * 	t	t	f	f	f		f		f
 */	
static Circuit* circuit_A() {
	// initialize input values
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(2);
	inputs[0] = x;
	inputs[1] = y;

	// output
	Boolean* out = new_Boolean(false);
	Boolean** output = new_Boolean_array(1);
	output[0] = out;

	// initialize gates
	Gate* notX = new_Inverter();
	Gate* notY = new_Inverter();
	Gate* andXnotY = new_AndGate();
	Gate* andYnotX = new_AndGate();
	Gate* or = new_OrGate();
	Gate** gates = new_Gate_array(5);
	gates[0] = notX;
	gates[1] = notY;
	gates[2] = andXnotY;
	gates[3] = andYnotX;
	gates[4] = or;
	
	// circuit connections
	Circuit* c = new_Circuit(2, inputs, 1, output, 5, gates);
	Circuit_connect(c, x, Gate_getInput(notX, 0));
	Circuit_connect(c, y, Gate_getInput(notY, 0));
	Circuit_connect(c, x, Gate_getInput(andXnotY, 0));
	Circuit_connect(c, y, Gate_getInput(andYnotX, 0));
	Circuit_connect(c, Gate_getOutput(notY), Gate_getInput(andXnotY, 1));
	Circuit_connect(c, Gate_getOutput(notX), Gate_getInput(andYnotX, 1));
	Circuit_connect(c, Gate_getOutput(andXnotY), Gate_getInput(or, 0));
	Circuit_connect(c, Gate_getOutput(andYnotX), Gate_getInput(or, 1));
	Circuit_connect(c, Gate_getOutput(or), out);
	
	return c;
}

/**
 * b) NOT((NOT(x AND y)) AND (NOT(x AND y))) ~~~ -(-(xy)-(xy))
 * 			x	   y
 * 			|\	  /|
 * 			| \	 / |
 * 			|  \/  |
 * 			|  /\  |			
 * 		   NAND   NAND
 * 			\		/
 * 			 \	   /
 * 	          \   /
 * 			  NAND
 * 				|
 * truth table...
 * x	y	xy	-(xy)	-(xy) 	-(xy)-(xy)	-(-(xy)-(xy))
 * f	f	f	t		t		t			f
 * f	t	f	t		t		t			f
 * t	f	f	t		t		t			f
 * t	t	t	f		f		f			t
 * 
 * NOTE: xy == -(-(xy)-(xy)), so only 1 gate needed: andXY
 */
static Circuit* circuit_B() {
	// initialize input values
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(2);
	inputs[0] = x;
	inputs[1] = y;

	// output
	Boolean* out = new_Boolean(false);
	Boolean** output = new_Boolean_array(1);
	output[0] = out;

	// initialize gates
	Gate* andXY = new_AndGate(x, y);	
	Gate** gates = new_Gate_array(1);
	gates[0] = andXY;

	// curcuit connections
	Circuit* c = new_Circuit(2, inputs, 1, output, 1, gates);
	Circuit_connect(c, x, Gate_getInput(andXY, 0));
	Circuit_connect(c, y, Gate_getInput(andXY, 1));
	Circuit_connect(c, Gate_getOutput(andXY), out);

	return c;
}

/**
 * c) ((x AND y) OR (x AND z)) OR (y AND z) ~~~ (xy + xz) + yz
 * 			x		y		z
 * 			| \	   /\	   /|
 * 			|  \  /  \	  /	|
 * 			|	\/	  \  /	|
 * 			|	/\	   \/	|
 * 			|  /  \	   /\	|
 * 		    AND    AND   AND
 * 			   \  /		  /
 * 				\/		 /
 * 				OR      /
 * 				 \	   /
 * 				  \   /
 * 				   OR
 * 				    |
 * truth table...
 * x	y	z	xy	xz	yz	(xy+xz) (xy+xz)+yz
 * f	f	f	f	f	f	f		f
 * f	f	t	f	f	f	f		f
 * f	t	f	f	f	f	f		f
 * f	t	t	f	f	t	f		t
 * t	f	f	f	f	f	f		f
 * t	f	t	f	t	f	t		t
 * t	t	f	t	f	f	t		t
 * t	t	t	t	t	t	t		t
 */
static Circuit* circuit_C() {
	// initialize input values
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	// output
	Boolean* out = new_Boolean(false);
	Boolean** output = new_Boolean_array(1);
	output[0] = out;

	// initialize gates
	Gate* andXY = new_AndGate();
	Gate* andXZ = new_AndGate();
	Gate* andYZ = new_AndGate();
	Gate* or1 = new_OrGate();
	Gate* or2 = new_OrGate();	
	Gate** gates = new_Gate_array(5);
	gates[0] = andXY;
	gates[1] = andXZ;
	gates[2] = andYZ;
	gates[3] = or1;
	gates[4] = or2;

	// circuit connections
	Circuit* c = new_Circuit(3, inputs, 1, output, 5, gates);
	Circuit_connect(c, x, Gate_getInput(andXY, 0));
	Circuit_connect(c, y, Gate_getInput(andXY, 1));
	Circuit_connect(c, x, Gate_getInput(andXZ, 0));
	Circuit_connect(c, z, Gate_getInput(andXZ, 1));
	Circuit_connect(c, y, Gate_getInput(andYZ, 0));
	Circuit_connect(c, z, Gate_getInput(andYZ, 1));
	Circuit_connect(c, Gate_getOutput(andXY), Gate_getInput(or1, 0));
	Circuit_connect(c, Gate_getOutput(andXZ), Gate_getInput(or1, 1));
	Circuit_connect(c, Gate_getOutput(or1), Gate_getInput(or2, 0));
	Circuit_connect(c, Gate_getOutput(andYZ), Gate_getInput(or2, 1));
	Circuit_connect(c, Gate_getOutput(or2), out);
	
	return c;
}

// f: -(ab) + -(ac)b + -(bc)
// g: -(abc) + -(a)bc + -(b)ac + -(c)ab
static Circuit* circuit_FG() {
	// initialize input values
	Boolean* a = new_Boolean(false);
	Boolean* b = new_Boolean(false);
	Boolean* c = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = a;
	inputs[1] = b;
	inputs[2] = c;

	// output
	Boolean* out1 = new_Boolean(false);
	Boolean* out2 = new_Boolean(false);
	Boolean** output = new_Boolean_array(2);
	output[0] = out1;
	output[1] = out2;

	// initialize gates
	Gate* notA = new_Inverter();
	Gate* notB = new_Inverter();
	Gate* notC = new_Inverter();
	Gate* nandAB = new_AndGate(); //f
	Gate* nandACandB = new_And3Gate(); //f
	Gate* nandBC = new_AndGate(); //f
	Gate* nandABC = new_And3Gate(); //g
	Gate* notAandBC = new_And3Gate(); //g
	Gate* notBandAC = new_And3Gate(); //g
	Gate* notCandAB = new_And3Gate(); //g
	Gate* or1 = new_Or4Gate();
	Gate* or2 = new_Or4Gate();
	Gate** gates = new_Gate_array(12);
	gates[0] = notA;
	gates[1] = notB;
	gates[2] = notC;
	gates[3] = nandAB;
	gates[4] = nandACandB;
	gates[5] = nandBC;
	gates[6] = nandABC;
	gates[7] = notAandBC;
	gates[8] = notBandAC;
	gates[9] = notCandAB;
	gates[10] = or1;
	gates[11] = or2;

	// curcuit connections
	Circuit* circuit = new_Circuit(3, inputs, 2, output, 12, gates);
	// f and g
	Circuit_connect(circuit, a, Gate_getInput(notA, 0));
	Circuit_connect(circuit, b, Gate_getInput(notB, 0)); 
	Circuit_connect(circuit, c, Gate_getInput(notC, 0));
	// f
	Circuit_connect(circuit, Gate_getOutput(notA), Gate_getInput(nandAB, 0));
	Circuit_connect(circuit, Gate_getOutput(notB), Gate_getInput(nandAB, 1));

	Circuit_connect(circuit, Gate_getOutput(notA), Gate_getInput(nandACandB, 0));
	Circuit_connect(circuit, b, Gate_getInput(nandACandB, 1));
	Circuit_connect(circuit, Gate_getOutput(notC), Gate_getInput(nandACandB, 2));

	Circuit_connect(circuit, Gate_getOutput(notB), Gate_getInput(nandBC, 0));
	Circuit_connect(circuit, Gate_getOutput(notC), Gate_getInput(nandBC, 1));

	// g
	Circuit_connect(circuit, Gate_getOutput(notA), Gate_getInput(nandABC, 0));
	Circuit_connect(circuit, Gate_getOutput(notB), Gate_getInput(nandABC, 1));
	Circuit_connect(circuit, Gate_getOutput(notC), Gate_getInput(nandABC, 2));
	
	Circuit_connect(circuit, Gate_getOutput(notA), Gate_getInput(notAandBC, 0));
	Circuit_connect(circuit, b, Gate_getInput(notAandBC, 1));
	Circuit_connect(circuit, c, Gate_getInput(notAandBC, 2));

	Circuit_connect(circuit, a, Gate_getInput(notBandAC, 0));
	Circuit_connect(circuit, Gate_getOutput(notB), Gate_getInput(notBandAC, 1));
	Circuit_connect(circuit, c, Gate_getInput(notBandAC, 2));

	Circuit_connect(circuit, a, Gate_getInput(notCandAB, 0));
	Circuit_connect(circuit, b, Gate_getInput(notCandAB, 1));
	Circuit_connect(circuit, Gate_getOutput(notC), Gate_getInput(notCandAB, 2));

	Circuit_connect(circuit, Gate_getOutput(nandAB), Gate_getInput(or1, 0));
	Circuit_connect(circuit, Gate_getOutput(nandACandB), Gate_getInput(or1, 1));
	Circuit_connect(circuit, Gate_getOutput(nandBC), Gate_getInput(or1, 2));
	Circuit_connect(circuit, Gate_getOutput(or1), out1);

	Circuit_connect(circuit, Gate_getOutput(nandABC), Gate_getInput(or2, 0));
	Circuit_connect(circuit, Gate_getOutput(notAandBC), Gate_getInput(or2, 1));
	Circuit_connect(circuit, Gate_getOutput(notBandAC), Gate_getInput(or2, 2));
	Circuit_connect(circuit, Gate_getOutput(notCandAB), Gate_getInput(or2, 3));
	Circuit_connect(circuit, Gate_getOutput(or2), out2);

	return circuit;
}

/*** INPUT TESTING FUNCTIONS ***/

static void test2In1Out(Circuit* circuit, bool in0, bool in1) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

static void test3In2Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	bool out1 = Circuit_getOutput(circuit, 1);
	printf("%s %s %s -> %s | %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0), b2s(out1));
}

// function takes a 2-input circuit and tests it on all possible combinations of its inputs
static void test2Inputs1Output(Circuit* c) {
	test2In1Out(c, false, false);
	test2In1Out(c, false, true);
	test2In1Out(c, true, false);
	test2In1Out(c, true, true);
}

// function takes a 3-input circuit and tests it on all possible combinations of its inputs
static void test3Inputs1Output(Circuit* c) {
	test3In1Out(c, false, false, false);
	test3In1Out(c, false, false, true);
	test3In1Out(c, false, true, false);
	test3In1Out(c, false, true, true);
	test3In1Out(c, true, false, false);
	test3In1Out(c, true, false, true);
	test3In1Out(c, true, true, false);
	test3In1Out(c, true, true, true);
}

// function takes a 3-input 2-output circuit and tests it on all possible combinations of its inputs
static void test3Inputs2Outputs(Circuit* c) {
	test3In2Out(c, false, false, false);
	test3In2Out(c, false, false, true);
	test3In2Out(c, false, true, false);
	test3In2Out(c, false, true, true);
	test3In2Out(c, true, false, false);
	test3In2Out(c, true, false, true);
	test3In2Out(c, true, true, false);
	test3In2Out(c, true, true, true);
}