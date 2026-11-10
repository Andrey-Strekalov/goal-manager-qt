#include "windows/mainwindow.h"
#include <QDebug>
#include "core/goalvalidator.h"
#include "core/goalcalculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    // Внутри MainWindow::MainWindow():
    Goal testGoal;
    testGoal.deadline = QDate::currentDate().addDays(10); // Дедлайн через 10 дней
    testGoal.steps = { {1, "Шаг 1", true}, {2, "Шаг 2", false}, {3, "Шаг 3", true} };

    // Тестируем логику
    qDebug() << "Прогресс:" << GoalCalculator::calculateProgress(testGoal) << "%";
    // Выведет 66% (потому что 2 из 3 шагов выполнены)

    qDebug() << "Дней до дедлайна:" << GoalCalculator::daysUntilDeadline(testGoal.deadline);
    // Выведет 10

    auto validation = GoalValidator::validateGoal("", QDate::currentDate().addDays(-5));
    qDebug() << "Валидация (пустое имя и прошлое):" << validation.first << validation.second;
    // Выведет false и "Название цели не может быть пустым."


    return QApplication::exec();
}
