#include "mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    networkManager(new QNetworkAccessManager(this)),
    apiKey("3db0125452c6ad65df86f9718dbe8bf7"),
    currentLangCode("uk")
{
    setWindowTitle("Weather Desktop Pro");
    resize(450, 750);
    setMinimumSize(400, 680);

    initTranslations();
    setupUI();
    updateUILanguage();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initTranslations()
{
    // Dictionary mapping UI strings for 4 supported languages
    translations["uk"] = {
        {"placeholder", "Введіть місто..."}, {"search", "Пошук"}, {"geo", "📍 Локація"},
        {"feels_like", "Відчувається як: %1°C"}, {"humidity", "Вологість"},
        {"wind", "Вітер"}, {"pressure", "Тиск"}, {"m_s", "м/с"}, {"hpa", "гПа"},
        {"not_found", "Місто не знайдено!"}
    };
    translations["en"] = {
        {"placeholder", "Enter city..."}, {"search", "Search"}, {"geo", "📍 Location"},
        {"feels_like", "Feels like: %1°C"}, {"humidity", "Humidity"},
        {"wind", "Wind"}, {"pressure", "Pressure"}, {"m_s", "m/s"}, {"hpa", "hPa"},
        {"not_found", "City not found!"}
    };
    translations["it"] = {
        {"placeholder", "Inserisci città..."}, {"search", "Cerca"}, {"geo", "📍 Posizione"},
        {"feels_like", "Percepita: %1°C"}, {"humidity", "Umidità"},
        {"wind", "Vento"}, {"pressure", "Pressione"}, {"m_s", "m/s"}, {"hpa", "hPa"},
        {"not_found", "Città non trovata!"}
    };
    translations["ru"] = {
        {"placeholder", "Введите город..."}, {"search", "Поиск"}, {"geo", "📍 Локация"},
        {"feels_like", "Ощущается как: %1°C"}, {"humidity", "Влажность"},
        {"wind", "Ветер"}, {"pressure", "Давление"}, {"m_s", "м/с"}, {"hpa", "гПа"},
        {"not_found", "Город не найден!"}
    };
}

void MainWindow::setupUI()
{
    // Clean, modern dark blue gradient styling
    this->setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0F172A, stop:0.5 #1E293B, stop:1 #0F172A);
        }
    )");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 15, 20, 20);
    mainLayout->setSpacing(15);

    // Top Bar: Language selector positioned at top right
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->addStretch();

    langCombo = new QComboBox(this);
    langCombo->addItem("🇺🇦 УКР", "uk");
    langCombo->addItem("🇬🇧 ENG", "en");
    langCombo->addItem("🇮🇹 ITA", "it");
    langCombo->addItem("🇷🇺 РУС", "ru");
    langCombo->setStyleSheet(
        "QComboBox { background: rgba(255, 255, 255, 0.12); color: white; border-radius: 10px; padding: 5px 10px; font-weight: bold; border: 1px solid rgba(255, 255, 255, 0.2); }"
        "QComboBox QAbstractItemView { background: #1E293B; color: white; selection-background-color: #334155; }"
        );
    connect(langCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onLanguageChanged);
    topBarLayout->addWidget(langCombo);
    mainLayout->addLayout(topBarLayout);

    // Search bar section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    cityInput = new QLineEdit(this);
    cityInput->setStyleSheet("QLineEdit { background: rgba(255, 255, 255, 0.1); color: white; border: 1px solid rgba(255, 255, 255, 0.2); border-radius: 12px; padding: 10px 15px; font-size: 14px; } QLineEdit:focus { border-color: #38BDF8; }");
    connect(cityInput, &QLineEdit::returnPressed, this, &MainWindow::onSearchClicked);

    searchBtn = new QPushButton(this);
    searchBtn->setStyleSheet("QPushButton { background: #0284C7; color: white; border-radius: 12px; padding: 10px 16px; font-weight: bold; } QPushButton:hover { background: #0369A1; }");
    connect(searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchClicked);

    geoBtn = new QPushButton(this);
    geoBtn->setStyleSheet("QPushButton { background: rgba(255, 255, 255, 0.15); color: white; border-radius: 12px; padding: 10px 12px; border: 1px solid rgba(255, 255, 255, 0.2); } QPushButton:hover { background: rgba(255, 255, 255, 0.25); }");
    connect(geoBtn, &QPushButton::clicked, this, &MainWindow::fetchGeoLocation);

    searchLayout->addWidget(cityInput);
    searchLayout->addWidget(searchBtn);
    searchLayout->addWidget(geoBtn);
    mainLayout->addLayout(searchLayout);

    // Main weather information card
    QFrame *mainCard = new QFrame(this);
    mainCard->setStyleSheet("QFrame { background: rgba(30, 41, 59, 0.7); border-radius: 20px; border: 1px solid rgba(255, 255, 255, 0.15); }");
    QVBoxLayout *cardLayout = new QVBoxLayout(mainCard);
    cardLayout->setContentsMargins(20, 20, 20, 20);
    cardLayout->setAlignment(Qt::AlignCenter);

    cityNameLabel = new QLabel("-", this);
    cityNameLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    cityNameLabel->setAlignment(Qt::AlignCenter);

    tempLabel = new QLabel("--°C", this);
    tempLabel->setStyleSheet("font-size: 52px; font-weight: 300; color: white;");
    tempLabel->setAlignment(Qt::AlignCenter);

    conditionLabel = new QLabel("-", this);
    conditionLabel->setStyleSheet("font-size: 16px; font-weight: 500; color: #94A3B8; text-transform: capitalize;");
    conditionLabel->setAlignment(Qt::AlignCenter);

    feelsLikeLabel = new QLabel("-", this);
    feelsLikeLabel->setStyleSheet("font-size: 14px; color: #CBD5E1;");
    feelsLikeLabel->setAlignment(Qt::AlignCenter);

    detailsLabel = new QLabel("-", this);
    detailsLabel->setStyleSheet("font-size: 13px; color: #94A3B8; margin-top: 8px;");
    detailsLabel->setAlignment(Qt::AlignCenter);

    cardLayout->addWidget(cityNameLabel);
    cardLayout->addWidget(tempLabel);
    cardLayout->addWidget(conditionLabel);
    cardLayout->addWidget(feelsLikeLabel);
    cardLayout->addWidget(detailsLabel);
    mainLayout->addWidget(mainCard);

    // Scrollable 5-day weather forecast list
    forecastScrollArea = new QScrollArea(this);
    forecastScrollArea->setWidgetResizable(true);
    forecastScrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");

    forecastContainer = new QWidget();
    forecastContainer->setStyleSheet("background: transparent;");
    forecastLayout = new QVBoxLayout(forecastContainer);
    forecastLayout->setContentsMargins(0, 0, 0, 0);
    forecastLayout->setSpacing(10);

    forecastScrollArea->setWidget(forecastContainer);
    mainLayout->addWidget(forecastScrollArea);
}

void MainWindow::updateUILanguage()
{
    auto langMap = translations[currentLangCode];
    cityInput->setPlaceholderText(langMap["placeholder"]);
    searchBtn->setText(langMap["search"]);
    geoBtn->setText(langMap["geo"]);

    if (!currentCity.isEmpty()) {
        fetchWeatherData(currentCity);
    }
}

void MainWindow::onLanguageChanged(int index)
{
    currentLangCode = langCombo->itemData(index).toString();
    updateUILanguage();
}

void MainWindow::onSearchClicked()
{
    QString city = cityInput->text().trimmed();
    if (!city.isEmpty()) {
        fetchWeatherData(city);
    }
}

void MainWindow::fetchGeoLocation()
{
    // Fetch current user location via HTTP IP-Geolocation API
    QUrl geoUrl("http://ip-api.com/json/");
    QNetworkReply *reply = networkManager->get(QNetworkRequest(geoUrl));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onGeoLocationReply(reply);
    });
}

void MainWindow::onGeoLocationReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QString city = doc.object()["city"].toString();
        if (!city.isEmpty()) {
            cityInput->setText(city);
            fetchWeatherData(city);
        }
    }
    reply->deleteLater();
}

void MainWindow::fetchWeatherData(const QString &cityName)
{
    currentCity = cityName;

    // Fetch current weather conditions
    QString currentUrl = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric&lang=%3")
                             .arg(cityName, apiKey, currentLangCode);
    QNetworkReply *currentReply = networkManager->get(QNetworkRequest(QUrl(currentUrl)));
    connect(currentReply, &QNetworkReply::finished, this, [this, currentReply]() {
        onCurrentWeatherReply(currentReply);
    });

    // Fetch 5-day weather forecast
    QString forecastUrl = QString("http://api.openweathermap.org/data/2.5/forecast?q=%1&appid=%2&units=metric&lang=%3")
                              .arg(cityName, apiKey, currentLangCode);
    QNetworkReply *forecastReply = networkManager->get(QNetworkRequest(QUrl(forecastUrl)));
    connect(forecastReply, &QNetworkReply::finished, this, [this, forecastReply]() {
        onForecastReply(forecastReply);
    });
}

void MainWindow::onCurrentWeatherReply(QNetworkReply *reply)
{
    auto langMap = translations[currentLangCode];
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (statusCode == 404) {
        QMessageBox::critical(this, "Error", langMap["not_found"]);
        reply->deleteLater();
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        QJsonObject mainObj = jsonObj["main"].toObject();
        QJsonObject windObj = jsonObj["wind"].toObject();
        QJsonObject weatherObj = jsonObj["weather"].toArray()[0].toObject();

        double temp = mainObj["temp"].toDouble();
        double feelsLike = mainObj["feels_like"].toDouble();
        int humidity = mainObj["humidity"].toInt();
        int pressure = mainObj["pressure"].toInt();
        double windSpeed = windObj["speed"].toDouble();

        cityNameLabel->setText(jsonObj["name"].toString());
        cityInput->setText(jsonObj["name"].toString());
        tempLabel->setText(QString("%1°C").arg(QString::number(temp, 'f', 1)));
        conditionLabel->setText(weatherObj["description"].toString());
        feelsLikeLabel->setText(langMap["feels_like"].arg(QString::number(feelsLike, 'f', 1)));

        detailsLabel->setText(QString("%1: %2%  |  %3: %4 %5  |  %6: %7 %8")
                                  .arg(langMap["humidity"], QString::number(humidity),
                                       langMap["wind"], QString::number(windSpeed, 'f', 1), langMap["m_s"],
                                       langMap["pressure"], QString::number(pressure), langMap["hpa"]));
    }
    reply->deleteLater();
}

void MainWindow::onForecastReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        renderForecastList(doc);
    }
    reply->deleteLater();
}

void MainWindow::renderForecastList(const QJsonDocument &jsonDoc)
{
    // Clear existing forecast cards from layout
    QLayoutItem *child;
    while ((child = forecastLayout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }

    QJsonArray listArray = jsonDoc.object()["list"].toArray();
    for (const QJsonValue &val : listArray) {
        QJsonObject obj = val.toObject();
        QString dtTxt = obj["dt_txt"].toString();

        // Filter daily data at 12:00 PM
        if (dtTxt.contains("12:00:00")) {
            QString dateStr = dtTxt.split(" ")[0];
            double temp = obj["main"].toObject()["temp"].toDouble();
            QString desc = obj["weather"].toArray()[0].toObject()["description"].toString();

            QFrame *itemCard = new QFrame(this);
            itemCard->setStyleSheet("QFrame { background: rgba(30, 41, 59, 0.6); border-radius: 12px; border: 1px solid rgba(255, 255, 255, 0.1); }");
            QHBoxLayout *itemLayout = new QHBoxLayout(itemCard);
            itemLayout->setContentsMargins(15, 12, 15, 12);

            QLabel *dateLbl = new QLabel(dateStr, this);
            dateLbl->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

            QLabel *descLbl = new QLabel(desc, this);
            descLbl->setStyleSheet("color: #CBD5E1; font-size: 13px; text-transform: capitalize;");

            QLabel *tempLbl = new QLabel(QString("%1°C").arg(QString::number(temp, 'f', 1)), this);
            tempLbl->setStyleSheet("color: white; font-weight: bold; font-size: 16px;");

            itemLayout->addWidget(dateLbl);
            itemLayout->addWidget(descLbl, 1);
            itemLayout->addWidget(tempLbl);

            forecastLayout->addWidget(itemCard);
        }
    }
}
