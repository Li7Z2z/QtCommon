#include "XmlData.h"

QList<QString>           XmlData::lSoftType;  // 软件类型
QList<QList<QString> >   XmlData::llSoftName; // 软件名称
QList<QList<QString> >   XmlData::llSoftPath; // 软件路径
QList<QList<QString> >   XmlData::llSoftIcon; // 软件图标

XmlData::XmlData()
{
    // 读取XML文件
    readXml();
}

// 读取XML文件
bool XmlData::readXml()
{
    // 清除已保存的数据
    lSoftType.clear();
    llSoftName.clear();
    llSoftPath.clear();
    llSoftIcon.clear();
    // 打开XML文件
    pugi::xml_document doc;
    if(!doc.load_file(xmlFilePath, pugi::parse_default, pugi::encoding_utf8))
    {
        qDebug() << "打开XML文件失败";
        return false;
    }
    // 读取根节点
    pugi::xml_node root = doc.child("root");
    // 读取第一个节点
    pugi::xml_node type = root.child("type");
    while (type)
    {
        // 软件类型
        lSoftType.append(type.attribute("name").value());
        // 创建软件类型文件夹
        QString dirPath = "./" + QString(type.attribute("name").value());
        createFolder(dirPath);
        // 软件名、路径、图标
        pugi::xml_node soft = type.child("soft");
        QStringList name;
        QStringList path;
        QStringList icon;
        while (soft)
        {
            name.append(soft.attribute("name").value());
            path.append(soft.attribute("path").value());
            icon.append(soft.attribute("icon").value());
            soft = soft.next_sibling();
        }
        llSoftName.append(name);
        llSoftPath.append(path);
        llSoftIcon.append(icon);
        type = type.next_sibling();
    }
    return true;
}

// 创建文件夹
bool XmlData::createFolder(QString dirPath)
{
    QDir dir;
    // 判断文件夹是否存在
    if (!dir.exists(dirPath))
    {
        // 不存在创建文件夹
        dir.mkdir(dirPath);
        return true;
    }
    return false;
}

// 判断软件名是否存在
bool XmlData::isExist(QString softName)
{
    // 打开XML文件
    pugi::xml_document doc;
    if(!doc.load_file(xmlFilePath, pugi::parse_default, pugi::encoding_utf8))
    {
        qDebug() << "打开XML文件失败";
        return false;
    }
    pugi::xml_node root = doc.child("root");
    // 读取第一个节点
    pugi::xml_node type = root.child("type");
    while (type)
    {
        // 查找软件名
        pugi::xml_node soft = type.child("soft");
        while (soft)
        {
            if (QString(soft.attribute("name").value()) == softName)
            {
                return true;
            }
            soft = soft.next_sibling();
        }
        type = type.next_sibling();
    }
    return false;
}

// 添加软件到XML文件中
bool XmlData::addSoftToXml(QString softType, const char *softName, const char *softPath, const char *softIcon)
{
    // 打开XML文件
    pugi::xml_document doc;
    if(!doc.load_file(xmlFilePath, pugi::parse_default, pugi::encoding_utf8))
    {
        qDebug() << "打开XML文件失败";
        return false;
    }
    pugi::xml_node root = doc.child("root");
    // 读取第一个节点
    pugi::xml_node type = root.child("type");
    while (type)
    {
        // 查找软件类型
        if (QString(type.attribute("name").value()) == softType)
        {
            pugi::xml_node soft = type.child("soft");
            while (soft)
            {
                if (QString(soft.attribute("name").value()) == "添加")
                {
                    // 添加节点
                    pugi::xml_node newNode = type.insert_child_before("soft", soft);
                    // 添加属性
                    newNode.append_attribute("name").set_value(softName);
                    newNode.append_attribute("path").set_value(softPath);
                    newNode.append_attribute("icon").set_value(softIcon);
                    // 保存XML文件
                    doc.save_file(xmlFilePath);
                    return true;
                }
                soft = soft.next_sibling();
            }
        }
        type = type.next_sibling();
    }
    return false;
}

// XML文件中删除软件
bool XmlData::removeSoftXml(QString name)
{
    // 打开XML文件
    pugi::xml_document doc;
    if(!doc.load_file(xmlFilePath, pugi::parse_default, pugi::encoding_utf8))
    {
        qDebug() << "打开XML文件失败";
        return false;
    }
    pugi::xml_node root = doc.child("root");
    // 读取第一个节点
    pugi::xml_node type = root.child("type");
    while (type)
    {
        // 查找软件名
        pugi::xml_node soft = type.child("soft");
        while (soft)
        {
            if (QString(soft.attribute("name").value()) == name)
            {
                // 删除软件
                type.remove_child(soft);
                // 保存XML文件
                doc.save_file(xmlFilePath);
                return true;
            }
            soft = soft.next_sibling();
        }
        type = type.next_sibling();
    }
    return false;
}

// XML文件中修改软件名
bool XmlData::modifySoftNameXml(const char *oldName, const char *newName)
{
    // 打开XML文件
    pugi::xml_document doc;
    if(!doc.load_file(xmlFilePath, pugi::parse_default, pugi::encoding_utf8))
    {
        qDebug() << "打开XML文件失败";
        return false;
    }
    pugi::xml_node root = doc.child("root");
    // 读取第一个节点
    pugi::xml_node type = root.child("type");
    while (type)
    {
        // 查找软件名
        pugi::xml_node soft = type.child("soft");
        while (soft)
        {
            if (QString(soft.attribute("name").value()) == QString(oldName))
            {
                // 修改属性
                soft.attribute("name").set_value(newName);
                // 保存XML文件
                doc.save_file(xmlFilePath);
                return true;
            }
            soft = soft.next_sibling();
        }
        type = type.next_sibling();
    }
    return false;
}
