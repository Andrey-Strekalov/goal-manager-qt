#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStringListModel>
#include "../core/itemdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void saveData();

private:
    Ui::MainWindow *ui;
    QTimer *autoSaveTimer;
    QStringListModel *listModel;
    ItemDelegate *itemDelegate;
};

#endif // MAINWINDOW_H