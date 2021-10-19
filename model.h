#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QStack>

////////////////////////////////////////////////////////////////////////////
/// \brief Json Item class
///

class Item
{
public:
    Item();
    Item(const QString& name, const QString& icon, const QString& url, int index);
    ~Item();

    QString name() const;
    QString icon() const;
    QString url() const;
    int index() const;
    bool folder() const;
    void addChild(Item* item);
    const QList<Item*>& children() const;

private:
    QString name_;
    QString icon_;
    QString url_;
    int index_;
    QList<Item*> children_;
};

////////////////////////////////////////////////////////////////////////////
/// \brief Json and GridView's Model class
///

class Model: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<Item*> items READ getItems NOTIFY itemsChanged)
    Q_PROPERTY(bool isRoot READ getIsRoot NOTIFY isRootChanged)
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        UrlRole,
        IndexRole
    };

    Model(QObject* parent = 0);
    ~Model();

    const QList<Item*> getItems() const;
    Q_SIGNAL void itemsChanged();

    bool getIsRoot() const;
    Q_SIGNAL void isRootChanged();

    void setRoot(Item* item);

    Q_INVOKABLE void open(int index);
    Q_INVOKABLE void levelUp();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    Item* root_;
    QStack<Item*> path_;
};

#endif // MODEL_H
