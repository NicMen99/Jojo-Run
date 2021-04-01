//
// Created by Niccolo on 01/04/2021.
//

#include "gtest/gtest.h"
#include "Game.h"
#include "Widgets/Widget.h"

class TestSubject : public Subject{
public:
    Observer * m_observer;
    std::string m_item_name;

    void subscribe(Observer *observer, const std::string &item_name) override{
        m_observer = observer;
        m_item_name = item_name;
    }

    void unsubscribe(Observer *observer, const std::string &item_name) override{
        if(m_observer == observer)
            m_observer = nullptr;
        if(m_item_name == item_name)
            m_item_name = "";
    }

    void notify(const std::string &item_value) override{
        m_observer->data_update(m_item_name, item_value);
    }

};

class TestWidget : public Widget {
    sf::Vector2f m_parent_position;
    std::string m_item_name;
    std::string m_item_value;
public:
    explicit TestWidget(std::string name) : Widget(std::move(name)){}
    sf::Vector2f getOffset() { return m_parent_position; }
    std::string getItemName() { return m_item_name; }
    std::string getItemValue() { return m_item_value; }
    void _render(sf::RenderWindow &window, const sf::Vector2f &parent_position) override {
        m_parent_position = parent_position;
    }

    void data_update(const std::string &item_name, const std::string &item_value) override {
        m_item_name = item_name;
        m_item_value = item_value;
    }
};

class WidgetTest : public ::testing::Test{
public:
    sf::RenderWindow window;
};

TEST_F(WidgetTest, EmptyWidget){
    auto widget = std::unique_ptr<Widget>(new Widget("TEST"));
    ASSERT_EQ(widget->findObjectByName("TEST"), widget.get());
}

TEST_F(WidgetTest, AddWidget){
    auto widget = std::unique_ptr<Widget>(new Widget("TEST"));
    auto child_widget = new Widget("TEST_CHILD");
    widget->add(child_widget);
    ASSERT_EQ(widget->findObjectByName("TEST_CHILD"), child_widget);
}

TEST_F(WidgetTest, WidgetPosition){
    auto widget = std::unique_ptr<TestWidget>(new TestWidget("TEST"));
    widget->setPosition(sf::Vector2f(10,10));
    auto widget_2 = new TestWidget("TEST_2");
    widget->add(widget_2);
    widget_2->setPosition(sf::Vector2f(10,10));
    widget_2->render(window);
    auto widget_3 = new TestWidget("TEST_3");
    widget_2->add(widget_3);
    widget_3->setPosition(sf::Vector2f(10,10));
    widget->render(window);
    ASSERT_EQ(widget->getOffset(), sf::Vector2f(10,10));
    ASSERT_EQ(widget_2->getOffset(), sf::Vector2f(20,20));
    ASSERT_EQ(widget_3->getOffset(), sf::Vector2f(30,30));
}

TEST_F(WidgetTest, TestObserver){
    auto widget = std::unique_ptr<TestWidget>(new TestWidget("TEST"));
    auto subject = std::unique_ptr<TestSubject>(new TestSubject);
    auto subject2 = std::unique_ptr<TestSubject>(new TestSubject);
    widget->observe(subject.get(), "TEST_ITEM");
    ASSERT_EQ(subject->m_item_name, "TEST_ITEM");
    ASSERT_EQ(subject->m_observer, widget.get());
    subject->notify("TEST_VALUE");
    ASSERT_EQ(widget->getItemName(), "TEST_ITEM");
    ASSERT_EQ(widget->getItemValue(), "TEST_VALUE");
    widget->observe(subject2.get(), "TEST_ITEM");
    ASSERT_EQ(subject->m_item_name, "");
    ASSERT_EQ(subject->m_observer, nullptr);
}