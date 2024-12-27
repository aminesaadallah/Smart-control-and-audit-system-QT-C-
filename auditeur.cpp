
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include"auditeur.h"
Auditeur::Auditeur()
{
    id_auditeur = 0;
    nom_auditeur = " ";
    mail_auditeur = " ";
    tel_auditeur = "";
    mdp_auditeur = " ";
}

Auditeur::Auditeur(int id_auditeur, QString nom_auditeur, QString mail_auditeur, QString tel_auditeur, QString mdp_auditeur, QString genre_auditeur)
{
    this->id_auditeur = id_auditeur;
    this->nom_auditeur = nom_auditeur;
    this->mail_auditeur = mail_auditeur;
    this->tel_auditeur = tel_auditeur;
    this->mdp_auditeur = mdp_auditeur;
    this->genre_auditeur = genre_auditeur;
}

int Auditeur::get_id_auditeur() { return id_auditeur; }
QString Auditeur::get_nom_auditeur() { return nom_auditeur; }
QString Auditeur::get_mail_auditeur() { return mail_auditeur; }
QString Auditeur::get_tel_auditeur() { return tel_auditeur; }
QString Auditeur::get_mdp_auditeur() { return mdp_auditeur; }
QString Auditeur::get_genre_auditeur() { return mdp_auditeur; }

void Auditeur::setid_auditeur(int id_auditeur) { this->id_auditeur = id_auditeur; }
void Auditeur::setnom_auditeur(QString nom_auditeur) { this->nom_auditeur = nom_auditeur; }
void Auditeur::setmail_auditeur(QString mail_auditeur) { this->mail_auditeur = mail_auditeur; }
void Auditeur::settel_auditeur(QString tel_auditeur) { this->tel_auditeur = tel_auditeur; }
void Auditeur::setmdp_auditeur(QString mdp_auditeur) { this->mdp_auditeur = mdp_auditeur; }
void Auditeur::setgenre_auditeur(QString genre_auditeur) { this->genre_auditeur = genre_auditeur; }

bool Auditeur::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id_auditeur);

    // Prepare the SQL query
    query.prepare("INSERT INTO AUDITEURS "
                   "VALUES (?, ?, ?, ?, ?, ?)");

    // Bind values to the query parameters
    //qDebug()<< id_auditeur << nom_auditeur << mail_auditeur << tel_auditeur << mdp_auditeur << genre_auditeur;
    query.bindValue(0, id_auditeur);
    query.bindValue(1, nom_auditeur);
    query.bindValue(2, mail_auditeur);
    query.bindValue(3, tel_auditeur);
    query.bindValue(4, mdp_auditeur);
    query.bindValue(5, genre_auditeur);

    // Execute the query
    if (query.exec()) {
        // If the query executed successfully
        qDebug() << "Ajout effectué avec succès";
        return true;
    } else {
        // If there was an error, display the error message
        qDebug() << "Erreur lors de l'ajout.  :" << query.lastError().text();

        return false;
    }

}

QSqlQueryModel *Auditeur::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Auditeurs");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));
    return model;
}

bool Auditeur::supprimer(int id_auditeur)
{
    QSqlQuery query;
    QString res = QString::number(id_auditeur);

    query.prepare("DELETE FROM AUDITEURS WHERE id_auditeur = :id_auditeur");
    query.bindValue(":id_auditeur", res);

    qDebug() << "Query: " << query.lastQuery();
    qDebug() << "Bound Values: " << query.boundValues();

    if (query.exec()) {
        // If the query executed successfully
        qDebug() << "Suppression effectuée avec succès";
        return true;
    } else {
        // If there was an error, display the error message
        qDebug() << "Erreur lors de la suppression :" << query.lastError().text();
        return false;
    }
}

bool Auditeur::modifier(int id_auditeur)
{
    QSqlQuery query;
    QString id_string = QString::number(id_auditeur);

    //qDebug()<< id_auditeur << nom_auditeur << mail_auditeur << tel_auditeur << mdp_auditeur << genre_auditeur;

    query.prepare("UPDATE auditeurs SET nom_auditeur = ?, mail_auditeur = ?, "
                  "tel_auditeur = ?, mdp_auditeur = ?, genre_auditeur = ? "
                  "WHERE id_auditeur = ?");

    query.bindValue(0, nom_auditeur);
    query.bindValue(1, mail_auditeur);
    query.bindValue(2, tel_auditeur);
    query.bindValue(3, mdp_auditeur);
    query.bindValue(4, genre_auditeur);
    query.bindValue(5, id_auditeur);

    return query.exec();
}

QSqlQueryModel *Auditeur::rechercher(int id_auditeur)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString id = QString::number(id_auditeur);
    model->setQuery("SELECT * FROM Auditeurs WHERE id_auditeur LIKE '" + id + "%'");
    qDebug()<< id_auditeur << nom_auditeur << mail_auditeur << tel_auditeur << mdp_auditeur ;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}

QSqlQueryModel *Auditeur::tri()
{
    QSqlQuery *m = new QSqlQuery();
    QSqlQueryModel *model = new QSqlQueryModel();
    m->prepare("SELECT * FROM AUDITEURS ORDER BY ID_AUDITEUR ASC");
    m->exec();
    model->setQuery(*m);

    return model;
}

QList<QMap<QString, QString>> Auditeur::retrieveAllDataAsList(const QString& tableName)
{
    QList<QMap<QString, QString>> dataList;

        QSqlQuery query;
        if (!query.exec("SELECT * FROM " + tableName)) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return dataList;
        }

        while (query.next()) {
            QMap<QString, QString> rowData;
            QSqlRecord record = query.record();

            for (int i = 0; i < record.count(); ++i) {
                rowData[record.fieldName(i).toLower()] = query.value(i).toString();
            }

            dataList.append(rowData);
        }

        qDebug() << "Data retrieved successfully!";
        return dataList;
}

QList<QMap<QString, QString>> Auditeur::searchData(const QString& tableName, const QString& column, const QString& searchTerm)
{
    QList<QMap<QString, QString>> searchResults;

    QSqlQuery query;
    QString queryString = "SELECT * FROM " + tableName + " WHERE " + column + " LIKE ?";
    query.prepare(queryString);
    query.addBindValue("%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return searchResults;
    }

    while (query.next()) {
        QMap<QString, QString> rowData;
        QSqlRecord record = query.record();

        for (int i = 0; i < record.count(); ++i) {
            rowData[record.fieldName(i).toLower()] = query.value(i).toString();
        }

        searchResults.append(rowData);
    }

    qDebug() << "Search results retrieved successfully!";
    return searchResults;
}

QMap<QString, QList<int>> Auditeur::retrieveAuditeurData(const QString &tableName) {
    QMap<QString, QList<int>> sourceData;

    QSqlQuery query;
    if (!query.exec("SELECT genre_auditeur, count(genre_auditeur) FROM " + tableName + " GROUP BY genre_auditeur")) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return sourceData;
    }

    while (query.next()) {
        QString source = query.value(0).toString();
        int quantity = query.value(1).toInt();

        if (!sourceData.contains(source)) {
            sourceData[source] = QList<int>();
        }

        sourceData[source].append(quantity);
    }

    qDebug() << "Source data retrieved successfully!";
    return sourceData;
}

bool Auditeur::checkIdEmailexist(const QString& generatedId) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Auditeurs WHERE mail_auditeur = ?");
    checkQuery.bindValue(0, generatedId);

    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        return count > 0;
    } else {
        qDebug() << "Query error:" << checkQuery.lastError().text();
        return false; // Handle the error condition
    }
}

bool Auditeur::checkIdmdpexist(const QString& generatedId) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Auditeurs WHERE mdp_auditeur = ?");
    checkQuery.bindValue(0, generatedId);

    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        return count > 0;
    } else {
        qDebug() << "Query error:" << checkQuery.lastError().text();
        return false; // Handle the error condition
    }
}

//rechercher des lignes dans une table de base de données en fonction d'une colonne spécifiée et d'un terme de recherche
//Elle renvoie la liste des résultats de la recherche
QList<QMap<QString, QString>> Auditeur::searchData1(const QString& tableName, const QString& column, const QString& searchTerm)
{
    QList<QMap<QString, QString>> searchResults;//Crée une liste pour stocker les résultats de la recherche

    QSqlQuery query;
    QString queryString = "SELECT * FROM " + tableName + " WHERE " + column + " = ?";
    query.prepare(queryString);
    query.bindValue(0,searchTerm); //l(liaison de valeur b les parametres fl requette)

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return searchResults;
    }

    while (query.next()) {
        QMap<QString, QString> rowData;
        QSqlRecord record = query.record();

        for (int i = 0; i < record.count(); ++i) {
            rowData[record.fieldName(i).toLower()] = query.value(i).toString();//Stocke le nom de la colonne  et sa valeur correspondante dans la carte
        }

        searchResults.append(rowData);
    }

    qDebug() << "Search results retrieved successfully!";
    return searchResults; //renvoie la liste des résultats de la recherche.
}


