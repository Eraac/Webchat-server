#ifndef ROOM_HPP
#define ROOM_HPP

#include <QString>
#include <QList>
#include "Entity/client.hpp"
#include "Utility/Handler/handlemessage.hpp"

class Room : public QObject
{
    Q_OBJECT

    public:
    Room() = default;
    Room(QString const& pName, QObject *pParent = nullptr);
    ~Room();

    QString getName() const;

    void addClient(Entity::Client* pClient);
    void disconnectUser(Entity::Client *pClient, Reason::Code pReason);
    void socketDisconnect();

    void processMessage(QString pMessage);
    void sendMessage(QString const& pMessage) const;

    signals:
    void roomEmpty(QString const& roomName);
    void commandSended(Utility::HandleMessage const& message, Room *room, Entity::Client *client);

    private:
    Entity::Client* whoisSender() const;

    QString m_name;
    QList<Entity::Client*> m_clients;
};

#endif // ROOM_HPP

