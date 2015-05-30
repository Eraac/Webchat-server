#include "handleconnection.hpp"

Utility::HandleConnection::HandleConnection(QObject *parent) :
    QObject(parent), m_userLoader(), m_queue()
{
}

Utility::HandleConnection::~HandleConnection()
{
    qDeleteAll(m_queue.begin(), m_queue.end());
}

void Utility::HandleConnection::handleConnection(QWebSocket *pSocket)
{
    qDebug() << "New connection (" << m_queue.size() + 1 << "socket in queue )";

    if (pSocket)
    {
        connect(pSocket, &QWebSocket::textMessageReceived, this, &HandleConnection::connectUser);
        connect(pSocket, &QWebSocket::disconnected, this, &HandleConnection::socketDisconnect);

        m_queue << pSocket;
    }
    else
        qDebug() << "Socket error";
}

void Utility::HandleConnection::connectUser(QString pAccount)
{
    qDebug() << "Client send authentification" << pAccount;

    QWebSocket *socket = qobject_cast<QWebSocket*> (sender());

    HandleMessage messageHandler{pAccount};

    try {

        Entity::Client *client = m_userLoader.loadUser(
            messageHandler.getKey("username").toString(),
            messageHandler.getKey("password").toString()
        );

        if (client)
            successConnect(socket, client);
        else {
            qDebug() << "Client send wrong password";
            errorConnect(socket, Error::WRONG_PASSWORD);
        }

    } catch (std::runtime_error e) {
        // Database not open
        errorConnect(socket, Error::SERVER_ERROR);

        // TODO Write log
        throw;
    }
}

void Utility::HandleConnection::successConnect(QWebSocket *pSocket, Entity::Client *pClient)
{
    qDebug() << "Client is authentified " << pClient->getUsername();

    if (pSocket)
    {
        disconnect(pSocket, &QWebSocket::textMessageReceived, this, &HandleConnection::connectUser);
        disconnect(pSocket, &QWebSocket::disconnected, this, &HandleConnection::socketDisconnect);

        pClient->setSocket(pSocket);
        m_queue.removeAll(pSocket);

        Utility::HandleMessage message;
            message.setType(TypeMessage::SUCCESS_MESSAGE);
            message.setKey("code", Success::CONNECTED);

        emit userConnected(pClient);
    }
    else {
        qDebug() << "Socket sender error";
        delete pClient;
    }
}

void Utility::HandleConnection::errorConnect(QWebSocket *pSocket, Error::Code code)
{    
    HandleMessage message{};

    message.setKey("code", code);
    message.setType(TypeMessage::ERROR_MESSAGE);

    pSocket->sendTextMessage(message.toString());
}

void Utility::HandleConnection::socketDisconnect()
{
    qDebug() << "Socket in queue disconnect (" << m_queue.size() - 1 << " socket in queue)";

    QWebSocket *socket = qobject_cast<QWebSocket*> (sender());

    if (socket)
    {
        m_queue.removeAll(socket);
        socket->deleteLater();
    }
}

