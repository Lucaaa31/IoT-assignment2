package view;

import controller.Controller;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GraficoPanel extends JPanel {
    private final XYSeries tempSeries; // Serie per la temperatura
    private final XYSeries levelSeries; // Serie per il livello
    private final NumberAxis domainAxis; // Asse X per gestire il tempo
    private final Controller controller;

    public GraficoPanel(Controller controller) {
        this.controller = controller;
        // Inizializza le serie di dati
        tempSeries = new XYSeries("Temperatura");
        levelSeries = new XYSeries("Livello");

        initDataset();

        // Crea dataset per ogni serie
        XYSeriesCollection tempDataset = new XYSeriesCollection(tempSeries);
        XYSeriesCollection levelDataset = new XYSeriesCollection(levelSeries);

        // Crea il grafico
        JFreeChart grafico = ChartFactory.createXYLineChart(
                "Andamento Dinamico", // Titolo
                "Tempo (s)", // Asse X
                "Temperatura (°C)", // Asse Y (primario)
                tempDataset,
                PlotOrientation.VERTICAL,
                true,
                true,
                false
        );

        // Configura il secondo asse Y per il livello
        XYPlot plot = grafico.getXYPlot();
        domainAxis = (NumberAxis) plot.getDomainAxis();
        domainAxis.setRange(0, 30); // Mostra gli ultimi 30 secondi inizialmente
        domainAxis.setTickUnit(new NumberTickUnit(2)); // Incrementi di 5 secondi        domainAxis.setAutoTickUnitSelection(false);

        NumberAxis livelloAxis = new NumberAxis("Livello (%)");
        livelloAxis.setAxisLinePaint(Color.BLUE);
        livelloAxis.setLabelPaint(Color.BLUE);
        livelloAxis.setTickLabelPaint(Color.BLUE);
        plot.setRangeAxis(1, livelloAxis); // Assegna il secondo asse Y al plot
        plot.setDataset(1, levelDataset); // Collega il dataset al secondo asse
        plot.mapDatasetToRangeAxis(1, 1);

        // Configura i renderer per le serie
        XYLineAndShapeRenderer rendererTemp = new XYLineAndShapeRenderer();
        rendererTemp.setSeriesPaint(0, Color.RED); // Temperatura in rosso
        plot.setRenderer(0, rendererTemp);

        XYLineAndShapeRenderer rendererLevel = new XYLineAndShapeRenderer();
        rendererLevel.setSeriesPaint(0, Color.BLUE); // Livello in blu
        plot.setRenderer(1, rendererLevel);

        // Pannello grafico
        ChartPanel pannelloGrafico = new ChartPanel(grafico);
        pannelloGrafico.setMouseWheelEnabled(true); // Consente lo zoom con la rotella
        pannelloGrafico.setPreferredSize(new Dimension(750, 500)); // Dimensioni iniziali

        // Layout e aggiunta al pannello
        setLayout(new BorderLayout());
        add(pannelloGrafico, BorderLayout.CENTER);

        // Aggiungi il KeyListener per pulire il grafico
        setFocusable(true);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                    clearGraph(); // Pulizia del grafico
                }
            }
        });

        // Timer per aggiornare il grafico dinamicamente
        Timer timer = new Timer(500, new AggiornaDati());
        timer.start();
    }

    private void initDataset() {
        // Aggiungi valori iniziali per le serie
        tempSeries.add(0, controller.getTemp());
        levelSeries.add(0, controller.getLevel());
    }

    private void clearGraph() {
        // Svuota le serie di dati
        tempSeries.clear();
        levelSeries.clear();
        domainAxis.setRange(0, 30); // Reimposta il dominio
    }

    private class AggiornaDati implements ActionListener {
        private int counter = 5; // Contatore per il tempo (asse X), parte da 5

        @Override
        public void actionPerformed(ActionEvent e) {
            // Ottieni i nuovi valori dal contenitore
            double nuovaTemperatura = controller.getTemp();
            double nuovoLivello = controller.getLevel();

            // Aggiungi i nuovi valori alle serie
            tempSeries.add(counter, nuovaTemperatura);
            levelSeries.add(counter, nuovoLivello);

            // Aggiorna l'intervallo dell'asse X per mostrare solo gli ultimi 30 secondi
            domainAxis.setRange(Math.max(0, counter - 30), counter);

            counter += 2; // Incrementa di 5 secondi
        }
    }
}