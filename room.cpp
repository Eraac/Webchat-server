#include "room.hpp"

Room::Room(const QString &pName, QObject *pParent) : QObject(pParent), m_name(pName), m_clients()
{
    qDebug() << "New room :" << pName;
}

Room::~Room()
{
    qDebug() << "Delete room :" << m_name;
    qDeleteAll(m_clients.begin(), m_clients.end());
}

QString Room::getName() const
{
    return m_name;
}

void Room::addClient(Entity::Client *pClient)
{
    if (pClient->getSocket())
    {
        qDebug() << "User connected (" << pClient->getUsername() << ") in room :" << m_name << "(" << m_clients.size() + 1 << ")";

        connect(pClient->getSocket(), &QWebSocket::textMessageReceived, this, &Room::processMessage);
        connect(pClient->getSocket(), &QWebSocket::disconnected, this, &Room::socketDisconnect);

        m_clients << pClient;

        Utility::HandleMessage message{};
            message.setKey("username", pClient->getUsername());
            message.setType(TypeMessage::NEW_USER);

            sendMessage(message.toString());
    }
    else
    {
        qDebug() << "Error";
        delete pClient;
    }
}

void Room::disconnectUser(Entity::Client *pClient, Reason::Code pReason)
{
    if (pClient)
    {
        qDebug() << "User in room (" << m_name << ") disconnected (" << pClient->getUsername() << ")" << "(" << m_clients.size() - 1 << ")";;

        disconnect(pClient->getSocket(), &QWebSocket::textMessageReceived, this, &Room::processMessage);
        disconnect(pClient->getSocket(), &QWebSocket::disconnected, this, &Room::socketDisconnect);

        Utility::HandleMessage message{};
            message.setType(TypeMessage::DISCONNET_USER);
            message.setKey("username", pClient->getUsername());
            message.setKey("reason", pReason);

        m_clients.removeAll(pClient);

        sendMessage(message.toString());
    }

    if (0 == m_clients.size())
        emit roomEmpty(m_name);
}

void Room::socketDisconnect()
{
    Entity::Client* client = whoisSender();

    if (client)
    {        
        disconnectUser(client, Reason::DISCONNECT);
        delete client;
    }
}

void Room::processMessage(QString pMessage)
{
    auto client = whoisSender();
    QString usernameSender = client->getUsername();
    qDebug() << "Message receive :" << pMessage << "by" << usernameSender;

    Utility::HandleMessage messageHandler{pMessage};

    if (TypeMessage::USER_MESSAGE == messageHandler.getType())
    {
        messageHandler.setKey("username", usernameSender);

        sendMessage(messageHandler.toString());
    }
    else if (TypeMessage::COMMAND == messageHandler.getType())
    {
        emit commandSended(messageHandler, this, client);
    }
    else
    {
        messageHandler.setType(TypeMessage::ERROR_MESSAGE);
        messageHandler.setKey("code", Error::UNKNOW_TYPE);

        client->sendTextMessage(messageHandler.toString());
    }
}

void Room::sendMessage(const QString &pMessage) const
{
    std::for_each(m_clients.cbegin(), m_clients.cend(),
        [&](Entity::Client *pClient) {
            pClient->sendTextMessage(pMessage);
        });
}

Entity::Client* Room::whoisSender() const
{
    QWebSocket *pSocket = qobject_cast<QWebSocket *>(sender());

    if (pSocket)
    {
        auto it = std::find_if(m_clients.cbegin(), m_clients.cend(),
            [&](Entity::Client *pClient) {
                return (pClient->getSocket() == pSocket);
            });

        if (it == m_clients.cend()) {
            return nullptr;
        } else {
            return *it;
        }
    }
    else {
        return nullptr;
    }

}
