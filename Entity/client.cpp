#include "client.hpp"

Entity::Client::Client(QString pUsername, unsigned int id) : m_hasHashedPassword(false),
    m_id(id), m_username(pUsername), m_password(), m_socket()
{

}

Entity::Client::~Client()
{
    qDebug() << "Client delete";
    m_socket->deleteLater();
}

void Entity::Client::sendTextMessage(QString const& pMessage)
{
    m_socket->sendTextMessage(pMessage);
}

QString const Entity::Client::getUsername() const
{
    return m_username;
}

QWebSocket* Entity::Client::getSocket() const
{
    return m_socket;
}

void Entity::Client::setUsername(QString pUsername)
{
    m_username = pUsername;
}

void Entity::Client::setSocket(QWebSocket *pSocket)
{
    delete m_socket;

    m_socket = pSocket;
}

void Entity::Client::setId(unsigned int id)
{
    m_id = id;
}

void Entity::Client::setPassword(const QString &pPassword, bool isHashed)
{
    m_password = pPassword;
    m_hasHashedPassword = isHashed;
}

unsigned int Entity::Client::getId() const
{
    return m_id;
}

bool Entity::Client::hasHashedPassword() const
{
    return m_hasHashedPassword;
}

QString Entity::Client::getPassword() const
{
    return m_password;
}
