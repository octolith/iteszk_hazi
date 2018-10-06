#pragma once
#include <systemc.h>

SC_MODULE(counter8)
{
	// input portok 
	sc_in<bool>		reset;
	sc_in<bool>		clk;

	// output portok
	sc_out<sc_uint<8> >	seconds;
	sc_out<bool>	tc;

	// az output portok belsõ regiszterei
	sc_uint<8>		count;
	bool			terminalCount;

	void	do_count()
	{
		// alacsony aktiv reset
		if (reset.read() == 0) {
			count = 0;
			terminalCount = false;
		}
		else {
			switch (count) {
			case 58:
				count++;
				terminalCount = true;
				break;
			case 59:
				count = 0;
				terminalCount = false;
				break;
			default:
				count++;
				terminalCount = false;
				break;
			}
		}

		seconds.write(count);
		tc.write(terminalCount);
	}

	// a konstruktorban adjuk meg a mûködést leíró metódust és az érzékenységi listát
	SC_CTOR(counter8)
	{
		SC_METHOD(do_count);
		// az órajel felfutó élére vagy a reset lefutó élére lesz érzékeny
		sensitive << clk.pos() << reset.neg();
	}
};

