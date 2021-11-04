package socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class testSocket2 implements Runnable{
    private String ipAddr;

    public testSocket2(String addr){
        ipAddr = addr;
    }

    @Override
    public void run() {
        Process p = null;
        try {
            p = Runtime.getRuntime().exec("ping " + ipAddr);
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = null;
            StringBuilder sb = new StringBuilder();

            while((line = br.readLine())!= null){
                if(line.length() != 0){
                    sb.append(line + "\r\n");
                }
            }

            if(sb.toString().contains("TTL")){
                System.out.println(ipAddr + "can be reachable");
            }
            br.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
