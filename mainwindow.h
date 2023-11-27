#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();

private:
    Ui::MainWindow *ui;
    bool isPlayerX;
    int movesCount;
    QLabel *lblTurn; // Додана мітка для відображення черги гравця
    void checkForWinner();
    void endGame(const QString &winner);
    void resetGame();
    void updateTurnLabel(); // Додано для оновлення мітки черги гравця
};

#endif // MAINWINDOW_H
