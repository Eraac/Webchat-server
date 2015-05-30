#ifndef HANDLECONNECTION_HPP
#define HANDLECONNECTION_HPP

#include <QMap>
#include <QList>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "Entity/client.hpp"
#include "Utility/code.hpp"
#include "Utility/Handler/handlemessage.hpp"

namespace Utility
{
    class HandleConnection : public QObject
    {
        Q_OBJECT

        public:
        explicit HandleConnection(QObject *parent = nullptr);
        ~HandleConnection();

        void handleConnection(QWebSocket *pSocket);

        signals:
        void userConnected(Entity::Client *client);

        private slots:
        void connectUser(QString pAccount);
        void socketDisconnect();

        private:
        void successConnect(QWebSocket *pSocket, Entity::Client *pClient);
        void errorConnect(QWebSocket *pSocket, Error::Code code);

        Model::ModelUser m_userLoader;
        QList<QWebSocket*> m_queue;
    };
}

#endif // HANDLECONNECTION_HPP


