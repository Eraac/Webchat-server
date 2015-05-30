#ifndef ENCODEPASSWORD_HPP
#define ENCODEPASSWORD_HPP

#include <QCryptographicHash>
#include <QString>

namespace Utility
{
    class EncodePassword
    {
        public:
        static QString encodePassword(QString const& pPassword, QString const& pSalt = "");

        private:
        static QString mergePasswordAndSalt(QString const& pPassword, QString const& pSalt);
    };
}

#endif // ENCODEPASSWORD_HPP

