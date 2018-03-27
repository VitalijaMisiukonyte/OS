import java.util.ArrayList;
public class VirtualMachine extends RealMachine {

	public static RealMachine realMachine;
	private int[] virtualMemory = new int[150];

	public static ArrayList<String> errorMessages;
	static {
		errorMessages = new ArrayList(6);
		errorMessages.add(0, "Neatpažinta komanda");
		errorMessages.add(1, "Adresas užeina už virtualios mašinos atminties ribų");
		errorMessages.add(2, "Į PC registrą patalpintas neteisingas adresas.");
		errorMessages.add(3, "Vienas iš operandų nėra teisingas skaičius (aritmetinė operacija).");
		errorMessages.add(4, "Programos pradžioje nėra komandos STRT.");
		errorMessages.add(5, "Programos pabaigoje nėra komandos HALT.");
		errorMessages.add(6, "Dalyba iš nulio.");
	}
	
	protected int[] registers = new int[8];

	protected int R1 = 0;
	protected int R2 = 0;
	protected int PC = 0;
	protected int C = 0;
	protected int DP = 0;
	protected int SF = 0;
	protected int ER = 0;
	protected int SP = 0;

	public int getR1()
	{
		return this.R1;
	}
	public void setR1(int R1)
	{
		this.R1 = R1;
	}
	public int getR2()
	{
		return this.R2;
	}
	public void setR(int R2)
	{
		this.R2 = R2;
	}
	public int getPC()
	{
		return this.PC;
	}
	public void setPC(int PC)
	{
		this.PC = PC;
	}
	public int getC()
	{
		return this.C;
	}
	public void setC(int C)
	{
		this.C = C;
	}
	public int getDP()
	{
		return this.DP;
	}
	public void setDP(int DP)
	{
		this.DP = DP;
	}
	public int getSF()
	{
		return this.SF;
	}
	public void setSF(int SF)
	{
		this.SF = SF;
	}
	public int getER()
	{
		return this.ER;
	}
	public void setER(int ER)
	{
		this.ER = ER;
	}
	public int getSP()
	{
		return this.SP;
	}
	public void setSP(int SP)
	{
		this.SP = SP;
	}
	
	//Atminties laukas - bus naudinga
	protected Memory memory;

	//Konstruktorius
	public VirtualMachine(Memory m){
		this.memory = m;
	}
}
