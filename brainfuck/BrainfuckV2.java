import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class BrainfuckV2 {
	public static final int DEFAULT_MEMORY_SIZE = 30000;

	private char[] program;
	private Map<Integer, Integer> bracket_index;
	private byte[] memory;
	private boolean debug;

	private int pointer = 0;
	private int programCounter = 0;
	private int stepCounter = 0;

	public BrainfuckV2(char[] program, int memorySize, boolean debug) {
		this.program = program;
		this.memory = new byte[memorySize];
		this.debug = debug;
		this.bracket_index = new HashMap<Integer, Integer>();
		compile();
	}

	private void compile() {
		Stack<Integer> stack = new Stack<Integer>();
		for (int i = 0; i < program.length; i++) {
			switch (program[i]) {
			case '[':
				stack.push(i);
				break;
			case ']':
				int n = stack.pop();
				bracket_index.put(n, i);
				bracket_index.put(i, n);
			}
		}
	}

	public BrainfuckV2(char[] program, int memorySize) {
		this(program, memorySize, false);
	}

	public BrainfuckV2(char[] program) {
		this(program, DEFAULT_MEMORY_SIZE, false);
	}

	public int run() throws IOException {
		while (program.length != programCounter) {
			debugDump();
			stepCounter++;

			switch (program[programCounter]) {
			case '>':
				if (++pointer == memory.length) {
					pointer = 0;
				}
				break;
			case '<':
				if (--pointer == -1) {
					pointer = memory.length - 1;
				}
				break;
			case '+':
				memory[pointer]++;
				break;
			case '-':
				memory[pointer]--;
				break;
			case '.':
				print((char) memory[pointer]);
				break;
			case ',':
				memory[pointer] = read();
				break;
			case '[':
				if (memory[pointer] == 0) {
					programCounter = bracket_index.get(programCounter);
				}
				break;
			case ']':
				if (memory[pointer] != 0) {
					programCounter = bracket_index.get(programCounter);
				}
				break;
			default:
				return error("Invalid instruction '" + program[programCounter] + "'");
			}
			programCounter++;
		}
		return succeed();
	}

	private void print(char c) {
		System.out.print(c);
	}

	private byte read() throws IOException {
		return (byte) (new BufferedReader(new InputStreamReader(System.in)).read());
	}

	private int succeed() {
		return 0;
	}

	private int error(String msg) {
		System.err.println(msg + " at character " + (programCounter + 1));
		return -1;
	}

	private void debugDump() {
		if (debug) {
			System.err.println(dump());
		}
	}

	private String dump() {
		return program[programCounter] + " <" + programCounter + ':' + stepCounter + "> " + '*' + pointer + ' '
				+ (Arrays.toString(memory));
	}

	public String toString() {
		return dump();
	}
}
