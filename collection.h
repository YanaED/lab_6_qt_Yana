#pragma once
#include <QtWidgets/QMainWindow>
#include <vector>
#include <QVBoxLayout> //��� ����� � ������ QtGui, ������� ����������� ������� � ������������ �����.
#include <QLabel>
#include <QSlider> //��� ������, ������� ������������� ������������ ��� �������������� ��������.
#include <QScrollBar> //��� ����� � ���������� Qt, �������������� ������ ���������, ������� ������������ ��� ��������� ����������� �������� Qt
#include <QSpinBox> //��������� ������������ ������� �������� ������ ����� �� ������� �����/���� 
                    //��� ������� ������� ���������� �����/���� ��� ����������/���������� ��������, ������������� � ��������� ������.
#include<QPushButton> //� ������� QPushButton ����� ��������� ������ � ������������ ��
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

