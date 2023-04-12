#ifndef CHANELPARADAO_H
#define CHANELPARADAO_H
#include <QMap>
#include <QSqlDatabase>
#include <dbconnection.h>
#include <dbtransienttasktmconfigdao.h>
#include <dbtransienttasktsconfigdao.h>
#include <dbiedinfodao.h>
#include <dbstationinfodao.h>
#include <dbbayinfodao.h>

class ChanelParaDAO
{
public:
    ChanelParaDAO();
    ~ChanelParaDAO();

public:
    static QString getStationName();
    static QString getBayName(const QString &);
    static QList<QStringList> getIedInfoList();
    static QStringList getIedInfo(const QString &);
    //模拟量
    QList<QStringList> getComtradeFactor();
    //开关量
    QList<QStringList> getSwitchComtradeFactor();

    bool init(const QString);
    bool getDbInfo();

private:
    bool dbInfoFlag;
    QSqlDatabase db;
};

#endif // CHANELPARADAO_H
