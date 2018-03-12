public class VirtualMachine {

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

	protected int R = 0;
	protected int PC = 0;
	protected int C = 0;
	protected int DP = 0;
	protected int SF = 0;
	protected int ER = 0;

	public int getR()
	{
		return this.R;
	}
	public void setR(int R)
	{
		this.R = R;
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
	public int getDP()
	{
		return this.ER;
	}
	public void setER(int ER)
	{
		this.ER = ER;
	}
	
}