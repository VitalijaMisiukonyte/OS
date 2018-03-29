//Cia surasysim visas komandas
//Reiketu sukurti dar viena registra - Stack pointeri. Kadangi nusprendem kad darysim su stacku tai jis bus tikrai reikalingas)
public class Commands extends VirtualMachine {
	
	public Commands(Memory m){
		super(m);
	}

	//-----------------Aritmetines komandos------------------------------
	
	//1 - AD(addition)

	//2 - SU (substract)
	protected void su_command(){
		this.R1 = this.memory.getWord(registers[SP]);
		int r1 = 0;
		registers[SP]--;
		int sp = 0;
		int result = sp - r1;
		registers[SP]++;
		this.memory.setWord(registers[SP]);
	}
	
	//3 - MU(multiply)

	//4 - DV(divide)
	protected void dv_command(){
		this.R1 = this.memory.getWord(registers[SP]);
		int r1 = 0;
		registers[SP]--;
		int sp = 0;
		
		int result = sp / r1;
		registers[SP]++;
		this.memory.setWord(registers[SP]);
	}

	//5 - MD(module)
	
	//------------------Duomenims pasideti skirtos komandos--------------------
	
	//6 - LR(load register)
	//7 - SR(save register)

	//------------------ I/O komandos---------------------------

	//8 - PR(print register)
	//9 - IN(ivesties zodzio rasymas i adresa)

	//-------------------Valdymo perdavimo komandos-------------------------
	
	//10 - JP(jump)
	//11 - JT(jump if true)
	//12 - JM
	//13 - JL
	//14 - JE(jump if equal)
	//15 - STRT(start)
	//16 - END
	//17 - HALT

	//--------------------Palyginimo komandos-----------------------------

	//18 - CR(compare)
	//19 - EQ(equal)

	//------------------------Stekines komanos(pushai, popai)---------------

}
Labas rytas
