#include "loader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QByteArray jsonAr = {"\"[\n\t{\n\t\t\"name\": \"Shell\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/shell.png\",\n\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/shell\"\n\t},\n\t{\n\t\t\"name\": \"Objects\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/folder.svg\",\n\t\t\"children\": [\n\t\t\t{\n\t\t\t\t\"name\": \"Corals\",\n\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/folder.svg\",\n\t\t\t\t\"children\": [\n\t\t\t\t\t{\n\t\t\t\t\t\t\"name\": \"Coral Green\",\n\t\t\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/coral_green.png\",\n\t\t\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/boat\"\n\t\t\t\t\t},\n\t\t\t\t\t{\n\t\t\t\t\t\t\"name\": \"Coral Yellow\",\n\t\t\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/coral_yellow.png\",\n\t\t\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/coral_yellow\"\n\t\t\t\t\t},\n\t\t\t\t\t{\n\t\t\t\t\t\t\"name\": \"Coral Orange\",\n\t\t\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/coral_orange.png\",\n\t\t\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/coral_orange\"\n\t\t\t\t\t},\n\t\t\t\t\t{\n\t\t\t\t\t\t\"name\": \"Coral Teal\",\n\t\t\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/coral_teal.png\",\n\t\t\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/coral_teal\"\n\t\t\t\t\t},\n\t\t\t\t\t{\n\t\t\t\t\t\t\"name\": \"Coral Purple\",\n\t\t\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/coral_purple.png\",\n\t\t\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/coral_purple\"\n\t\t\t\t\t}\n\t\t\t\t]\n\t\t\t},\n\t\t\t{\n\t\t\t\t\"name\": \"Boulder\",\n\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/boulder.png\",\n\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/boulder\"\n\t\t\t},\n\t\t\t{\n\t\t\t\t\"name\": \"Seaweed\",\n\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/seaweed.png\",\n\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/seaweed\"\n\t\t\t},\n\t\t\t{\n\t\t\t\t\"name\": \"Starfish\",\n\t\t\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/starfish.png\",\n\t\t\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/starfish\"\n\t\t\t}\n\t\t]\n\t},\n\t{\n\t\t\"name\": \"Boat\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/boat.png\",\n\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/boat\"\n\t},\n\t{\n\t\t\"name\": \"Bubble\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/bubble.png\",\n\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/bubble\"\n\t},\n\t{\n\t\t\"name\": \"Sand\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/sand.png\",\n\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/sand\"\n\t},\n\t{\n\t\t\"name\": \"Water\",\n\t\t\"icon\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/water.png\",\n\t\t\"url\": \"https://s3.amazonaws.com/com.buildbox.dev.interview/UnderTheSea/post/water\"\n\t}\n]\n\""};

void trim(QByteArray& ar, char ch = '"')
{
    for (int i = 0; i < ar.size() && ar[i] == ch; i++)
        ar[i] = ' ';
    for (int i = ar.size() - 1; i >= 0 && ar[i] == ch; i--)
        ar[i] = ' ';
}

Loader::Loader(QObject *parent):
    QObject(parent),
    nam(nullptr),
    model_(nullptr)
{
}

void Loader::load(const QString& url, Model& model)
{
    nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(onReply(QNetworkReply*)));

    model_ = &model;
    QNetworkReply* reply = nam->get(QNetworkRequest(QUrl(url)));
    return;
    QJsonParseError err;
    trim(jsonAr);
    QJsonDocument doc = QJsonDocument::fromJson(jsonAr, &err);
    if (err.error != QJsonParseError::NoError) {
            qWarning() << "Parse error at " << err.offset << ":" << err.errorString();
    }

    if (doc.isArray())
    {
        qDebug() << "Document contain array";
        QJsonArray array = doc.array();

        Item* item = new Item();
        loadArray(array, item);
        model.setRoot(item);
    }
    else
        if (doc.isObject())
        {
            qDebug() << "Document contain object";
        }
}

void Loader::onReply(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError && model_ != nullptr)
    {
        QByteArray result = reply->readAll();
        //qDebug() << result;
        trim(result);

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(result, &err);

        if (err.error != QJsonParseError::NoError) {
            qWarning() << "Json parse error at " << err.offset << ":" << err.errorString();
        }
        else {
            if (doc.isArray())
            {
                qDebug() << "Json Document is an Array";
                QJsonArray array = doc.array();
                Item* root = new Item();
                loadArray(array, root);
                qDebug() << root->children().size();
                model_->setRoot(root);
            }
            else if (doc.isObject()) {
                // Just in case

                qDebug() << "Json Document is an Object";

                QJsonObject obj = doc.object();
                QString name = obj["name"].toString();
                QString icon = obj["icon"].toString();
                QString url = obj["url"].toString();


                Item* item = new Item(name, icon, url, 0);

                Item* root = new Item();
                root->addChild(item);
                model_->setRoot(root);

                if (obj.contains("children")) {
                    qDebug()<<"children: " << obj["children"].toArray().size();

                    loadArray(obj["children"].toArray(), item);
                }
            }
        }
    }
    else if (model_ != nullptr)
        qWarning() << "Network Error: " << reply->errorString();

    reply->deleteLater();
    nam->deleteLater();
}

void Loader::loadArray(const QJsonArray& arr, Item* parent)
{
    if (parent == nullptr)
        return;

    for (int i = 0; i < arr.size(); i++) {
        const QJsonValue& val = arr[i];
        if (val.isObject()) {
            QJsonObject obj = val.toObject();
            QString name = obj["name"].toString();
            QString icon = obj["icon"].toString();
            QString url = obj["url"].toString();

            qDebug() << "name: " << name;
            qDebug() << "icon: " << icon;
            qDebug() << "url: " << url;

            Item* item = new Item(name, icon, url, i);
            if (parent != nullptr)
                parent->addChild(item);

            if (obj.contains("children")) {
                qDebug()<<"children: " << obj["children"].toArray().size();

                loadArray(obj["children"].toArray(), item);
            }
        }
        else
            qWarning("Not an Object");
    }
};
