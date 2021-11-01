package multipleThread;

public class TestSleep {
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
                    System.out.printf("have palyed the game for %d seconds %n", seconds++);
                }
            }
        };
        t1.start();
    }
}
