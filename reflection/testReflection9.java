package reflection;

import charactor.Hero;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class testReflection9 {
    public static void main(String[] args) {
        File f = new File("/home/youpub/IdeaProjects/demo1/src/reflection/hero.config");
        try(FileReader fr = new FileReader(f)){
            String fileContent = null;
            char[] all = new char[(int) f.length()];
            fr.read(all);
            fileContent = new String(all);
            String[] cs = fileContent.split("\n");
            System.out.println(cs);
            String hero1className = cs[0];
            String hero1Name = cs[1];
            String hero2className = cs[2];
            String hero2Name = cs[3];

            Class hero1Class = Class.forName(hero1className);
            Constructor hero1Constructor = hero1Class.getConstructor();
            Object hero1 = hero1Constructor.newInstance();
            Field hero1NameField = hero1Class.getField("name");
            hero1NameField.set(hero1, hero1Name);

            Class hero2Class = Class.forName(hero2className);
            Constructor hero2Constructor = hero2Class.getConstructor();
            Object hero2 = hero2Constructor.newInstance();
            Field hero2NameField = hero2Class.getField("name");
            hero2NameField.set(hero2, hero2Name);

            Method attackHeroMet = hero1Class.getMethod("attackHero", Hero.class);
            attackHeroMet.invoke(hero1, hero2);

        }catch (IOException | ClassNotFoundException e){
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }
}
