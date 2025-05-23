#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "QtCore/qbuffer.h"
#include "player.h"
#include "signal-processing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent*);

    std::optional<SignalData> GetSignalData() const;

private:
    void CreateSignal();

private slots:

    void on_cb_type_currentIndexChanged(int index);

    void on_le_duration_editingFinished();

    void on_le_wavelength_editingFinished();

    void on_le_cycle_editingFinished();

    void on_le_amplitude_editingFinished();

    void on_btn_play_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<std::int16_t> data_;

    Player player_;

};
#endif // MAINWINDOW_H
