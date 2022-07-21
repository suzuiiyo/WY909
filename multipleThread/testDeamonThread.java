package multipleThread;

public class testDeamonThread {
    public static void main(String[] args) {
        Thread t1 = new Thread(){
            @Override
            public void run(){
                int seconds = 0;

                while(true){
                    try{
                        Thread.sleep(1000);
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                    System.out.printf("have played LOL %d s%n", seconds++);
                }
            }
        };
        t1.setDaemon(true);
        t1.start();
    }
}
