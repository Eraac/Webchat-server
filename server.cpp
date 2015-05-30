#include "server.hpp"

Server::Server(QObject *pParent) :
    QObject(pParent), m_connectionHandler(this), m_commandHandler(),
    m_server("Chat server", QWebSocketServer::NonSecureMode, this),
    m_rooms()
{
    connect(&m_commandHandler, &Utility::HandleCommand::changeUserRoom, this, &Server::addUserInRoom);
}

Server::~Server()
{

}

void Server::run(quint16 pPort)
{
    if (m_server.listen(QHostAddress::Any, pPort))
    {
        qDebug() << "Server start on port :" << pPort;
        qDebug() << "Max connection is :" << m_server.maxPendingConnections();

        connect(&m_server, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
        connect(&m_connectionHandler, &Utility::HandleConnection::userConnected, this, &Server::onNewUserConnected);
    }
    else
        throw std::runtime_error("Server is not open");
}

void Server::onNewConnection()
{
    QWebSocket *socket = m_server.nextPendingConnection();

    m_connectionHandler.handleConnection(socket);
}

void Server::onNewUserConnected(Entity::Client *pClient)
{
    addUserInRoom("default", pClient);
}

void Server::handleCommand(const Utility::HandleMessage &pMessage, Room *pRoom, Entity::Client *pClient)
{
    m_commandHandler.command(pMessage, pRoom, pClient);
}

void Server::addUserInRoom(const QString &pRoomName, Entity::Client *pClient)
{
    auto room = findRoom(pRoomName);

    if (room != m_rooms.end())
    {
        (*room)->addClient(pClient);
    }
    else
    {
        auto room = new Room{pRoomName, this};
            room->addClient(pClient);

        connect(room, &Room::roomEmpty, this, &Server::deleteRoom);
        connect(room, &Room::commandSended, this, &Server::handleCommand);

        m_rooms.push_back(room);
    }
}

std::vector<Room*>::iterator Server::findRoom(const QString &pName)
{
    return std::find_if(m_rooms.begin(), m_rooms.end(),
            [&](Room *pRoom) {
                return (pRoom->getName() == pName);
            });
}

void Server::deleteRoom(QString const& pRoomName)
{
    auto room = findRoom(pRoomName);

    disconnect(*room, &Room::roomEmpty, this, &Server::deleteRoom);
    disconnect(*room, &Room::commandSended, this, &Server::handleCommand);

    (*room)->deleteLater();
    m_rooms.erase(room);
}
