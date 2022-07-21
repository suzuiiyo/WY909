package charactor;

import exceptions.IndexIsNagetiveException;
import exceptions.IndexIsOutofRangeException;

public interface IStringBuffer {
    public void append(String str) throws IndexIsOutofRangeException, IndexIsNagetiveException;
    public void append(char c) throws IndexIsOutofRangeException, IndexIsNagetiveException;
    public void insert(int pos, char b) throws IndexIsNagetiveException, IndexIsOutofRangeException;
    public void insert(int pos, String b) throws IndexIsNagetiveException, IndexIsOutofRangeException;
    public void delete(int start) throws IndexIsNagetiveException, IndexIsOutofRangeException;
    public void delete(int start, int end) throws IndexIsNagetiveException, IndexIsOutofRangeException;
    public void reverse();
    public int length();
}
