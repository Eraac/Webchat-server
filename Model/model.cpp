#include "model.hpp"

QSqlDatabase Model::BaseModel::m_db = QSqlDatabase();

void Model::BaseModel::initDB()
{    
    if (m_db.isOpen())
        return;

    qDebug() << "Init database";

    Utility::Settings settings;

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName(settings.getSettings(DB_HOST).toString());
    m_db.setDatabaseName(settings.getSettings(DB_NAME).toString());
    m_db.setUserName(settings.getSettings(DB_USER).toString());
    m_db.setPassword(settings.getSettings(DB_PASS).toString());
    m_db.setPort(settings.getSettings(DB_PORT).toInt());

    qDebug() << "Last error database (init) :" << m_db.lastError().text();

    bool ok = m_db.open();

    qDebug() << "Status database :" << ok;

    if (!ok) {
        throw std::runtime_error("Database is not open");
    }
}

