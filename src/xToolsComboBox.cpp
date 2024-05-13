/***************************************************************************************************
 * Copyright 2023-2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of xTools project.
 *
 * xTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "xToolsComboBox.h"

#include <QLineEdit>

xToolsComboBox::xToolsComboBox(QWidget* parent)
    : QComboBox(parent)
{
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

void xToolsComboBox::setCurrentIndexFromData(const QVariant& data)
{
    int ret = findData(data);
    if (ret != -1) {
        setCurrentIndex(ret);
    }
}

void xToolsComboBox::setGroupKey(const QString& group, const QString& key, bool isIndex)
{
    mKey = group + "/" + key;
    mIsIndex = isIndex;

}




