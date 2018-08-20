#ifndef DBUTILS_H
#define DBUTILS_H

// 数据库类
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>

class DbUtils
{
public:
    DbUtils();

    // 打开数据
    static void openDb();
    // 创建软件类型表
    static void createSoftType();
    // 创建软件信息表
    static void createSoftInfo();
    // 获取软件类型
    static QList<QString> getSoftType();
    // 获取软件类型
    static QList<QString> getSoftTypeId();
    // 获取软件名称
    static QList<QString> getSoftName(int tid);
    // 获取软件路径
    static QList<QString> getSoftPath(int tid);
    // 获取软件图标
    static QList<QString> getSoftIcon(int tid);
    // 添加软件类型
    static bool insertSoftType(QString softType);
    // 修改软件类型
    static bool updateSoftType(QString oldSoftType, QString newSoftType);
    // 删除软件类型
    static bool deleteSoftType(QString softType);
    // 添加软件
    static bool insertSoftInfo(QString tid, QString name, QString path, QString icon);
    // 修改软件名称
    static bool updateSoftName(QString oldSoftName, QString newSoftName);
    // 删除软件
    static bool deleteSoftInfo(QString name);
};

#endif // DBUTILS_H
