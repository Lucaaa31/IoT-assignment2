package model;

import utilities.CommChannel;
import utilities.SerialCommChannel;

public class Loop extends Thread{
    private CommChannel channel;
    private Container container;
    private enum AllarmType {
        FULL, TEMPERATURE, NULL
    }
    private AllarmType allarmType;

    public Loop(Container container) {
        this.allarmType = AllarmType.NULL;
        this.container = container;
    }

    public void run() {
        try {
            channel = new SerialCommChannel("/dev/cu.usbmodem101", 9600);
            System.out.println("Channel created");
            System.out.println("Waiting Arduino for rebooting...");
            Thread.sleep(4000);
            System.out.println("Ready.");

            System.out.println("Done. Let's start.");

        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        while(true) {

                try {
                    receive();
                } catch (Exception ignored) {

                }

        }
    }

    void receive(){
        String msg = null;
        try {
            msg = channel.receiveMsg();

        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        try {
            if (msg.startsWith("F")) {
                allarmType = AllarmType.FULL;
                System.out.println("FULL");
                container.setFull(true);
            } else if (msg.startsWith("A")) {
                allarmType = AllarmType.TEMPERATURE;
                container.setMaxTemp(true);
                System.out.println("TEMPERATURE");
            } else if (msg.startsWith("L")) {
                String livello = msg.replaceAll("L(\\d+)T.*", "$1");
                String temperatura = msg.replaceAll(".*T(\\d+)", "$1");
                container.setTemp(Integer.parseInt(temperatura));
                container.setWastelvl(Integer.parseInt(livello));
                /*
                System.out.println("LEVEL: " + livello);
                System.out.println("TEMPERATURE: " + temperatura);
                 */
            } else {
                send();
            }
        } catch (NumberFormatException  e) {
            System.out.println("Error: " + e.getMessage());
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    void send() throws InterruptedException {
        if (!container.isFull() && allarmType == AllarmType.FULL) {
            System.out.println("EMPTY");
            this.allarmType = AllarmType.NULL;
            channel.sendMsg("EMPTY");
        } else if (!container.isMaxTemp() && allarmType == AllarmType.TEMPERATURE) {
            System.out.println("RESTORE");
            this.allarmType = AllarmType.NULL;
            channel.sendMsg("RESTORE");
        } else {
            channel.sendMsg("X");
        }
    }
}