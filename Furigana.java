import java.io.IOException;
import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.xml.sax.SAXException;

public class Furigana {
	public static void main(String[] args) {
		try {
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dbf.newDocumentBuilder();
			String url = "http://jlp.yahooapis.jp/FuriganaService/V1/furigana?appid=PhoTouch&sentence=" + args[1] + "&grade=1";
			Document doc = builder.parse(url);
			Element root = doc.getDocumentElement();
			Element result = (Element) root.getElementsByTagName("Result").item(0);
			Element wordList = (Element) result.getElementsByTagName("WordList").item(0);
			NodeList words = wordList.getElementsByTagName("Word");
			for (int i = 0; i < words.getLength(); i++) {
				Element word = (Element) words.item(i);
				System.out.print(word.getElementsByTagName("Surface").item(0).getFirstChild().getNodeValue());
				NodeList furigana = word.getElementsByTagName("Furigana");
				if (furigana.getLength() > 0) {
					System.out.print("[" + furigana.item(0).getFirstChild().getNodeValue() + "]");
				}
			}
		} catch (ParserConfigurationException e) {
			e.printStackTrace();
		} catch (SAXException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}