#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <QWebSocket>
#include <memory>
#include "Model/modeluser.hpp"

namespace Model {
    class ModelUser;
}

namespace Entity
{
    class Client
    {
        friend class Model::ModelUser;

        public:
        explicit Client(QString pUsername, unsigned int id = 0);
        ~Client();

        void sendTextMessage(QString const& pMessage);

        QString const getUsername() const;
        QWebSocket* getSocket() const;
        void setUsername(QString pUsername);
        void setSocket(QWebSocket *pSocket);
        void setPassword(QString const& pPassword, bool isHashed = false);

        private:
        void setId(unsigned int id);
        unsigned int getId() const;
        bool hasHashedPassword() const;
        QString getPassword() const;

        bool m_hasHashedPassword;
        unsigned int m_id;
        QString m_username;
        QString m_password;
        QWebSocket* m_socket;
    };
}

#endif // CLIENT_HPP


