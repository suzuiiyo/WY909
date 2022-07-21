package multipleThread;

import charactor.Hero;
import exceptions.EnemyHeroIsDeadException;

public class TestTempraryPause {
    public static void main(String[] args) {
        final Hero gareen = new Hero();
        gareen.name = "盖伦";
        gareen.hp = 61600;
        gareen.damage = 103;

        final Hero teemo = new Hero();
        teemo.name = "提莫";
        teemo.hp = 30000;
        teemo.damage = 123;

        final Hero bh = new Hero();
        bh.name = "赏金猎人";
        bh.hp = 50000;
        bh.damage = 99;

        final Hero leesin = new Hero();
        leesin.name = "盲僧";
        leesin.hp = 45050;
        leesin.damage = 340;

        Thread t1 = new Thread(){
            @Override
            public void run(){
                while (!leesin.isDead()){
                    try {
                        bh.attackHero(leesin);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };

        Thread t2 = new Thread(){
            @Override
            public void run(){
                while (!leesin.isDead()){
                    Thread.yield();

                    try {
                        bh.attackHero(leesin);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };

        t1.setPriority(5);
        t2.setPriority(5);
        t1.start();
        t2.start();
    }
}
