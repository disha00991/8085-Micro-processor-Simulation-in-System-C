#include "accumulator.h"
#include "flagreg.h"
#include "ctrlunit.h"
#include "alu.h"
#include "idb.h"
#include "Intersplitter.h"
#include "MDR.h"
#include "temp.h"
#include "register.h"
#include "instreg.h"
#include "ram.h"
sc_main(int argc,char *argv)
{
	char stbuf[256];
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	
	
	
	//data signals
	sc_signal<sc_bv<8> > accidb;
	sc_signal<sc_bv<8> > accalu;
	sc_signal<sc_bv<8> > alutemp;
	sc_signal<sc_bv<8> > aluidb;
	sc_signal<sc_bv<1> > flags;
	sc_signal<sc_bv<1> > flagp;
	sc_signal<sc_bv<1> > flagac;
	sc_signal<sc_bv<1> > flagc;
	sc_signal<sc_bv<1> > flagz;
	sc_signal<sc_bv<8> > tempidb;
	sc_signal<sc_bv<8> > regidb;
	sc_signal<sc_bv<8> > iridb;
	sc_signal<sc_bv<8> > irsplit;
	sc_signal<sc_bv<5> > ctrlsplit;
	sc_signal<sc_bv<8> > mdridb;
	sc_signal<sc_bv<8> > rammdr;
	//control signals
	sc_signal<sc_bv<1> > sigacc;
	sc_signal<sc_bv<1> > sigtemp;
	sc_signal<sc_bv<1> > sigflag;
	sc_signal<sc_bv<1> > sigalu;
	sc_signal<sc_bv<1> > sigsplit;
	sc_signal<sc_bv<1> > sigreg;
	sc_signal<sc_bv<1> > sigir;
	sc_signal<sc_bv<1> > sigs0;
	sc_signal<sc_bv<1> > sigs1;
	sc_signal<sc_bv<1> > sigwr;
	sc_signal<sc_bv<1> > sigrd;
	cerr << "Signals OK";
	
	//object modules
	ACCUMULATOR acc("acc");
	FLAGREG flag("flag");
	CTRL_UNIT ctrl("ctrl");
	ALU alu("alu");
	IDB idb("idb");
	INTERSPLITTER insp("insp");
	MDR mdr("mdr");
	TEMP_REG temp("temp");
	REGISTER reg("reg");
	IR ir("ir");
	ram ram1("ram1");
	sc_clock clk("clock", 20);		// Clock
	cerr << "Modules OK";
	//connections
	
	//ACCUMULATOR
	acc.ctrlsig(sigacc);
	acc.value_to_alu(accalu);
	acc.databus(accidb);
	
	//FLAGREG
	flag.flag[0](flags);
	flag.flag[1](flagz);
	flag.flag[3](flagac);
	flag.flag[5](flagp);
	flag.flag[7](flagc);
	flag.ctrlsig(sigflag);
	
	//CTRL_UNIT
	ctrl.cbyte1(ctrlsplit);
	ctrl.state(clk);
	ctrl.c2bits(ctrlsplit);
	ctrl.c5bits(ctrlsplit);
	ctrl.nextstate(clk);
	ctrl.alusig(sigalu);
	ctrl.accsig(sigacc);
	ctrl.tempsig(sigtemp);
	ctrl.s0(sigs0);
	ctr.s1(sigs1);
	ctrl.rd(sigrd);
	ctrl.wr(sigwr);
	ctrl.flagsig(sigflag);
	ctrl.irsig(sigir);
	ctrl.regsig(sigreg);
	ctrl.inspsig(sigsplit);
	
	//ALU
	alu.acc_in(accalu);
	alu.temp_in(alutemp);
	alu.ctrl_in(sigalu);
	alu.result(aluidb);
	alu.carry(flagc);
	alu.aux_carry(flagac);
	alu.parity(flagp);
	alu.zero(flagz);
	alu.sign(flags);
	
	//IDB
	idb.acc_inout(accidb);
	idb.temp_out(tempidb);
	idb.alu_in(aluidb);
	idb.ir_out(iridb);
	idb.reg_inout(regidb);
	idb.s0(sigs0);
	idb.s1(sigs1);
	idb.mdr_in(mdridb);
	
	//INTERSPLITTER
	insp.inst_in(irsplit);
	insp.byte1(ctrlsplit);
	insp.byte2(ctrlsplit);
	insp.byte3(ctrlsplit);
	insp.5bits(ctrlsplit);
	insp.2bits(ctrlsplit);
	insp.3bit_1(ctrlsplit);
	insp.3bit_2(ctrlsplit);
	
	//MDR
	mdr.mdr_in(rammdr);
	mdr.mdr_out(mdridb);
	
	//TEMP_REG
	temp.idbout(tempidb);
	temp.alu_in(alutemp);
	temp.temp_sig(sigtemp);
	
	//REGISTER
	reg.indata(regidb);
	reg.ctrlsig(sigreg);
	reg.outdata(regidb);
	
	//IR
	inr.irin(iridb);
	inr.irout(irsplit);
	
	//ram
	//ram1.address();
	ram1.d_write(rammdr);
	ram1.w(sigwr);
	ram1.r(sigrd);
	cerr << "Connections OK";
	
	// Initialization
	mem.ram_init("8085.bin");
cerr << "Memory OK";

	// Tracing
	sc_trace_file *tf;
	tf = sc_create_vcd_trace_file("final_project");
cerr << "TraceFile OK";
	sc_trace(tf, clk, "clock");
	sc_trace(tf, accidb, "acc to data bus");
	sc_trace(tf, accalu, "acc to alu");
	sc_trace(tf, alutemp, "alu to temporary");
	sc_trace(tf, aluidb, "alu to data bus");
	sc_trace(tf, flags, "sign flag");
	sc_trace(tf, flagz, "zero flag");
	sc_trace(tf, flagp, "parity flag");
	sc_trace(tf, flagac, "auxillary carry");
	sc_trace(tf, flagc, "carry flag");
	sc_trace(tf, tempidb, "temp to data bus");
	sc_trace(tf, regidb, "register to data bus");
	sc_trace(tf, iridb, "ir to idb");
	sc_trace(tf, irsplit, "ir to splitter");
	sc_trace(tf, ctrlsplit, "ctrl to splitter");
	sc_trace(tf, mdridb, "mdr to idb");
	sc_trace(tf, rammdr, "memory to mdr");
	sc_trace(tf, sigacc, "acc signal");
	sc_trace(tf, sigtemp, "temp signal");
	sc_trace(tf, sigflag, "flag ctrl signal");
	sc_trace(tf, sigalu, "alu signal");
	sc_trace(tf, sigsplit, "splitter signal");
	sc_trace(tf, sigreg, "register signal");
	sc_trace(tf, sigir, "ir signal");
	sc_trace(tf, sigs0, "S0");
	sc_trace(tf, sigs1, "S1");
	sc_trace(tf, sigwr, "write signal");
	sc_trace(tf, sigrd, "read signal");
	
	//Signals
		for (int i = 0; i < 8; i++) 
	{
		sprintf(stbuf, "registers.reg(%d)", i);
		sc_trace(tf, registers.rfile[i], stbuf);
	}

	for (int i = 0; i < 128; i++) //ram size=128 bytes
	{
		sprintf(stbuf, "memory.dmem(%d)", i);
		sc_trace(tf, mem.ramfile[i], stbuf);
	}

cerr << "Tracing OK";

	// Simulation
	int sim_time = 2000;
	//if (argc == 2)
		//sim_time = atoi(argv[1]);

	sc_start(sim_time, SC_NS);
cerr << "Simulation OK";

	sc_close_vcd_trace_file(tf);
	mem.ram_dump("8085.dump");

	return 0;
}

	




