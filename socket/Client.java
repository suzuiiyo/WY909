package socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try{
            Socket s = new Socket("127.0.0.1", 8888);

            OutputStream os = s.getOutputStream();
            DataOutputStream dos = new DataOutputStream(os);
            InputStream is_client = s.getInputStream();
            DataInputStream dis_client = new DataInputStream(is_client);

            while(true) {
                Scanner sc = new Scanner(System.in);
                dos.writeUTF(sc.next());

                String msg = dis_client.readUTF();
                System.out.println("connection came " + msg);
            }
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
