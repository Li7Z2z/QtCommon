#ifndef XMLDATA_H
#define XMLDATA_H

// 正常显示中文
#pragma execution_character_set("utf-8")

#include "pugixml.hpp"
#include <QDebug>
#include <QList>
#include <QDir>

// XML文件路径
const char xmlFilePath[64] = "./softinfo.xml";

class XmlData
{
public:
    XmlData();

    // 读取XML文件
    static bool readXml();
    // 创建文件夹
    static bool createFolder(QString dirPath);
    // 判断软件名是否存在
    static bool isExist(QString softName);
    // 添加软件到XML文件中
    static bool addSoftToXml(QString softType, const char *softName, const char *softPath, const char *softIcon);
    // XML文件中删除软件
    static bool removeSoftXml(QString name);
    // XML文件中修改软件名
    static bool modifySoftNameXml(const char *oldName, const char *newName);

public:
    static QList<QString>           lSoftType;  // 软件类型
    static QList<QList<QString> >   llSoftName; // 软件名称
    static QList<QList<QString> >   llSoftPath; // 软件路径
    static QList<QList<QString> >   llSoftIcon; // 软件图标
};

#endif // XMLDATA_H
