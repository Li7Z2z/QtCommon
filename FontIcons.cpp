#include "FontIcons.h"

FontIcons::FontIcons()
{
    // 添加图标字体文件
    int fontId = QFontDatabase::addApplicationFont(":/Font/fontawesome-webfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    Q_ASSERT_X(fontFamilies.size() == 1,"Font","Font not exist");

    m_font.setFamily(fontFamilies.at(0));
}

FontIcons &FontIcons::Instance()
{
    static FontIcons _instance;
    return _instance;
}

QFont FontIcons::getFont()
{
    return m_font;
}

QChar FontIcons::getIconChar(FontIcons::IconCode code)
{
    return QChar((int)code);
}
