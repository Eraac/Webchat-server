#ifndef HANDLEMESSAGE_HPP
#define HANDLEMESSAGE_HPP

#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QString>
#include "Utility/code.hpp"


const QString KEY_TYPE = "type";

namespace Utility
{
    class HandleMessage
    {
        public:
        HandleMessage() = default;
        HandleMessage(QString const& pJson);

        bool keyExist(QString const& pKey) const;

        QJsonValue getKey(QString const& pKey, QJsonValue pDefaultValue = QJsonValue()) const;
        void setKey(QString const& pKey, QJsonValue const& pValue);

        TypeMessage::Code getType() const;
        void setType (TypeMessage::Code const& type);

        QString toString() const;

        private:
        QJsonObject m_json;
    };
}

#endif // HANDLEMESSAGE_HPP

