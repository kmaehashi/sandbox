import java.io.IOException;
import java.util.Scanner;

public class BrainfuckMain {
	public static void main(String[] args) throws IOException {
		Scanner scanner = new Scanner(System.in);
		String program = scanner.nextLine();
		// Brainfuck bf = new Brainfuck(program.toCharArray(), Brainfuck.DEFAULT_MEMORY_SIZE, false);
		BrainfuckV2 bf = new BrainfuckV2(program.toCharArray(), Brainfuck.DEFAULT_MEMORY_SIZE, false);
		bf.run();
	}
}
