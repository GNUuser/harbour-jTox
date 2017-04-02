#include "event.h"
#include "utils.h"
#include <QDebug>

namespace JTOX {

    Event::Event(int id, quint32 friendID, QDateTime createdAt, EventType eventType, const QString& message, qint64 sendID) :
        fID(id), fFriendID(friendID), fEventType(eventType), fMessage(message), fSendID(sendID)
    {
        createdAt.setTimeSpec(Qt::UTC);
        fCreated = createdAt.toLocalTime();
    }

    const QVariant Event::value(int role) const {
        switch ( role ) {
            case erID: return fID;
            case erCreated: return fCreated;
            case erEventType: return fEventType;
            case erMessage: return hyperLink(fMessage);
        }

        return QVariant("invalid_role");
    }

    int Event::id() const {
        return fID;
    }

    const QString Event::message() const
    {
        return fMessage;
    }

    qint64 Event::sendID() const
    {
        return fSendID;
    }

    EventType Event::type() const
    {
        return fEventType;
    }

    void Event::setSendID(qint64 sendID)
    {
        fSendID = sendID;
    }

    void Event::setEventType(EventType eventType)
    {
        fEventType = eventType;
    }

    const QString Event::hyperLink(const QString& message) const
    {
        int n = message.indexOf("http://");
        if ( n < 0 ) n = message.indexOf("https://");

        if ( n < 0 ) return message;

        if ( n > 0 && !message.at(n - 1).isSpace() ) return message; // probably wrapped already

        QString link = "";
        for ( int i = n; i < message.length(); i++ ) {
            if ( message.at(i).isSpace() ) {
                break;
            }
            link += message.at(i);
        }

        QString newMsg = message;
        return hyperLink(newMsg.replace(link, "<a href=\"" + link + "\">" + link + "</a>"));
    }

    void Event::delivered() {
        if ( fEventType != etMessageOutPending ) {
            Utils::bail("Delivered called on non pending message. MessageID: " + QString::number(fID) + " event type: " + QString::number(fEventType));
        }

        fEventType = etMessageOut;
    }

    void Event::viewed()
    {
        if ( fEventType != etMessageInUnread ) {
            Utils::bail("Viewed called on non unread message. MessageID: " + QString::number(fID) + " event type: " + QString::number(fEventType));
        }

        fEventType = etMessageIn;
    }

}
