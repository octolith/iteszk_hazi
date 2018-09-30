#include "systemc.h"
#include "counter.h"

int sc_main(int argc, char **argv)
{
	// a "top" modul jelei	
	sc_clock clk("CLK", 1.0, SC_NS);	// orajel generator
	
	// jelek a sz�ml�l� bek�t�s�hez
	sc_signal<bool> reset("RESET");
	sc_signal<bool> enable("ENABLE");
	sc_signal< sc_uint<4> > output("COUNT");

	// a sz�ml�l� p�ld�nyos�t�sa �s bek�t�se
	counter4 counter("COUNTER");
	// g�pel�si gyakorlat, mert egyes�vel kell a jeleket bek�tni
	counter.clk(clk);
	counter.reset(reset);
	counter.enable(enable);
	counter.output(output);

	// hull�mforma �s cout st�lus� kimenet gener�lunk 
	// el�sz�r a hull�mforma file megnyit�sa �s konfigur�l�sa
	// megtekinthet� pl. gtkwave program seg�ts�g�vel
	// http://gtkwave.sourceforge.net/
	// vagy online az EPWave seg�ts�g�vel
	// https://www.edaplayground.com/w
	sc_trace_file *fp;
	fp = sc_create_vcd_trace_file("wave");
	sc_trace(fp, clk, "clk");
	sc_trace(fp, reset, "reset");
	sc_trace(fp, enable, "enable");
	sc_trace(fp, output, "output");

	// itt kezd�dik a szimul�ci�
	// k�t �rajelnyi reset
	reset = false;
	sc_start(2, SC_NS);
	reset = true;
	// enged�lyezz�k, majd 19 �rajelet p�rget�nk
	enable = true;
	sc_start(19, SC_NS);
	// meg�llunk m�g 3 �rajelre �s v�ge
	enable = false;
	sc_start(3, SC_NS);
	// takaritas
	sc_close_vcd_trace_file(fp);
	return 0;
}