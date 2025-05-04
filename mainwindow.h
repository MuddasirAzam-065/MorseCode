#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_convert_clicked();
    void on_clear_clicked();
    void on_count_clicked();
    void on_play_clicked();
    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    QString convertToMorse(const QString &text);
    void playMorse(const QString &morseCode);

};
#endif // MAINWINDOW_H
