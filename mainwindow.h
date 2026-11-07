#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFrame>
#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchClicked();
    void onLanguageChanged(int index);
    void fetchGeoLocation();
    void onCurrentWeatherReply(QNetworkReply *reply);
    void onForecastReply(QNetworkReply *reply);
    void onGeoLocationReply(QNetworkReply *reply);

private:
    void setupUI();
    void initTranslations();
    void updateUILanguage();
    void fetchWeatherData(const QString &cityName);
    void renderForecastList(const QJsonDocument &jsonDoc);

    QNetworkAccessManager *networkManager;

    QString apiKey;
    QString currentCity;
    QString currentLangCode;

    // UI Elements
    QComboBox *langCombo;
    QLineEdit *cityInput;
    QPushButton *searchBtn;
    QPushButton *geoBtn;

    QLabel *cityNameLabel;
    QLabel *tempLabel;
    QLabel *feelsLikeLabel;
    QLabel *conditionLabel;
    QLabel *detailsLabel;

    QScrollArea *forecastScrollArea;
    QWidget *forecastContainer;
    QVBoxLayout *forecastLayout;

    // Multi-language UI translation map (UKR, ENG, ITA, RU)
    QMap<QString, QMap<QString, QString>> translations;
};

#endif // MAINWINDOW_H
