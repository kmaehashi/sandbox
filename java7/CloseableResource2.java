import java.io.*;

public class CloseableResource2 {
	public static void main(String[] args) {
		try (BufferedReader br = new BufferedReader(new FileReader(new File("input.txt"))) ){
			System.out.println(br.readLine());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

