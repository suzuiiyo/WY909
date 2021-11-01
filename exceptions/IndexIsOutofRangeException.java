package exceptions;

/**
 * @author youpub
 */
public class IndexIsOutofRangeException extends Exception {
    public IndexIsOutofRangeException(){

    }

    public IndexIsOutofRangeException(String msg){
        super(msg);
    }
}
