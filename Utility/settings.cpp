#include "settings.hpp"

Utility::Settings::Settings() : m_ini(FILE_INI, QSettings::Format::IniFormat)
{
    // TODO Optimiser m_ini pour qu'il soit loader une seule fois (et non à chaque appel)

    m_ini.setValue(DB_HOST, "127.0.0.1");
    m_ini.setValue(DB_NAME, "webchat");
    m_ini.setValue(DB_USER, "webchat");
    m_ini.setValue(DB_PASS, "webchatpass");
    m_ini.setValue(DB_PORT, 3306);
    m_ini.setValue(CHAT_PORT, 12345);
}

QVariant Utility::Settings::getSettings(const QString &pKey, QVariant const& pDefaultValue)
{
    return m_ini.value(pKey, pDefaultValue);
}
