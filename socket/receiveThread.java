package socket;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

/**
 * @author youpub
 */
public class receiveThread extends Thread{
    private Socket s;
    public receiveThread(Socket s){
        this.s =s;
    }

    @Override
    public void run() {
        try {
            InputStream is = s.getInputStream();
            DataInputStream dis = new DataInputStream(is);
            while(true) {
                String msg = dis.readUTF();
                System.out.println(msg);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
