#include <QCoreApplication>
#include "server.hpp"
#include "Utility/settings.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a{argc, argv};

    Utility::Settings settings;

    Server server{};
        server.run( static_cast<quint16> (settings.getSettings(CHAT_PORT).toInt()) );

    return a.exec();
}
