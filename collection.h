#pragma once
#include <QtWidgets/QMainWindow>
#include <vector>
#include <QVBoxLayout> //это класс в модуле QtGui, который выстраивает виджеты в вертикальную линию.
#include <QLabel>
#include <QSlider> //это виджет, который предоставляет вертикальный или горизонтальный ползунок.
#include <QScrollBar> //это класс в библиотеке Qt, представляющий полосу прокрутки, которая используется для прокрутки содержимого виджетов Qt
#include <QSpinBox> //позволяет пользователю указать значение щелкая мышью по кнопкам вверх/вниз 
                    //или нажимая клавиши клавиатуры вверх/вниз для увеличения/уменьшения значения, отображенного в настоящий момент.
#include<QPushButton> //С помощью QPushButton можно создавать кнопки и обрабатывать их
#include <ctime>

class Collection : public QWidget
{
    Q_OBJECT
public:
    Collection(QWidget* parent = nullptr);
    ~Collection();
    void add_widget(QWidget* wid);
    void remove_widget(int num);
signals:
    void value_changed(int val);
    void text_changed(const QString& str);
private slots:
    void click_slot();
    void get_signal(int value);
private:
    QVBoxLayout* layout;
    QPushButton* add_button;
    QPushButton* delete_button;
    std::vector<QWidget*> widgets_collection;
    void connect_widget(QWidget* wid);
    void disconnect_widget(int ind);
    int data;
};

