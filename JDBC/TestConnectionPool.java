package JDBC;

import java.util.ArrayList;
import java.util.List;

public class TestConnectionPool {
    private static int threadNumber = 100;
    public static int insertTime = 1;

    public static void main(String[] args) {
        traditionalWay();
        connectionPoolWay();
    }

    private static void connectionPoolWay(){
        testConnectionPool cp = new testConnectionPool(10);

        System.out.println("start connectPool insert data test");
        long start = System.currentTimeMillis();
        List<Thread> ts = new ArrayList<>();
        for(int i=0; i<threadNumber; i++){
            Thread t = new ConnectionpoolWorkingThread(cp);
            t.start();
            ts.add(t);
        }

        //wait for all thread over
        for(Thread t : ts){
            try{
                t.join();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        long end = System.currentTimeMillis();
        System.out.printf("by connectionPool style, start %d thread, insert %d data per thread, waste time %d s%n", threadNumber, insertTime, end - start);
    }

    private static void traditionalWay(){
        System.out.println("start troditional way insert data test");
        long start = System.currentTimeMillis();
        List<Thread> ts = new ArrayList<>();
        for(int i=0; i<threadNumber; i++){
            Thread t = new TraditionalWorkingThread();
            t.start();
            ts.add(t);
        }

        //wait for all the thread
        for(Thread t :ts){
            try{
                t.join();
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        long end = System.currentTimeMillis();
        System.out.printf("by traditional style, start %d thread, insert %d data per thread, waste time %d s%n", threadNumber, insertTime, end - start);
    }
}
