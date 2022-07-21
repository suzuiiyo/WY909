package junit;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class SumUtil {
    private static Logger logger = LogManager.getLogger(SumUtil.class.getName());
    @Before
    public void before(){
        System.out.println("prepareWork before test, such as link database");
    }

    @After
    public void after(){
        System.out.println("doneWork after test, such as close link");
    }

    @Test
    public void testSum1(){
        int result = SumUtil.sum1(1, 2);
        Assert.assertEquals(result, 3);
    }

    @Test
    public void testSum2(){
        int result = SumUtil.sum2(1, 2, 3);
        Assert.assertEquals(result, 5);
    }

    public static int sum1(int i, int j){
        return i+j;
    }

    public static int sum2(int i, int j, int k){
        return i+j+k;
    }
}
