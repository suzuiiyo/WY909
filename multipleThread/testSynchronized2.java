package multipleThread;

import charactor.Hero;

public class testSynchronized2 {
    public static void main(String[] args) {
        final Object someObject = new Object();
        final Hero gareen = new Hero();
        gareen.name = "盖伦";
        gareen.hp = 10000;

        int n = 10000;
        Thread[] addThreads = new Thread[n];
        Thread[] reduceThreads = new Thread[n];

        for(int i=0; i<n; i++){
            Thread t = new Thread(){
                @Override
                public void run() {
                    synchronized(someObject){
                        gareen.recover();
                    }

                    try{
                        Thread.sleep(100);
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                }
            };
            t.start();
            addThreads[i] = t;
        }
    }
}
