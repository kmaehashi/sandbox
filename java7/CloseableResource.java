import java.io.*;

public class CloseableResource {
	public static void main(String[] args) {
		BufferedReader br = null;
		try {
			File f = new File("input.txt");
			br = new BufferedReader(new FileReader(f));
			System.out.println(br.readLine());
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				br.close();
			} catch (IOException e){ 
				e.printStackTrace();
			}
		}
	}
}

