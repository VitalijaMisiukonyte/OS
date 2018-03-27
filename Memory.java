//Klase darbui su atmintimi
// 300 zodziu - 4800 bitu, pataisykit jei as neteisus.
import java.util.ArrayList;

public class Memory{

	private ArrayList<String> buffer;
	private boolean correct;
	
	//Konstruktorius
	public Memory(){
		this.buffer = new ArrayList<String>(4800);
	}
	
	//Metodas, grazinantis zodi is atminties pagal adresa
	public String getWord(int address){
		this.correct = true;
		
		if((address < 4800)&&(address >= 0)){
			return this.buffer.get(address);
		}
		else{
			this.correct = false;
			System.out.println("Operation failed");
		}
	}

	//Metodas, leidziantis irasyti zodi i atminti pagal adresa
	public void setWord(int address, String word){
		this.correct = true;
	
		if((address < 4800)&&(address >= 0)){
			if(word.length() > 8)
				word = word.substring(0, 8);
			while(word.length() < 8)
				word+= " ";
			this.buffer.set(address, word);
		}
		else{
			this.correct = false;
			System.out.println("Operation failed");
		}
	}
}
