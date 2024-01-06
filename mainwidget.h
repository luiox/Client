#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_test_network_btn_clicked();

    void replyFinished(QNetworkReply * reply);
private:
    Ui::MainWidget *ui;
    QNetworkAccessManager * m_networkManager;
};
#endif // MAINWIDGET_H
