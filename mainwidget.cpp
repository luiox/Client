#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("短波红外相机上位机");
    m_networkManager = new QNetworkAccessManager;
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_networkManager;
}


void MainWidget::on_test_network_btn_clicked()
{
    QUrl url("http://121.40.191.121:8080/test");
    QNetworkRequest request;
    request.setUrl(url);
    QObject::connect(m_networkManager,
                     &QNetworkAccessManager::finished,
                     this,
                     &MainWidget::replyFinished);
    auto reply = m_networkManager->get(request);
}

void MainWidget::replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // 读取响应数据
        QByteArray data = reply->readAll();

        // 解析 JSON 数据
        QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonResponse.object();

        QString result = jsonObject["result"].toString();

        QMessageBox::information(this,"提示","\"result\" : "+result);

    } else {
        // 处理错误
        qDebug() << "Error:" << reply->errorString();
    }
}

