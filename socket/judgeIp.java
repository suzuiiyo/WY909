package socket;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.LinkedList;

public class judgeIp {
    public static void main(String[] args) throws UnknownHostException {
        InetAddress host = InetAddress.getLocalHost();
        String ip = host.getHostAddress();
        String ipRange = ip.substring(0, ip.lastIndexOf("."));

        for(int i=0; i<255; i++){
            threadpool tp = new threadpool(3);
            String ipAddr = ipRange + "." + i;
            testSocket2 pingAddr2 = new testSocket2(ipAddr);

            tp.add(pingAddr2);
        }
    }

    static class threadpool {
        int threadPoolSize = 0;
        static LinkedList<Runnable> tasks = new LinkedList<>();

        public threadpool(int sizeVar){
            this.threadPoolSize = sizeVar;
            synchronized (tasks){
                for(int i=0; i< threadPoolSize; i++){
                    new workingThread("thread_" + i).start();
                }
            }
        }

        public void add(Runnable r){
            synchronized (tasks){
                tasks.add(r);
                tasks.notifyAll();
            }
        }

        static class workingThread  extends Thread{
            public workingThread(String name){
                super(name);
            }

            Runnable  task;

            @Override
            public void run() {
                while(true){
                    synchronized (tasks){
                        while (tasks.isEmpty()){
                            try{
                                tasks.wait();
                            }catch (InterruptedException e){
                                e.printStackTrace();
                            }
                        }
                        task = tasks.removeLast();
                        tasks.notifyAll();
                    }
                    task.run();
                }
            }
        }
    }
}
