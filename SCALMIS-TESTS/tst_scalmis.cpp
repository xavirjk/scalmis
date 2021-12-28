#include <QtTest>

// add necessary includes here

class scalmis : public QObject
{
    Q_OBJECT

public:
    scalmis();
    ~scalmis();

private slots:
    void test_case1();

};

scalmis::scalmis()
{

}

scalmis::~scalmis()
{

}

void scalmis::test_case1()
{

}

QTEST_APPLESS_MAIN(scalmis)

#include "tst_scalmis.moc"
