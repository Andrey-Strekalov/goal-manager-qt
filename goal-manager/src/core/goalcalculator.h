#pragma once
#include <QDate>
#include "goal.h"

class GoalCalculator {
public:
    // Высчитывает процент выполнения на основе шагов (от 0 до 100)
    static int calculateProgress(const Goal& goal);

    // Сколько дней осталось до дедлайна (если отрицательное - значит просрочено)
    static int daysUntilDeadline(const QDate& deadline);

    // Просрочена ли цель
    static bool isOverdue(const QDate& deadline);
};