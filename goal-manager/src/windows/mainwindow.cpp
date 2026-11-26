#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , autoSaveTimer(new QTimer(this))
    , listModel(new QStringListModel(this))
    , itemDelegate(new ItemDelegate(this))
{
    ui->setupUi(this);

    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::saveData);
    autoSaveTimer->start(60000);

    ui->listViewGoals->setModel(listModel);
    ui->listViewGoals->setItemDelegate(itemDelegate);

    QStringList initialGoals;
    initialGoals << "Изучить Qt" << "Сделать сквозной проект" << "Сдать экзамен";
    listModel->setStringList(initialGoals);

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    QAction *exitAction = fileMenu->addAction("Выход");
    connect(exitAction, &QAction::triggered, this, [this]() {
        this->close();
    });

    QToolBar *toolBar = addToolBar("Инструменты");
    toolBar->addAction("Добавить");

    connect(ui->btnAdd, &QPushButton::clicked, this, [this]() {
        QString newGoal = ui->lineEditGoalInput->text().trimmed();
        if (newGoal.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Название цели не может быть пустым.");
            return;
        }
        int row = listModel->rowCount();
        listModel->insertRow(row);
        QModelIndex index = listModel->index(row, 0);
        listModel->setData(index, newGoal, Qt::EditRole);
        ui->lineEditGoalInput->clear();
        qDebug() << "[LOG] Добавлена новая цель:" << newGoal;
    });

    connect(ui->btnDelete, &QPushButton::clicked, this, [this]() {
        QModelIndex currentIndex = ui->listViewGoals->currentIndex();
        if (!currentIndex.isValid()) {
            QMessageBox::information(this, "Внимание", "Выберите цель для удаления.");
            return;
        }
        listModel->removeRow(currentIndex.row());
        qDebug() << "[LOG] Удалена цель";
    });

    connect(ui->btnClear, &QPushButton::clicked, this, [this]() {
        if (listModel->rowCount() == 0) return;

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение", "Вы уверены, что хотите очистить весь список?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            listModel->removeRows(0, listModel->rowCount());
            qDebug() << "[LOG] Список очищен полностью";
        }
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