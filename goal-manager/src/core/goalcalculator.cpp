#include "goalcalculator.h"

int GoalCalculator::calculateProgress(const Goal& goal) {
    if (goal.steps.isEmpty()) {
        return 0; // Если шагов нет, прогресс 0%
    }

    int completed = 0;
    for (const Step& step : goal.steps) {
        if (step.isCompleted) {
            completed++;
        }
    }

    // Считаем процент: (выполненные / всего) * 100
    return (completed * 100) / goal.steps.size();
}

int GoalCalculator::daysUntilDeadline(const QDate& deadline) {
    return QDate::currentDate().daysTo(deadline);
}

bool GoalCalculator::isOverdue(const QDate& deadline) {
    return daysUntilDeadline(deadline) < 0;
}