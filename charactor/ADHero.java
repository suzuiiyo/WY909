package charactor;

import exceptions.EnemyHeroIsDeadException;

/**
 * @author youpub
 */
public class ADHero extends Hero{
    public void adAattack(Hero h) throws EnemyHeroIsDeadException {
        if(h.hp == 0){
            throw new EnemyHeroIsDeadException(h.name + "is dead");
        }

        h.hp -= this.damage;

        if(h.isDead()){
            System.out.println(h.name + "is dead");
        }
    }
}
