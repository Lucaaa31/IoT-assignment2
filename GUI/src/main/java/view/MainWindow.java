package view;

import controller.Controller;
import model.Container;
import utilities.ScreenSize;
import javax.swing.*;
import java.awt.*;

public class MainWindow extends JFrame {
    private WorkingPanel workingPanel;
    private RestoreButtonPanel restoreButtonPanel;
    private History history;
    private EmptyButtonPanel emptyButtonPanel;


    private JPanel mainPanel;

    public MainWindow(final Controller controller) {
        workingPanel = new WorkingPanel(controller);
        restoreButtonPanel = new RestoreButtonPanel(controller);
        history = new History(controller);
        emptyButtonPanel = new EmptyButtonPanel(controller);
        mainPanel = buildMainPanel();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        double width = ScreenSize.getWidth() / 1.2;
        double height = ScreenSize.getHeight() / 1.2;
        setSize((int) width,(int) height);

        setLocationRelativeTo(null);
        add(mainPanel);
        setVisible(true);

    }

    private JPanel buildMainPanel() {
        JPanel mainPanel = new JPanel();

        mainPanel.setLayout(new GridLayout(2, 2));
        mainPanel.setBackground(Color.darkGray);
        //mainPanel.setBorder(new MatteBorder(3, 3, 3, 3, Color.BLACK));

        mainPanel.add(workingPanel);
        mainPanel.add(history);
        mainPanel.add(restoreButtonPanel);
        mainPanel.add(emptyButtonPanel);

        return mainPanel;

    }


}
