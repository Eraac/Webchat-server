#ifndef MODELUSER_HPP
#define MODELUSER_HPP

#include <QString>
#include <QDebug>
#include "model.hpp"
#include "Entity/client.hpp"
#include "Utility/encodepassword.hpp"

namespace Entity {
    class Client;
}

namespace Model
{
    class ModelUser : public BaseModel
    {
        public:
        Entity::Client* loadUser(QString pUsername, QString pPassword);
        void persistUser(Entity::Client &user);

        private:
        void insertUser(Entity::Client &user);
        void updateUser(Entity::Client &user);
    };
}

#endif // MODELUSER_HPP

