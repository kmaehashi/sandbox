/** 
 * String 型の switch 文をテストするサンプルクラスです。
 * @author Kenichi Maehashi
 */
public class StringSwitch {
	/**
	 * メインメソッドです。
	 * 入力されたパラメタに応じて数値または文字列を表示します。
	 * @param args "fizz", "buzz" または任意の文字列を指定します。
	 */
	public static void main(String[] args) {
		switch(args[0]) {
			case "fizz":
				System.out.println(2);
				break;
			case "buzz":
				System.out.println(3);
				break;
			default:
				System.out.println("hello");
		}
	}
}

