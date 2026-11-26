#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , autoSaveTimer(new QTimer(this))
{
    ui->setupUi(this);

    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::saveData);
    autoSaveTimer->start(60000);

    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *saveAction = fileMenu->addAction("Сохранить сейчас");
    connect(saveAction, &QAction::triggered, this, [this]() {
        qDebug() << "[LOG] Пользователь нажал 'Сохранить сейчас'";
        saveData();
    });

    QAction *exitAction = fileMenu->addAction("Выход");
    connect(exitAction, &QAction::triggered, this, [this]() {
        qDebug() << "[LOG] Пользователь закрывает приложение.";
        this->close();
    });

    QMenu *helpMenu = menuBar()->addMenu("Справка");
    QAction *aboutAction = helpMenu->addAction("О программе");
    connect(aboutAction, &QAction::triggered, this, []() {
        qDebug() << "[LOG] Пользователь открыл окно 'О программе'";
    });

    QToolBar *toolBar = addToolBar("Инструменты");

    QAction *addAction = toolBar->addAction("Добавить");
    connect(addAction, &QAction::triggered, this, []() {
        qDebug() << "[LOG] Пользователь нажал кнопку 'Добавить'";
    });

    QAction *deleteAction = toolBar->addAction("Удалить");
    connect(deleteAction, &QAction::triggered, this, []() {
        qDebug() << "[LOG] Пользователь нажал кнопку 'Удалить'";
    });

    statusBar()->showMessage("Готов к работе");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveData()
{
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    qDebug() << "[AUTOSAVE] Автоматическое сохранение данных выполнено в" << currentTime;
    statusBar()->showMessage("Данные автосохранены", 2000);
}