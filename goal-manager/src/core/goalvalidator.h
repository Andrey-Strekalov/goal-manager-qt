#pragma once
#include <QString>
#include <QDate>
#include <QPair>

class GoalValidator {
public:
    // Возвращает true (успех) или false + текст ошибки
    static QPair<bool, QString> validateGoal(const QString& title, const QDate& deadline);
    static QPair<bool, QString> validateProgress(int progress);
};