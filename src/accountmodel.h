/*
    Copyright (C) 2017-18 Sebastian J. Wolf

    This file is part of Piepmatz.

    Piepmatz is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Piepmatz is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Piepmatz. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <QUrl>
#include <QNetworkConfigurationManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "o1twitter.h"
#include "o1requestor.h"
#include "twitterapi.h"
#include "locationinformation.h"
#include "wagnis/wagnis.h"

class AccountModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AccountModel();

    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void obtainPinUrl();
    Q_INVOKABLE void enterPin(const QString &pin);
    Q_INVOKABLE bool isLinked();
    Q_INVOKABLE void verifyCredentials();
    Q_INVOKABLE void unlink();
    Q_INVOKABLE QVariantMap getCurrentAccount();

    TwitterApi *getTwitterApi();
    LocationInformation *getLocationInformation();
    Wagnis *getWagnis();

signals:
    void pinRequestError(const QString &errorMessage);
    void pinRequestSuccessful(const QString &url);
    void linkingFailed(const QString &errorMessage);
    void linkingSuccessful();
    void credentialsVerified();
    void verificationError(const QString &errorMessage);

public slots:
    void handlePinRequestError(const QString &errorMessage);
    void handlePinRequestSuccessful(const QUrl &url);
    void handleLinkingFailed();
    void handleLinkingSucceeded();
    void handleVerifyCredentialsSuccessful(const QVariantMap &result);
    void handleVerifyCredentialsError(const QString &errorMessage);

private:
    QList<QVariantMap> availableAccounts;
    QNetworkConfigurationManager * const networkConfigurationManager;
    QString encryptionKey;
    O1Twitter * const o1;
    QNetworkAccessManager * const manager;
    O1Requestor *requestor;
    TwitterApi *twitterApi;
    LocationInformation *locationInformation;
    Wagnis *wagnis;

    void obtainEncryptionKey();

};

#endif // ACCOUNTMODEL_H
