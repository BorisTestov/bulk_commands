#include "test_bulk.h"

void TestBulk::Test_data()
{
    QTest::addColumn<QString>("inputBulk");
    QTest::addColumn<QString>("expectedBulk");

    QTest::addRow("Just commands")
        << "cmd1\ncmd2\ncmd3"
        << "bulk:cmd1,cmd2,cmd3";

    QTest::addRow("Big block")
        << "{\ncmd1\ncmd2\ncmd3\ncmd4\n}"
        << "bulk:cmd1,cmd2,cmd3,cmd4";

    QTest::addRow("Small block")
        << "{\ncmd1\ncmd2\n}"
        << "bulk:cmd1,cmd2";
}

void TestBulk::Test()
{
    QFETCH(QString, inputBulk);
    std::stringstream sstream;
    sstream << inputBulk.toStdString();
    Stream console(sstream);
    auto CP = std::make_shared<CommandProcessor>(3);
    auto BP = std::make_shared<BlockProcessor>();
    console.addObserver(CP);
    console.addObserver(BP);
    console.run();
    auto fileTime = CP->getTime();
    if (BP->getTime() < fileTime and BP->getTime() != 0)
    {
        fileTime = BP->getTime();
    }
    QString fileName = "bulk" + QString::number(fileTime) + ".log";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString errorMessage = "Can't open file " + fileName + " !";
        QFAIL(errorMessage.toStdString().c_str());
    }
    QTextStream in(&file);
    QString line = in.readLine();
    QString content;
    while (!line.isNull())
    {
        content += line;
        line = in.readLine();
    }
    QTEST(content, "expectedBulk");
}