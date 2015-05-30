#ifndef CODE_HPP
#define CODE_HPP

namespace TypeMessage
{
    enum Code
    {
        NONE,
        USER_MESSAGE,
        ERROR_MESSAGE,
        SUCCESS_MESSAGE,
        NEW_USER,
        DISCONNET_USER,
        COMMAND
    };
}

namespace Reason
{
    enum Code
    {
        NONE,
        DISCONNECT,
        CHANGE_ROOM,
        KICK,
        BAN
    };
}

namespace Success
{
    enum Code
    {
        NONE,
        PASSWORD_EDITED,
        CONNECTED
    };
}

namespace Error
{
    enum Code
    {
        NONE,
        SERVER_ERROR,
        WRONG_PASSWORD,
        UNKNOW_COMMAND,
        EMPTY_NEW_PASSWORD,
        UNKNOW_TYPE
    };
}

namespace Command
{
    enum Code
    {
        NONE,
        EDIT_PASSWORD,
        JOIN_ROOM
    };
}

#endif // CODE_HPP

