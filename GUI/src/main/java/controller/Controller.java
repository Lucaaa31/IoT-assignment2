package controller;

import model.Container;
import model.Loop;

public class Controller {
    private final Container container;
    public Controller() {
        this.container = new Container(0, 0);
        new Loop(container).start();
        System.out.println("Loop started");
    }
    public void empty() {
        container.empty();
    }
    public void restore() {
        container.restore();
    }
    public int getLevel() {
        return container.getWastelvl();
    }
    public int getTemp() {
        return container.getTemp();
    }
    public boolean isFull() {
        return container.isFull();
    }
    public boolean isMaxTemp() {
        return container.isMaxTemp();
    }
}

