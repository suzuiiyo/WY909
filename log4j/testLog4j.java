package log4j;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * @author youpub
 */
public class testLog4j {
    String name;
    private static Logger logger = LogManager.getLogger(testLog4j.class.getName());
    public static void main(String[] args) throws InterruptedException {
        testLog4j log = new testLog4j();
        logger.debug("修改前的名字为：" + log.name);
        log.name = "longger";
        logger.trace("修改后的名字为：" + log.name);
        logger.debug("修改后的名字为：" + log.name);
        logger.info("修改后的名字为：" + log.name);
        logger.warn("修改后的名字为：" + log.name);
        logger.error("修改后的名字为：" + log.name);
        logger.fatal("修改后的名字为：" + log.name);
    }
}
