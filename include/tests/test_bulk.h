#pragma once
#include "block_processor.h"
#include "command_processor.h"
#include "stream.h"
#include "version.h"

#include <QtTest/QtTest>

class TestBulk : public QObject
{
    Q_OBJECT
private slots:
    void Test();
    void Test_data();
};