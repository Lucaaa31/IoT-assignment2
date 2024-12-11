package view;

import utilities.ScreenSize;

import javax.swing.*;
import javax.swing.border.MatteBorder;
import java.awt.*;
import java.util.Objects;
import controller.Controller;

public class WorkingPanel extends JPanel {
    private Controller controller;
    private final JProgressBar progressBar; // Barra principale
    public WorkingPanel(final Controller controller) {
        this.controller = controller;
        setLayout(new BorderLayout());
        setBorder(new MatteBorder(5, 5, 3, 5, Color.black));
        setBackground(Color.LIGHT_GRAY);

        setOpaque(true);

        // Carica e ridimensiona l'immagine
        ImageIcon originalIcon = new ImageIcon(Objects
                .requireNonNull(ClassLoader
                        .getSystemClassLoader().getResource("Battery.png")));
        Dimension screenSize = ScreenSize.getSize();

        // Calcola la dimensione ridimensionata, es. 50% della larghezza dello schermo
        int scaledWidth = screenSize.width / 8;
        int scaledHeight = scaledWidth * originalIcon.getIconHeight() / originalIcon.getIconWidth();
        Image scaledImage = originalIcon.getImage().getScaledInstance(scaledWidth, scaledHeight, Image.SCALE_SMOOTH);
        ImageIcon scaledIcon = new ImageIcon(scaledImage);

        JLabel imageLabel = new JLabel();
        imageLabel.setOpaque(true);
        imageLabel.setBackground(Color.LIGHT_GRAY);
        imageLabel.setIcon(scaledIcon);
        imageLabel.setLayout(new GridBagLayout()); // Layout per centrare la progressBar

        // Configura la barra verticale (Waste Level)
        progressBar = new JProgressBar(JProgressBar.VERTICAL);
        progressBar.setStringPainted(true);
        progressBar.setForeground(Color.GREEN);
        progressBar.setBackground(Color.DARK_GRAY);
        progressBar.setFont(new Font("Arial", Font.BOLD, 14));
        progressBar.setPreferredSize(new Dimension(200, 200)); // Aumenta larghezza verticale

        // Pannello per la barra e immagine
        JPanel progressPanel = new JPanel(new BorderLayout());
        progressPanel.setBackground(Color.LIGHT_GRAY);
        progressPanel.add(progressBar, BorderLayout.CENTER);

        JPanel centerPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);
        gbc.gridx = 0;
        centerPanel.add(imageLabel, gbc);

        gbc.gridx = 1;
        centerPanel.add(progressPanel, gbc);

        centerPanel.setBackground(Color.LIGHT_GRAY);

        // Aggiungi i componenti al pannello principale
        add(centerPanel, BorderLayout.CENTER); // Pannello centrale con immagine e progressBar centrati

        // Timer per aggiornare la barra
        Timer timer = new Timer(100, e -> updateProgress());
        timer.start();

        setVisible(true);
    }

    private void updateProgress() {
        int wasteLevel = controller.getLevel();
        if (controller.isFull()) {
            progressBar.setForeground(Color.RED);
            progressBar.setBackground(Color.RED);
            progressBar.setString("FULL");
        } else {
            progressBar.setForeground(Color.GREEN);
            progressBar.setBackground(Color.DARK_GRAY);
            progressBar.setValue(wasteLevel);
            progressBar.setString(wasteLevel + "%");
        }
    }
}