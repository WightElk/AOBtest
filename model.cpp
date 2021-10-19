#include "model.h"
#include <QDesktopServices>
#include <QUrl>

Item::Item():
    index_(0)
{
}

Item::Item(const QString& name, const QString& icon, const QString& url, int index):
    name_(name),
    icon_(icon),
    url_(url),
    index_(index)
{
}

Item::~Item()
{
    qDeleteAll(children_);
}

QString Item::name() const
{
    return name_;
}

QString Item::icon() const
{
    return icon_;
}

QString Item::url() const
{
    return url_;
}

int Item::index() const
{
    return index_;
}

void Item::addChild(Item* item)
{
    if (item != nullptr)
        children_.push_back(item);
}


bool Item::folder() const
{
    return children_.size() > 0;
}

const QList<Item*>& Item::children() const
{
    return children_;
}

////////////////////////////////////////////////////////////////////////////

Model::Model(QObject* parent):
    QAbstractListModel(parent),
    root_(nullptr)
{
}

Model::~Model()
{
    delete root_;
}

void Model::setRoot(Item* item)
{
    if (item != root_ && item != nullptr) {
        beginResetModel();
        delete root_;
        root_ = item;
        endResetModel();
    }
}

const QList<Item*> Model::getItems() const
{
    QList<Item*> items;
    if (path_.isEmpty()) {
        if (root_ != nullptr)
            items = root_->children();
    } else
        items = path_.top()->children();
    return items;
}

void Model::open(int index)
{
    Item* parent = path_.isEmpty() ? root_ : path_.top();
    if (parent == nullptr)
        return;
    const QList<Item*>& children = parent->children();

    if (0 <= index && index < children.size()) {
        if (children[index]->children().empty()) {
            // Open the url
            QDesktopServices::openUrl(QUrl(children[index]->url()));
        } else {
            bool wasEmpty = path_.isEmpty();
            // Walk down
            beginResetModel();
            path_.push(children[index]);
            endResetModel();

            // Enable Level up button
            if (wasEmpty) {
                Q_EMIT isRootChanged();
            }
        }
    }
}

void Model::levelUp()
{
    if (!path_.isEmpty()) {
        beginResetModel();
        path_.pop();
        endResetModel();

        // Disable Level up button
        if (path_.isEmpty()) {
            Q_EMIT isRootChanged();
        }
    }
}

bool Model::getIsRoot() const
{
    return root_ == nullptr || path_.isEmpty();
}

int Model::rowCount(const QModelIndex& parent) const
{
    return getItems().count();
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    const QList<Item*>& items = getItems();
    if (index.row() < 0 || index.row() >= items.count())
        return QVariant();

    const Item& item = *items[index.row()];
    if (role == NameRole)
        return item.name();
    else if (role == IconRole)
        return item.icon();
    else if (role == UrlRole)
        return item.url();
    else if (role == IndexRole)
        return item.index();
    return QVariant();
}

QHash<int, QByteArray> Model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[UrlRole] = "url";
    roles[IndexRole] = "index";
    return roles;
}
