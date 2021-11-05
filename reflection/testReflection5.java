package reflection;

import charactor.Hero;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/**
 * @author youpub
 */
public class testReflection5 {
    public static void main(String[] args) throws IOException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, InstantiationException, IllegalAccessException {
        Hero h = getHero();
        h.adugen();
    }

    public static Hero getHero() throws IOException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/reflection/hero.config");
        FileReader fr = new FileReader(f);
        char[] buffer = new char[(int) f.length()];
        fr.read(buffer);

        Constructor c = Class.forName(new String(buffer)).getConstructor();
        Hero h = (Hero) c.newInstance();
        return h;
    }
}
