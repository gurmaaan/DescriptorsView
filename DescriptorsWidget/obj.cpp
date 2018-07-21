#include "obj.h"

Obj::Obj(QObject *parent) : QObject(parent)
{

}

Obj::Obj(const Obj &other)
{
    if ( (this->id() == other.id()) && (descriptors_.count() == other.descriptors().count()) )
    {
        this->setName( other.name() );
        this->setFullName( other.fullName() );
        for(int i = 0; i < descriptors_.count(); i++)
        {
            descriptors_.at(i)->setObjId(other.descriptors().at(i)->objId());
            descriptors_.at(i)->setId(other.descriptors().at(i)->id());
            descriptors_.at(i)->setName(other.descriptors().at(i)->name());
            descriptors_.at(i)->setData(other.descriptors().at(i)->data());
        }
    }
}

Obj::Obj(int id, QString fullName)
    :id_(id), fullName_(fullName)
{
    name_ = StringService::cutFilePath( fullName_ );
}

Obj::Obj(int id, QString fullName, QVector<Descriptor *> &descriptors)
    :id_(id), fullName_(fullName)
{
    name_ = StringService::cutFilePath( fullName_ );
    for(int i = 0; i < descriptors.count(); i++)
    {
        Descriptor *desc = new Descriptor(descriptors.at(i)->objId(), descriptors.at(i)->id(), descriptors.at(i)->name(), descriptors.at(i)->data());
        descriptors_.push_back(desc);
    }
}

Obj &Obj::operator =(const Obj &o)
{
    if( (this->id() == o.id()) && (descriptors_.count() == o.descriptors().count()) )
    {
        setName(o.name());
        setFullName(o.fullName());
        for(int i = 0; i < descriptors_.count(); i++)
        {
            descriptors_.at(i)->setObjId(o.descriptors().at(i)->objId());
            descriptors_.at(i)->setId(o.descriptors().at(i)->id());
            descriptors_.at(i)->setName(o.descriptors().at(i)->name());
            descriptors_.at(i)->setData(o.descriptors().at(i)->data());
        }
        return *this;
    } else
    {
        return *this;
    }
}

int Obj::id() const
{
    return id_;
}

void Obj::setId(int id)
{
    id_ = id;
}

QString Obj::name() const
{
    return name_;
}

void Obj::setName(const QString &name)
{
    name_ = name;
}

QVector<Descriptor *> Obj::descriptors() const
{
    return descriptors_;
}

void Obj::setDescriptors(const QVector<Descriptor *> &descriptors)
{
    descriptors_ = descriptors;
}

void Obj::apendDescriptor(Descriptor *descriptor)
{
    this->descriptors_.push_back(descriptor);
}

QList<QStandardItem *> Obj::modelRow()
{
    QList<QStandardItem*> list;
    foreach(auto descr, this->descriptors())
    {
        QStandardItem *item = new QStandardItem();
        item->setData( ItemsService::displayingStr(descr->data()), Qt::DisplayRole);
        item->setData(descr->data(), Qt::EditRole);
        list << item;
    }

    return list;
}

QStandardItem *Obj::rowVerticalHeader()
{
    QStandardItem *headerItem = new QStandardItem(this->name());
    ItemsService::makeFontBold(headerItem);
    ItemsService::alignText(headerItem, Qt::AlignRight);
    ItemsService::alignText(headerItem, Qt::AlignVCenter);
    ItemsService::changeBgColor(headerItem, Qt::lightGray);
    ItemsService::addDescription(headerItem, this->fullName());
    return headerItem;
}

QString Obj::fullName() const
{
    return fullName_;
}

void Obj::setFullName(const QString &fullName)
{
    fullName_ = fullName;
}

bool operator ==(const Obj &o1, const Obj &o2)
{
    if( (o1.id() == o2.id()) && (o1.descriptors().count() == o2.descriptors().count()) )
        return true;
    else
        return false;
}

QDebug operator <<(QDebug dbg, const Obj *o)
{
    dbg << "Объект " << o->id() << " - " << o->fullName() << "[ " << o->name() << " ]:" << endl;
    foreach (auto desr, o->descriptors()) {
        dbg << desr << endl;
    }
    dbg << "------------------";
    return dbg.nospace();
}
