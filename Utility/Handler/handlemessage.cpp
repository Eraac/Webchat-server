#include "handlemessage.hpp"

Utility::HandleMessage::HandleMessage(const QString &pJson)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(pJson.toUtf8());

    m_json = jsonDocument.object();
}

bool Utility::HandleMessage::keyExist(const QString &pKey) const
{
    return m_json.contains(pKey);
}

QJsonValue Utility::HandleMessage::getKey(const QString &pKey, QJsonValue pDefaultValue) const
{
    if (m_json.contains(pKey))
        return m_json[pKey];
    else
        return pDefaultValue;
}

void Utility::HandleMessage::setKey(const QString &pKey, const QJsonValue &pValue)
{
    m_json.insert(pKey, pValue);
}

TypeMessage::Code Utility::HandleMessage::getType() const
{
    return static_cast<TypeMessage::Code> (getKey(KEY_TYPE, TypeMessage::NONE).toInt());
}

void Utility::HandleMessage::setType(const TypeMessage::Code &type)
{
    setKey(KEY_TYPE, type);
}

QString Utility::HandleMessage::toString() const
{
    QJsonDocument doc(m_json);

    return doc.toJson(QJsonDocument::Compact);
}
