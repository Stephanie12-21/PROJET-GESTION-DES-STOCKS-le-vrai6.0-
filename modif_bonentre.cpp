#include "modif_bonentre.h"
#include "ui_modif_bonentre.h"
#include "Connection.h"
#include "produit.h"
#include <QSqlQuery>
#include <QDate>
#include <QMessageBox>
#include <QSqlError>

modif_bonEntre::modif_bonEntre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modif_bonEntre)
{
    ui->setupUi(this);

    Connection m_db;
    if (!m_db.connOpen())
        {
            qDebug() << "Failed to open database";
        }
    else if(m_db.connOpen())
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM produit");

            if (query.exec())
                {

                    while (query.next())
                        {
                            QString numPro  = query.value(0).toString();
                            QString nomPro = query.value(1).toString();
                            Produit produit(numPro,nomPro);
                            recupId = produit.getId();
                            ui->numProduit->addItem(produit.toString());

                        }
                }

        }
    else
        {
            qDebug() << "Database connection failed.";
        }

}

modif_bonEntre::~modif_bonEntre()
{
    delete ui;
}

void modif_bonEntre::getInfo(QString qttBE)
{

    ui->qttEdit->setText(qttBE);
}

void modif_bonEntre::on_cancelBEbtn_clicked()
{
    this->close();
}

//void modif_bonEntre::on_numProduit_activated(int index)
//{
//    QString itemText = ui->numProduit->currentText();
//    QStringList parts = itemText.split(" - ");
//    if (parts.size() == 2)
//    {
//        recupId = parts[0];
//        // Ajoutez cette ligne pour récupérer la quantité associée à l'ID
//        oldQtEntre = ui->numProduit->itemData(index, Qt::UserRole).toString();
//        QString nomPro = parts[1];
//        int id = recupId.toInt();
//        qDebug() << "ID: " << id;
//        qDebug() << "NumPro: " << recupId;
//        qDebug() << "NomPro: " << nomPro;
//    }
//}

//void modif_bonEntre::on_confirmBEbtn_clicked()
//{
//    Connection m_db;
//    if (!m_db.connOpen())
//    {
//        qDebug() << "Failed to open database";
//    }

//    m_db.connOpen();
//    newQtEntre = ui->qttEdit->text();

//    QDateTime currentDate = QDateTime::currentDateTime();
//    QString formatteDate = currentDate.toString("yyyy-MM-dd HH:mm:ss");

//    qDebug() << "qtt: " << newQtEntre;
//    qDebug() << "date: " << currentDate;
//    qDebug() << "NumPro: " << recupId;

//    if (newQtEntre.isEmpty())
//    {
//        QMessageBox::warning(this, "Attention", "Veuillez remplir les champs vides.");
//    }
//    else
//    {
//        QSqlQuery req;

//        // Modification d'un bon d'entrée existant
//        QString requete = "UPDATE bonEntree SET qtEntre = :qtt, dateBEModifPro = :date WHERE numPro = :recupId;";
//        req.prepare(requete);
//        req.bindValue(":qtt", newQtEntre);
//        req.bindValue(":date", formatteDate);
//        req.bindValue(":recupId", recupId.toInt());



//        if (req.exec())

//        {


//            // Mise à jour du stock dans la table produit
//            QSqlQuery updateQuery;
//            QString updateRequete = "UPDATE produit SET stock = stock - :oldQtEntre + :newQtEntre, dateBEModifPro = :date WHERE numPro = :recupId;";
//            qDebug() << "Requête de mise à jour du stock : " << updateRequete;
//            updateQuery.prepare(updateRequete);
////            updateQuery.bindValue(":oldQtEntre", oldQtEntre.toInt()); // Convert old quantity from QString to int
//            updateQuery.bindValue(":newQtEntre", newQtEntre.toInt());
//            updateQuery.bindValue(":recupId", recupId.toInt());
//            updateQuery.bindValue(":date", formatteDate);

//            if (updateQuery.exec())
//            {
//                QMessageBox::information(this, "Succès", "Le bon d'entrée a été modifié avec succès, et le stock a été mis à jour.");
//            }
//            else
//            {
//                QMessageBox::warning(this, "Erreur", "Le bon d'entrée a été modifié mais la mise à jour du stock est un échec.");
//                qDebug() << "Erreur de mise à jour du stock : " << updateQuery.lastError();
//            }

//        }
//        else
//        {
//            QMessageBox::warning(this, "Erreur", "Échec de la modification du bon d'entrée.");
//            qDebug() << req.lastError();
//        }

//        m_db.connClose();
//        this->close();
//    }

//}



//void modif_bonEntre::on_numProduit_activated(int index)
//{
//    QString itemText = ui->numProduit->currentText();
//    QStringList parts = itemText.split(" - ");
//    if (parts.size() == 2)
//    {
//        recupId = parts[0];
//        // Retrieve the quantity associated with the ID
//        oldQtEntre = ui->numProduit->itemData(index, Qt::UserRole).toString();
//        QString nomPro = parts[1];
//        int id = recupId.toInt();
//        qDebug() << "ID: " << id;
//        qDebug() << "NumPro: " << recupId;
//        qDebug() << "NomPro: " << nomPro;
//    }
//}

//void modif_bonEntre::on_confirmBEbtn_clicked()
//{
//    Connection m_db;
//    if (!m_db.connOpen())
//    {
//        qDebug() << "Failed to open database";
//    }

//    newQtEntre = ui->qttEdit->text();

//    QDateTime currentDate = QDateTime::currentDateTime();
//    QString formatteDate = currentDate.toString("yyyy-MM-dd HH:mm:ss");

//    qDebug() << "qtt: " << newQtEntre;
//    qDebug() << "date: " << currentDate;
//    qDebug() << "NumPro: " << recupId;

//    if (newQtEntre.isEmpty())
//    {
//        QMessageBox::warning(this, "Attention", "Veuillez remplir les champs vides.");
//    }
//    else
//    {
//        QSqlQuery req;
//        QString requete = "UPDATE bonEntree SET qtEntre = :qtt, dateBEModifPro = :date WHERE numPro = :recupId;";
//        req.prepare(requete);
//        req.bindValue(":qtt", newQtEntre);
//        req.bindValue(":date", formatteDate);
//        req.bindValue(":recupId", recupId.toInt());

//        if (req.exec())

//        {
//             QMessageBox::information(this, "Succès", "Le bon d'entrée a été modifié avec succès.");
////            QSqlQuery updateQuery;
////            QString updateRequete = "UPDATE produit SET stock = stock - :oldQtEntre + :newQtEntre, dateBEModifPro = :date WHERE numPro = :recupId;";
////            qDebug() << "Requête de mise à jour du stock : " << updateRequete;
////            updateQuery.prepare(updateRequete);
////            updateQuery.bindValue(":oldQtEntre", oldQtEntre.toInt());
////            updateQuery.bindValue(":newQtEntre", newQtEntre.toInt());
////            updateQuery.bindValue(":recupId", recupId.toInt());
////            updateQuery.bindValue(":date", formatteDate);

////            if (updateQuery.exec())
////            {
////                QMessageBox::information(this, "Succès", "Le bon d'entrée a été modifié avec succès, et le stock a été mis à jour.");
////            }
////            else
////            {
////                QMessageBox::warning(this, "Erreur", "Le bon d'entrée a été modifié mais la mise à jour du stock est un échec.");
////                qDebug() << "Erreur de mise à jour du stock : " << updateQuery.lastError();
////            }

//        }
//        else
//        {
//            QMessageBox::warning(this, "Erreur", "Échec de la modification du bon d'entrée.");
//            qDebug() << req.lastError();
//        }

//        m_db.connClose();
//        this->close();
//    }
//}
void modif_bonEntre::on_numProduit_activated(int index)
{
    QString itemText = ui->numProduit->currentText();
    QStringList parts = itemText.split(" - ");
    if (parts.size() == 2)
    {
        recupId = parts[0];
        // Retrieve the quantity associated with the ID
        oldQtEntre = ui->numProduit->itemData(index, Qt::UserRole).toString();
        QString nomPro = parts[1];
        int id = recupId.toInt();
        qDebug() << "ID: " << id;
        qDebug() << "NumPro: " << recupId;
        qDebug() << "NomPro: " << nomPro;
    }
}

//void modif_bonEntre::on_confirmBEbtn_clicked()
//{
//    Connection m_db;
//    if (!m_db.connOpen())
//    {
//        qDebug() << "Failed to open database";
//    }

//    Entre = ui->qttEdit->text();

//    QDateTime currentDate = QDateTime::currentDateTime();
//    QString formatteDate = currentDate.toString("yyyy-MM-dd HH:mm:ss");

//    qDebug() << "qtt: " << Entre;
//    qDebug() << "date: " << currentDate;
//    qDebug() << "NumPro: " << recupId;

//    if (Entre.isEmpty())
//    {
//        QMessageBox::warning(this, "Attention", "Veuillez remplir les champs vides.");
//    }
//    else
//    {
//        QSqlQuery req;
//        QString requete = "UPDATE bonEntree SET qtEntre = :qtt, dateBEModifPro = :date WHERE numPro = :recupId;";
//        req.prepare(requete);
//        req.bindValue(":qtt", Entre);
//        req.bindValue(":date", formatteDate);
//        req.bindValue(":recupId", recupId.toInt());

//        if (req.exec())
//        {
//            QMessageBox::information(this, "Succès", "Le bon d'entrée a été modifié avec succès.");
//        }
//        else
//        {
//            QMessageBox::warning(this, "Erreur", "Échec de la modification du bon d'entrée.");
//            qDebug() << req.lastError();
//        }

//        m_db.connClose();
//        this->close();
//    }
//}
void modif_bonEntre::on_confirmBEbtn_clicked()
{
    {
        Connection m_db;
        if (!m_db.connOpen())
        {
            qDebug() << "Failed to open database";
        }

        Entre = ui->qttEdit->text();

        QDateTime currentDate = QDateTime::currentDateTime();
        QString formatteDate = currentDate.toString("yyyy-MM-dd HH:mm:ss");

        qDebug() << "qtt: " << Entre;
        qDebug() << "date: " << currentDate;
        qDebug() << "NumPro: " << recupId;

        if (Entre.isEmpty())
        {
            QMessageBox::warning(this, "Attention", "Veuillez remplir les champs vides.");
        }
        else
        {
            QSqlQuery req;
            QString requete = "UPDATE bonEntree SET qtEntre = :qtt, dateBEModifPro = :date WHERE numPro = :recupId;";
            req.prepare(requete);
            req.bindValue(":qtt", Entre);
            req.bindValue(":date", formatteDate);
            req.bindValue(":recupId", recupId.toInt());

            if (req.exec())
            {
                QMessageBox::information(this, "Succès", "Le bon d'entrée a été modifié avec succès.");

            }
            else
            {
                QMessageBox::warning(this, "Erreur", "Échec de la modification du bon d'entrée.");
                qDebug() << req.lastError();
            }

            m_db.connClose();
            this->close();
        }
    }
}


//void updateProductStockForSelectedRow(QString recupId, QString Entre)
//{
//    // Utilisation de QSqlDatabase pour gérer la connexion de manière centralisée
//    QSqlDatabase db = QSqlDatabase::database();  // Utilisez votre instance de base de données appropriée
//    if (!db.isOpen())
//    {
//        qDebug() << "Database connection is not open";
//        return;
//    }

//    QSqlQuery stockQuery(db);

//    // Utilisation de transactions pour garantir l'intégrité de la base de données
//    if (db.transaction())
//    {
//        // Utilisation de requêtes préparées pour éviter les injections SQL
//        stockQuery.prepare("UPDATE produit SET stock = stock + :quantity WHERE id_produit = :productId;");
//        stockQuery.bindValue(":quantity", Entre);
//        stockQuery.bindValue(":productId", recupId);

//        // Exécution de la requête
//        if (stockQuery.exec())
//        {
//            // Validation de la transaction
//            if (db.commit())
//            {
//                qDebug() << "Stock updated successfully for product ID" << recupId;
//                return;  // Sortie de la fonction en cas de succès
//            }
//            else
//            {
//                qDebug() << "Failed to commit transaction";
//            }
//        }
//        else
//        {
//            qDebug() << "Failed to update stock for product ID" << recupId;
//            qDebug() << stockQuery.lastError();
//        }

//        // Annulation de la transaction en cas d'échec
//        db.rollback();
//    }
//    else
//    {
//        qDebug() << "Failed to start transaction";
//    }

//    // Affichage d'un message d'erreur en cas d'échec
//    QMessageBox::critical(nullptr, "Erreur", "Échec de la mise à jour du stock pour le produit sélectionné.");
//}
