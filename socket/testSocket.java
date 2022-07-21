package socket;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class testSocket {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress host = InetAddress.getLocalHost();
        String ip = host.getHostAddress();
        System.out.println("host ip address: " +  ip);
    }
}
