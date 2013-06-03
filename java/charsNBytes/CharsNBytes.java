
import java.lang.String;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.nio.CharBuffer;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetEncoder;
import java.nio.charset.CharsetDecoder;
import java.nio.charset.CharacterCodingException;
import java.util.SortedMap;

public class CharsNBytes {
    private static String str = "\u2622 \u2671";

    public static void main(String[] args) throws UnsupportedEncodingException, CharacterCodingException {
        // Note that the default charset on MacOS is MacRoman which peaks out
        // at unicode point U+02C7. So, it cannot represent these characters.
        // So, the regular output stream will dump garbage to the console. In
        // order to remedy this, we have to create a utf-8 output stream since
        // this is what the console supports.
        System.out.println("System default char set is: " + Charset.defaultCharset());
        PrintStream out = new PrintStream(System.out, true, "UTF-8");
        System.out.println("Orig string:");
        out.println(str);
        System.out.println("Now we get a UTF-8 byte sequence from the string and recreate the string from the bytes");
        byte[] bytes = new byte[20];
        bytes = str.getBytes("UTF-8");
        printHexBytes(bytes);
        System.out.println("Reconstructed string: " + new String(bytes));
        System.out.println("Now wrap in a CharBuffer and converto a ByteBuffer and print char array built from literals");
        char chars[] = { '\u2622', ' ', '\u266c' };
        //char chars[] = "\u2622 \u2671";
        System.out.println("Try to create a new string - note it does not work sice String constructor assumes UTF-8: " + new String(chars));
        System.out.println("But, it does work if you specify the code points as an int array");
        int ints[] = { 0x2622, 0x0041, 0x266c };
        System.out.println("String: " + new String(ints, 0, 3));
        System.out.println("Print the char array as hex bytes - this is the unicode:");
        printHexChars(chars);
        ByteBuffer bBuf = Charset.forName("UTF-8").encode(CharBuffer.wrap(chars));
        byte[] newBArray = bBuf.array();
        System.out.println("The new byte arra has length: " + String.valueOf(newBArray.length));
        System.out.println("Print a new String built from ByteBuffer encode to UTF-8 is: " + new String(newBArray));
        System.out.println("Print the hex bytes of the new byte array - this will be UTF-8:");
        printHexBytes(newBArray);
        CharBuffer newCBuf = Charset.forName("UTF-8").decode(ByteBuffer.wrap(newBArray));
        char[] newCArray = newCBuf.array();
        System.out.println("Decode the byte array back into a CharBuffer and print the underlying hex byte array"); 
        System.out.println("Length of char array is: " + String.valueOf(newCArray.length));
        printHexChars(newCArray);
        System.out.println("A new string built from the underlying char array: " + new String(newCArray));
        //SortedMap<String, Charset> map = Charset.availableCharsets();
        //System.out.println("Sorted Map: " + map);
    }

    private static void printHexBytes(byte[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.format("%02x ", arr[i]);
        }
        System.out.println("");
    }

    private static void printHexChars(char[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.format("%02x%02x ", ((((short) arr[i]) & 0xFF00) >> 8), (((short) arr[i]) & 0x00FF));
        }
        System.out.println("");
    }

    /*
    private static void printHexString(String str) {
        byte[] bytes = (byte[]) str;
        for (int i = 0; i < 20; i++) {
            System.out.format("%02x%02x ", (byte) arr[i], ((byte) arr[i]) + 1);
        }
        System.out.println("");
    }
    */
}
