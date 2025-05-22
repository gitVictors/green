#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

#include <QThread>

#include "signal-processing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* e) {
    QPainter painter(this);

    const auto x_off = ui->widget->geometry().left();
    const auto y_off = ui->widget->geometry().top();
    const auto w = ui->widget->width();
    const auto h = ui->widget->height();

    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);

    painter.drawRect(QRect{x_off, y_off, w, h});

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);

    auto data = GetSignalData();
    if (!data) {
        return;
    }

    int src_amplitude = 1 << 15;

    const int padding = 10;
    auto dst_amplitude = h / 2 - padding;

    auto to_draw = std::min(w, static_cast<int>(data_.size()));

    std::vector<QPointF> points;
    points.reserve(to_draw);
    for (int i = 0; i < to_draw; ++i) {
        points.push_back({x_off + double(i), y_off + h / 2 - double(data_[i]) * dst_amplitude / src_amplitude});
    }

    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.drawPolyline(points.data(), points.size());

    QMainWindow::paintEvent(e);
}

std::optional<SignalData> MainWindow::GetSignalData() const {
    bool is_ok = false;
    const int samples = ui->le_duration->text().toInt(&is_ok);

    if(!is_ok) {
        return std::nullopt;
    }

    int amplitude = ui->le_amplitude->text().toInt(&is_ok);

    if (!is_ok || amplitude <= 0 || amplitude >= (1 << 15)) {
        return std::nullopt;
    }

    int wavelength = ui->le_wavelength->text().toInt(&is_ok);

    if (!is_ok || wavelength <= 0 || samples < wavelength) {
        return std::nullopt;
    }

    double cycle = ui->le_cycle->text().toDouble(&is_ok);

    if (!is_ok || cycle < 0 || cycle > 1) {
        return std::nullopt;
    }

    SignalType signal_type;
    int index = ui->cb_type->currentIndex();
    switch(index) {
    case 1: signal_type = SignalType::kSin; break;
    case 2: signal_type = SignalType::kCos; break;
    case 3: signal_type = SignalType::kMeander; break;
    default:
        return std::nullopt;
    }

    return SignalData{
        .signal_type = signal_type,
        .samples = samples,
        .wave_length = wavelength,
        .amplitude = static_cast<int16_t>(amplitude),
        .cycle = cycle,
    };
}

void MainWindow::on_cb_type_currentIndexChanged([[maybe_unused]]int index) {
    CreateSignal();
}

void MainWindow::on_le_duration_editingFinished() {
    CreateSignal();
}

void MainWindow::on_le_wavelength_editingFinished() {
    CreateSignal();
}

void MainWindow::on_le_cycle_editingFinished() {
    CreateSignal();
}

void MainWindow::on_le_amplitude_editingFinished() {
    CreateSignal();
}

void MainWindow::CreateSignal() {
    // Обновите сигнал.
    // 1. Получите параметры сигнала через метод GetSignalData().
    // 2. Проверьте, что они корректные.
    // 3. Постройте сигнал, используя функцию GenerateSignal
    //    из файла signal-processing.h и сохраните его в поле data_.
    // 4. Перерисуйте окно, вызвав repaint().
}

void MainWindow::on_btn_play_clicked() {
    // Воспроизведите звук.
    // 1. Скопируйте вектор в локальную переменную.
    // 2. Примените к копии ApplyDecayAndAttack с параметром 12000.
    // 3. Добавьте в конец 1200 нулевых отсчётов используя std::fill_n.
    // 4. Проиграйте, используя player_.Play.
}
