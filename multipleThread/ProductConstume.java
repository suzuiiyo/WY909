package multipleThread;

import generic.MyStackEdge;

public class ProductConstume {
    static MyStackEdge<Character> myStackEdge = new MyStackEdge<>();

    static public class Productor extends Thread {
        String name;
        public Productor(String var){
            this.name = var;
        }

        @Override
        public void run() {
            while (true) {
                char ch = (char) (Math.random() * ('Z' + 1 - 'A') + 'A');
                System.out.println(this.getName() + " push into: " + ch);
                myStackEdge.push(ch);
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static public class Consumer extends Thread {
        String name;

        public Consumer(String var) {
            this.name = name;
        }

        @Override
        public void run() {
            while (true) {
                char ch = myStackEdge.pull();
                System.out.println(this.getName() + " pull out: " + ch);
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        for(int i=0; i<2; i++){
            new Productor("Productor" + i).start();
        }

        for(int i=0; i<3; i++){
            new Consumer("Consumer" + i).start();
        }
    }
}
