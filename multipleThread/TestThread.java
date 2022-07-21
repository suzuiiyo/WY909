package multipleThread;

import charactor.Hero;

public class TestThread {
    public static void main(String[] args) {
        Hero h1 = new Hero("hhh");
        Hero h2 = new Hero("lll");
        Hero h3 = new Hero("ooo");
        Hero h4 = new Hero("ttt");

        Battle battle1 = new Battle(h1, h2);
        new Thread(battle1).start();
        Battle battle2 = new Battle(h3, h4);
        new Thread(battle2).start();
    }
}
