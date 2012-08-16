import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class Brainfuck {
	public static final int DEFAULT_MEMORY_SIZE = 30000;
	private static final int NOT_FOUND = -1;

	private final char[] program;
	private final byte[] memory;
	private final boolean debug;

	private int pointer = 0;
	private int programCounter = 0;
	private int stepCounter = 0;

	public Brainfuck(char[] program, int memorySize, boolean debug) {
		this.program = program;
		this.memory = new byte[memorySize];
		this.debug = debug;
	}

	public Brainfuck(char[] program, int memorySize) {
		this(program, memorySize, false);
	}

	public Brainfuck(char[] program) {
		this(program, DEFAULT_MEMORY_SIZE, false);
	}

	public int run() throws IOException {
		while (program.length != programCounter) {
			debugDump();
			stepCounter++;

			switch (program[programCounter]) {
			case '>':
				pointer++;
				programCounter++;
				break;
			case '<':
				pointer--;
				programCounter++;
				break;
			case '+':
				setMemory((byte) (getMemory() + 1));
				programCounter++;
				break;
			case '-':
				setMemory((byte) (getMemory() - 1));
				programCounter++;
				break;
			case '.':
				print((char) getMemory());
				programCounter++;
				break;
			case ',':
				setMemory(read());
				programCounter++;
				break;
			case '[':
				if (getMemory() == 0) {
					int jump = find(']', true, '[');
					if (jump == NOT_FOUND) {
						return error("Can't find matching ']' for '['");
					}
					programCounter = jump;
				}
				programCounter++;
				break;
			case ']':
				if (getMemory() != 0) {
					int jump = find('[', false, ']');
					if (jump == NOT_FOUND) {
						return error("Can't find matching '[' for ']'");
					}
					programCounter = jump;
				}
				programCounter++;
				break;
			default:
				return error("Invalid instruction '" + program[programCounter] + "'");
			}
		}
		return 0;
	}

	private int getPointer() {
		int actualAddress = pointer % memory.length;
		if (pointer < 0) {
			actualAddress = memory.length + actualAddress;
		}
		return actualAddress;
	}

	private byte getMemory() {
		return memory[getPointer()];
	}

	private void setMemory(byte value) {
		memory[getPointer()] = value;
	}

	private void print(char c) {
		System.out.print(c);
	}

	private byte read() throws IOException {
		return (byte) (new BufferedReader(new InputStreamReader(System.in)).read());
	}

	private int find(char c, boolean forward, char skip) {
		int skipCount = 0;
		for (int n = programCounter; (forward && n++ < program.length) || (!forward && (0 <= n--));) {
			if (program[n] == skip) {
				skipCount++;
			} else if (program[n] == c) {
				if (skipCount-- == 0) {
					return n;
				}
			}
		}
		return NOT_FOUND;
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
