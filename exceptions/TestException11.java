package exceptions;

public class TestException11 {
    public static void main(String[] args){
        //ArithmeticException e
        int k = 5/0;
        //ArrayIndexOutOfBoundsException
        int j[] = new int[5];

        j[10] = 10;
        //NullPointerException
        String str = null;
        str.length();
    }
}
