package reflection;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Properties;

public class testSpring {
    public static void main(String[] args) throws IOException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        File springConfigFile = new File("/home/youpub/IdeaProjects/demo1/src/reflection/spring.txt");
        Properties springConfig = new Properties();
        springConfig.load(new FileInputStream(springConfigFile));
        String className = (String) springConfig.get("class");
        String methodName = (String) springConfig.get("method");

        Class clazz = Class.forName(className);
        Method m = clazz.getMethod(methodName);
        Constructor c = clazz.getConstructor();
        Object service = c.newInstance();
        m.invoke(service);
    }
}
