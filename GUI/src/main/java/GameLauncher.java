
import controller.Controller;
import model.Container;
import model.Loop;
import view.MainWindow;

import java.awt.*;

public class GameLauncher {
    public static void main(String[] args) {
        Container container = new Container(0, 0);
        MainWindow mainWindow = new MainWindow(new Controller());
    }
}
