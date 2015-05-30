#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include <QString>

const QString DB_HOST = "host";
const QString DB_NAME = "name";
const QString DB_USER = "user";
const QString DB_PASS = "pass";
const QString DB_PORT = "port";
const QString CHAT_PORT = "chat_port";
const QString FILE_INI = "settings.ini";

namespace Utility
{
    class Settings
    {
        public:
        Settings();
        QVariant getSettings(QString const& pKey, QVariant const& pDefautValue = "");

        private:
        QSettings m_ini;
    };
}

#endif // SETTINGS_HPP

