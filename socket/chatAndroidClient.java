package socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class chatAndroidClient {
    public static void main(String[] args) throws IOException {
        Socket s = new Socket("127.0.0.1", 8080);

        OutputStream os = s.getOutputStream();
        DataOutputStream dos = new DataOutputStream(os);

        while(true){
            Scanner sc = new Scanner(System.in);
            dos.writeUTF(sc.next());
        }
    }
}
