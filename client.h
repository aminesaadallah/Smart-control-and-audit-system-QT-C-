#ifndef CLIENT_H
#define CLIENT_H
#include"QString"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
class client

{
public:
      client();

    QString nomcl,adressecl,adresseEmail;
    QString dateAud,dateEm;
    QString ID_client,num_client;

      client(QString,QString,QString ,QString,QString,QString,QString);
       void setID_client(QString n);
       void setnum_client(QString n);
       void setnomcl(QString n);
       void setadressecl(QString n);
       void setadresseEmail(QString n);
       void setdateAud(QString n);
       void setdateEm(QString n);


       QString  getID_client();
       QString getnum_client();
       QString  getnomcl();
       QString getadressecl();
       QString getadresseEmail();
       QString getdateAud();
       QString  getdateEm();


      bool Ajouter();
      QSqlQueryModel *Afficher();
      bool Supprimer(QString);
      bool Modifier ();
      bool Rechercher (int ID_client,client  &resultclient);

      QList<QMap<QString, QString>> retrieveAllDataAsList(const QString& tableName);
      QList<QMap<QString, QString>> retrieveAllDataAsListSorted(const QString& tableName, const QString& orderByColumn);
      QList<QMap<QString, QString>> searchData(const QString& tableName, const QString& column, const QString& searchTerm);
      bool checkIdExists(const QString& generatedId);

      //stat
      QMap<QString, QList<int>> retrieveAdrsData(const QString &tableName);
      QStringList retrieveAllClientsIds(const QString &tableName);

      //calander
      QList<QMap<QString, QString>> retrieveAllCalanderDataAsList(const QString& tableName, const QDate& x);


};
#endif // LIVREUR_H
