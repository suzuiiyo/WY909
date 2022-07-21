package multipleThread;

import charactor.Hero;
import exceptions.EnemyHeroIsDeadException;

public class testHeroAttack {
    public static void main(String[] args) {
        final Hero gareen = new Hero();
        gareen.name = "盖伦";
        gareen.hp = 6160;
        gareen.damage = 56;

        final Hero teemo = new Hero();
        teemo.name = "提莫";
        teemo.hp = 3000;
        teemo.damage = 89;

        final Hero bh = new Hero();
        bh.name = "赏金猎人";
        bh.hp = 5000;
        bh.damage = 45;

        final Hero leesin = new Hero();
        leesin.name = "盲僧";
        leesin.hp = 4505;
        leesin.damage = 67;

        Thread t1 = new Thread() {
            @Override
            public void run() {
                while (!teemo.isDead()) {
                    try {
                        gareen.attackHero(teemo);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };

        Thread t2 = new Thread(){
            @Override
            public void run(){
                while(!leesin.isDead()){
                    try {
                        bh.attackHero(leesin);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };

        t1.setPriority(Thread.MAX_PRIORITY);
        t2.setPriority(Thread.MIN_PRIORITY);
        t1.start();
        t2.start();
    }
}
