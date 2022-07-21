package multipleThread;

import charactor.Hero;
import exceptions.EnemyHeroIsDeadException;

public class TestJoin {
    public static void main(String[] args) {
        final Hero jumo = new Hero();
        jumo.name = "huge master";
        jumo.hp = 616;
        jumo.damage = 50;

        final Hero mepoo = new Hero();
        mepoo.name = "meter poo";
        mepoo.hp = 300;
        mepoo.damage = 60;

        final Hero tiao = new Hero();
        tiao.name = "jugle lee";
        tiao.hp = 365;
        tiao.damage = 46;

        final Hero luna = new Hero();
        luna.name = "fuji wan";
        luna.hp = 616;
        luna.damage = 50;

        Thread t1 = new Thread(){
            @Override
            public void run(){
                while(!jumo.isDead()){
                        try {
                            jumo.attackHero(mepoo);
                        } catch (EnemyHeroIsDeadException e) {
                            e.printStackTrace();
                        }
                    }
                }
            };
        t1.start();

        //代码执行到这里，一直是main线程在运行
        try{
            //t1线程加入到main线程中来，只有t1线程运行结束，才会继续往下走
            t1.join();
        }catch (InterruptedException e){
            e.printStackTrace();
        }

        Thread t2 = new Thread(){
            @Override
            public void run() {
                while (!tiao.isDead()){
                    try {
                        luna.attackHero(tiao);
                    } catch (EnemyHeroIsDeadException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        //after t1 overed, then t2 will start
        t2.start();
    }
}
