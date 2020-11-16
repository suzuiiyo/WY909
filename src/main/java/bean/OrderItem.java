package bean;

public class OrderItem {
    private int id;
    private Product product;
    private int num;
    private Order order;

    public void setId(int id){
        this.id = id;
    }

    public int getId(){
        return id;
    }

    public void setNum(int num){
        this.num = num;
    }

    public int getNum(){
        return num;
    }

    public void setProduct(Product product){
        this.product = product;
    }

    public Product getProduct(){
        return product;
    }

    public void setOrder(Order order){
        this.order = order;
    }

    public Order getOrder(){
        return order;
    }

    @Override
    public String toString(){
        return "id:" + product.getId() + " name:" + product.getName();
    }
}
