#ifndef CITYSORTPROXYMODEL_H
#define CITYSORTPROXYMODEL_H
#include <QSortFilterProxyModel>
#include <QObject>

class CitySortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged FINAL)
public:
    explicit CitySortProxyModel(QObject *parent = nullptr);
    QString filterString() const;
    void setFilterString(const QString &filterString);
signals:
    void filterStringChanged();
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
private:
    QString _filterString;
};

#endif // CITYSORTPROXYMODEL_H
