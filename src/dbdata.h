#ifndef DBDATA_H
#define DBDATA_H

#include "event.h"
#include "friendrequest.h"
#include "encryptsave.h"
#include <QString>
#include <QSqlDatabase>
#include <QDateTime>
#include <QSqlQuery>

namespace JTOX {

    class DBData
    {
    public:
        DBData(EncryptSave& encryptSave);
        void getEvents(EventList& list, quint32 friendID, int eventType = -1);
        int getUnviewedEventCount(qint64 friendID);
        int insertEvent(qint64 sendID, quint32 friendID, EventType eventType, const QString& message, QDateTime& createdAt);
        void updateEventType(int id, EventType eventType);
        void updateEventSent(int id, EventType eventType, qint64 sendID);
        void deliverEvent(quint32 sendID, quint32 friendID);
        void deleteEvent(int id);
        void insertRequest(FriendRequest& request);
        void updateRequest(const FriendRequest& request);
        void deleteRequest(const FriendRequest& request);
        void getRequests(RequestList& list);
        void setFriendOfflineName(const QString& address, quint32 friendID, const QString& name);
        const QString getFriendOfflineName(const QString& address);
        void wipe(qint64 friendID);
        void wipeLogs();
    private:
        EncryptSave& fEncryptSave;
        QSqlDatabase fDB;
        QSqlQuery fEventSelectQuery;
        QSqlQuery fLastEventSelectQuery;
        QSqlQuery fEventUnviewedCountQuery;
        QSqlQuery fEventInsertQuery;
        QSqlQuery fEventUpdateQuery;
        QSqlQuery fEventUpdateSentQuery;
        QSqlQuery fEventDeliveredQuery;
        QSqlQuery fEventDeleteQuery;
        QSqlQuery fRequestSelectQuery;
        QSqlQuery fRequestInsertQuery;
        QSqlQuery fRequestUpdateQuery;
        QSqlQuery fRequestDeleteQuery;
        QSqlQuery fLastRequestSelectQuery;
        QSqlQuery fFriendOfflineNameSelectQuery;
        QSqlQuery fFriendOfflineNameUpdateQuery;
        QSqlQuery fWipeEventsQuery;
        QSqlQuery fWipeRequestsQuery;
        QSqlQuery fWipeFriendsQuery;
        void createTables();
        void prepareQueries();
        const QSqlQuery prepareQuery(const QString& sql);
    };

}

#endif // DBDATA_H
