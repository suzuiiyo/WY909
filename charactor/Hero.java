package charactor;

import exceptions.EnemyHeroIsDeadException;

import java.io.Serializable;

public class Hero implements Serializable{
    public String name;
    public float hp;
    public float damage;
    public Hero(){

    }

    public Hero(String nameVar, float hpVar){
        this.name = nameVar;
        this.hp = hpVar;
    }

    public Hero(String nameVar) {
        this.name = nameVar;
    }

    public Hero(String s, int hpVar, int damageVar) {
        this.name = s;
        this.hp = hpVar;
        this.damage = damageVar;
    }

    public void attackHero(Hero h) throws EnemyHeroIsDeadException {
        if (h.hp == 0) {
            throw new EnemyHeroIsDeadException(h.name + " is dead, no need to put a skill");
        }

        h.hp -= damage;
        System.out.format("%s is attacking %s, %s's blood becames %.0f%n", name, h.name, h.name, h.hp);

        if(h.isDead()){
            System.out.println(h.name + "is Dead!");
        }
    }

    @Override
    public String toString()
    {
        return name;
    }

    public static void main(String[] args) {
        Hero garen = new Hero();
        garen.name = "GAILUN";
        garen.hp = 616;

        Hero teemo = new Hero();
        teemo.name = "TIMO";
        teemo.hp = 0;

        try {
            garen.attackHero(teemo);
        } catch (EnemyHeroIsDeadException e) {
            System.out.println("the specific reson of the exception: " + e.getMessage());
            e.printStackTrace();
        }

        garen.adugen();
    }

    public void setName(String name) {
        this.name = name;
    }


    public String getName(){
        return name;
    }

    public boolean isDead() {
        if (this.hp <= 0) {
            return true;
        } else {
            return false;
        }
    }

    int totalTime = 3;
    public void adugen(){
        while(true) {
            for (int i = 0; i < totalTime; i++) {
                System.out.printf("a du gen %drd %n", i+1);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("rest 5 seconds to get recharge");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void recover(){
        hp = hp+1;
    }

    public void hurt(){
        hp = hp -1;
    }
}
