#ifndef NUOVOFILEWIDGET_H
#define NUOVOFILEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QSpinBox>
#include <QIcon>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QStackedLayout>

class NuovoFileWidget: public QWidget {
private:
    QVBoxLayout* layout;
    QFormLayout* formLayout;
    QHBoxLayout* buttonLayout;
    QLineEdit* nome;
    QLineEdit* estensione;
    QLineEdit* descrizione;
    QSpinBox* dimensione;
    QCalendarWidget* dataCreazione;
    QComboBox* tipo;
    QPushButton* aggiungi;
    QPushButton* annulla;

    QFormLayout* layoutArchivio;
    QFormLayout* layoutTesto;
    QFormLayout* layoutAudio;
    QFormLayout* layoutImmagine;
    QFormLayout* layoutVideo;

    QStackedLayout* layoutInfo;

    // Archivio
    QSpinBox* dimensioneOriginale;
    QSpinBox* numeroDiFile;
    QCheckBox* protetto;

    // Testo
    QSpinBox* numeroCaratteri;
    QSpinBox* numeroParole;

    // Immagine
    QButtonGroup* compressioneI;
    QRadioButton* nessunaI;
    QRadioButton* losslessI;
    QRadioButton* lossyI;
    QButtonGroup* tipoImmagine;
    QRadioButton* raster;
    QRadioButton* vettoriale;
    QSpinBox* altezzaI;
    QSpinBox* larghezzaI;

    // Video
    QButtonGroup* compressioneV;
    QRadioButton* nessunaV;
    QRadioButton* losslessV;
    QRadioButton* lossyV;
    QLineEdit* codec;
    QSpinBox* durataV;
    QSpinBox* fps;
    QSpinBox* altezzaV;
    QSpinBox* larghezzaV;

    // Audio
    QButtonGroup* compressioneA;
    QRadioButton* nessunaA;
    QRadioButton* losslessA;
    QRadioButton* lossyA;
    QSpinBox* bitrate;
    QSpinBox* durataA;

    void resetForm();

public:
    NuovoFileWidget(QWidget *parent = nullptr);
};

#endif // NUOVOFILEWIDGET_H
