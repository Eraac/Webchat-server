#include "handlecommand.hpp"

void Utility::HandleCommand::command(const HandleMessage &pCommand, Room *pRoom, Entity::Client *pClient)
{    
    switch ( static_cast<Command::Code> (pCommand.getKey("command").toInt()) )
    {
        case Command::EDIT_PASSWORD:
            updatePassword(pCommand.getKey("newPassword").toString(), pClient);
            break;

        case Command::JOIN_ROOM:
            joinRoom(pCommand.getKey("newRoom").toString(), pRoom, pClient);
            break;

        default:
            Utility::HandleMessage message{};
                message.setType(TypeMessage::ERROR_MESSAGE);
                message.setKey("code", Error::UNKNOW_COMMAND);

            pClient->sendTextMessage(message.toString());
            break;
    }
}

void Utility::HandleCommand::updatePassword(const QString &pNewPassword, Entity::Client *pClient)
{
    Utility::HandleMessage message{};

    if (pNewPassword.isEmpty())
    {
        message.setType(TypeMessage::ERROR_MESSAGE);
        message.setKey("code", Error::EMPTY_NEW_PASSWORD);
    }
    else
    {
        pClient->setPassword(pNewPassword, false);

        Model::ModelUser userModel{};
            userModel.persistUser(*pClient);

        message.setType(TypeMessage::SUCCESS_MESSAGE);
        message.setKey("code", Success::PASSWORD_EDITED);
    }

    pClient->sendTextMessage(message.toString());
}

void Utility::HandleCommand::joinRoom(const QString &pNewRoom, Room *pOldRoom, Entity::Client *pClient)
{
    pOldRoom->disconnectUser(pClient, Reason::CHANGE_ROOM);

    emit changeUserRoom(pNewRoom, pClient);
}
