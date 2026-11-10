#pragma once
#include <QString>
#include <QDate>
#include <QList>
#include "step.h"

struct Goal {
    int id;
    QString title;
    QString description;
    QDate deadline;
    QList<Step> steps;
};