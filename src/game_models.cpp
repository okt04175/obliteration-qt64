#include "game_models.hpp"
#include "util.hpp"

#include <QPixmap>

Game::Game(const QString &name, const QString &directory) :
    m_name(name),
    m_directory(directory)
{
}

Game::~Game()
{
}

GameListModel::GameListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

GameListModel::~GameListModel()
{
}

void GameListModel::add(Game *game)
{
    game->setParent(this);

    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    m_items.append(game);
    endInsertRows();
}

void GameListModel::clear()
{
    beginResetModel();

    for (auto i : m_items) {
        delete i;
    }

    m_items.clear();

    endResetModel();
}

int GameListModel::rowCount(const QModelIndex &) const
{
    return m_items.size();
}

QVariant GameListModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return m_items[index.row()]->name();
    case Qt::DecorationRole:
        return QPixmap(joinPath(m_items[index.row()]->directory(), "icon0.png").c_str()).scaled(256, 256, Qt::KeepAspectRatio);
    default:
        return QVariant();
    }
}
