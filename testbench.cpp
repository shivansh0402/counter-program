#include "systemc.h"
#include "design.cpp"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool>   clock;
    sc_signal<bool>   reset;
    sc_signal<bool>   enable;
    sc_signal<sc_uint<4> > output;
    int i = 0;
   
    T
    counter c1("COUNTER");
    c1.clock(clock);
    c1.reset(reset);
    c1.enable(enable);
    c1.output(output);

    sc_start(1, SC_NS);

   
    sc_trace_file* t = sc_create_vcd_trace_file("wavwform");
    
    sc_trace(t, clock, "clock");
    sc_trace(t, reset, "reset");
    sc_trace(t, enable, "enable");
    sc_trace(t, output, "count");

   
    reset = 0;      
    enable = 0;    
    for (i = 0;i < 5;i++) {
        clock = 0;
        sc_start(1, SC_NS);
        clock = 1;
        sc_start(1, SC_NS);
    }
    reset = 1;   
    cout << "@" << sc_time_stamp() << " Asserting reset\n" << endl;
    for (i = 0;i < 10;i++) {
        clock = 0;
        sc_start(1, SC_NS);
        clock = 1;
        sc_start(1, SC_NS);
    }
    reset = 0;    
    cout << "@" << sc_time_stamp() << " De-Asserting reset\n" << endl;
    for (i = 0;i < 5;i++) {
        clock = 0;
        sc_start(1, SC_NS);
        clock = 1;
        sc_start(1, SC_NS);
    }
    cout << "@" << sc_time_stamp() << " Asserting Enable\n" << endl;
    enable = 1; 
    for (i = 0;i < 20;i++) {
        clock = 0;
        sc_start(1, SC_NS);
        clock = 1;
        sc_start(1, SC_NS);
    }
    cout << "@" << sc_time_stamp() << " De-Asserting Enable\n" << endl;
    enable = 0; 

    cout << "@" << sc_time_stamp() << " Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(t);
    return 0;

}
