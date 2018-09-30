/****************************************************
 Egy 4 bites felfele számláló System-C modellje
 bemenetek: clk, reset, enable
 kimenetek: q(4)
****************************************************/
#pragma once
#include <systemc.h>

SC_MODULE(counter4) // az SC_MODULE makró az sc_module osztályból származtat
{
	// a portok az osztály belsõ változói lesznek
	// digitális jelet szimplán a bool adattípussal, 
	// n bites elõjel nélküli számot az sc_uint<> template
	// használatával modellezünk

	// input portok 
	sc_in<bool>		reset;
	sc_in<bool>		enable;
	sc_in<bool>		clk;

	// output port - 4 bites kimenet 
	sc_out<sc_uint<4> >	output;

	// az output port belsõ regisztere
	// magán a porton csak a write mûvelet értelmezett
	// a tárolást belsõ változókkal kell megoldani.
	sc_uint<4>		count;

	// itt írjuk meg a valódi mûködést. A metódus neve tetszõleges, a do_foobar szokásjog
	void	do_count()
	{
		// alacsony aktiv reset
		if (reset.read() == 0) 
			count = 0;
		else if (enable == true) // nem kell állandóan kiírni, ez enable.read()-et jelent
			count++;

		output.write(count);
	}

	// a konstruktorban adjuk meg a mûködést leíró metódust
	// és az érzékenységi listát (vö. Verilog always, VHDL PROCESS)
	SC_CTOR(counter4)
	{
		SC_METHOD(do_count);
		// az órajel felfutó élére vagy a reset lefutó élére lesz érzékeny
		sensitive << clk.pos() << reset.neg();	
	}
};

