import java.io.*;

public class ExpHandle {
	public static void main(String[] args) {
		try {
			File f = new File("input.txt");
			BufferedReader br = new BufferedReader(new FileReader(f));
			System.out.println(br.readLine());
			br.close();
			Thread.currentThread().sleep(10);
		} catch (IOException | InterruptedException ex) {
			ex.printStackTrace();
		}
	}
}

