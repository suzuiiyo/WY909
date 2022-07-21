package charactor;

import exceptions.IndexIsNagetiveException;
import exceptions.IndexIsOutofRangeException;

import java.lang.module.FindException;

public class MyStringBuffer implements IStringBuffer {
    int capacity = 16;
    int length = 0;
    char[] value;

    //no args struct
    public MyStringBuffer(){
        value = new char[capacity];
    }

    //args struct
    public MyStringBuffer(String str){
        this();
        if(null == str) {
            return;
        }

        if(capacity < str.length()){
            capacity = value.length * 2;
            value = new char[capacity];
        }

        if(capacity >= str.length()){
            System.arraycopy(str.toCharArray(), 0, value, 0, str.length());
        }
        length = str.length();
    }

    @Override
    public void append(String str) throws IndexIsOutofRangeException, IndexIsNagetiveException {
        insert(length, str);
    }

    @Override
    public void append(char c) throws IndexIsOutofRangeException, IndexIsNagetiveException {
        append(String.valueOf(c));
    }

    @Override
    public void insert(int pos, char b) throws IndexIsOutofRangeException, IndexIsNagetiveException {
        insert(pos, String.valueOf(b));
    }

    @Override
    public void insert(int pos, String b) throws IndexIsNagetiveException, IndexIsOutofRangeException {
        // TODO document why this method is empty

        //judge the edge
        if(pos < 0){
            throw new IndexIsNagetiveException();
        }

        if(pos > length) {
            throw new IndexIsOutofRangeException();
        }

        //expend the capacity
        if(length + b.length() > capacity){
            capacity = (int)((length + b.length())*2.5f);
            char[] newValue = new char[capacity];
            System.arraycopy(value, 0, newValue, 0, length);
            value = newValue;
        }

        char[] cs = b.toCharArray();
        //backdown exist data
        System.arraycopy(value, pos, value, pos + cs.length, length - pos);
        //insert data into position
        System.arraycopy(cs, 0, value, pos, cs.length);
    }

    @Override
    public void delete(int start) throws IndexIsNagetiveException, IndexIsOutofRangeException {
        if(start<length()){
            throw new IndexIsNagetiveException("index is a nagetive");
        }
        else if(start>length()){
            throw new IndexIsOutofRangeException("index is out of range");
        }
    }

    @Override
    public void delete(int start, int end) throws IndexIsNagetiveException, IndexIsOutofRangeException {
        if(start<length){
            throw new IndexIsNagetiveException("index is a nagetive");
        }
        else if(start>length){
            throw new IndexIsOutofRangeException("index is out of range");
        }

        if(end<0){
            throw new IndexIsNagetiveException("index is a nagetive");
        }else if(end>length){
            throw new IndexIsOutofRangeException("index is out of range");
        }

        if(start >= end){
            throw new IndexIsOutofRangeException("index is out of range");
        }

        System.arraycopy(value, end, value, start, length - end);
        length -= end - start;
    }

    @Override
    public void reverse() {
        for(int i = 0; i < length / 2; i++){
            char temp = value[i];
            value[i] = value[length - i - 1];
            value[length - i - 1] = temp;
        }
    }

    @Override
    public int length() {
        return this.length();
    }

    @Override
    public String toString(){
        char[] realValue = new char[length];
        System.arraycopy(value, 0, realValue, 0, length);
        return new String(realValue);
    }
}