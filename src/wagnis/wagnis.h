#ifndef WAGNIS_H
#define WAGNIS_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QVariantMap>

const char MIME_TYPE_JSON[] = "application/json";

const char API_REGISTRATION[] = "https://ssl.webpack.de/ygriega.de/wagnis/registration.php";

class Wagnis : public QObject
{
    Q_OBJECT
public:
    explicit Wagnis(QNetworkAccessManager *manager, const QString &applicationName, const QString applicationVersion, QObject *parent = 0);
    ~Wagnis();
    Q_INVOKABLE QString getId();
    Q_INVOKABLE void registerApplication();
    Q_INVOKABLE void getApplicationRegistration();
    Q_INVOKABLE bool isRegistered();

signals:
    void registrationError(const QString &errorMessage);

public slots:

private:
    void generateId();
    void getIpInfo();
    QString applicationName;
    QString applicationVersion;
    QString wagnisId;
    QVariantMap ipInfo;
    QNetworkAccessManager *manager;

private slots:
    void handleGetIpInfoError(QNetworkReply::NetworkError error);
    void handleGetIpInfoFinished();
    void handleRegisterApplicationError(QNetworkReply::NetworkError error);
    void handleRegisterApplicationFinished();
    void handleGetApplicationRegistrationError(QNetworkReply::NetworkError error);
};

#endif // WAGNIS_H
