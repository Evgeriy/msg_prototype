#ifndef AUTHORIZATIONDATA_H
#define AUTHORIZATIONDATA_H

#include <QObject>
#include <QtWebSockets/QWebSocket>

#include <QTime>
#include <QDebug>
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>
#include <QAbstractListModel>

#include "nlohmann/json.hpp"

struct FriendData {
    FriendData() {}
    FriendData(const QString &_phoneNumber, const QString &_firstName, const QString &_secondName) :
        m_phoneNumber(_phoneNumber),
        m_firstName(_firstName),
        m_secondName(_secondName) {

    }
    QString m_phoneNumber;
    QString m_firstName;
    QString m_secondName;
};

class FriendListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(FriendListRoles)
public:
    enum FriendListRoles {
        PhoneNumber = Qt::UserRole + 1,
        FirstName,
        SecondName
    };

    using QAbstractListModel::QAbstractListModel;

    QHash<int,QByteArray> roleNames() const override {
        return { { PhoneNumber, "phoneNumber" },
                 { FirstName,   "firstName"   },
                 { SecondName,  "secondName"  },
        };
    }

    void addFriend(const QString &_phoneNumber, const QString &_firstName, const QString &_secondName) {
        m_list.append(FriendData(_phoneNumber, _firstName, _secondName));
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const override {
        if (parent.isValid())
            return 0;
        return m_list.size();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
            return false;

        FriendData &item = m_list[index.row()];
        if (role == FirstName) item.m_phoneNumber = value.toString();
        else if (role == PhoneNumber) item.m_firstName = value.toString();
        else if (role == SecondName) item.m_secondName = value.toString();
        else return false;

        emit dataChanged(index, index, { role } );

        return true ;

    }

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
        if (!hasIndex(index.row(), index.column(), index.parent()))
            return {};

        const FriendData &item = m_list.at(index.row());
        if (role == FirstName) return item.m_phoneNumber;
        if (role == PhoneNumber) return item.m_firstName;
        if (role == SecondName) return item.m_secondName;

        return {};
    }

private:
    QVector<FriendData> m_list = {
        { "8926497821", "Ivan", "Ivanov" },
        { "8926421821", "Pert", "Petrov" },
        { "8924497821", "Nikolay", "Nikolaev" }
    };
};

class TCPClient : public QObject {
    Q_OBJECT

    // FOR QML LAYER
    Q_PROPERTY(QString m_phoneNumber READ getPhoneNumber WRITE setPhoneNumber)
    Q_PROPERTY(QString m_nikName READ getNikName WRITE setNikName)
    Q_PROPERTY(QString m_firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString m_secondName READ getSecondName WRITE setSecondName)
    Q_PROPERTY(QString m_code READ getCode WRITE setCode)
    Q_PROPERTY(QStringList m_friends READ getFriends WRITE setFriends)
    Q_PROPERTY(QStringList m_messages READ getMessages WRITE setMessages)

public:
    explicit TCPClient(QObject *_parent = nullptr);
    ~TCPClient();

signals:
    void closed();

public:
    void connectToHost(const QString &_hostAddressString, const quint16 &_port);

public:
    Q_INVOKABLE void sendAuthorizationData();
    Q_INVOKABLE void sendUserNikname(const QString &_userNikName);

public:
    Q_INVOKABLE QString getPhoneNumber() const;
    Q_INVOKABLE QString getNikName() const;
    Q_INVOKABLE QString getFirstName() const;
    Q_INVOKABLE QString getSecondName() const;
    Q_INVOKABLE QString getCode() const;
    Q_INVOKABLE QStringList getFriends() const;
    Q_INVOKABLE QStringList getMessages() const;

public:
    Q_INVOKABLE void setPhoneNumber(const QString &_phoneNumber);
    Q_INVOKABLE void setNikName(const QString &_nikName);
    Q_INVOKABLE void setFirstName(const QString &_firstName);
    Q_INVOKABLE void setSecondName(const QString &_secondName);
    Q_INVOKABLE void setCode(const QString &_code);
    Q_INVOKABLE void setFriends(const QStringList &_friends);
    Q_INVOKABLE void setMessages(const QStringList &_messages);

private slots:
    void onConnected();
    void onMessageReceived();

private:
    void onAuthorizationReceived(const QString &_message);
    void onFriendsReceived(const QString &_message);
    void onMessagesReceived(const QString &_messages);

private:
    QString m_phoneNumber{"+7"};
    QString m_nikName;
    QString m_firstName;
    QString m_secondName;
    QString m_code{"+7"};
    QStringList m_friends;
    QStringList m_messages;

    QTcpSocket* pSocket;
    quint16     mNextBlockSize;
    bool        mIsAuthorized;
};

#endif
