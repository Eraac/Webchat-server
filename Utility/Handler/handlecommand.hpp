#ifndef HANDLECOMMAND_HPP
#define HANDLECOMMAND_HPP

#include <QObject>
#include <QString>
#include "Utility/code.hpp"
#include "room.hpp"
#include "Entity/client.hpp"

namespace Utility
{
    class HandleCommand : public QObject
    {
        Q_OBJECT

        public:
        void command(HandleMessage const& pCommand, Room *pRoom, Entity::Client *pClient);

        signals:
        void changeUserRoom(QString const& pNewRoom, Entity::Client *pClient);

        private:
        void updatePassword(QString const& pNewPassword, Entity::Client *pClient);
        void joinRoom(QString const& pNewRoom, Room *pOldRoom, Entity::Client *pClient);
    };
}

#endif // HANDLECOMMAND_HPP

