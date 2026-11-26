#include "goalvalidator.h"

QPair<bool, QString> GoalValidator::validateGoal(const QString& title, const QDate& deadline) {
    if (title.trimmed().isEmpty()) {
        return {false, "Название цели не может быть пустым."};
    }
    if (!deadline.isValid()) {
        return {false, "Указана некорректная дата."};
    }
    if (deadline < QDate::currentDate()) {
        return {false, "Дедлайн не может быть в прошлом."};
    }
    return {true, ""};
}

QPair<bool, QString> GoalValidator::validateProgress(int progress) {
    if (progress < 0 || progress > 100) {
        return {false, "Прогресс должен быть от 0 до 100."};
    }
    return {true, ""};
}