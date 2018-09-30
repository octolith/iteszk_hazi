#include "systemc.h"
#include "counter.h"

int sc_main(int argc, char **argv)
{
	// a "top" modul jelei	
	sc_clock clk("CLK", 1.0, SC_NS);	// orajel generator
	
	// jelek a számláló bekötéséhez
	sc_signal<bool> reset("RESET");
	sc_signal<bool> enable("ENABLE");
	sc_signal< sc_uint<4> > output("COUNT");

	// a számláló példányosítása és bekötése
	counter4 counter("COUNTER");
	// gépelési gyakorlat, mert egyesével kell a jeleket bekötni
	counter.clk(clk);
	counter.reset(reset);
	counter.enable(enable);
	counter.output(output);

	// hullámforma és cout stílusú kimenet generálunk 
	// elõször a hullámforma file megnyitása és konfigurálása
	// megtekinthetõ pl. gtkwave program segítségével
	// http://gtkwave.sourceforge.net/
	// vagy online az EPWave segítségével
	// https://www.edaplayground.com/w
	sc_trace_file *fp;
	fp = sc_create_vcd_trace_file("wave");
	sc_trace(fp, clk, "clk");
	sc_trace(fp, reset, "reset");
	sc_trace(fp, enable, "enable");
	sc_trace(fp, output, "output");

	// itt kezdõdik a szimuláció
	// két órajelnyi reset
	reset = false;
	sc_start(2, SC_NS);
	reset = true;
	// engedélyezzük, majd 19 órajelet pörgetünk
	enable = true;
	sc_start(19, SC_NS);
	// megállunk még 3 órajelre és vége
	enable = false;
	sc_start(3, SC_NS);
	// takaritas
	sc_close_vcd_trace_file(fp);
	return 0;
}