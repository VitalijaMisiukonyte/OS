public class RealMachine{
	private int[] memory = new int[300];
	
	//private int[] = registers;
	//Registers
	private boolean MODE = false;
	private int PTR = 0;
	private int VM = 0;
	
	private int PI = 0;
	private int IOI = 0;
	private int SI = 0;
	private int TI = 0;
	//private int ER = ??
	
	//Getters
	public boolean getMODE(){
		return this.MODE;
	}
	
	public int getPTR(){
		return this.PTR;
	}
	
	public int getVM(){
		return this.VM;
	}
	
	public int getPI(){
		return this.PI;
	}
	
	public int getIOI(){
		return this.IOI;
	}					
	
	public int getSI(){
		return this.TI;
	}
	
	public int getTI(){
		return this.TI;
	}
	
	//Setters
	public void setMODE(boolean MODE){
		this.MODE = MODE;
	}
	
	public void setPTR(int PTR){
		this.PTR = PTR;
	}
	
	public void setVM(int VM){
		this.VM = VM;
	}

	public void setPI(int PI){
		this.PI = PI;
	}

	public void setIOI(int IOI){
		this.IOI = IOI;
	}

	public void setSI(int SI){
		this.SI = SI;
	}

	public void setTI(int TI){
		this.TI = TI;
	}

	
}
