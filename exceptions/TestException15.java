package exceptions;

public class TestException15 {
    public static void main(String[] args) {
        String str = null;
        try {
            str.toString();
        } catch (NullPointerException e) {
            System.out.println("catch a runable exception");
        }

        StringBuffer sb = new StringBuffer("1234567890");
        try {
            for (int i = 0; i < 100; i++) {
                sb.append(sb.toString());
            }
        } catch (OutOfMemoryError e) {
            System.out.println("catch a memmory runout error");
        }
    }
}
