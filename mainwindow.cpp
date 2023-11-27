#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isPlayerX(true),
    movesCount(0)
{
    ui->setupUi(this);

    ui->btn_1->setFixedSize(80, 80);
    ui->btn_2->setFixedSize(80, 80);
    ui->btn_3->setFixedSize(80, 80);
    ui->btn_4->setFixedSize(80, 80);
    ui->btn_5->setFixedSize(80, 80);
    ui->btn_6->setFixedSize(80, 80);
    ui->btn_7->setFixedSize(80, 80);
    ui->btn_8->setFixedSize(80, 80);
    ui->btn_9->setFixedSize(80, 80);

    ui->statusBar->showMessage("Черга хрестиків");

    setWindowTitle("Хрестики-нулики");

    // Connect all buttons to the same slot
    connect(ui->btn_1, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_2, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_3, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_4, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_5, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_6, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_7, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_8, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
    connect(ui->btn_9, SIGNAL(clicked()), this, SLOT(handleButtonClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        if (button->text().isEmpty()) {
            button->setText(isPlayerX ? "X" : "O");
            isPlayerX = !isPlayerX;
            movesCount++;

            // Оновлення напису про те, чия черга ходити
            ui->statusBar->showMessage(isPlayerX ? "Черга хрестиків" : "Черга нуликів");

            checkForWinner();
        }
    }
}


void MainWindow::checkForWinner()
{
    // Create a 2D array to represent the buttons in the grid
    QPushButton* buttons[3][3] = {
        { ui->btn_1, ui->btn_2, ui->btn_3 },
        { ui->btn_4, ui->btn_5, ui->btn_6 },
        { ui->btn_7, ui->btn_8, ui->btn_9 }
    };

    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (buttons[i][0]->text() == buttons[i][1]->text() &&
            buttons[i][1]->text() == buttons[i][2]->text() &&
            !buttons[i][0]->text().isEmpty()) {
            endGame(buttons[i][0]->text());
            return;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (buttons[0][i]->text() == buttons[1][i]->text() &&
            buttons[1][i]->text() == buttons[2][i]->text() &&
            !buttons[0][i]->text().isEmpty()) {
            endGame(buttons[0][i]->text());
            return;
        }
    }

    // Check diagonals
    if (buttons[0][0]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][2]->text() &&
        !buttons[0][0]->text().isEmpty()) {
        endGame(buttons[0][0]->text());
        return;
    }

    if (buttons[0][2]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][0]->text() &&
        !buttons[0][2]->text().isEmpty()) {
        endGame(buttons[0][2]->text());
        return;
    }

    // Check for a draw
    if (movesCount == 9) {
        endGame("Нічия!");
    }
}

void MainWindow::endGame(const QString &winner)
{
    QString message;
    if (winner == "Нічия!") {
        message = "Гра закінчилась нічиєю!";
    } else {
        message = QString("%1 виграли!").arg(winner);
    }

    // Вивести повідомлення
    QMessageBox::information(this, "Результат", message);

    // Оновити інформацію про чергу гравця
    isPlayerX = true;
    movesCount = 0;
    ui->statusBar->showMessage("Черга хрестиків!");

    // Очистити всі кнопки
    resetGame();
}

void MainWindow::resetGame()
{
    // Clear all buttons
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton *button = qobject_cast<QPushButton*>(ui->gridLayout->itemAtPosition(i, j)->widget());
            button->setText("");
        }
    }

    // Reset game state
    isPlayerX = true;
    movesCount = 0;
}
