#ifndef MODEL_HPP
#define MODEL_HPP

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <stdexcept>
#include "Utility/settings.hpp"

namespace Model
{
    class BaseModel
    {
        protected:
        void initDB();
        static QSqlDatabase m_db;
    };
}

#endif // MODEL_HPP
