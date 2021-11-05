package socket;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

/**
 * @author youpub
 */
public class sendThread extends Thread{
    private Socket s;

    public sendThread(Socket s){
        this.s = s;
    }

    @Override
    public void run() {
        try{
            OutputStream os = s.getOutputStream();
            DataOutputStream dos = new DataOutputStream(os);

            while(true) {
                Scanner sc = new Scanner(System.in);
                String str = sc.next();
                dos.writeUTF(str);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
