package view;

import javax.swing.*;
import java.awt.*;

import controller.Controller;

public class History extends JPanel {
    private JEditorPane statisticsPane; // Changed to JEditorPane
    private GraficoPanel graficoPanel;

    public History(final Controller controller) {
        statisticsPane = new JEditorPane(); // Changed to JEditorPane
        graficoPanel = new GraficoPanel(controller);
        this.add(graficoPanel);
        this.setBackground(Color.darkGray);
    }
}
