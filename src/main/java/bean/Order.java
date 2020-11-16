package bean;

public class Order {
    private int id;
    private User user;

    public void setId(int id){
        this.id = id;
    }

    public int getId(){
        return id;
    }

    public void setUser(User user){
        this.user = user;
    }

    public User getUser(){
        return user;
    }
}
