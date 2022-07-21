package multipleThread;

import charactor.Hero;

/**
 * @author youpub
 */
public class testADuGen {
    public static void main(String[] args) {
        final Hero winds = new Hero();
        winds.name = "盖伦";
        winds.hp = 61600;
        winds.damage = 103;

        winds.adugen();
    }
}
