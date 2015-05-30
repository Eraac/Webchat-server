#ifndef SERVER_HPP
#define SERVER_HPP

#include <QObject>
#include <QString>
#include <QWebSocketServer>
#include <vector>
#include "room.hpp"
#include "Utility/Handler/handleconnection.hpp"
#include "Utility/Handler/handlecommand.hpp"

class Server : public QObject
{
    Q_OBJECT

    public:
    explicit Server(QObject *pParent = nullptr);
    ~Server();

    void run(quint16 pPort);

    public slots:    
    void onNewConnection();
    void onNewUserConnected(Entity::Client *pClient);    
    void handleCommand(Utility::HandleMessage const& pMessage, Room *pRoom, Entity::Client *pClient);
    void addUserInRoom(QString const& pRoomName, Entity::Client *pClient);
    void deleteRoom(QString const& pRoom);

    private:
    std::vector<Room*>::iterator findRoom(QString const &pName);

    Utility::HandleConnection m_connectionHandler;
    Utility::HandleCommand m_commandHandler;
    QWebSocketServer m_server;
    std::vector<Room*> m_rooms;
};

#endif // SERVER_HPP

