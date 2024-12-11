package model;

public class Container {
    private Integer wastelvl;
    private Integer temp;
    private boolean full = false;
    private boolean maxTemp = false;

    public Container(Integer wastelvl, Integer temp) {
        this.wastelvl = wastelvl;
        this.temp = temp;
    }
    public Integer getWastelvl() {
        return wastelvl;
    }
    public Integer getTemp() {
        return temp;
    }
    public void setWastelvl(Integer wastelvl) {
        this.wastelvl = wastelvl;
        if (wastelvl >= 100) {
            setFull(true);
        }
    }
    public void setTemp(Integer temp) {
        this.temp = temp;
    }
    public boolean isFull() {
        return full;
    }
    public void setFull(boolean full) {
        this.wastelvl = 100;
        this.full = full;
    }
    public boolean isMaxTemp() {
        return maxTemp;
    }
    public void setMaxTemp(boolean maxTemp) {
        this.maxTemp = maxTemp;
    }
    public void empty() {
        this.full = false;
        this.wastelvl = 0;
    }
    public void restore() {
        this.maxTemp = false;
        this.temp = 0;
    }
    public boolean genericAllarm() {
        return this.full || this.maxTemp;
    }
}
