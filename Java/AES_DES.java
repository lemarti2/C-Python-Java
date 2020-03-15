import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

import java.util.Scanner;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Base64;


public class AES_DES {
  public static void main(String[] argv) throws Exception {
	String AES = "AES";
	String DES = "DES";
	Scanner input = new Scanner(System.in);
	System.out.println("AES or DES?");
	String choice = input.nextLine();
	if (choice.equals(DES)){
		Scanner input2 = new Scanner(System.in);
		System.out.println("What is your message?");
		String user = input2.nextLine();
		SecretKey key = KeyGenerator.getInstance("DES").generateKey();
		DesEncrypter encrypter = new DesEncrypter(key);
		String encrypted = encrypter.encrypt(user);
		String decrypted = encrypter.decrypt(encrypted);
		System.out.print("Message before Encryption: ");
		System.out.println(user);
		System.out.print("Encrypted message: ");
		System.out.println(encrypted);
		System.out.print("Decrypted message: ");
		System.out.println(decrypted);
	}
	if(choice.contentEquals(AES)) {
		Scanner input2 = new Scanner(System.in);
		System.out.println("What is your message?");
		String user = input2.nextLine();
		SecretKey key = KeyGenerator.getInstance("AES").generateKey();
		AES_Encrypter encrypter = new AES_Encrypter(key);
		String encrypted = encrypter.encrypt(user);
		String decrypted = encrypter.decrypt(encrypted);
		System.out.print("Message before Encryption: ");
		System.out.println(user);
		System.out.print("Encrypted message: ");
		System.out.println(encrypted);
		System.out.print("Decrypted message: ");
		System.out.println(decrypted);
		}
	
	}
  }

class DesEncrypter {
  Cipher eCipher;
  Cipher dCipher;

  DesEncrypter(SecretKey key) throws Exception {
    eCipher = Cipher.getInstance("DES");
    dCipher = Cipher.getInstance("DES");
    eCipher.init(Cipher.ENCRYPT_MODE, key);
    dCipher.init(Cipher.DECRYPT_MODE, key);
  }

  public String encrypt(String str) throws Exception {
    byte[] utf8 = str.getBytes("UTF8");
    byte[] enc = eCipher.doFinal(utf8);
    return new sun.misc.BASE64Encoder().encode(enc);
  }

  public String decrypt(String str) throws Exception {
    byte[] dec = new sun.misc.BASE64Decoder().decodeBuffer(str);
    byte[] utf8 = dCipher.doFinal(dec);
    return new String(utf8, "UTF8");
  }
}

class AES_Encrypter{
	
	Cipher eCipher;
	Cipher dCipher;
	
	AES_Encrypter(SecretKey key) throws Exception {
	    eCipher = Cipher.getInstance("AES");
	    dCipher = Cipher.getInstance("AES");
	    eCipher.init(Cipher.ENCRYPT_MODE, key);
	    dCipher.init(Cipher.DECRYPT_MODE, key);
	  }
	 public String encrypt(String str) throws Exception {
		   byte[] utf8 = str.getBytes("UTF8");
		   byte[] enc = eCipher.doFinal(utf8);
		   return new sun.misc.BASE64Encoder().encode(enc);
	  }
	 public String decrypt(String str) throws Exception {
		    byte[] dec = new sun.misc.BASE64Decoder().decodeBuffer(str);
		    byte[] utf8 = dCipher.doFinal(dec);
		    return new String(utf8, "UTF8");
		  }
}

