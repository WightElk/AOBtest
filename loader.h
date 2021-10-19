#ifndef LOADER_H
#define LOADER_H

#include "model.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

////////////////////////////////////////////////////////////////////////////
/// \brief Loader class - loads Model from Json
///

class Loader: public QObject
{
    Q_OBJECT
public:
    explicit Loader(QObject* parent = nullptr);

    void load(const QString& url, Model& model);

signals:

private slots:
    void onReply(QNetworkReply* reply);

private:
    void loadArray(const QJsonArray& arr, Item* parent = nullptr);

    QNetworkAccessManager* nam;
    Model* model_;
};

#endif // LOADER_H
