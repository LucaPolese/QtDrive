#include "account.h"

/*Account::Account(QString email_, QString password_, provider host_, unsigned int spazioFornito_):
email(email_), password(password_), host(host_), spazioFornito(spazioFornito_), listaFile(){}*/

Account::Account(QString email_, QString password_, servizio host_, unsigned int spazioFornito_, Container<Deepptr<File>> listaFile_):
    email(email_), password(password_), host(host_), spazioFornito(spazioFornito_), listaFile(listaFile_){}

Account* Account::clone() const{
    return new Account(*this);
}
