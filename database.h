#ifndef DATABASE_H
#define DATABASE_H
#include "apiclient.h"

class Database
{
public:
    Database() = default;
    Database(const ApiClient *client);
private:
    ApiClient *client;
};

#endif // DATABASE_H
