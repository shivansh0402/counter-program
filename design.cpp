#include"systemc.h"
using namespace std;

SC_MODULE(counter)
{
	sc_in<bool> clock;
	sc_in<bool> reset;
	sc_in<bool> enable;
	sc_out<sc_uint <4>> output;
	sc_uint<4> count;

	void increment_count()
	{
		if (reset.read() == 1)
		{
			count = 0;
			output.write(count);
		}
		if (enable.read() == 1)
		{
			count++;
			output.write(count);
			cout << "@ sc_time : " << sc_time_stamp() << "incremented count" << output.read() << endl;
		}
	}
	SC_CTOR(counter)
	{
		SC_METHOD(increment_count);
		sensitive << reset;
		sensitive << clock.pos();
	}
};