package multipleThread;

import charactor.Hero;
import exceptions.EnemyHeroIsDeadException;

public class TestThread2 {
    public static void main(String[] args) {
        Hero h1 = new Hero("ede");
        Hero h2 = new Hero("fgf");
        Hero h3 = new Hero("jkj");
        Hero h4 = new Hero("mnm");

        Thread t1 = new Thread(){
            @Override
            public void run(){
                while (!h1.isDead()){
                    try {
                        h2.attackHero(h1);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        t1.start();

        Thread t2 = new Thread(){
            @Override
            public void run(){
                while(!h3.isDead()){
                    try {
                        h4.attackHero(h3);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        t2.start();
    }
}
