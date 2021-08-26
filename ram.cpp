#include "ram.h"
#define ram_BITMASK 0xffffffff

void ram::
ram_thread(void)
{
	sc_uint<16> addr_t;
	sc_uint<16> data_t;
	sc_uint<0x1> w_t;
	sc_uint<0x1> r_t;
	sc_uint<16> data;

	while (true) {

		if (clk.read() == 1) {	// Check that data must be read from mem
			r_t = r.read();
		
			if(r_t == 1) {	// Read word
				addr_t = address.read();
				addr_t = addr_t & ram_BITMASK;

                		// Check that address is word aligned, 
                		// if not issue a warning
				if ((addr_t & 0x3) != 0) {
					cout << "WARNING: memory address ("; 
					cout << addr_t.to_string(SC_HEX);
					cout << ") not word aligned in ";
					cout << "read operation.";
					cout << endl;
				}

				// Word align address
				addr_t = addr_t & ~(0x3);
				if (addr_t < 128) {	
					data = 0;
					for (int i = 0; i < (16 / 8); i++) {
						data = data << 8;
						data_t = ramfile[addr_t + i];
						data = data | data_t; 
					}
					d_read.write(data);
				}
			} else if(r_t == 2) {	// Read byte
				addr_t = address.read();
				addr_t = addr_t & ram_BITMASK;

				if (addr_t < 128) {	
					data = 0;
					for (int i = 0; i < (16 / 8); i++) {
						data = data << 8;
						data_t = ramfile[addr_t + i];
						data = data | data_t; 
					}
					d_read.write(data);
				}
			}
		}
		if (clk.read() == 0) {	// Check that data must be written to mem
			w_t = w.read();

			if(w_t == 1) {	// write word to ram
				addr_t = address.read();
				addr_t = addr_t & ram_BITMASK;

				// Check that address is word aligned, 
				// if not issue a warning
				if ((addr_t & 0x3) != 0) {
					cout << "WARNING: memory address ("; 
					cout << addr_t.to_string(SC_HEX);
					cout << ") not word aligned in ";
					cout << "write operation.";
					cout << endl;
				}

				// Word align address
				addr_t = addr_t & ~(0x3);

				data = d_write.read();

				if (addr_t < 128) {
					for (int i = (16 / 8); i > 0; i--) {
						ramfile[addr_t + i - 1] = 
							data & 0xff;
						data = data >> 8;
					}
				} else {
					cout << "WARNING: writting to invalid ";
					cout << "memory location. (";
					cout << addr_t << ")" << endl;
				}
 			} else if (w_t == 2) {	// write byte to ram
				addr_t = address.read();
				addr_t = addr_t & ram_BITMASK;
				data = d_write.read();
				if (addr_t < 128) {
					ramfile[addr_t] = data & 0xff;
				} else {
					cout << "WARNING: writting to invalid ";
					cout << "memory location. (";
					cout << addr_t << ")" << endl;
				}		
			} 
		}
        	wait();
	}
}

void
ram::
ram_init(const char *filename)
{
	sc_uint<16> word;
	sc_uint<16> addr = 0;
	int c;

	ifstream ramf(filename, ios::in | ios::binary);

	while (!ramf.eof()) {
		word = 0;

		c = ramf.get();
                if (c==-1) 
			break;

		word = c;

		ramfile[addr] = word;
		addr++;

		if (addr >= 128)
			break;
	}
}

void
ram::
ram_dump(const char *filename)
{
	ofstream ramf(filename, ios::out | ios::binary);
	char c;
	sc_uint<8> a;

	for (unsigned int i = 0; i < 128; i++) {
		a = ramfile[i];
		c = a;
		ramf.put(c);
	}
	
	ramf.close();
}
