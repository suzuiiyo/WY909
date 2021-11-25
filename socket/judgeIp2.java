package socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

public class judgeIp2 {
    public static void main(String[] args) throws UnknownHostException, InterruptedException {
        InetAddress host = InetAddress.getLocalHost();
        String ip = host.getHostAddress();
        String ipRange = ip.substring(0, ip.lastIndexOf("."));
        System.out.println("this host ip is" + ip);
        System.out.println("net range is" + ipRange);

        List<String> ips = Collections.synchronizedList(new ArrayList<>());
        ThreadPoolExecutor threadPool = new ThreadPoolExecutor(10, 15, 60, TimeUnit.SECONDS,
        new LinkedBlockingDeque<Runnable>());
        AtomicInteger number = new AtomicInteger();

        for(int i=0; i<255; i++){
            String testIP = ipRange + "." + (i + 1);
            threadPool.execute(new Runnable() {
                @Override
                public void run() {
                    boolean reachable = isReachable(testIP);
                    if(reachable) {
                        ips.add(testIP);
                    }
                    synchronized (number){
                        System.out.println("has finished:" + number.incrementAndGet() + " ips' test");
                    }
                }
            });
        }
        //after all thread is over
        threadPool.shutdown();
        if(threadPool.awaitTermination(1, TimeUnit.HOURS)){
            System.out.println("those ip can be reachable");
            for(String theip : ips){
                System.out.println(theip);
            }
            System.out.println("totally has:" + ips.size() + " addresses");
        }
    }

    private static boolean isReachable(String ip){
        try {
            boolean reachable = false;
            Process p = Runtime.getRuntime().exec("ping -n l " + ip);
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = null;
            StringBuilder sb = new StringBuilder();
            while ((line = br.readLine()) != null) {
                if (line.length() != 0) {
                    sb.append(line + "\r\n");
                }
            }

            //when TTL shows, means is reachable
            reachable = sb.toString().contains("TTL");
            br.close();
            return reachable;
        }catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }
}
