#ifndef CITYSORTPROXYMODEL_H
#define CITYSORTPROXYMODEL_H
#include <QSortFilterProxyModel>
#include <QObject>

class CitySortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filterString READ filterString WRITE setFilterString NOTIFY filterStringChanged FINAL)
    Q_PROPERTY(QString filterVoivodeship READ filterVoivodeship WRITE setFilterVoivodeship NOTIFY filterVoivodeshipChanged FINAL)
public:
    explicit CitySortProxyModel(QObject *parent = nullptr);
    QString filterString() const;
    void setFilterString(const QString &filterString);
    QString filterVoivodeship() const;
    void setFilterVoivodeship(const QString &filterVoivodeship);
signals:
    void filterStringChanged();
    void filterVoivodeshipChanged();
protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
private:
    QString _filterString;
    QString _filterVoivodeship;
};

#endif // CITYSORTPROXYMODEL_H
