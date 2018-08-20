#include "DbUtils.h"

DbUtils::DbUtils()
{

}


// 打开数据
void DbUtils::openDb()
{
    // 连接数据库
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("QTools.db");
    }

    // 打开数据库
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
}

// 创建软件类型表
void DbUtils::createSoftType()
{
    QSqlQuery query;
    QString check_sql = "select * from sqlite_master where name='SoftType'";
    QString create_sql = "create table SoftType (id INTEGER primary key, type TEXT UNIQUE, time TEXT)";

    // 检查表是否存在
    query.exec(check_sql);
    if (query.next())
    {
        return;
    }

    // 创建表
    if (!query.exec(create_sql))
    {
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 创建软件信息表
void DbUtils::createSoftInfo()
{
    QSqlQuery query;
    QString check_sql = "select * from sqlite_master where name='SoftInfo'";
    QString create_sql = "create table SoftInfo ("
                         "id INTEGER primary key,"
                         "tid INTEGER,"
                         "name TEXT UNIQUE,"
                         "path TEXT UNIQUE,"
                         "icon TEXT UNIQUE,"
                         "time TEXT,"
                         "foreign key (tid) references  SoftType(id) on delete cascade on update cascade);";

    // 检查表是否存在
    query.exec(check_sql);
    if (query.next())
    {
        return;
    }

    // 创建表
    if (!query.exec(create_sql))
    {
        qDebug() << "Error: Fail to create table." << query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }
}

// 获取软件类型
QList<QString> DbUtils::getSoftType()
{
    QSqlQuery query;
    QList<QString> lSoftType;     // 软件类型
    QString select_sql = "select type from SoftType order by id";

    if (!query.exec(select_sql))
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            QString type = query.value(0).toString();
            qDebug() << type;
            lSoftType.append(type);
        }
    }

    return lSoftType;
}

// 获取软件类型ID
QList<QString> DbUtils::getSoftTypeId()
{
    QSqlQuery query;
    QList<QString> lSoftTypeId;     // 软件类型ID
    QString select_sql = "select id from SoftType order by id";

    if (!query.exec(select_sql))
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            QString id = query.value(0).toString();
            lSoftTypeId.append(id);
        }
    }

    return lSoftTypeId;
}

// 获取软件名称
QList<QString> DbUtils::getSoftName(int tid)
{
    QSqlQuery query;
    QList<QString> lSoftName;   // 软件名称
    QString select_sql = QString("select name from SoftInfo where tid = %1 order by id").arg(tid);

    if (!query.exec(select_sql))
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            QString name = query.value(0).toString();
            lSoftName.append(name);
        }
    }

    return lSoftName;
}

// 获取软件路径
QList<QString> DbUtils::getSoftPath(int tid)
{
    QSqlQuery query;
    QList<QString> lSoftPath;   // 软件路径
    QString select_sql = QString("select path from SoftInfo where tid = %1 order by id").arg(tid);

    if (!query.exec(select_sql))
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            QString path = query.value(0).toString();
            lSoftPath.append(path);
        }
    }

    return lSoftPath;
}

// 获取软件图标
QList<QString> DbUtils::getSoftIcon(int tid)
{
    QSqlQuery query;
    QList<QString> lSoftIcon;           // 软件图标
    QString select_sql = QString("select icon from SoftInfo where tid = %1 order by id").arg(tid);

    if (!query.exec(select_sql))
    {
        qDebug() << query.lastError();
    }
    else
    {
        while (query.next())
        {
            QString icon = query.value(0).toString();
            lSoftIcon.append(icon);
        }
    }

    return lSoftIcon;
}

// 添加软件类型
bool DbUtils::insertSoftType(QString softType)
{
    QSqlQuery query;
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString("yyyy-MM-dd hh:mm:ss");
    QString insert_sql = QString("insert into SoftType (type, time) values ('%1', '%2')").arg(softType, time);
    if(!query.exec(insert_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "insert success!";
        return true;
    }
}

// 修改软件类型
bool DbUtils::updateSoftType(QString oldSoftType, QString newSoftType)
{
    QSqlQuery query;
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString("yyyy-MM-dd hh:mm:ss");
    QString update_sql = QString("update SoftType SET type = '%2', time = '%3' WHERE type = '%1'").arg(oldSoftType, newSoftType, time);
    if(!query.exec(update_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "update success!";
        return true;
    }
}

// 删除软件类型
bool DbUtils::deleteSoftType(QString softType)
{
    QSqlQuery query;
    QString delete_sql = QString("delete from SoftType where type = '%1'").arg(softType);
    if(!query.exec(delete_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "delete success!";
        return true;
    }
}

// 添加软件名称
bool DbUtils::insertSoftInfo(QString tid, QString name, QString path, QString icon)
{
    QSqlQuery query;
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString("yyyy-MM-dd hh:mm:ss");
    QString insert_sql = QString("insert into SoftInfo (tid, name, path, icon, time) values ('%1', '%2', '%3', '%4', '%5')").arg(tid, name, path, icon, time);
    if(!query.exec(insert_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "insert success!";
        return true;
    }
}

// 修改软件名称
bool DbUtils::updateSoftName(QString oldSoftName, QString newSoftName)
{
    QSqlQuery query;
    QDateTime dt = QDateTime::currentDateTime();
    QString time = dt.toString("yyyy-MM-dd hh:mm:ss");
    QString update_sql = QString("update SoftInfo SET name = '%2', time = '%3' WHERE type = '%1'").arg(oldSoftName, newSoftName, time);
    if(!query.exec(update_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "update success!";
        return true;
    }
}

// 删除软件
bool DbUtils::deleteSoftInfo(QString name)
{
    QSqlQuery query;
    QString delete_sql = QString("delete from SoftInfo where name = '%1'").arg(name);
    if(!query.exec(delete_sql))
    {
        qDebug() << query.lastError();
        return false;
    }
    else
    {
        qDebug() << "delete success!";
        return true;
    }
}
