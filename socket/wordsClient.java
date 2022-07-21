package socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class wordsClient {
    public static void main(String[] args) {
        try{
            Socket s = new Socket("127.0.0.1", 8080);

            OutputStream os = s.getOutputStream();
            DataOutputStream dos = new DataOutputStream(os);
            InputStream is = s.getInputStream();
            DataInputStream dis = new DataInputStream(is);

            while(true){
                Scanner sc = new Scanner(System.in);
                String str = sc.next();
                dos.writeUTF(str);

                String msg = dis.readUTF();
                System.out.println(msg);
                System.out.println();
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
