#include "ihmgraphique.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtCharts/QValueAxis>

IhmGraphique::IhmGraphique(QWidget *parent) : QMainWindow(parent)
{

    QSqlQuery query("SELECT * FROM MATERIEL_AUDITE ORDER BY ID_MATERIEL_AUDITE");


    courbe = new QLineSeries();
    int index = 1;
    while (query.next()) {
        int id_materiel_audite = query.value("ID_MATERIEL_AUDITE").toInt();

        // Utilisation de l'index de la requête comme abscisse
        int indexFromQuery = query.value("QT").toInt(); // Remplacez INDEX_COLUMN_NAME par le nom de la colonne contenant les indices dans votre base de données
        courbe->append(indexFromQuery, id_materiel_audite);
        index++;
    }
    graphe = new QChart();
    graphe->addSeries(courbe);
    graphe->setTitle("graphe equipement ");



    QValueAxis *axeX = new QValueAxis;
    axeX->setTickCount(index);
    axeX->setLabelFormat("%i");
    graphe->addAxis(axeX, Qt::AlignBottom);
    courbe->attachAxis(axeX);

    QValueAxis *axeY = new QValueAxis;
    axeY->setRange(0,100);  // Ajustez cette plage selon vos données
    axeY->setLabelFormat("%.1f");
    axeY->setTitleText(QString::fromUtf8("identifiant equipemnt"));
    graphe->addAxis(axeY, Qt::AlignLeft);
    courbe->setPointsVisible(true);
    courbe->setPointLabelsFormat("");
    courbe->setPointLabelsVisible(true);
    courbe->attachAxis(axeY);
    // Le widget
    graphique = new QChartView(graphe);
    graphique->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(graphique);
resize(800, 600);}

IhmGraphique::~IhmGraphique()
{
}
