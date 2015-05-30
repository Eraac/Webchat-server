#include "modeluser.hpp"

Entity::Client* Model::ModelUser::loadUser(QString pUsername, QString pPassword)
{
    initDB();

    QSqlQuery query = m_db.exec("SELECT id, username, password FROM user WHERE username = ? AND password = ?");

    QString hashedPassword = Utility::EncodePassword::encodePassword(pPassword);

    query.bindValue(0, pUsername);
    query.bindValue(1, hashedPassword);
    query.exec();

    qDebug() << "Load User error SQL :" << query.lastError().text();

    Entity::Client *client = nullptr;

    if (query.first())
    {
        client = new Entity::Client(pUsername, query.value(0).toInt());
        client->setPassword(query.value(2).toString(), true);
    }

    return client;
}

void Model::ModelUser::persistUser(Entity::Client &user)
{
    initDB();

    if (0 == user.getId())
        insertUser(user);
    else
        updateUser(user);
}

void Model::ModelUser::insertUser(Entity::Client &user)
{
    qDebug() << "Insert user in database";

    QSqlQuery query = m_db.exec("INSERT user (username, password) VALUES (?)");

    query.bindValue(0, user.getUsername());
    query.bindValue(1, user.getPassword());

    query.exec();

    user.setId(query.lastInsertId().toInt());

    qDebug() << "Last error (insert) :" << query.lastError().text();
}

void Model::ModelUser::updateUser(Entity::Client &user)
{
    qDebug() << "Update user :" << user.getId();

    QString password = user.getPassword();

    if (!user.hasHashedPassword())
    {
        password = Utility::EncodePassword::encodePassword(user.getPassword());
        user.setPassword(password, true);
    }

    QSqlQuery query = m_db.exec("UPDATE user SET username = ?, password = ? WHERE id = ?");

    query.bindValue(0, user.getUsername());
    query.bindValue(1, password);
    query.bindValue(2, user.getId());

    query.exec();

    qDebug() << "Last error (update) :" << query.lastError().text();
}


