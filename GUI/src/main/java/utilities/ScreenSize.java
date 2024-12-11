package utilities;

import java.awt.*;

public class ScreenSize {

    public static int getWidth() {
        return Toolkit.getDefaultToolkit().getScreenSize().width;
    }

    public static int getHeight() {
        return Toolkit.getDefaultToolkit().getScreenSize().height;
    }

    public static java.awt.Dimension getSize() {
        return Toolkit.getDefaultToolkit().getScreenSize();
    }

}
